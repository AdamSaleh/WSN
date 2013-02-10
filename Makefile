#
# OMNeT++/OMNEST Makefile for WSN
#
# This file was generated with the command:
#  opp_makemake -f --deep --nolink -O out -d simulations/Policemen -d simulations/BMacTest -d src -Xboinc -Xout -Xsimulations -I/home/asaleh/Install/omnetpp-4.2.1/src/envir -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/base -L/home/asaleh/Diplomka/MiXiM/out/gcc-debug/src/modules -L./out//src -lmiximbase -lmiximmodules -KMIXIM_PROJ=/home/asaleh/Diplomka/MiXiM/out/gcc-debug
#

# C++ include paths (with -I)
INCLUDE_PATH = -I/home/asaleh/Install/omnetpp-4.2.1/src/envir -I/home/asaleh/Install/omnetpp-4.2.1/include/platdep -I.

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS =

# Message files
MSGFILES =

# Other makefile variables (-K)
MIXIM_PROJ=/home/asaleh/Diplomka/MiXiM/out/gcc-debug

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

all: $(OBJS) submakedirs Makefile
	@# Do nothing

submakedirs:  simulations__Policemen_dir simulations__BMacTest_dir src_dir

.PHONY: simulations__Policemen simulations__BMacTest src
simulations__Policemen: simulations__Policemen_dir
simulations__BMacTest: simulations__BMacTest_dir
src: src_dir

simulations__Policemen_dir:
	cd simulations/Policemen && $(MAKE) all

simulations__BMacTest_dir:
	cd simulations/BMacTest && $(MAKE) all

src_dir:
	cd src && $(MAKE) all

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)
	cd simulations/Policemen && $(MAKE) msgheaders
	cd simulations/BMacTest && $(MAKE) msgheaders
	cd src && $(MAKE) msgheaders

clean:
	-rm -rf $O
	-rm -f WSN WSN.exe libWSN.so libWSN.a libWSN.dll libWSN.dylib
	-rm -f ./*_m.cc ./*_m.h

	-cd simulations/Policemen && $(MAKE) clean
	-cd simulations/BMacTest && $(MAKE) clean
	-cd src && $(MAKE) clean

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc
	-cd simulations/Policemen && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd simulations/BMacTest && if [ -f Makefile ]; then $(MAKE) depend; fi
	-cd src && if [ -f Makefile ]; then $(MAKE) depend; fi

# DO NOT DELETE THIS LINE -- make depend depends on it.

