#LIBS=-lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32
LIBS=-lcomdlg32 -lcomctl32 -lgdi32
CFLAG=-finput-charset=utf-8 -fexec-charset=gbk
RMDIR=rd /s /q
RM=del
BIN=bin
BUILD=build
SRC=src
RES=res
TARGET=$(BIN)/PwdMaker.exe

all: $(TARGET)

$(TARGET): $(BUILD)/resource.o $(SRC)/main.cpp
	g++ $(SRC)/main.cpp $^ $(LIBS) $(CFLAG) -mwindows -o $@

$(BUILD)/resource.o: $(RES)/PwdMaker.rc
	windres -i $^ -o $@


.PHONY: clean run

run: $(TARGET)
	$(TARGET)

clean: 
	$(RM) $(BIN)/*.exe