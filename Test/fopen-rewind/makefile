all: build run clean
build:
	gcc fopen.c -o fopen
	gcc rewind.c -o rewind
run:
	time ./fopen 1000
	time ./rewind 1000
clean:
	rm ./fopen
	rm ./rewind