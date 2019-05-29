CC       = $(GLOBAL_CC)
AR       = $(GLOBAL_AR)
CFLAGS   = $(GLOBAL_CFLAGS) -Wno-cpp
ARFLAGS  = $(GLOBAL_ARFLAGS) rcs

TARGET      = libuuid$(strip $(STLIB_EXT))
sources     = $(wildcard *.c)
objects     = $(sources:.c=.o)
dependence := $(sources:.c=.d)

SHARED_LIBS = $(GLOBAL_SHARED_LIBS)
STATIC_LIBS = $(GLOBAL_STATIC_LIBS)

include $(MAKE_RULE)/find.library.make.rule 

-include $(dependence)

include $(MAKE_RULE)/dependency.make.rule

include $(MAKE_RULE)/submodule.make.rule

all: lib $(MAKE_SUB_MODULES)

lib: $(objects)
	$(AR) $(ARFLAGS) $(TARGET) $^

clean: $(CLEAN_SUB_MODULES)
	rm -rf $(TARGET) $(objects) $(dependence) *.d.*

.PHONY: clean $(MAKE_SUB_MODULES) $(CLEAN_SUB_MODULES)