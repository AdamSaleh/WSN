#
# OMNeT++/OMNEST Makefile for Policemen
#
# This file was generated with the command:
#  opp_makemake -f --deep -o Policemen -O out -Xout -Xresults -I/home/asaleh/Install/omnetpp-4.2.1/src/envir -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep -I/home/asaleh/Diplomka/MiXiM/src/base/modules -I/home/asaleh/Diplomka/MiXiM/src/modules/utility -I/home/asaleh/Diplomka/MiXiM/src/base/utils -I/home/asaleh/Diplomka/MiXiM/src/modules/phy -I/home/asaleh/Diplomka/MiXiM/src/base/phyLayer -I/home/asaleh/Diplomka/MiXiM/src/modules/analogueModel -I/home/asaleh/Diplomka/MiXiM/src/modules/messages -I/home/asaleh/Diplomka/MiXiM/src/modules/mac -I/home/asaleh/Diplomka/MiXiM/src/base/connectionManager -I/home/asaleh/Diplomka/MiXiM/src/base/messages -I../../src/ids -I../../src/netw -I/home/asaleh/Diplomka/MiXiM/src/modules/netw -I../../src/messages -I../../src/mobility -I../../src/utility -I/home/asaleh/Diplomka/MiXiM/src/modules/mobility -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules -L../../out/gcc-debug/src -lmiximbase -lmiximmodules -KMIXIM_PROJ=/home/asaleh/Diplomka/MiXiM
#

# Name of target to be created (-o option)
TARGET = Policemen$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I/home/asaleh/Install/omnetpp-4.2.1/src/envir \
    -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep \
    -I/home/asaleh/Diplomka/MiXiM/src/base/modules \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/utility \
    -I/home/asaleh/Diplomka/MiXiM/src/base/utils \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/phy \
    -I/home/asaleh/Diplomka/MiXiM/src/base/phyLayer \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/analogueModel \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/messages \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/mac \
    -I/home/asaleh/Diplomka/MiXiM/src/base/connectionManager \
    -I/home/asaleh/Diplomka/MiXiM/src/base/messages \
    -I../../src/ids \
    -I../../src/netw \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/netw \
    -I../../src/messages \
    -I../../src/mobility \
    -I../../src/utility \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/mobility \
    -I. \
    -Iapplication \
    -Imac \
    -Imessages \
    -Imobility \
    -Inic \
    -Inode \
    -Isensors \
    -Iutility

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules -L../../out/gcc-debug/src  -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath /home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base` -Wl,-rpath,`abspath /home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules` -Wl,-rpath,`abspath ../../out/gcc-debug/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/application/PolicemenApplLayer.o \
    $O/mac/PolicemenBMacLayer.o \
    $O/mobility/AttackerMobility.o \
    $O/mobility/PolicemanMobility.o \
    $O/sensors/BaseSensor.o \
    $O/sensors/MotionSensor.o \
    $O/utility/SimHelper.o \
    $O/messages/DataPkt_m.o

# Message files
MSGFILES = \
    messages/DataPkt.msg

# Other makefile variables (-K)
MIXIM_PROJ=/home/asaleh/Diplomka/MiXiM

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f Policemen Policemen.exe libPolicemen.so libPolicemen.a libPolicemen.dll libPolicemen.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f application/*_m.cc application/*_m.h
	-rm -f mac/*_m.cc mac/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f mobility/*_m.cc mobility/*_m.h
	-rm -f nic/*_m.cc nic/*_m.h
	-rm -f node/*_m.cc node/*_m.h
	-rm -f sensors/*_m.cc sensors/*_m.h
	-rm -f utility/*_m.cc utility/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc application/*.cc mac/*.cc messages/*.cc mobility/*.cc nic/*.cc node/*.cc sensors/*.cc utility/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/application/PolicemenApplLayer.o: application/PolicemenApplLayer.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  mac/PolicemenBMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/NetwControlInfo.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  messages/DataPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/Packet.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  sensors/MotionSensor.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/AddressingInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  application/PolicemenApplLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  sensors/BaseSensor.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/mac/PolicemenBMacLayer.o: mac/PolicemenBMacLayer.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/ChannelState.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  mac/PolicemenBMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  messages/DataPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Mapping.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MacToPhyInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Signal_.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/AnalogueModel.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/MacPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingUtils.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/PhyUtils.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/mobility/AttackerMobility.o: mobility/AttackerMobility.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  mobility/AttackerMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/mobility/PolicemanMobility.o: mobility/PolicemanMobility.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mobility/ConstSpeedMobility.h \
  mobility/PolicemanMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/sensors/BaseSensor.o: sensors/BaseSensor.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/Packet.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  application/PolicemenApplLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h \
  sensors/BaseSensor.h
$O/sensors/MotionSensor.o: sensors/MotionSensor.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/Packet.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  sensors/MotionSensor.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  application/PolicemenApplLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  sensors/BaseSensor.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/utility/SimHelper.o: utility/SimHelper.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  mac/PolicemenBMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/netw/WiseRoute.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/Packet.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  application/PolicemenApplLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  utility/SimHelper.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
