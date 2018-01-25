all: main.o front_end.o bomb_player.o
	gcc -o bomb_it.exe main.o front_end.o bomb_player.o

front_end.o: front_end.c bomb_it.h
	gcc -c front_end.c

bomb_player.o: bomb_player.c bomb_it.h
	gcc -c bomb_player.c

main.o: main.c bomb_it.h
	gcc -c main.c bomb_it.h

clean:
	-rm -rf *.o
	-rm -rf *~
	-rm -rf *.gch
	-rm -rf bomb_it.exe

run: all
	./bomb_it.exe

host: all
	./bomb_it.exe -h

connect: all
	./bomb_it.exe -c

rules: all
	./bomb_it.exe -r

maps: all
	./bomb_it.exe -m

test: all
	gcc -o testS networking.c bomb_it.h main2.c
