# EE319K_Lab10

Inputs:

  1 slide pot (PD2):
  
		position of the slide pot directly maps to the y level of the player
  
  2 directional buttons (PE0 and PE1)
		
		will change the player's x coordinate
		
  1 shoot button
		
		moves along the same y level and for a certain distance in the x level
  
  
Outputs:

  Sound
  
  LCD
  
Timers:

  Systick checks player input
  
  Timer0 tracks sound output
  
  Timer1 tracks creature interactions
  
  Busy-Wait LCD
  
  
 Gameplay:
  static background
  
  1 human. panics and runs around
  
  2 enemies
  
  Lander:
  
    goes to a humans x coordinate, picks them up
    
  Mutant:
  
    moves randomly, tries to reach players y level and shoot them
  
  
