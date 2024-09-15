///////////////////////////////////////////////
/*Official Name : 
*
* Call me :
*
* E - mail : 
*
*Assignment:  Assignment 2
*
*Environment / Compiler : Visual Studio Community 2022
*
*Date submitted : 
*
*References :


https://www.opengl.org/resources/libraries/glut/spec3/node81.html
I was not sure how glutsolidsphere worked
https://followtutorials.com/2012/05/rendering-spheres-glutsolidsphere-and-glutwiresphere-using-glut-in-c-a-sample-program.html
I used this to help me structure the sphere so it would appear in frustum
https://stackoverflow.com/questions/16803044/what-does-the-glfrustum-function-do
I was not sure what frustum was needed for in the display window
*Interactions : 
1. "Right click for menu options."
2. 
*/
////////////////////////////////////////////////

#include <cmath>
//for sin, cos
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

using namespace std;

// Globals.
static int GUIWindow,RoseWindow;
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static float square_color[3] = { 1.0, 0.0, 0.0 }; // Color of the square.
//static double xmax = 5.0, ymax = 5.0;
//static int viewcount = 0;
//atic int shape;
int GreenBall = 1;
static GLsizei width, height;
static int isAnimate = 0; // Animated?
static float angle = 0.0;

/* circularAnnulusesMod.cpp:
36-60
*/
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

void writeBitmapString(void* font, const char* string)
{
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

/* circularAnnulusesMod.cpp: 63-87 */

void drawSceneGUI(void)

{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glutSetWindow(GUIWindow);
    float angle;
    int i;
//_______________________________________
// PlanetCheckbox
  
    glColor3f(0.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glRectf(355, 330, 380, 350);
    glRectf(320, 220, 345, 245);
    // Draw black boundary.
    glColor3f(0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(320, 220, 345, 245);

    glFlush();
  



// Radio Buttons
// ----------------------------------------------------------

// TotalBox
    glPolygonMode(GL_FRONT, GL_FILL);

    // Upper left circular annulus: the white disc overwrites the blue disc.
    //glColor(0.752941, 0.752941, 0.752941)
    glColor3f(1.0, 1.0, 1.0);
    drawDisc(5.0, 75.0, 350.0, 0.0);
    glColor3f(0.752941, 0.752941, 0.752941);
    drawDisc(10.0, 75.0, 350.0, 0.0);
  
    glutSwapBuffers();
    glFlush();
// AnnularBox
   
  
    glPolygonMode(GL_FRONT, GL_FILL);
  
    glColor3f(1.0, 1.0, 1.0);
    drawDisc(5.0, 75.0, 285.0, 0.0);
    glColor3f(0.752941, 0.752941, 0.752941);
    drawDisc(10.0, 75.0, 285.0, 0.0);
    glutSwapBuffers();
    glFlush();

// PartialBox
    glPolygonMode(GL_FRONT, GL_FILL);

    // Upper left circular annulus: the white disc overwrites the blue disc.
    glColor3f(1.0, 1.0, 1.0);
    drawDisc(5.0, 75.0, 185.0, 0.0);
    glColor3f(0.752941, 0.752941, 0.752941);
    drawDisc(10.0, 75.0, 185.0, 0.0);
    glutSwapBuffers();
    glFlush();
// NoneBox
    glPolygonMode(GL_FRONT, GL_FILL);

    // Upper left circular annulus: the white disc overwrites the blue disc.
    glColor3f(1.0, 1.0, 1.0);
    drawDisc(5.0, 75.0, 120.0, 0.0);
    glColor3f(0.752941, 0.752941, 0.752941);
    drawDisc(10.0, 75.0, 120.0, 0.0);
    glutSwapBuffers();
    glFlush();

    // Write labels.
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(105.0, 350.0, 0.0);
    writeBitmapString((void*)font, "Total Eclispe");
    glRasterPos3f(105.0, 285.0, 0.0);
    writeBitmapString((void*)font, "Annular Eclispe");
    glRasterPos3f(105.0, 185.0, 0.0);
    writeBitmapString((void*)font, "Partial Eclispe");
    glRasterPos3f(105.0, 120.0, 0.0);
    writeBitmapString((void*)font, "None");
    glRasterPos3f(260.0, 230.0, 0.0);
    writeBitmapString((void*)font, "Planet");

    glFlush();
   
    glutSwapBuffers();
}



// -----------------------------------------------------------------------
// A rotating planet with wiresphere

void increaseAngle(void)
{
    angle += 5.0;
    if (angle > 360.0) angle -= 360.0;
    glutPostRedisplay();
}

/* rotatingHelix2.cpp - 32-54
MJBBasicTransformations.cpp - 137-149*/
void drawSceneRose(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glutSetWindow(RoseWindow);

    GLfloat angle = -90;
    int i;
    int x;
    int y;
    int stars = 1 ;

// Rotating Circle Drawing

    if (GreenBall == true)
        {
        glColor3f(0.0, 1.0, 0.0);

        glPushMatrix();

        glTranslatef(10.0, -2.0, -25.0);

        glRotatef(angle, 1.0, 0.0, 0.0);
        glTranslatef(10.0, 2.0, 25.0);

        glutWireSphere(5, 40, 7);

        glPopMatrix();
        glutSwapBuffers();
        glFlush();
    }


// drawPartial
    // Top sphere
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(10.0, -15.0, -22.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(10.0, 15.0, 22.0);
    glutSolidSphere(6, 20, 8);
    glPopMatrix();
    glutSwapBuffers();

    // Under sphere

    glColor3f(0.8, 0.498039, 0.196078);
    glPushMatrix();
    glTranslatef(10.0, -20.0, -25.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(10.0, 20.0, 25.0);
    glutSolidSphere(8, 20, 8);
    glPopMatrix();
    glutSwapBuffers();
    glFlush();

//drawAnnular
    // Top Sphere
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-17.0, 0.0, 0.0);
    glTranslatef(0.0, -18.0, -22.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 15.0, 22.0);
    glutSolidSphere(5.9, 20, 8);
    glPopMatrix();
    glutSwapBuffers();

    // Under sphere

    glColor3f(0.8, 0.498039, 0.196078);;
    glPushMatrix();
    glTranslatef(-17.0, 0.0, 0.0);
    glTranslatef(-3.0, -20.0, -25.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 20.0, 25.0);
    glutSolidSphere(8, 20, 8);
    glPopMatrix();
    glutSwapBuffers();
    glFlush();

//drawTotal
    // Top Sphere
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -18.0, -22.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 15.0, 22.0);
    glutSolidSphere(6.56, 20, 8);
    glPopMatrix();
    glutSwapBuffers();

    // Under sphere

    glColor3f(0.8, 0.498039, 0.196078);
    glPushMatrix();
    glTranslatef(0.0, -20.0, -25.0);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 20.0, 25.0);
    glutSolidSphere(8, 20, 8);
    glPopMatrix();
    glutSwapBuffers();
    glFlush();

// drawNone!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    glPolygonMode(GL_FRONT, GL_FILL);

    // Upper left circular annulus: the white disc overwrites the blue disc.
    glColor3f(1.0, 1.0, 1.0);
    drawDisc(5.0, 75.0, 185.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    drawDisc(10.0, 75.0, 185.0, 0.0);
    glutSwapBuffers();
    glFlush(); //send drawing to the screen
}

/*/ menus.cpp - 80-116*/
void top_menu(int id)
{
    if (id == 1) exit(0);
}

// The sub-menu callback function.
void color_menu(int id)
{
    if (id == 2)
    {
        square_color[0] = 1.0; square_color[1] = 0.0; square_color[2] = 0.0;
    }
    if (id == 3)
    {
        square_color[0] = 0.0; square_color[1] = 0.0; square_color[2] = 1.0;
    }
    glutPostRedisplay();
}

// Routine to make the menu.
void makeMenu(void)
{
    // The sub-menu is created first (because it should be visible when the top
    // menu is created): its callback function is registered and menu entries added.
    int sub_menu;
    sub_menu = glutCreateMenu(color_menu);
    

    // The top menu is created: its callback function is registered and menu entries,
    // including a submenu, added.
    glutCreateMenu(top_menu);
    
    glutAddMenuEntry("Quit", 1);

    // The menu is attached to a mouse button.
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setupGUI(void)
{
    //background color 
    glClearColor(0.309804, 0.309804, 0.184314, 0.0);
}

void setupRose(void)
{
    //DarkOliveGreen background color 
    glClearColor(0, 0, 0, 0.0);
}

/* canvas.cpp 362-376*/

// OpenGL window reshape routine.
void resizeGUI(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Aspect ratio matches the window.
    glOrtho(0.0, 400.0, 0.0, 400.0, -1.0, 1.0);

    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
}

/*rotatingHelix2.cpp - 64-71*/

void resizeRose(int w, int h)
{ 
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

/* windowsWMouseClickOptions.cpp 146-159*/

void GUIMouseSControl(int button, int state, int x, int y)
{

    int yy;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glRectf(320, 220, 345, 245);
        yy = 400 - y;
        cout << x << "  " << y << endl;
        if (x >= 320 && x <= 345 && yy >= 320 && yy <= 245)
            GreenBall = true;
        GreenBall = !GreenBall;
        //isRed = !isRed; 
        glutSetWindow(GUIWindow);
        glutPostRedisplay();
        glutSetWindow(RoseWindow);
        glutPostRedisplay();

    }
 

}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Right click for menu options." << endl;
   
}
/*windowsWMouseClickOptions.cpp - 162-199

*/
// Main routine.
int main(int argc, char** argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
// --------------------------------------------------------------
    // First top - level window definition.
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(300, 300);

    GUIWindow = glutCreateWindow("GUI");

    setupGUI();
    glutDisplayFunc(drawSceneGUI);
    glutReshapeFunc(resizeGUI);
    glutMouseFunc(GUIMouseSControl);
    //glutMouseFunc(GUIMouseCControl);
    glutKeyboardFunc(keyInput);

 
   
// ------------------------------------------------
    
    // Second top-level window definition.
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 300);

    // Create the second window and return id.
    RoseWindow = glutCreateWindow("Rose");

    // Initialization, display, and other routines of the second window. 
    setupRose();
    glutDisplayFunc(drawSceneRose);
    glutReshapeFunc(resizeRose);
    glutKeyboardFunc(keyInput); // Routine is shared by both windows.
 
    glEnable(GL_DEPTH_TEST);

    makeMenu();
    
    glutMainLoop();

    return 0;
}