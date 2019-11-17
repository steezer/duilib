SOURCES_CPP=$(wildcard src/*.cpp src/*/*.cpp)
SOURCES_C=$(wildcard src/*/*.c)
PROJECT_NAME=duilib
TARGET_DIR=release
CC=g++
AR=ar -rc
EXE_EXT=.exe
DLL_EXT=.dll
#CFLAGS=-fpermissive -DWIN32 -DNDEBUG -D_WINDOWS -DUILIB_STATIC
CFLAGS=-fpermissive -DWIN32 -DNDEBUG -D_WINDOWS -DUILIB_EXPORTS
LDFLAGS= 
LIBS=-lkernel32 -lwinspool -lcomdlg32 -luser32 -loledlg -lole32 -luuid -lGdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi
INC_DIR=-I./include
PREFIX=/usr/local
INSTALL_DIR=$(PREFIX)/$(PROJECT_NAME)
BUILD_DIR=build
EXE_TARGET=$(TARGET_DIR)/bin/$(PROJECT_NAME)$(EXE_EXT)
SHARE_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME)$(DLL_EXT)
STATIC_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME).a
OBJECTS_CPP=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_CPP:.cpp=.o)))
OBJECTS_C=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_C:.c=.o)))

all:share static

share:$(OBJECTS_CPP) $(OBJECTS_C)
	$(CC) -fPIC -shared -o $(SHARE_TARGET) $(LDFLAGS) $(LIBS) $^

static:$(OBJECTS_CPP) $(OBJECTS_C)
	@$(AR) $(STATIC_TARGET) $^

$(BUILD_DIR)/%.o:%.cpp
	@$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<

$(BUILD_DIR)/%.o:%.c
	@$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<


.PHONY: dirs clean install run stop
dirs: clean
	mkdir -p $(TARGET_DIR)\lib
	mkdir -p $(BUILD_DIR)
	cp -r src $(BUILD_DIR)
	find $(BUILD_DIR)/src -name "*.cpp" -o -name "*.c" | xargs rm -f

clean:
	rm -rf $(TARGET_DIR) $(BUILD_DIR)
