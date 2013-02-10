#
# OMNeT++/OMNEST Makefile for libWSN
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -O out -I/home/asaleh/Install/omnetpp-4.2.1/src/envir -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep -I/home/asaleh/Diplomka/MiXiM/src/base/modules -I/home/asaleh/Diplomka/MiXiM/src/base/phyLayer -I/home/asaleh/Diplomka/MiXiM/src/modules/analogueModel -I/home/asaleh/Diplomka/MiXiM/src/modules/messages -I/home/asaleh/Diplomka/MiXiM/src/base/connectionManager -I/home/asaleh/Diplomka/MiXiM/src/modules/utility -I/home/asaleh/Diplomka/MiXiM/src/base/messages -I/home/asaleh/Diplomka/MiXiM/src/base/utils -I/home/asaleh/Diplomka/MiXiM/src/modules/phy -I../simulations/Policemen/sensors -I../simulations/Policemen/application -I/home/asaleh/Diplomka/MiXiM/src/modules/netw -I../simulations/Policemen/utility -I../simulations/Policemen/messages -I../simulations/Policemen/mac -I/home/asaleh/Diplomka/MiXiM/src/modules/mac -I/home/asaleh/Diplomka/MiXiM/src/modules/application -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules -lmiximbase -lmiximmodules -KMIXIM_PROJ=/home/asaleh/Diplomka/MiXiM
#

# Name of target to be created (-o option)
TARGET = libWSN$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I/home/asaleh/Install/omnetpp-4.2.1/src/envir \
    -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep \
    -I/home/asaleh/Diplomka/MiXiM/src/base/modules \
    -I/home/asaleh/Diplomka/MiXiM/src/base/phyLayer \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/analogueModel \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/messages \
    -I/home/asaleh/Diplomka/MiXiM/src/base/connectionManager \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/utility \
    -I/home/asaleh/Diplomka/MiXiM/src/base/messages \
    -I/home/asaleh/Diplomka/MiXiM/src/base/utils \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/phy \
    -I../simulations/Policemen/sensors \
    -I../simulations/Policemen/application \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/netw \
    -I../simulations/Policemen/utility \
    -I../simulations/Policemen/messages \
    -I../simulations/Policemen/mac \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/mac \
    -I/home/asaleh/Diplomka/MiXiM/src/modules/application \
    -I. \
    -Iapplication \
    -Iids \
    -Imac \
    -Imessages \
    -Imobility \
    -Inetw \
    -Inetworks \
    -Inic \
    -Inode \
    -Iphy \
    -Iutility

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules  -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath /home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base` -Wl,-rpath,`abspath /home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = /src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/application/SensorApplLayerEx.o \
    $O/ids/IDSLayer.o \
    $O/ids/IDSSimpleLayer.o \
    $O/mobility/StaticMobility.o \
    $O/netw/StaticNetwLayer.o \
    $O/phy/Decider802154NarrowEx.o \
    $O/phy/PhyLayerBatteryEx.o \
    $O/utility/OptEngine.o \
    $O/utility/SimHelper.o \
    $O/messages/StaticNetwPkt_m.o

# Message files
MSGFILES = \
    messages/StaticNetwPkt.msg

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
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

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
	$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(SHLIB_POSTPROCESS) $O/$(TARGET)

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
	-rm -f WSN WSN.exe libWSN.so libWSN.a libWSN.dll libWSN.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f application/*_m.cc application/*_m.h
	-rm -f ids/*_m.cc ids/*_m.h
	-rm -f mac/*_m.cc mac/*_m.h
	-rm -f messages/*_m.cc messages/*_m.h
	-rm -f mobility/*_m.cc mobility/*_m.h
	-rm -f netw/*_m.cc netw/*_m.h
	-rm -f networks/*_m.cc networks/*_m.h
	-rm -f nic/*_m.cc nic/*_m.h
	-rm -f node/*_m.cc node/*_m.h
	-rm -f phy/*_m.cc phy/*_m.h
	-rm -f utility/*_m.cc utility/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc application/*.cc ids/*.cc mac/*.cc messages/*.cc mobility/*.cc netw/*.cc networks/*.cc nic/*.cc node/*.cc phy/*.cc utility/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/application/SensorApplLayerEx.o: application/SensorApplLayerEx.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/application/SensorApplLayer.h \
  application/SensorApplLayerEx.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/Packet.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/ids/IDSLayer.o: ids/IDSLayer.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h \
  ids/IDSLayer.h
$O/ids/IDSSimpleLayer.o: ids/IDSSimpleLayer.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  messages/StaticNetwPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/NetwPkt_m.h \
  ../simulations/Policemen/utility/SimHelper.h \
  ids/IDSSimpleLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/MacPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  netw/StaticNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h \
  ids/IDSLayer.h
$O/mobility/StaticMobility.o: mobility/StaticMobility.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  mobility/StaticMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  ../simulations/Policemen/utility/SimHelper.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/netw/StaticNetwLayer.o: netw/StaticNetwLayer.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  messages/StaticNetwPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/NetwControlInfo.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/NetwPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/ArpInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  netw/StaticNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/phy/Decider802154NarrowEx.o: phy/Decider802154NarrowEx.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/DeciderToPhyInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/ChannelState.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/BaseDecider.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Decider.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ChannelSenseRequest_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Mapping.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Signal_.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/phy/Decider802154Narrow.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/AirFrame_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingUtils.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  phy/Decider802154NarrowEx.h
$O/phy/PhyLayerBatteryEx.o: phy/PhyLayerBatteryEx.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/ChannelState.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Decider.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/phy/PhyLayerBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/BasePhyLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Mapping.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/phy/Decider802154Narrow.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/phy/PhyLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/connectionManager/ChannelAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/ChannelInfo.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/AirFrame_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  phy/Decider802154NarrowEx.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/DeciderToPhyInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/BaseDecider.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ChannelSenseRequest_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MacToPhyInterface.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Signal_.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  phy/PhyLayerBatteryEx.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/AnalogueModel.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingUtils.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/PhyUtils.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/utility/OptEngine.o: utility/OptEngine.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  utility/OptEngine.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/NetwPkt_m.h \
  ../simulations/Policemen/utility/SimHelper.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  netw/StaticNetwLayer.h \
  ids/IDSLayer.h \
  messages/StaticNetwPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  ids/IDSSimpleLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/MacPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
$O/utility/SimHelper.o: utility/SimHelper.cc \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/PassedMessage.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/MappingBase.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseNetwLayer.h \
  mobility/StaticMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseBattery.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/NetwPkt_m.h \
  ../simulations/Policemen/utility/SimHelper.h \
  /home/asaleh/Diplomka/MiXiM/src/base/phyLayer/Interpolation.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/ApplPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Coord.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/utility/DroppedPacket.h \
  /home/asaleh/Diplomka/MiXiM/src/modules/mac/BMacLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/SimpleAddress.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/miximkerneldefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FindModule.h \
  utility/SimHelper.h \
  netw/StaticNetwLayer.h \
  ids/IDSLayer.h \
  messages/StaticNetwPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/MiXiMDefs.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseModule.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/FWMath.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/Move.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMacLayer.h \
  ids/IDSSimpleLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseWorldUtility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseMobility.h \
  /home/asaleh/Diplomka/MiXiM/src/base/messages/MacPkt_m.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BaseLayer.h \
  /home/asaleh/Diplomka/MiXiM/src/base/modules/BatteryAccess.h \
  /home/asaleh/Diplomka/MiXiM/src/base/utils/HostState.h
