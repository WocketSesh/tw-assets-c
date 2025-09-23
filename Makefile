CC = gcc
SRC = $(wildcard src/*.c include/*.c)
OUT = build/tw-assets.exe


all: build $(OUT)

build:
	mkdir build 2>nul || exit 0

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

run: all
	$(OUT)

clean:
	del /q build\tw-assets.exe

