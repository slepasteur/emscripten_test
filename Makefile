CC = emcc
all: test.cpp
	$(CC) test.cpp -O2 -std=c++14 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets -o test.html
