SOURCES_CPP=$(wildcard src/*.cpp src/*/*.cpp)
SOURCES_C=$(wildcard src/*/*.c)
PROJECT_NAME=duilib
TARGET_DIR=release
LIBS_DIR=../../libs
LIBS_OPT_DIR=../../bin/mingw-posix/opt/lib
CC=g++
AR=ar -rc
EXE_EXT=.exe
DLL_EXT=.dll
#CFLAGS=-fpermissive -fleading-underscore -DWIN32 -DNDEBUG -D_WINDOWS -DUILIB_STATIC
CFLAGS= -Os  
CFLAGS+= -ffunction-sections -fdata-sections 
CFLAGS+= -fno-exceptions -fpermissive 
CFLAGS+= -DWIN32 -D_DEBUG -D_WINDOWS -DUILIB_EXPORTS -DCURL_STATICLIB
LDFLAGS= -Wl,--gc-sections
#LIBS=-lkernel32 -lwinspool -lcomdlg32 -luser32 -loleaut32 -loledlg -lole32 -luuid -lmsimg32 -lgdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi
LIBS= -lcomctl32 -lole32 -luuid -lgdiplus -limm32 -lshlwapi 
LIBS+= -static -L$(LIBS_DIR)/utils/lib -lutils 
LIBS+= -L$(LIBS_DIR)/curl/lib -lcurl -lwinhttp
LIBS+= -L$(LIBS_DIR)/brotli/lib -lbrotlidec-static -lbrotlienc-static -lbrotlicommon-static 
LIBS+= -L$(LIBS_DIR)/nghttp2/lib -lnghttp2
LIBS+= -L$(LIBS_DIR)/openssl/lib -lssl -lcrypto
LIBS+= -L$(LIBS_DIR)/libssh2/lib -lssh2
LIBS+= -lz -lws2_32 -lcrypt32 -lwldap32 -lnormaliz -lmsvcr100 
INC_DIR=-I./include -I$(LIBS_DIR)/utils/include -I$(LIBS_DIR)/curl/include
PREFIX=/usr/local
INSTALL_DIR=$(PREFIX)/$(PROJECT_NAME)
BUILD_DIR=build
RES_DIR=res
SHARE_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME)$(DLL_EXT)
STATIC_TARGET=$(TARGET_DIR)/lib/lib$(PROJECT_NAME).a
EXE_TARGET=$(TARGET_DIR)/bin/app$(EXE_EXT)
OBJECTS_CPP=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_CPP:.cpp=.o)))
OBJECTS_C=$(addprefix $(BUILD_DIR)/,$(strip $(SOURCES_C:.c=.o)))

all: rmtarget $(EXE_TARGET)
.PHONY: dirs clean rmtarget

#编译测试目标文件
$(EXE_TARGET): $(BUILD_DIR)/app.o $(BUILD_DIR)/resource.o $(STATIC_TARGET)
	$(CC) $(LDFLAGS) -o $@ $(INC_DIR) -mwindows $^ $(LIBS)
	strip $(EXE_TARGET)
	$(EXE_TARGET)

$(BUILD_DIR)/app.o: app.cpp
	$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<
$(BUILD_DIR)/resource.o: $(RES_DIR)/Project1.rc
	windres -i $^ -o $@

# 编译动态库
$(SHARE_TARGET): share
share:$(OBJECTS_CPP) $(OBJECTS_C)
	$(CC) -fPIC -shared  $(LDFLAGS) -o $(SHARE_TARGET) $^ $(LIBS)
# 编译静态库
$(STATIC_TARGET): static
static:$(OBJECTS_CPP) $(OBJECTS_C)
	@$(AR) $(STATIC_TARGET) $^

#编译目标文件
$(BUILD_DIR)/%.o:%.cpp
	$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<
$(BUILD_DIR)/%.o:%.c
	$(CC) -c -o $@ $(CFLAGS) $(INC_DIR) $<

# 创建目录
dirs: clean
	-mkdir -p $(BUILD_DIR)/src/Control \
		$(BUILD_DIR)/src/Core \
		$(BUILD_DIR)/src/Layout \
		$(BUILD_DIR)/src/Utils \
		$(TARGET_DIR)/bin \
		$(TARGET_DIR)/lib

# 删除目标文件
rmtarget:
	-rm -f $(EXE_TARGET)

# 清理
clean:
	-rm -rf $(EXE_TARGET) $(BUILD_DIR)
