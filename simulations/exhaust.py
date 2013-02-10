# -*- coding: utf-8 -*-
import os, shutil, errno,math,re,sqlite3,csv,cProfile
import logging
logging.basicConfig(filename='evolve.log',level=logging.DEBUG)

exp_folder = "/home/asaleh/Diplomka/moeo_wsn/WSN/simulations/"
binary_folder = "/home/asaleh/Diplomka/moeo_wsn/WSN/simulations/BMacTest_small/"
template = "/home/asaleh/Diplomka/moeo_wsn/WSN/simulations/default_indi.ini"

def initTemplate(templatePath,templateOut,dictValues):
        template = open(templatePath)
	text = template.read()
	for key, value in dictValues.iteritems():
	        text=text.replace(key,value)
        target = open(templateOut, 'w')
	target.write(text)

def dict_to_string(val_dict):
  s = ""
  for k,v in val_dict.items():
    s+="_" + str(k) + "-" +str(v)  
  return s

def run_search(val_dict):
  dir_name =exp_folder + "BMacTest_small"+ dict_to_string(val_dict) +"/"
  dexperiment = os.path.dirname( dir_name)
  dbinary = os.path.dirname(binary_folder)
  if os.path.exists(dexperiment):
    return;
  shutil.copytree(dbinary,dexperiment)
  initTemplate(template,dir_name+"/default_indi.ini",val_dict)
  os.system("cd "+dir_name+";./BMacTest -r 0 -u Cmdenv -n \"../../src;/home/asaleh/Diplomka/MiXiM/src\" -l \"/home/asaleh/Diplomka/MiXiM/src/base/miximbase\" -l \"/home/asaleh/Diplomka/MiXiM/src/modules/miximmodules\" -l \"../../src/WSN\" omnetpp.ini default_indi.ini") 

def getResults(pathToScalar):
        f = open(pathToScalar)
	text = f.read()
	lines = text.split("\n")
	flter = "BasicIDS.node"
	dictSumAns = {
	  "forwarders_falseNegatives":0.0,
          "forwarders_falsePositives":0.0,
          "forwarders_trueNegatives":0.0,
	  "forwarders_truePositives":0.0,
	  "Mean power consumption":0.0
	}
	for line in lines:
		if flter in line:
			for key in dictSumAns.keys():
				if key in line:
					out = float(line.split()[-1])
					dictSumAns[key]=dictSumAns[key]+out
	return dictSumAns

def add_raw_data(raw_data,node,neighbour,recieved_forwarded_treshold):
  if node in raw_data:
    if neighbour in raw_data[node]:
      return raw_data[node][neighbour].update(recieved_forwarded_treshold)
    else:
      raw_data[node].update({neighbour:{}})
      return add_raw_data(raw_data,node,neighbour,recieved_forwarded_treshold)
  else:
    raw_data.update({node:{}})
    return add_raw_data(raw_data,node,neighbour,recieved_forwarded_treshold)

def data_node_complete(raw_data,node,neighbour):
  return (node in raw_data) and (neighbour in raw_data[node]) and ("recieved" in raw_data[node][neighbour]) and ("forwarded" in raw_data[node][neighbour]) and ("treshold" in raw_data[node][neighbour])

def inc_db(db,what,bufferSize,maxMonitorNodes,treshold,min_packets):
  cur = db.cursor()
  query0 = "Select {0} from precomputed where bufferSize = ? and maxMonitorNodes = ? and treshold = ? and minPackets = ?".format(what)
  cur.execute(query0,(bufferSize,maxMonitorNodes,treshold,min_packets))
  result = cur.fetchall()
  new = result[0][0] + 1
  query1 = "Update precomputed set {0} = {1} where bufferSize = ? and maxMonitorNodes = ? and treshold = ? and minPackets = ?".format(what,new)
  cur.execute(query1,(bufferSize,maxMonitorNodes,treshold,min_packets))

def prepare(db):
  cur = db.cursor()
  cur.execute('PRAGMA journal_mode = OFF')
  cur.execute('CREATE TABLE IF NOT EXISTS precomputed (bufferSize REAL,maxMonitorNodes REAL,treshold REAL,minPackets REAL, tp REAL,tn REAL, fp REAL,fn REAL)')
  cur.execute('CREATE INDEX IF NOT EXISTS fastsearch on precomputed (bufferSize,maxMonitorNodes,treshold,minPackets)')
  
  db.commit()
  for val_dict in [{"{{fwdBufferSize}}": str(bfs), 
                    "{{maxMonitorNodes}}":str(mmn)} for bfs in range(1,101)  for mmn in range(1,6)]:
      pathToScalar =exp_folder + "BMacTest_small"+ dict_to_string(val_dict) +"/results/Test3-0.sca"
      print pathToScalar 
      bufferSize = val_dict["{{fwdBufferSize}}"]
      maxMonitorNodes = val_dict["{{maxMonitorNodes}}"]
      for rest in [{"treshold": (float(tr)/100), 
			 "packets": pckts} for tr in range(1,100) for pckts in range (1,100)]:
	      treshold = rest["treshold"]
	      min_packets = rest["packets"]
	      cur.execute('INSERT OR IGNORE INTO precomputed (bufferSize,maxMonitorNodes,treshold,minPackets,tp,tn,fp,fn) VALUES (?,?,?,?,?,?,?,?)',(bufferSize,maxMonitorNodes,treshold,min_packets,0,0,0,0))
  db.commit()

def gather():
  db = sqlite3.connect("test-real.db")
  cur = db.cursor()

  cur.execute('PRAGMA journal_mode = OFF')
  cur.execute('PRAGMA cache_size = -600')

  prepare(db)

  for val_dict in [{"{{fwdBufferSize}}": str(bfs), 
                    "{{maxMonitorNodes}}":str(mmn)} for bfs in range(1,101)  for mmn in range(1,6)]:
      db.commit()
      pathToScalar =exp_folder + "BMacTest_small"+ dict_to_string(val_dict) +"/results/Test3-0.sca"
      print pathToScalar 
      bufferSize = val_dict["{{fwdBufferSize}}"]
      maxMonitorNodes = val_dict["{{maxMonitorNodes}}"]
      f = open(pathToScalar)
      text = f.read()
      f.close()
      lines = text.split("\n")
      snode = "BMacTest.node"
      sneighbour = "neighbour"
      raw_data = {}
      lnum = 0;
      for line in lines:
	if (snode in line) and (sneighbour in line):
          values = re.findall(r'\d+',line)
	  node = float(values[0])
	  neighbour = float(values[1])
	  if "PacketsReceived" in line:
	    add_raw_data(raw_data,node,neighbour,{"recieved":float(values[2])})
	  elif "PacketsForwarded" in line:
	    add_raw_data(raw_data,node,neighbour,{"forwarded":float(values[2])})
	  elif "IntentionalPacketDropping" in line:
	    if len(values) > 3:
	      add_raw_data(raw_data,node,neighbour,{"treshold":float(values[2]+'.'+values[3])})	  
	    else:
	      add_raw_data(raw_data,node,neighbour,{"treshold":float(values[2])})
	  if data_node_complete(raw_data,node,neighbour):
	    for rest in [{"treshold": (float(tr)/100), 
			 "packets": pckts} for tr in range(1,100) for pckts in range (1,100)]:
	      treshold = rest["treshold"]
	      min_packets = rest["packets"]
	      if raw_data[node][neighbour]["recieved"] > rest["packets"]:

                is_badguy = raw_data[node][neighbour]["treshold"]>0.4
                thinks_is_badguy =False
		if (raw_data[node][neighbour]["forwarded"]/raw_data[node][neighbour]["recieved"]) < rest["treshold"]:
		  thinks_is_badguy = True
		if is_badguy and thinks_is_badguy:
		  inc_db(db,"tp",bufferSize,maxMonitorNodes,treshold,min_packets)
		if is_badguy and not thinks_is_badguy:
		  inc_db(db,"fp",bufferSize,maxMonitorNodes,treshold,min_packets)
		if not is_badguy and  thinks_is_badguy:
		  inc_db(db,"fn",bufferSize,maxMonitorNodes,treshold,min_packets)
		if not is_badguy and not thinks_is_badguy:
		  inc_db(db,"tn",bufferSize,maxMonitorNodes,treshold,min_packets)
  db.commit()
def exhaust1():
  for i in [{"{{fwdBufferSize}}": str(bfs),
               "{{maxMonitorNodes}}":str(mmn)
               } for bfs in range(50,101) for mmn in range(1,6)]:
    run_search(i)

def exhaust2():
  for i in [{"{{fwdBufferSize}}": str(bfs),
               "{{maxMonitorNodes}}":str(mmn)
               } for bfs in range(1,50) for mmn in range(1,6)]:
    run_search(i)

def exhaust3():
  for i in [{"{{fwdBufferSize}}": str(bfs),
               "{{maxMonitorNodes}}":str(mmn)
               } for bfs in range(50,101) for mmn in range(5,11)]:
    run_search(i)

def exhaust4():
  for i in [{"{{fwdBufferSize}}": str(bfs),
               "{{maxMonitorNodes}}":str(mmn)
               } for bfs in range(1,50) for mmn in range(5,11)]:
    run_search(i)
