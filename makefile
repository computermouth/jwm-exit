jwm-exit:
	gcc -o jwm-exit jwm-exit.c `pkg-config --libs --cflags gtk+-2.0`
