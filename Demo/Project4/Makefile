#LIBS=-lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32
LIBS=-lcomdlg32 -lcomctl32 -lgdi32
CFLAG=-fpermissive -DUILIB_STATIC -finput-charset=utf-8 -fexec-charset=gbk -IG:\duilib\SDK-GCC\include
RMDIR=rd /s /q
RM=rm -f
BIN=bin
BUILD=build
SRC=src
RES=res
TARGET=$(BIN)/Project4.exe

all: $(TARGET)

$(TARGET): $(BUILD)/resource.o app.cpp
	g++ $(LIBS) $(CFLAG) -mwindows $^ -static -LG:\duilib\SDK\lib -lduilib -o $@

$(BUILD)/resource.o: Project1.rc
	windres -i $^ -o $@


.PHONY: clean run

run: $(TARGET)
	$(TARGET)

clean: 
	$(RM) $(BIN)/*.exe