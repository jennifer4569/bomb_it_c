all: main.o front_end.o bomb_player.o
	gcc -o bomb_it.exe main.o front_end.o bomb_player.o -lcurses

front_end.o: front_end.c bomb_it.h
	gcc -c front_end.c -lcurses

bomb_player.o: bomb_player.c bomb_it.h
	gcc -c bomb_player.c -lcurses

main.o: main.c bomb_it.h
	gcc -c main.c bomb_it.h -lcurses

main2.o: main2.c bomb_it.h
	gcc -c main2.c bomb_it.h -lcurses

clean:
	-rm -rf *.o
	-rm -rf *~
	-rm -rf *.gch
	-rm -rf bomb_it.exe

run: all
	./bomb_it.exe

single: all
	./bomb_it.exe -s

rules: all
	./bomb_it.exe -r
