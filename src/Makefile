#
# OMNeT++/OMNEST Makefile for multicmain
#
# This file was generated with the command:
#  opp_makemake -f --deep -lOverSim -linet -O out -o multicmain -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/tcp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/applications/pingapp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/mpls -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ipv4 -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/linklayer/contract -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/linklayer/mfcore -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ldp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ipv6 -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/arp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/applications/udpapp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ted -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/rsvp_te -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/util/headerserializers -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/contract -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/common -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/sctp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/udp -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/icmpv6 -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/world -ID:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/util -ID:\Developement/Oversim2/multic/src/../../OverSim-20100526/src/common -LD:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src -LD:\Developement/Oversim2/multic/src/../../OverSim-20100526/src -L/usr/lib -KINET_PROJ=D:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505 -KOVERSIM_PROJ=D:\Developement/Oversim2/multic/src/../../OverSim-20100526
#

# Name of target to be created (-o option)
TARGET = multicmain$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/tcp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/applications/pingapp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/mpls \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ipv4 \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/linklayer/contract \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/linklayer/mfcore \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ldp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ipv6 \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/arp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/applications/udpapp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/ted \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/rsvp_te \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/util/headerserializers \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/contract \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/common \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/sctp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/transport/udp \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/icmpv6 \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/world \
    -ID:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/util \
    -ID:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common \
    -I. \
    -Iapplications \
    -Iapplications/datatest \
    -Imisc \
    -Ioverlay \
    -Ioverlay/aimd \
    -Ioverlay/basic \
    -Ioverlay/perfect \
    -Ioverlay/qlearn

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -LD:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src -LD:/Developement/Oversim2/multic/src/../../OverSim-20100526/src -L/usr/lib  -lOverSim -linet
LIBS += -Wl,-rpath,`abspath D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src` -Wl,-rpath,`abspath D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src` -Wl,-rpath,`abspath /usr/lib`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = /src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/applications/datatest/DataTest.o \
    $O/misc/stringtools.o \
    $O/misc/symmatrix.o \
    $O/misc/uppermatrix.o \
    $O/overlay/aimd/AimdCC.o \
    $O/overlay/basic/BasicCC.o \
    $O/overlay/perfect/PerfectCC.o \
    $O/overlay/qlearn/QLearnCC.o \
    $O/applications/datatest/DataMsg_m.o \
    $O/overlay/aimd/IncreaseTimer_m.o \
    $O/overlay/basic/AckMsg_m.o \
    $O/overlay/basic/LookupExt_m.o \
    $O/overlay/basic/TimeoutMessage_m.o

# Message files
MSGFILES = \
    applications/datatest/DataMsg.msg \
    overlay/aimd/IncreaseTimer.msg \
    overlay/basic/AckMsg.msg \
    overlay/basic/LookupExt.msg \
    overlay/basic/TimeoutMessage.msg

# Other makefile variables (-K)
INET_PROJ=D:\Developement/Oversim2/multic/src/../../INET-OverSim-20100505
OVERSIM_PROJ=D:\Developement/Oversim2/multic/src/../../OverSim-20100526

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
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

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
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f multicmain multicmain.exe libmulticmain.so libmulticmain.a libmulticmain.dll libmulticmain.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f applications/*_m.cc applications/*_m.h
	-rm -f applications/datatest/*_m.cc applications/datatest/*_m.h
	-rm -f misc/*_m.cc misc/*_m.h
	-rm -f overlay/*_m.cc overlay/*_m.h
	-rm -f overlay/aimd/*_m.cc overlay/aimd/*_m.h
	-rm -f overlay/basic/*_m.cc overlay/basic/*_m.h
	-rm -f overlay/perfect/*_m.cc overlay/perfect/*_m.h
	-rm -f overlay/qlearn/*_m.cc overlay/qlearn/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc applications/*.cc applications/datatest/*.cc misc/*.cc overlay/*.cc overlay/aimd/*.cc overlay/basic/*.cc overlay/perfect/*.cc overlay/qlearn/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/applications/datatest/DataMsg_m.o: applications/datatest/DataMsg_m.cc \
  applications/datatest/DataMsg_m.h
$O/applications/datatest/DataTest.o: applications/datatest/DataTest.cc \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  applications/datatest/../../overlay/basic/BasicCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TopologyVis.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseOverlay.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  applications/datatest/DataMsg_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INotifiable.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/UnderlayConfigurator.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcMacros.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcListener.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeVector.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  applications/datatest/../../overlay/basic/../../misc/uppermatrix.h \
  applications/datatest/DataTest.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RecursiveLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/ProxNodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseApp.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/IterativeLookupConfiguration.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/AbstractLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcState.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/InitStages.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  applications/datatest/../../overlay/basic/../../misc/symmatrix.h \
  applications/datatest/../../overlay/basic/LookupExt_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseRpc.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Comparator.h
$O/misc/stringtools.o: misc/stringtools.cc
$O/misc/symmatrix.o: misc/symmatrix.cc \
  misc/symmatrix.h
$O/misc/uppermatrix.o: misc/uppermatrix.cc \
  misc/uppermatrix.h \
  misc/symmatrix.h
$O/overlay/aimd/AimdCC.o: overlay/aimd/AimdCC.cc \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  overlay/aimd/../basic/../../misc/uppermatrix.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TopologyVis.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  overlay/aimd/../../misc/stringtools.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseOverlay.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INotifiable.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcMacros.h \
  overlay/aimd/../basic/../../misc/symmatrix.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeVector.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcListener.h \
  overlay/aimd/../basic/LookupExt_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RecursiveLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/GlobalStatistics.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/ProxNodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  overlay/aimd/IncreaseTimer_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/IterativeLookupConfiguration.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/AbstractLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcState.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/InitStages.h \
  overlay/aimd/AimdCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  overlay/aimd/../basic/BasicCC.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseRpc.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Comparator.h
$O/overlay/aimd/IncreaseTimer_m.o: overlay/aimd/IncreaseTimer_m.cc \
  overlay/aimd/IncreaseTimer_m.h
$O/overlay/basic/AckMsg_m.o: overlay/basic/AckMsg_m.cc \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  overlay/basic/AckMsg_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h
$O/overlay/basic/BasicCC.o: overlay/basic/BasicCC.cc \
  overlay/basic/BasicCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TopologyVis.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseOverlay.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INotifiable.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcMacros.h \
  overlay/basic/LookupExt_m.h \
  overlay/basic/../../misc/uppermatrix.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcListener.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeVector.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  overlay/basic/AckMsg_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RecursiveLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/GlobalStatistics.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/ProxNodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/IterativeLookupConfiguration.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/AbstractLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcState.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/InitStages.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseRpc.h \
  overlay/basic/../../misc/symmatrix.h \
  overlay/basic/TimeoutMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Comparator.h
$O/overlay/basic/LookupExt_m.o: overlay/basic/LookupExt_m.cc \
  overlay/basic/LookupExt_m.h
$O/overlay/basic/TimeoutMessage_m.o: overlay/basic/TimeoutMessage_m.cc \
  overlay/basic/TimeoutMessage_m.h
$O/overlay/perfect/PerfectCC.o: overlay/perfect/PerfectCC.cc \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  overlay/perfect/../basic/LookupExt_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TopologyVis.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseOverlay.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INotifiable.h \
  overlay/perfect/../../misc/stringtools.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcMacros.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeVector.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcListener.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  overlay/perfect/PerfectCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RecursiveLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/GlobalStatistics.h \
  overlay/perfect/../basic/../../misc/symmatrix.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/ProxNodeHandle.h \
  overlay/perfect/../basic/BasicCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/IterativeLookupConfiguration.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/AbstractLookup.h \
  overlay/perfect/../basic/../../misc/uppermatrix.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/InitStages.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcState.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseRpc.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Comparator.h
$O/overlay/qlearn/QLearnCC.o: overlay/qlearn/QLearnCC.cc \
  overlay/qlearn/../basic/BasicCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Vector2D.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BinaryValue.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TopologyVis.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverlayKey.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeHandle.h \
  overlay/qlearn/../basic/LookupExt_m.h \
  overlay/qlearn/../../misc/stringtools.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseOverlay.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/TransportAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INotifiable.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcMacros.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPv6Address.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/NodeVector.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcListener.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/base/INETDefs.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RecursiveLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/GlobalStatistics.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/ProxNodeHandle.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/oversim_mapset.h \
  overlay/qlearn/QLearnCC.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/IterativeLookupConfiguration.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/AbstractLookup.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/InitStages.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/RpcState.h \
  overlay/qlearn/../basic/../../misc/uppermatrix.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/CommonMessages_m.h \
  overlay/qlearn/../basic/../../misc/symmatrix.h \
  D:/Developement/Oversim2/multic/src/../../INET-OverSim-20100505/src/networklayer/contract/IPvXAddress.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/BaseRpc.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/OverSimMessage_m.h \
  D:/Developement/Oversim2/multic/src/../../OverSim-20100526/src/common/Comparator.h
