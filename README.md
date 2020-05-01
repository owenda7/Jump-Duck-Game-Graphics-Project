# OA-Final-Project-Graphics

For the graphics portion of my final project, I will be creating a simple jump and duck
game (similar to that of the google chrome dinosaur loading game). This will use polymorphism
for the character, made from various shapes which inherit a parent Shape class. There will also
be an Obstacle class for creating obstacle objects for the character to dodge. To dodge items,
the character will be controlled by the up and down keys, up to jump and down to duck. The
character will only be able to move along the y axis while objects move towards the character
on the x axis. 

# Classes: 

* Shape 
    * Circle
    * Rect

* Game

Note: After delving into this project, I decided to simply use the Rect class to build objects that were
identical for both floor and ceiling objects as opposed to giving this its own class for simplicity of testing
object collisions and randomization.

# How to play:

* Compile and run game.cpp
* Press the up key to jump and the down key to duck
    * Note: To unduck the player must jump, the player can also cancel a jump by ducking mid jump
* Once the character collides with a block, the character will dissapear ending the game
* To quit the game, hit the escape key 
