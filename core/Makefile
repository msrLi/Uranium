CXX      = $(GLOBAL_CXX)
CXXFLAGS = $(GLOBAL_CXXFLAGS)
LDFLAGS  = $(GLOBAL_LDFLAGS)

TARGET      = libcore$(strip $(DYLIB_EXT))
sources     = $(wildcard *.cpp)
objects     = $(sources:.cpp=.o)
dependence := $(sources:.cpp=.d)

SHARED_LIBS = $(GLOBAL_SHARED_LIBS) libtransmission libthreads libwebsocket libfswatch libcurl libarchive libz
STATIC_LIBS = $(GLOBAL_STATIC_LIBS) libencrypt libmonitor libmd5sum_sha1sum libuuid libutils libaes libbsdtar

include $(MAKE_RULE)/find.library.make.rule

-include $(dependence)

include $(MAKE_RULE)/dependency.make.rule

include $(MAKE_RULE)/submodule.make.rule

all: compile link $(MAKE_SUB_MODULES)

compile: $(objects) $(COMPILE_SUB_MODULES)

link: $(objects)
	$(CXX) $^ $(LDFLAGS) -o $(TARGET)
	$(MAKE) $(LINK_SUB_MODULES)

clean: $(CLEAN_SUB_MODULES)
	rm -f $(TARGET) $(objects) $(dependence)

.PHONY: clean $(COMPILE_SUB_MODULES) $(LINK_SUB_MODULES) $(MAKE_SUB_MODULES) $(CLEAN_SUB_MODULES)
