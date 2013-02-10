library(tcltk)

mywait <- function() {
    tt <- tktoplevel()
    tkpack( tkbutton(tt, text='Continue', command=function()tkdestroy(tt)),
        side='bottom')
    tkbind(tt,'<Key>', function()tkdestroy(tt) )

    tkwait.window(tt)
}

library(RSQLite)
driver = dbDriver("SQLite")
con <- dbConnect(driver,dbname="test-real.db")
dbListTables(con) # show tables
#using mathews corelation coeficient
#rs <- dbSendQuery(con, "select distinct (tp/(tp+fn)) as sensitivity,(tn/(fp+tn)) as specificity,(tp+tn) as evaluated from precomputed;")  # send a query
#rs <- dbSendQuery(con, ".load libsqlitefunctions.so")  # send a query
#rs <- dbSendQuery(con, "select distinct (tp+tn)/(tp+tn+fp+fn) as accuracy,(tp / (tp+fp)) as precision,  (tp+tn+fp+fn) as evr  from precomputed")  # send a query
#rs <- dbSendQuery(con, "select distinct (tp+tn)/(tp+tn+fp+fn) as accuracy,(tp / (tp+fp)) as precision  from precomputed")  # send a query
#rs <- dbSendQuery(con, "select distinct tp/(tp+fn) as sensitivity,(tn / (tn+fp)) as specificity from precomputed")  # send a query
#rs <- dbSendQuery(con, "select distinct (tp+tn)/(tp+tn+fp+fn) as accuracy,(tp / (tp+fp)) as precision,(bufferSize*16+maxMonitorNodes*8) as memory,(tp+tn+fp+fn) as scope  from precomputed")
#rs <- dbSendQuery(con, "select distinct (tp+tn)/(tp+tn+fp+fn) as accuracy,(tp+tn+fp+fn) as scope  from precomputed")

#rs <- dbSendQuery(con, "select  accuracy as a1,memory as m1,scope as s1 from accmemsc  where (m1 < 100) and (not exists (select accuracy as a2,memory as m2, scope as s2 from accmemsc where (a2>a1 and m2<=m1 and s2>=s1) or (a2>=a1 and m2<m1 and s2>=s1) or (a2>=a1 and m2<=m1 and s2>s1)))")

rs <- dbSendQuery(con, "select  accuracy as a1,memory as m1,scope as s1 from accmemsc")


data <- fetch(rs,n=-1) # fetch 3 rows from result (use -1 to fetch all rows)
#columns <- c("sensitivity","specificity","evaluated")
memory <- data$m1
accuracy <- data$a1
scope <- data$s1
#precision <- data$precision

#z <- data$evaluated

library(rgl)
png("mem-scope.png")
plot(memory,scope)
png("acc-scope.png")
plot(accuracy,scope)
png("acc-mem.png")
plot(accuracy,memory)
library(scatterplot3d)
png("acc-mem-scope.png")
scatterplot3d(memory,accuracy,scope,highlight.3d = T, angle = 75, scale.y = .5)
plot3d(accuracy,memory,scope)
#png("acc-all.png")
#plot(sensitivity,evr)
#png("pr-mem.png")
#plot(specificity,evr)
dev.off()

mywait()
#cleanup
dbClearResult(rs)
dbDisconnect(con)
dbUnloadDriver(driver)
