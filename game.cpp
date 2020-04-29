#include "circle.h"
#include "game.h"
#include "rect.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
Circle c;
Rect ground;
int characterYDirection;
vector<unique_ptr<Shape>> character;
vector<Rect> obstacle;

void populateCharacter(){

}

void populateObstacle(){
    point2D gnd_obstacle = point2D(800,325);
    point2D air_obstacle = point2D(1400,75);
    color obstacle_color = color(1,.7,.4,1);
    obstacle.push_back(Rect(obstacle_color,gnd_obstacle,150,150));
    obstacle.push_back(Rect(obstacle_color,air_obstacle,150,150));
}

// first function called to initialize graphics
void init(){
    width = 1500;
    height = 500;

    // set ground
    ground.setColor(color(.4,.2,.2,1));
    ground.setCenter(750,450);
    ground.setHeight(100);
    ground.setWidth(1500);

    populateObstacle();
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
    glViewport(0, 0, 2*width, 2*height); // DO NOT CHANGE THIS LINE

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

    ground.draw();

    for (Rect &r : obstacle) {
        r.draw();
    }

    glFlush();  // Render now
}


void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            characterYDirection = -1;
            break;
        case GLUT_KEY_UP:
            characterYDirection = 1;
            break;
    }

    glutPostRedisplay();
}


void timer(int dummy) {
    for (Rect &r : obstacle) {
        r.moveX(-r.getWidth()/25);
        if (r.getCenterX() < 1) {
            // choose at random if obstacle will be an air or ground obstacle
            int type  = rand()%2;
            if (type == 0){
                r.setCenter(1400,75);
            } else{
                r.setCenter(1400,325);
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/**
void timerSnowperson(int dummy) {

    if (characterYDirection < 0) {
        // Move the snowperson left using ~polymorphism~
        for (unique_ptr<Shape> &s : character) {
            s->moveX(-1);
        }
    } else if (characterYDirection > 0) {
        // Move the snowperson right using ~polymorphism~
        for (unique_ptr<Shape> &s : character) {
            s->moveX(1);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timerSnowperson, dummy);
}

**/
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(250, 180); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Graphics Examples!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles timer
    glutTimerFunc(0, timer, 0);
    //glutTimerFunc(0, timerSnowperson, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}