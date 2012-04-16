# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMNTdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := Y:/TP-1-Pilote
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/ProjetPilote



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks67
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = ProjetPilote/$(MODE_DIR)/ProjetPilote.out \
	 ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage.o


#Rules

# ProjetPilote
ifeq ($(DEBUG_MODE),1)
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetPilote/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
ProjetPilote/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
ProjetPilote/$(MODE_DIR)/% : IDE_LIBRARIES = 
ProjetPilote/$(MODE_DIR)/% : PROJECT_TYPE = DKM
ProjetPilote/$(MODE_DIR)/% : DEFINES = 
ProjetPilote/$(MODE_DIR)/% : EXPAND_DBG = 0
ProjetPilote/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
ProjetPilote/$(MODE_DIR)/% : CPU = SIMNT
ProjetPilote/$(MODE_DIR)/% : TOOL_FAMILY = diab
ProjetPilote/$(MODE_DIR)/% : TOOL = diab
ProjetPilote/$(MODE_DIR)/% : TOOL_PATH = 
ProjetPilote/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
ProjetPilote/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
ProjetPilote/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
ProjetPilote/$(MODE_DIR)/% : LIBPATH = 
ProjetPilote/$(MODE_DIR)/% : LIBS = 
ProjetPilote/$(MODE_DIR)/% : OBJ_DIR := ProjetPilote/$(MODE_DIR)

OBJECTS_ProjetPilote = ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage.o

ProjetPilote/$(MODE_DIR)/ProjetPilote.out : $(OBJECTS_ProjetPilote)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_ProjetPilote) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_ProjetPilote) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

ProjetPilote/$(MODE_DIR)/ProjetPilote_compile_file : $(FILE) ;

_clean :: ProjetPilote/$(MODE_DIR)/ProjetPilote_clean

ProjetPilote/$(MODE_DIR)/ProjetPilote_clean : 
	$(TRACE_FLAG)if [ -d "ProjetPilote" ]; then cd "ProjetPilote"; rm -rf $(MODE_DIR); fi


# ProjetPilote_partialImage
ifeq ($(DEBUG_MODE),1)
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
ProjetPilote_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
ProjetPilote_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
ProjetPilote_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
ProjetPilote_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
ProjetPilote_partialImage/$(MODE_DIR)/% : DEFINES = 
ProjetPilote_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
ProjetPilote_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
ProjetPilote_partialImage/$(MODE_DIR)/% : CPU = SIMNT
ProjetPilote_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
ProjetPilote_partialImage/$(MODE_DIR)/% : TOOL = diab
ProjetPilote_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
ProjetPilote_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
ProjetPilote_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
ProjetPilote_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
ProjetPilote_partialImage/$(MODE_DIR)/% : LIBPATH = 
ProjetPilote_partialImage/$(MODE_DIR)/% : LIBS = 
ProjetPilote_partialImage/$(MODE_DIR)/% : OBJ_DIR := ProjetPilote_partialImage/$(MODE_DIR)

ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/ISR.o : $(PRJ_ROOT_DIR)/ISR.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/facteur.o : $(PRJ_ROOT_DIR)/facteur.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/fonctionsBasiques.o : $(PRJ_ROOT_DIR)/fonctionsBasiques.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/main.o : $(PRJ_ROOT_DIR)/main.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/monPilote.o : $(PRJ_ROOT_DIR)/monPilote.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateur.o : $(PRJ_ROOT_DIR)/simulateur.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurApplication.o : $(PRJ_ROOT_DIR)/simulateurApplication.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurPeripherique.o : $(PRJ_ROOT_DIR)/simulateurPeripherique.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


OBJECTS_ProjetPilote_partialImage = ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/ISR.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/facteur.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/fonctionsBasiques.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/main.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/monPilote.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateur.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurApplication.o \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurPeripherique.o

ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage.o : $(OBJECTS_ProjetPilote_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_ProjetPilote_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage_compile_file : $(FILE) ;

_clean :: ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage_clean

ProjetPilote_partialImage/$(MODE_DIR)/ProjetPilote_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "ProjetPilote_partialImage" ]; then cd "ProjetPilote_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/ISR.d ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/facteur.d ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/fonctionsBasiques.d \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/main.d ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/monPilote.d ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateur.d \
	 ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurApplication.d ProjetPilote_partialImage/$(MODE_DIR)/Objects/ProjetPilote/simulateurPeripherique.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
