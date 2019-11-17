INCS=-I"G:\compiler\mingw\i686-w64-mingw32\include" -I"G:\libs\freeglut\include"
LIBS=-L"G:\compiler\mingw\i686-w64-mingw32\lib" -L"G:\libs\freeglut\lib"

all: app.exe

app.exe: app.o
	g++ -o $@ $^ $(LIBS) -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -Wl,--subsystem,windows

%.o: %.cpp
	g++ -c -o app.o app.cpp -D FREEGLUT_STATIC $(INCS)
	
.PHONY: clean
clean:
	-rm -rf *.exe *.o