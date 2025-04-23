run:
	g++ -I src/include -L src/lib -o main.exe *.cpp *.h -lmingw32 -lSDL2main -lSDL2
	./main.exe
run-ubuntu:
	g++ -I src/include -L src/lib -o main.o main.cpp Renderer.cpp Renderer.h InputHandler.cpp InputHandler.h -lSDL2main -lSDL2
	./main.o
run-valgrind:
	g++ -I src/include -L src/lib -o main.o main.cpp Renderer.cpp Renderer.h InputHandler.cpp InputHandler.h -lSDL2main -lSDL2
	