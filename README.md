# EE319K_Lab10

Inputs:

  1 slide pot (PD2):
  
		position of the slide pot directly maps to the y level of the player
  
  2 directional buttons (PE0 and PE1)
		
		will change the player's x coordinate
		
  1 shoot button (PE2)
		
		moves along the same y level and for a certain distance in the x level
  
  
Outputs:

  Sound
  
  LCD
- some LEDs, don't know that theyll do yet but we can figure that out
  
Timers:

  Systick checks player input
  
  Timer0 tracks sound output
  
  Timer1 tracks creature interactions
  
  Timer2 will be for animation and keeping track of game time
  
  Busy-Wait LCD
  
  
 Gameplay:
  static background
  
  1 human. panics and runs around
  
  3 enemies for level 1 and increases each level
  
  Lander:
  
    goes to a humans x coordinate, picks them up
    
  Mutant:
  
    moves randomly, tries to reach players y level and shoot them
  
  
