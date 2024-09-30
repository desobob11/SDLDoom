compileshit:
	gcc *.c -o main `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -F/Library/Frameworks -framework SDL2 -framework SDL2_image -lm
	./main
