all: dll

.PHONY: run clean

# 生成动态库dll以及导出文件
dll: math.c
	gcc math.c -shared -o math.dll -Wl,--out-implib,math.lib

# 生成静态库
static: math.o
	ar -rc libmath.a math.o
%.o: %.c
	gcc -c -o $@ $^

# 直接从动态库dll调用
demo.exe: demo.c dll
	gcc -o $@ demo.c
run: clean demo.exe
	demo.exe

# 通过导出文件(lib)调用
demo2.exe: demo2.c dll
	gcc -o $@ demo2.c math.lib
run2: clean demo2.exe
	demo2.exe

# 通过静态库调用
demo3.exe: demo2.c static
	gcc -o $@ demo2.c -L. -lmath
run3: clean demo3.exe
	demo3.exe

# 清理
clean:
	-@rm -rf "*.lib" "*.exe" "*.dll" "*.o" "*.a"

	