all: main.exe clean

main.exe: main.o
	gcc -o main.exe main.o
	./main.exe

main.o: main.c
	gcc -c main.c

clean:
	rm main.o main.exe
