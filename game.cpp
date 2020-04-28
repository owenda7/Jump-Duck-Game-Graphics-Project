#include "circle.h"
#include "game.h"
#include "rect.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
vector<unique_ptr<Shape>> character;
int characterYDirection;
void populateCharacter() {
    // Three white circles
    // red, green, blue, alpha, x, y, radius
    character.push_back(make_unique<Circle>(1, 1, 1, 1, 100, 400, 100));
    character.push_back(make_unique<Circle>(1, 1, 1, 1, 100, 250, 75));
    character.push_back(make_unique<Circle>(1, 1, 1, 1, 100, 130, 50));
    // Black buttons
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 100, 230, 10));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 100, 260, 10));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 100, 290, 10));
    // Eyes
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 80, 120, 8));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 120, 120, 8));
    // Mouth
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 75, 145, 5));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 85, 155, 5));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 100, 160, 5));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 115, 155, 5));
    character.push_back(make_unique<Circle>(0, 0, 0, 1, 125, 145, 5));
}

// first function called to initialize graphics
void init(){
    srand(time(0));
    width = 1000;
    height = 400;
    populateCharacter();
    characterYDirection = 0;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.83f, 0.9f, 1.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */
    // ground shape
    glColor3f(0.34f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glTexCoord2f(-1.0f, -0.5f);
    glTexCoord2f(1.0f, -0.5f);
    glTexCoord2f(1.0f, -1.0f);
    glTexCoord2f(-1.0f, -1.0f);
    glEnd();

    // Draw the character with ~polymorphism~
    for (unique_ptr<Shape> &s : character) {
        s->draw();
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
            characterYDirection = 1;
            break;
        case GLUT_KEY_DOWN:
            characterYDirection = -1;
            break;
    }

    glutPostRedisplay();
}

void timer(int dummy) {
/*
    for (Rect &r : ) {
        r.moveX(r.getWidth());
        if (r.getCenterX() > (width + r.getWidth())) {
            // TODO: set obstacle random up or down (2 specific locations)
            r.setCenter(rand() % int(width), -r.getRadius());
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
    */
}

void timerCharacter(int dummy) {
    if (characterYDirection < 0) {
        for (unique_ptr<Shape> &s : character) {
            s->moveX(-5);
        }
    } else if (characterYDirection > 0) {
        jump();
    }

    glutPostRedisplay();
    glutTimerFunc(30, timerCharacter, dummy);
}

void jump(){
    int gravity = -10;
    int jumpCounter;

    //while()
    for (unique_ptr<Shape> &s : character) {
        s->moveY(1);
    }
}

void duck(){

}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(250, 180); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    glutCreateWindow("Jump and Duck game" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles timer
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timerCharacter, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}