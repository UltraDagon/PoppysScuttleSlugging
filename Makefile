run:
	g++ -I src/include -L src/lib -o main.exe *.cpp *.h scenes/*.cpp scenes/*.h entities/*.cpp entities/*.h -lmingw32 -lSDL2main -lSDL2
	./main.exe
debug:
	g++ -g -I src/include -L src/lib -o main.exe *.cpp *.h scenes/*.cpp scenes/*.h -lmingw32 -lSDL2main -lSDL2
	gdb main.exe

push message=none:
	@if [$(message) = "none"]; then\
		echo "Uh oh!";\
		fi
	echo message is $(message)
run-ubuntu:
	g++ -I src/include -L src/lib -o main.o main.cpp Renderer.cpp Renderer.h InputHandler.cpp InputHandler.h -lSDL2main -lSDL2
	./main.o
run-valgrind:
	g++ -I src/include -L src/lib -o main.o main.cpp Renderer.cpp Renderer.h InputHandler.cpp InputHandler.h -lSDL2main -lSDL2
	