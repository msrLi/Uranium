CXX      = $(GLOBAL_CXX)
AR       = $(GLOBAL_AR)
CXXFLAGS = $(GLOBAL_CXXFLAGS)
ARFLAGS  = $(GLOBAL_ARFLAGS)

TARGET      = libmonitor$(strip $(STLIB_EXT))
sources     = $(wildcard *.cpp)
objects     = $(sources:.cpp=.o)
dependence := $(sources:.cpp=.d)

SHARED_LIBS = $(GLOBAL_SHARED_LIBS) libpthread libfswatch libarchive
STATIC_LIBS = $(GLOBAL_STATIC_LIBS) libbsdtar libaes libmd5sum_sha1sum libuuid

include $(MAKE_RULE)/find.library.make.rule

-include $(dependence)

include $(MAKE_RULE)/dependency.make.rule

include $(MAKE_RULE)/submodule.make.rule

all: compile link $(MAKE_SUB_MODULES)

compile: $(objects) $(COMPILE_SUB_MODULES)

link: $(objects)
	$(AR) $(ARFLAGS) $(TARGET) $^
	$(MAKE) $(LINK_SUB_MODULES)

clean: $(CLEAN_SUB_MODULES)
	rm -rf $(TARGET) $(objects) $(dependence) *.d.*

.PHONY: clean $(MAKE_SUB_MODULES) $(COMPILE_SUB_MODULES) $(LINK_SUB_MODULES) $(CLEAN_SUB_MODULES)
