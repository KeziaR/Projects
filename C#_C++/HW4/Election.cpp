///////////////////////////////////////////////
/*Official Name : Kezia Regis
*
* Call me : Kezia
*
* E - mail : knregis@syr.edu
*
*Assignment:  Assignment 4
*
*Environment / Compiler : Visual Studio Community 2022
*
*Date submitted : 
*
*References :
https://community.khronos.org/t/how-to-draw-a-room-with-walls/20148

*Interactions :
cout << "Press up/down arrows to step forward/backward" << endl;
    cout << "Press right/left arrows to rotate" << endl;
    cout << "Press h to turn on/off the headlamp" << endl
        cout << "Press d to open/close door." << endl;
*/
////////////////////////////////////////////////

#include <cmath>
//for sin, cos
#include <iostream>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

using namespace std;

// Globals.
float origin[] = { 0.0, 0.0, 0.0, 1.0 };
static float spotAngle = 20.0; // Spotlight cone half-angle.
static float spotExponent = 2.0; // Spotlight exponent = attenuation.
static float spotAngle1 = 10.0; // Spotlight cone half-angle.
static float spotExponent1 = 2.0; // Spotlight exponent = attenuation.
static float spotAngle2 = 10.0; // Spotlight cone half-angle.
static float spotExponent2 = 2.0; // Spotlight exponent = attenuation.
bool light0control = 0;
bool light1control = 0;
bool light2control = 0;

int seecone = 1;
int seecir = 1;


static float valX = 0, valY = 0, valZ = 0;
static float angle = 0;  //angle facing
static float stepsize = 5.0;  //step size
static float turnsize = 10.0; //degrees to turn


static float d = 1.0; // Diffuse and specular white light intensity.
static float p = 1.0; // Positional light?
int seeCone = 1;//MJB
static int open = true;

static float isAnimate = 0.0f; // Animated?
static float speed = 0.2f;

/*https://community.khronos.org/t/how-to-draw-a-room-with-walls/20148 and DifferentMaterials.cpp
lines: 111-113 */

void walls() {

    glPushMatrix();
    float matAmbAndDifCol1[] = { 1.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol1);
    glPopMatrix();
 
    //back wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-40, -10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, 10, 25);
    glVertex3f(-40, 10, 25);
    

    glPushMatrix();
    float matAmbAndDifCol2[] = { 1.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol2);
    glPopMatrix();
    
    // front wall
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-40, -10, -25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, 10, -25);
    glVertex3f(-40, 10, -25);
    

    glPushMatrix();
    float matAmbAndDifCol3[] = {0.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol3);
    glPopMatrix();

    // right wall
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(10, 10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, 10, -25);
    


    glPushMatrix();
    float matAmbAndDifCol4[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol4);
    glPopMatrix();
    
    // left wall
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40, 10, 25);
    glVertex3f(-40, -10, 25);
    glVertex3f(-40, -10, -25);
    glVertex3f(-40, 10, -25);
    glPopMatrix();

    glEnd();

    
}

/*https://community.khronos.org/t/how-to-draw-a-room-with-walls/20148 */

void floor() {

    int i;
    float z;

    glPushMatrix();
    float matAmbAndDifCol5[] = { .32, 0.5, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol5);
    glPopMatrix();

    //floor
    glBegin(GL_QUADS);
    glColor3f(.32, 0.5, 1.0);
    glVertex3f(-40, -10, -25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, -10, 25);
    glVertex3f(-40, -10, 25);
    glEnd();


 
}

/* DifferentMaterials.cpp
lines: 85-96 */

void outside() {
    glPushMatrix();
    glColor3f(0, 1, 0); //green
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    glTranslatef(-25, -7, -15);
    glutSolidTeapot(3);
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}


/*https://community.khronos.org/t/how-to-draw-a-room-with-walls/20148 */

void ceiling() {

    glPushMatrix();
    float matAmbAndDifCol5[] = { 0.0, 0.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol5);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-40, 10, -25);
    glVertex3f(10, 10, -25);
    glVertex3f(10, 10, 25);
    glVertex3f(-40, 10, 25);
    glEnd();
}


void wall2(){

    glPushMatrix();
    float matAmbAndDifCol6[] = { 1.0, 0.2, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol6);
    glPopMatrix();

    //back wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.2, 1.0);
    glVertex3f(-40, -10, 5);
    glVertex3f(10, -10, 5);
    glVertex3f(10, 10, 5);
    glVertex3f(-40,10, 5);

    glEnd();
}

void wall3() {

    glPushMatrix();
    float matAmbAndDifCol7[] = { 0.7, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol7);
    glPopMatrix();

    // top wall
    glBegin(GL_QUADS);
    glColor3f(.7, 0, 0);
    glVertex3f(-10, -3, 5);
    glVertex3f(-10, -10, 5);
    glVertex3f(-10, -10, -25);
    glVertex3f(-10, -3, -25);

    glPushMatrix();
    float matAmbAndDifCol8[] = { 0.7, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol8);
    glPopMatrix();

    // bottom wall
    glColor3f(.7, 0, 0);
    glVertex3f(-10, 10, 5);
    glVertex3f(-10, 3, 5);
    glVertex3f(-10, 3, -25);
    glVertex3f(-10, 10, -25);

    glPushMatrix();
    float matAmbAndDifCol9[] = { 0.7, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol9);
    glPopMatrix();

    //right wall
    glColor3f(.7, 0, 0);
    glVertex3f(-10, 10, -25);
    glVertex3f(-10, -10, -25);
    glVertex3f(-10, -10, -15);
    glVertex3f(-10, 10, -15);

    glPushMatrix();
    float matAmbAndDifCola[] = { 0.7, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCola);
    glPopMatrix();

    // left wall
    glColor3f(.7, 0, 0);
    glVertex3f(-10, 10, -5);
    glVertex3f(-10, -10, -5);
    glVertex3f(-10, -10, 5);
    glVertex3f(-10, 10, 5);
    glPopMatrix();


    glEnd();
}

/* Collector.cpp & MJBclownW2timers.cpp
*
lines: 40-52*/

void doormotion(int value) {
    if (isAnimate < 1.0)
        isAnimate = -1.0f;

    isAnimate -= speed;

    glutPostRedisplay();
    glutTimerFunc(100, doormotion, 0);
    //glutPostRedisplay();

}


void door1() {
    
    glPushMatrix();
    float matAmbAndDifCol9[] = { 0.725, 0.578, 0.1, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol9);
    glPopMatrix();

    glBegin(GL_QUADS);
    glColor3f(.725, 0.578, .1);
    glVertex3f(.1, -10, 4.5);
    glVertex3f(10, -10, 4.5);
    glVertex3f(10, 10, 4.5);
    glVertex3f(.1, 10, 4.5);
    
    glEnd();



}

void door2() {

    glPushMatrix();
    float matAmbAndDifCol9[] = { 0.725, 0.578, 0.1, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol9);
    glPopMatrix();

    glBegin(GL_QUADS);

    glColor3f(.725, 0.578, .1);
    glVertex3f(-.1, -10, 4.5);
    glVertex3f(-10, -10, 4.5);
    glVertex3f(-10, 10, 4.5);
    glVertex3f(-.1, 10, 4.5);
    glEnd();



}

/* collector.cpp (previous project)*/

void drawDisc(float R, float X, float Y, float Z)
{
    float t;
    int i;


    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(X, Y, Z);
    for (i = 0; i <= N; ++i)
    {
        t = 2 * PI * i / N;
        glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
    }
    glEnd();
}

void button() {

    glPolygonMode(GL_FRONT, GL_FILL);

    // Upper left circular annulus: the white disc overwrites the blue disc.
    //glColor(0.752941, 0.752941, 0.752941)
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(1, 10, 9);
    glRotatef(120.0, 0.0, -60.0, -10.0);
    drawDisc(1.0, 10.0, 10.0, -5.0);
    glColor3f(0.29, 0.75, 0.941);
    drawDisc(1.2, 10.0, 10.0, -5.0);
    glPopMatrix();
    glEnd();

    /*glVertex3f(10, 10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, 10, -25);*/

    

}

/*lightAndMaterial2.cpp and spotlightModified.cpp
lines: 133-142 */

void lights2() {

    // headlamp
    float dir2X = sin(angle * PI / 180);
    float dir2Z = cos(angle * PI / 180);

    float lightPos2[] = { valX, valY, valZ, 1.0f };
    float lightDir2[] = { dir2X, -1.0f, dir2Z };

    //float lightAmb2[] = { 0.0, 0.0, 0.0, 1.0 };
    //float lightDifAndSpec2[] = { 1.0, 1.0, 1.0, 1.0 };
    //float matSpec2[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent2);

    // Material properties for all objects
    //glLightfv(GL_LIGHT2, GL_DIFFUSE, matSpec2);//MJB
    //glLightfv(GL_LIGHT2, GL_SPECULAR, matSpec2);//MJB;


    glDisable(GL_LIGHT2);


    //glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);

    if (seecone) {

        seecone = !seecone;

        glPushMatrix();
        glRotatef(0, lightDir2[0], 0, lightDir2[2]);
        glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
        glColor3f(1.0, 1.0, 1.0);
        glutSolidCone(3.0 * tan(spotAngle2 / 180.0 * PI), 3.0, 20, 20);
        glPopMatrix();

        glEnable(GL_LIGHT2);


    }

    glEnd();
}
  
 void lights0() {
//sun

    float lightPos0[] = { valX, valY, valZ, 1.0f };

    float lightAmb0[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    float matSpec0[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    // Material properties for all objects
    glLightfv(GL_LIGHT0, GL_DIFFUSE, matSpec0);//MJB
    glLightfv(GL_LIGHT0, GL_SPECULAR, matSpec0);//MJB;


    //glDisable(GL_LIGHT0);


    if (seecir) {

        //seecir = !seecir;

        glColor3f(1, 1, 1);//lightbulb color
        glPushMatrix();
        glTranslated(-25, 15, -10);
        glutSolidSphere(1, 10, 10);  //at the origin
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glPopMatrix();

        glEnable(GL_LIGHT0);

    }


    
    glutPostRedisplay();

}


void drawScene(void)
{
    //fill background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    //glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   // gluLookAt(5, 20, 50,2,1, 9, 0, 1, 0);
    //glFrustum(5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

    // Place camera.
    gluLookAt(valX, valY, valZ, valX + sin(angle * PI / 180), 
        valY, valZ + cos(angle * PI / 180),0, 1, 0);
// ______________________________________________________
  // button
    /*glPushMatrix();
    if (button){
    glTranslatef(isAnimate, 0.0f, 0.0f);
    else {
    }
    door();
    glPopMatrix(); */

// Animates clouds
    glPushMatrix();
    glTranslatef(isAnimate, 0.0f, 0.0f);
    door1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(isAnimate, 0.0f, 0.0f);
    door2();
    glPopMatrix();
// ______________________________________________________
    walls();
    ceiling();
    floor();
    wall2();
    wall3();
    outside();
    door1();
    //door2();
    //button();
    lights0();
    lights2();

// ______________________________________________________
//headlamp
    glPushMatrix();
    if (light0control) {
        glEnable(GL_LIGHT0);
    }
    else {
        glDisable(GL_LIGHT0);
    }
    glPopMatrix();
// ______________________________________________________
// sun 
    glPushMatrix();
    if (light2control) {
        glEnable(GL_LIGHT2);
    }
    else {
        glDisable(GL_LIGHT2);
    }
    glPopMatrix();

// ______________________________________________________

 glutSwapBuffers();
 glFlush();
}

void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press up/down arrows to step forward/backward" << endl;
    cout << "Press right/left arrows to rotate" << endl;
    cout << "Press h to turn on/off the headlamp" << endl;
    cout << "Press c to make the card float up." << endl;
    cout << "Press G/g increases/decreases the global ambient light" << endl;
    cout << "Press c for collision detection." << endl;
    cout << "Press d to open/close door." << endl;
    cout << "Press w to open/close shade." << endl;
    cout << "Press r  makes the card rotate to read." << endl;



}

/*lightAndMaterial2.cpp
lines:132-133 */

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'h':
        if (light0control)
        light0control = 0;
        else light0control = 1;
        glutPostRedisplay();
        break;
    case 'd':
        if (isAnimate)
            isAnimate = 0;
        else
            isAnimate = 1;
        glutPostRedisplay();
    default:
        break;
    }
}
/*spaceTravel.cpp
lines: 280-313*/

void specialKeyInput(int key, int x, int y)
{
    

    switch (key) {
    case GLUT_KEY_UP: //forward
        valX += stepsize * sin(angle * PI / 180);
        valZ += stepsize * cos(angle * PI / 180);
        break;
        break;
    case GLUT_KEY_DOWN: //back
        valX -= stepsize * sin(angle * PI / 180);
        valZ -= stepsize * cos(angle * PI / 180);
        break;
    case GLUT_KEY_RIGHT: //turn right
        angle = angle - turnsize;
        break;
    case GLUT_KEY_LEFT: //turn left
        angle = angle + turnsize;

        break;
    }//end switch

    // Angle correction.
    if (angle > 360.0) angle -= 360.0;
    if (angle < 0.0) angle += 360.0;

    glutPostRedisplay();
}

void setup(void)
{
    //background color 
    glClearColor(0.309804, 0.309804, 0.184314, 0.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing

// ______________________________________________________
//  Lights
    // Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0); // Headlamp
    glEnable(GL_LIGHT1); // roomlamp
    glEnable(GL_LIGHT2); // sun
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
// ______________________________________________________
//  global lights
// 
    //float matAmbAndCol[] = { 1.5, .5, .2, 1.0 };
    float lightAmba[] = {0.0, 0.0, 0.0, 1.0};
    float lightDifAndSpeca[] = { 1.0, 1.0, 1.0, 1.0 };
    float globAmba[] = { 0.05, 0.05, 0.05, 1.0 };

    // Material property vectors for all objects

    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 50.0 };

    // Material properties for all objects
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmba); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
// ______________________________________________________
//  HeadLamp


    //Postion can't go here, because it is changeable
// ______________________________________________________
//  sun


/*// Cull back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); */

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}


void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);

}





// Main routine.
int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    // --------------------------------------------------------------

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Election Day");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(30, doormotion, 0);
    glutMainLoop();


    return 0;

}