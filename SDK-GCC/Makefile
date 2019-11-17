SOURCES_CPP=$(wildcard src/*.cpp src/*/*.cpp)
SOURCES_C=$(wildcard src/*/*.c)
PROJECT_NAME=duilib
TARGET_DIR=release
CC=g++
AR=ar -rc
EXE_EXT=.exe
DLL_EXT=.dll
#CFLAGS=-fpermissive -fleading-underscore -DWIN32 -DNDEBUG -D_WINDOWS -DUILIB_STATIC
CFLAGS=-fpermissive -DWIN32 -DNDEBUG -D_WINDOWS -DUILIB_EXPORTS
LDFLAGS= 
#LIBS=-lkernel32 -lwinspool -lcomdlg32 -luser32 -loleaut32 -loledlg -lole32 -luuid -lmsimg32 -lgdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi
LIBS=-lwinspool -lcomdlg32 -loleaut32 -loledlg -lole32 -luuid -lmsimg32 -lgdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi
INC_DIR=-I./include
PREFIX=/usr/local
INSTALL_DIR=$(PREFIX)/$(PROJECT_NAME)
BUILD_DIR=build
EXE_TARGET=$(TARGET_DIR)/bin/$(PROJECT_NAME)$(EXE_EXT)
SHARE_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME)$(DLL_EXT)
STATIC_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME).a
OBJECTS_CPP=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_CPP:.cpp=.o)))
OBJECTS_C=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_C:.c=.o)))
BIN_DIR=bin
RES_DIR=res
TARGET=$(BIN)/app.exe

all: $(TARGET)
.PHONY: dirs clean

#编译测试目标文件
$(TARGET): $(BUILD_DIR)/resource.o app.cpp $(OBJECTS_CPP) $(OBJECTS_C)
	$(CC) $(LIBS) $(CFLAGS) $(INC_DIR) -mwindows $^ -o $@
$(BUILD_DIR)/resource.o: $(RES_DIR)/Project1.rc
	windres -i $^ -o $@

# 编译动态库
share:$(OBJECTS_CPP) $(OBJECTS_C)
	$(CC) -fPIC -shared -o $(SHARE_TARGET) $(LDFLAGS) $(LIBS) $^

# 编译静态库
static:$(OBJECTS_CPP) $(OBJECTS_C)
	@$(AR) $(STATIC_TARGET) $^

#编译目标文件
$(BUILD_DIR)/%.o:%.cpp
	@$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<
$(BUILD_DIR)/%.o:%.c
	@$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<

# 创建目录
dirs: clean
	-mkdir -p $(BUILD_DIR)/src/Control \
		$(BUILD_DIR)/src/Core \
		$(BUILD_DIR)/src/Layout \
		$(BUILD_DIR)/src/Utils

# 清理
clean:
	-rm -rf $(TARGET_DIR) $(BUILD_DIR)
