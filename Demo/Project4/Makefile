LIBS=-lkernel32 -lwinspool -lcomdlg32 -luser32 -loledlg -lole32 -luuid -lGdi32 -lgdiplus -lwinmm -lcomctl32 -limm32 -lshlwapi
#LIBS=-lcomdlg32 -lcomctl32 -lgdi32
CFLAG=-fpermissive -DUILIB_STATIC -I"G:\\duilib\\SDK\\include"
RMDIR=rd /s /q
RM=rm -f
BIN=bin
BUILD=build
SRC=src
RES=res
TARGET=$(BIN)/Project4.exe

all: $(TARGET)

$(TARGET): $(BUILD)/resource.o app.cpp
	g++ $(CFLAG) -mwindows -o $@ $^ "G:\\duilib\\SDK\\lib\\libduilib.a" -static $(LIBS)

$(BUILD)/resource.o: Project1.rc
	windres -i $^ -o $@

$(BUILD)/resource.o: Project1.rc
	windres -i $^ -o $@

.PHONY: clean run

run: $(TARGET)
	$(TARGET)

clean: 
	$(RM) $(BIN)/*.exe