# Project: demo

CC       = gcc
TMPDIR   = obj
OBJ      = obj/exception.o obj/genlib.o obj/graphics.o obj/random.o obj/simpio.o obj/strlib.o obj/main.o obj/imgui.o obj/linkedlist.o obj/enhancedGUI.o
LINKOBJ  = obj/exception.o obj/genlib.o obj/graphics.o obj/random.o obj/simpio.o obj/strlib.o obj/main.o obj/imgui.o obj/linkedlist.o obj/enhancedGUI.o
LIBS     = -L"C:/Program Files/Dev-Cpp/MinGW32/lib" -L"C:/Program Files/Dev-Cpp/MinGW32/mingw32/lib" -static-libstdc++ -static-libgcc -mwindows
INCS     = -I"C:/Program Files/Dev-Cpp/MinGW32/include" -I"./lib/" -I"./lib/libgraphics" -I"./lib/simpleGUI"
BIN      = main.exe
CFLAGS   = $(INCS)
RM       = rm -f

.PHONY: all clean

all: $(BIN)

clean:
	${RM} $(OBJ) $(BIN)
	${RM} -r $(TMPDIR)

$(BIN): $(TMPDIR) $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)
	$(BIN)

$(TMPDIR):
	mkdir $(TMPDIR)

obj/exception.o: ./lib/libgraphics/exception.c
	$(CC) -c ./lib/libgraphics/exception.c -o obj/exception.o $(CFLAGS)

obj/genlib.o: ./lib/libgraphics/genlib.c
	$(CC) -c ./lib/libgraphics/genlib.c -o obj/genlib.o $(CFLAGS)

obj/graphics.o: ./lib/libgraphics/graphics.c
	$(CC) -c ./lib/libgraphics/graphics.c -o obj/graphics.o $(CFLAGS)

obj/random.o: ./lib/libgraphics/random.c
	$(CC) -c ./lib/libgraphics/random.c -o obj/random.o $(CFLAGS)

obj/simpio.o: ./lib/libgraphics/simpio.c
	$(CC) -c ./lib/libgraphics/simpio.c -o obj/simpio.o $(CFLAGS)

obj/strlib.o: ./lib/libgraphics/strlib.c
	$(CC) -c ./lib/libgraphics/strlib.c -o obj/strlib.o $(CFLAGS)

obj/main.o: ./main.c
	$(CC) -c ./main.c -o obj/main.o $(CFLAGS)

obj/imgui.o: ./lib/simpleGUI/imgui.c
	$(CC) -c ./lib/simpleGUI/imgui.c -o obj/imgui.o $(CFLAGS)

obj/linkedlist.o: ./lib/linkedlist.c
	$(CC) -c ./lib/linkedlist.c -o obj/linkedlist.o $(CFLAGS)

obj/enhancedGUI.o: ./lib/enhancedGUI.c
	$(CC) -c ./lib/enhancedGUI.c -o obj/enhancedGUI.o $(CFLAGS)