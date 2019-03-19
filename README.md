# Bomb It C!
### by Connie Lei, Charles Weng, and Jennifer Zhang


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

* Start a single player game

      ./bomb_it.exe -s
      make single

* Set up a multiplayer game

      make multiplayer

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
* *-* : Bomb explosion range
* *#* : Indestructable obstacle
* *=* : Bombable obstacle

* **Powerups:**
  * *+* : Increase maximum bomb's limit
  * *\** : Increase bomb power (increasing its explosion range)
  * *m* : Add gloves (for the rest of the game, you can push bombs around -- while in mid-push, the bomb's timer is frozen.)


---
---


## Known Bugs/Unresolved Issues:
* Bomb explosion doesn't always kill players
  * Since the bomb explosion time is so short, the players sometimes step on the explosion range at the right time so that they seemingly die, but they don't.
* Bomb explosion range glitches out
  * Doesn't always go through all directions
* Keyboard interception puts each key into a queue: So if you spam a button too much, you have to wait a long time before you can move to a different direction again
* Tried implimenting multiplayer features, but could not get networking to work
  * Trying to connect with more than four players bugs out the player's terminal
* Ascii characters make it somewhat difficult to visually see the gameplay

## Attempted:
* Coloring features
* Map creation/selection features
* Multiplayer features

## Mid-Development Design Changes:
* Removed coloring features
  * Changed ascii representations of each character to reflect that
* Didn't implement creating/selecting maps
* Didn't implement glove powerup features
* Changed the way powerups were dropped (now it has a 4% chance of appearing on a SAFE space)
* Didn't implement multiplayer features

## Files & Function Headers
### Header Files

* **bomb\_it.h**: includes all the headers required for our code.

### .c Files

* **bomb\_player.c**: includes all the definitions of functions necessary for the player, including the bomb functions; mostly used for updating the map

* **front\_end.c**: includes all the definitions of functions necessary for the front end, including display map

* **main.c**: includes all the defintions required for initializing the game, and initializes the game

**NOT USED IN FINAL STATE**
* **main2.c**: backup for networking in case it breaks

* **networking.c**: networking code

### .txt Files

* **instructions.txt**: includes the instructions on how to start the game using flags

* **rules.txt**: includes the rules of the game, including controls, how to play, and ascii representations

* **maps/ \*.txt**: includes all the maps we made for 
  * **maps/map4.txt**: the final map
  
* **DESIGN.txt**: the design of the project, includes our plans (created before we started, not updated to current state: see Mid-Development Design Changes)

* **devlog.txt**: the devlog, including unresolved issues, mid-development design changes, and lessons learned
