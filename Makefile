CC=clang

all:
	$(CC) src/main.c -o ./bin/myfamily `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.1`
