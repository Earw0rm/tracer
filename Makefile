BUILD_DIR = ./build
SOURCE_DIR = ./src
LIBS_SRC = ./libs/src

IMGUI_DIR = deps/imgui
IMGUI_SRC = $(IMGUI_DIR)/imgui.cpp \
			$(IMGUI_DIR)/imgui_draw.cpp \
			$(IMGUI_DIR)/imgui_tables.cpp \
			$(IMGUI_DIR)/imgui_widgets.cpp \
			$(IMGUI_DIR)/imgui_demo.cpp \
			$(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp \
			$(IMGUI_DIR)/backends/imgui_impl_sdlrenderer2.cpp 
IMGUI_INCLUDES = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

COMPILER ?= clang++
CCOMPILER ?= clang


OPS = -g -Wvarargs -Wall -Werror -std=c++23 
COPS = -g -Wvarargs -Wall -Werror 
INCLUDE_FLAGS = -I./include -I./libs/include $(IMGUI_INCLUDES) -I/usr/include/SDL2/
LINKER_FLAGS =  -lglfw  -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lSDL2

CORE = core.out

CPP_FILES = $(shell find $(SOURCE_DIR) -name '*.cpp') $(IMGUI_SRC)
C_LIBS_FILES = $(shell find $(LIBS_SRC) -name '*.c')

OBJ_FILES  = $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/src/%.o, $(CPP_FILES))
COBJ_FILES  = $(patsubst $(LIBS_SRC)/%.c, $(BUILD_DIR)/libs/%.o, $(C_LIBS_FILES))


.PHONY: all clean test  

all: core
	$(BUILD_DIR)/$(CORE)
debug: core
	gdb $(BUILD_DIR)/$(CORE) 	
clean:
	rm -rf $(BUILD_DIR)/*

core: $(OBJ_FILES) $(COBJ_FILES)
	$(COMPILER) -o $(BUILD_DIR)/$(CORE) $(OBJ_FILES) $(COBJ_FILES) $(DEFINES) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $(OPS)

$(BUILD_DIR)/$(CORE): core

$(BUILD_DIR)/src/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(@D)
	$(COMPILER) $(OPS) -c $< -o $@ $(DEFINES) $(INCLUDE_FLAGS)

$(BUILD_DIR)/libs/%.o: $(LIBS_SRC)/%.c
	mkdir -p $(@D)
	$(CCOMPILER) $(COPS) -c $< -o $@ $(DEFINES) $(INCLUDE_FLAGS)	
