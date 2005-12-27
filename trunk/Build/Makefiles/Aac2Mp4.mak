##########################################################################
#
#    Aac2Mp4 Program
#
#    (c) 2001-2002 Gilles Boccon-Gibod
#
##########################################################################

##########################################################################
# includes
##########################################################################
include $(BUILD_ROOT)/Makefiles/Crypto.exp
include $(BUILD_ROOT)/Makefiles/Core.exp
include $(BUILD_ROOT)/Makefiles/System.exp
include $(BUILD_ROOT)/Makefiles/Codecs.exp
include $(BUILD_ROOT)/Makefiles/MetaData.exp

##########################################################################
# targets
##########################################################################
TARGET_SOURCES = Aac2Mp4.cpp

##########################################################################
# make path
##########################################################################
VPATH += $(SOURCE_ROOT)/Apps/Aac2Mp4

##########################################################################
# variables
##########################################################################
LINK = $(LINK_CPP_OPTIONS) $(OPTIMIZE_CPP) $(DEBUG_CPP) $(PROFILE_CPP)

##########################################################################
# rules
##########################################################################
aac2mp4: $(TARGET_SOURCES:.cpp=.o) $(TARGET_OBJECTS) $(TARGET_LIBRARY_FILES)
	$(LINK) $^ -o $@ 

##########################################################################
# includes
##########################################################################
include $(BUILD_ROOT)/Makefiles/Rules.mak


