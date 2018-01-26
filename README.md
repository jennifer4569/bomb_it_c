# Bomb It C!
### by Connie Lei, Charles Weng, and Jennifer Zhang
**Systems Level Programming, Period 4** 


## Description
Our program mimics the popular children's game, Bomb It!

Players will be able to move around, dropping bombs to destroy obstacles and kill other players. The goal of the game is to be the last one standing. Features will include powerups and multiplayer. 

## Required Libraries
In order to use our project, you must have __ncurses__ installed. 

If you do not already have ncurses installed, please open your terminal, and type in the following command:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
  
## Instructions on how to use project
To run our code, open your terminal, and type in the following commands:
```
git clone https://github.com/jennifer4569/bomb_it_c
cd bomb_it_c
make
```

From here, there are several options for the commands you can use:

* Host a new game

      ./bomb_it.exe -h
      make host
      
* Connect to the game with the host's IP address
	   	
      ./bomb_it.exe -c 149.89.150.101
      
* Shows you all the rules of the game
		 
      ./bomb_it.exe -r
      make rules

### RULES:
**Controls:**
  * *WASD*: Move your character
  * *Spacebar*: Drop bomb
  
**How to play:**
	
  The goal of the game is to be the last one standing.
  
  Move around and kill other players by bombing them. There will be obstacles in the way, some bombable, and others indestructable. Powerups will appear randomly on the map. Step on them to get the powerup.
		
**Ascii Representations:**
* *P* : Player (Different Colors)
* *O* : Bomb
* *#* : Bomb explosion range (solid red)
* *#* : Indestructable obstacle (solid white)
* *#* : Bombable obstacle (white)

* **Powerups:**
  * *+* : Increase maximum bomb's limit
  * *\** : Increase bomb power (increasing its explosion range)
  * *m* : Add gloves (for the rest of the game, you can push bombs around -- while in mid-push, the bomb's timer is frozen.)


