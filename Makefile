run:
	g++ -I src/include -L src/lib -o main main.cpp Renderer.cpp Renderer.h InputHandler.cpp InputHandler.h -lmingw32 -lSDL2main -lSDL2
	./main.exe