BUILD=build
CC=g++
LIBS=-lkernel32 -lwinspool -lcomdlg32 -luser32 -loledlg -lole32 -luuid -lmsimg32 -lgdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi

all: dll

.PHONY: run clean

# 生成动态库dll以及导出文件
dll: math.cpp
	$(CC) math.cpp -shared -o $(BUILD)/math.dll -Wl,--out-implib,$(BUILD)/math.lib

duilib: $(BUILD)/duilib.o
	ar -rc $(BUILD)/libduilib.a $(BUILD)/duilib.o
$(BUILD)/duilib.o: UIActiveX.cpp
	$(CC) -c -o $@ $^

# 生成静态库
static: $(BUILD)/math.o
	ar -rc $(BUILD)/libmath.a $(BUILD)/math.o
$(BUILD)/%.o: %.cpp
	$(CC) -c -o $@ $^

# 直接从动态库dll调用
$(BUILD)/demo.exe: demo.cpp dll
	$(CC) -o $@ $<
run: clean $(BUILD)/demo.exe
	$(BUILD)/demo.exe

# 通过导出文件(lib)调用
$(BUILD)/demo2.exe: demo2.cpp dll
	$(CC) -o $@ $< $(BUILD)/math.lib
run2: clean $(BUILD)/demo2.exe
	$(BUILD)/demo2.exe

# 通过静态库调用
$(BUILD)/demo3.exe: demo3.cpp static
	$(CC) -o $@ $< -L$(BUILD) -lmath
run3: clean $(BUILD)/demo3.exe
	$(BUILD)/demo3.exe

# 清理
clean:
	-@rm -rf build
	-@mkdir build

	