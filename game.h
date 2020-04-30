#ifndef OA_FINAL_PROJECT_GRAPHICS_GAME_H
#define OA_FINAL_PROJECT_GRAPHICS_GAME_H

#include "circle.h"

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init();

// Initialize OpenGL Graphics
void initGL();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void display();

// purely for escape key
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Function handles jump and gravity
void jump();

// Calls itself after a specified time
void timer(int dummy);

void timerCharacter(int dummy);


#endif //OA_FINAL_PROJECT_GRAPHICS_GAME_H
