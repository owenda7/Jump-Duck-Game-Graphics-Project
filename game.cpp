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
int score;
Circle c;
Rect ground;
int characterYDirection;
vector<unique_ptr<Shape>> character;
vector<Rect> obstacle;

int JUMP_DIRECTION;
int dy;
int JUMP_TIME;

int DUCK;

bool GAME_OVER;

// adds shapes to vector character to create the main character
void populateCharacter(){
    color green = color(0,.4,.2,1);
    color black = color(0,0,0,1);
    color tan = color(1,.9,.6,1);

    // SHOES (0-1)
    character.push_back(make_unique<Circle>(black,175, 390, 12));
    character.push_back(make_unique<Circle>(black,125, 390, 12));

    // HANDS (2-3)
    character.push_back(make_unique<Circle>(tan,195, 320, 10));
    character.push_back(make_unique<Circle>(tan,105, 320, 10));

    // BODY (4)
    character.push_back(make_unique<Rect>(green,point2D(150,315),90,50));

    // HEAD (5-8)
    character.push_back(make_unique<Circle>(tan,150, 230, 30));
    character.push_back(make_unique<Circle>(black,160, 225, 4));
    character.push_back(make_unique<Circle>(black,140, 225, 4));
    character.push_back(make_unique<Circle>(black,150, 245, 6));
}

// adds shapes to vector obstacle to build the obstacles
void populateObstacle(){
    point2D gnd_obstacle = point2D(700,350);
    point2D air_obstacle = point2D(1400,200);
    color obstacle_color = color(1,.7,.4,1);
    obstacle.push_back(Rect(obstacle_color,gnd_obstacle,100,100));
    obstacle.push_back(Rect(obstacle_color,air_obstacle,100,100));
}

// first function called to initialize graphics
void init(){
    width = 1500;
    height = 500;
    score = 0;
    JUMP_DIRECTION = 0;
    JUMP_TIME = 0;
    DUCK = 0;
    GAME_OVER = false;

    // set ground
    ground.setColor(color(.4,.2,.2,1));
    ground.setCenter(750,450);
    ground.setHeight(100);
    ground.setWidth(1500);

    populateObstacle();
    populateCharacter();
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

    /**** DRAWINGS ****/
    ground.draw();

    for (Rect &r : obstacle) {
        r.draw();
    }

    for (unique_ptr<Shape> &s : character) {
        s->draw();
    }

    glFlush();  // Render now
}

// escape key to quit game
void kbd(unsigned char key, int x, int y) {
    switch(key) {
        // escape
        case 27: {
            glutDestroyWindow(wd);
            exit(0);
            break;
        }
    }
    glutPostRedisplay();
}

// gets up and down arrow key inputs
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

// function checks for collisions
bool isGameOver(Rect r){
    if (r.getCenterY() == 350 && (character[0]->getCenterY()) > 300){
        GAME_OVER = true;
        for (unique_ptr<Shape> &s : character) {
            s->moveY(1000);
        }
        return true;
    } else if ((r.getCenterY() == 200 && (character[5]->getCenterY()) < 250)){
        GAME_OVER = true;
        for (unique_ptr<Shape> &s : character) {
            s->moveY(1000);
        }
        return true;
    }
    return false;
}

// handles object movement
void timer(int dummy) {
    for (Rect &r : obstacle) {
        if (r.getCenterX() < 225 && r.getCenterX() > 100){
            isGameOver(r);
        }
        r.moveX(-(r.getWidth()/10) - score/5);
        if (r.getCenterX() < 1) {
            // choose at random if obstacle will be an air or ground obstacle
            int type  = rand()%2;
            if (type == 0){
                r.setCenter(1400,200);
                score ++;
            } else{
                r.setCenter(1400,350);
                score ++;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

// handles character movement
void timerCharacter(int dummy) {
    if (characterYDirection > 0) {
        if (JUMP_DIRECTION == 0){
            JUMP_DIRECTION = 1;
            if (DUCK == -1){
                /**** UNDUCK LOGIC ****/
                character[0]->moveX(-10);
                character[1]->moveX(10);
                for(int i = 2; i < character.size(); i++){
                    if (i < 5){ character[i]->moveY(-30);}
                    if (i > 4){ character[i]->moveY(-50);}
                }
                DUCK = 0;
            }
        }
    } else if (characterYDirection < 0 && DUCK == 0) {
        /**** DUCK LOGIC ****/
        character[0]->moveX(10);
        character[1]->moveX(-10);
        for(int i = 2; i < character.size(); i++){
            if (i < 5){ character[i]->moveY(30);}
            if (i > 4){ character[i]->moveY(50);}
        }
        DUCK = -1;

        // Check if mid jump to allow for cancel jump
        if(JUMP_DIRECTION == 1){
            JUMP_DIRECTION = -1;
        }
    } else if (JUMP_DIRECTION == 0 && !GAME_OVER && characterYDirection == 0 && character[0]->getCenterY() != 390){
        dy = 390 - character[0]->getCenterY();
        for (unique_ptr<Shape> &s : character) {
            s->moveY(dy);
        }

    }

    /**** JUMP LOGiC ****/
    if(JUMP_DIRECTION == 1){
        dy = (-20 + JUMP_TIME) - (score);
        if(character[0]->getCenterY() < 190 || dy > 0){
            JUMP_DIRECTION = - 1;
            JUMP_TIME = 0;
        } else{
            for (unique_ptr<Shape> &s : character) {
                s->moveY(-20 + JUMP_TIME);
            }
            JUMP_TIME ++;
        }
    }
    if(JUMP_DIRECTION == -1){
        dy = 5 + JUMP_TIME;
        if(character[0]->getCenterY() > 385) {
            JUMP_DIRECTION = 0;
            characterYDirection = 0;
            JUMP_TIME = 0;
        } else{
            for (unique_ptr<Shape> &s : character) {
                s->moveY(dy);
            }
            JUMP_TIME++;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timerCharacter, dummy);
}


/* Main function */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);  // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(250, 180); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Jump and Duck Game" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    glutKeyboardFunc(kbd);

    // handles timer
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, timerCharacter, 0);

    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}