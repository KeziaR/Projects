///////////////////////////////////////////////
/*Official Name : 
*
* Call me : 
*
* E - mail : 
*
*Assignment:  Assignment 1
*
*Environment / Compiler : Visual Studio Community 2022
*
*Date submitted : 
*
*References : 
https://community.khronos.org/t/setting-color-of-bitmap-text/59281/2
I wanted to know how to set the color of a bitmap
https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl
I stillw as not sure how to use glortho/frustum
https://www.youtube.com/watch?v=Ut1VznJb00M&list=PL-_EjQgF0g9h84Mg13XDGD17U2ak-mIoT&index=3
I was confused about making a triangle strip
Square.cpp: I used the polygon function in drawscene to make the lion's body
wolf.cpp: used functions like  
     drawHead() to draw the lion's head
     drawTail(); to draw the back legs of the lion
circularAnnulusesMod.cpp: 
    Used the entire program to draw the cylinder and the keyboard inputs
circleAndMore.cpp
    used the draw scene for filling a polygon/ cylinder
*Interactions : "Interaction:" 
    "Press O for parallel view." - when 'o' is pressed the perspective gets smaller or larger
    "Press escape to quit" - when esc is pressed by user, the program stops running
    "Press the space bar to toggle between wireframe and filled for the lower annulus." - Line is filled then unfilled
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


static float bodyLength=10.0;
static float neckLength=3;
static float legHeight=7;
static float legWidth=3;
static float tailHeight=10;
static float pawSide=3;
static int isWire = 0; // Is wireframe?
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
bool big = true;



void lionHead()
{
    
    //Mane
    int j;
    //draw circle vertices,
    GLfloat wx = -23.0; GLfloat wy = 29.0;  GLfloat wz = -10.0; GLfloat Rad1 = 10;
    //center at (centerx,centery,wz)
    static int v1 = 5;  //number of vertices for paws

    float centerx = wx + neckLength + bodyLength - legWidth;
    float centery = wy - legHeight - Rad1 / 2.0;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(150, 87, 27);
        glVertex3f(centerx, centery,wz);
        for (j = 0; j <= v1; j++)
        {
            glVertex3f(Rad1 * cos((float)(j) / v1 * 2 * PI) + centerx,
                Rad1 * sin((float)(j) / v1 * 2 * PI) + centery,
                wz);
        }
        glEnd();


    //Lion face
    //draw circle vertices,
    GLfloat vx = -25.5; GLfloat vy = 24.5;  GLfloat vz = -10.0; GLfloat Rad2 = 5;
    //center at (centerx,centery,wz)
    static int v2 = 20;  //number of vertices for paws

    float cenx = vx + neckLength + bodyLength - legWidth;
    float ceny = vy - legHeight - Rad2 / 2.0;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(237, 218, 70);
    glVertex3f(cenx, ceny, wz);
    for (j = 0; j <= v2; j++)
    {
        glVertex3f(Rad2 * cos((float)(j) / v2 * 2 * PI) + cenx,
            Rad2 * sin((float)(j) / v2 * 2 * PI) + ceny,
            vz);
    }

    glEnd();

    glFlush();

 
    }

/* Square.cpp
   // Clear screen to background color.
   glClear(GL_COLOR_BUFFER_BIT);

   // Set foreground (or drawing) color.
   glColor3f(0.0, 0.0, 0.0);

   // Draw a polygon with specified vertices.
   glBegin(GL_POLYGON);
      glVertex3f(20.0, 20.0, 0.0);
      glVertex3f(80.0, 20.0, 0.0);
      glVertex3f(80.0, 80.0, 0.0);
      glVertex3f(20.0, 80.0, 0.0);
   glEnd();

   // Flush created objects to the screen, i.e., force rendering.
   glFlush(); 
} */

/* circularAnnulusesMod.cpp
glEnable(GL_DEPTH_TEST); // Enable depth testing.
   glColor3f(1.0, 1.0, 1.0);
   drawDisc(10.0, 75.0, 75.0, 0.5);
   glColor3f(0.0, 1.0, 0.0);
   drawDisc(20.0, 75.0, 75.0, 0.0);
    // Compare this z-value with
        // that of the green disc.
    glDisable(GL_DEPTH_TEST); // Disable depth testing.

   // Lower circular annulus: with a true hole.
   if (isWire) glPolygonMode(GL_FRONT, GL_LINE);
       else glPolygonMode(GL_FRONT, GL_FILL);*/

void lionBody()
{

   
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glColor3f(0.55, 0.47, 0.14);

    if (isWire) glPolygonMode(GL_FRONT, GL_LINE);
    else glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 8.0, -0.5);
    glVertex3f(26.0, 10.0, -0.5);
    glVertex3f(26.0, 24.0, -0.5);
    glVertex3f(-10.0, 20.0, -0.5);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex3f(-10.0, 8.0, -0.5);
    glVertex3f(26.0, 10.0, -0.5);
    glVertex3f(26.0, 24.0, -0.5);
    glVertex3f(-10.0, 20.0, -0.5);
    glEnd();

    glFlush();
}

/* circularAnnulusesMod.cpp
void writeBitmapString(void *font, const char *string)
{  
   const char *c;

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
} */

// bitmap character string
void writeBitmapString(void* font, const char* string)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glDisable(GL_LIGHTING);
    const char* c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

/* circleAndMore.cpp
glLineWidth(5);
   glColor4f(0.0f, 1.0f, 1.0f, 1.0f);  //*********needs values************
   glBegin(GL_LINE_LOOP);
      for(i = 0; i < numVertices; ++i)  //*********needs a value************
	  {
          
         glVertex3f(R  +  X * cos(t),R  +  Y * sin(t), numVertices);  //*********needs values************
		 t += 2 * PI / numVertices;  //*********needs a value************

         //glVertex3f(pawRadius * cos((float)(j) / nv * 2 * PI) + centerx,pawRadius * sin((float)(j) / nv * 2 * PI) + centery,wz);
	  }*/

/* circularAnnulusesMod.cpp
if (isWire) glPolygonMode(GL_FRONT, GL_LINE);
       else glPolygonMode(GL_FRONT, GL_FILL);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= N; ++i)
	  {
         angle = 2 * PI * i / N; 
         glVertex3f(50 + cos(angle) * 10.0, 30 + sin(angle) * 10.0, 0.0);
         glVertex3f(50 + cos(angle) * 20.0, 30 + sin(angle) * 20.0, 0.0);
	  }
   glEnd();
*/

#define PI 3.1415927

void lionLeg1(float radius, float height, int numSlices) {
    float angleStep = 2.0f * PI / numSlices;
    glColor3f(0.0, 0.0, 0.0);

    // Draw the bottom circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = i * angleStep;
        glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));
    }
    glEnd();

    // Draw the top circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, height, 0.0);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = i * angleStep;
        glVertex3f(radius * cos(angle), height, radius * sin(angle));
    }
    glEnd();

    // Draw the side
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = i * angleStep;
        glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));
        glVertex3f(radius * cos(angle), height, radius * sin(angle));
    }

    glBegin(GL_LINES);
    for (int i = 0; i < numSlices; ++i)
    {
       float angle = 2 * PI * i / numSlices;
        glVertex3f(radius * cos(angle), 0.0, radius * sin(angle));
        glVertex3f(radius * cos(angle), height, radius * sin(angle));
    }

    glEnd();
}

/* wolf.cpp
void drawTail()
{
    //draw  the tail
    glColor3f(0,1,0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3f(wx+neckLength+bodyLength,wy,wz);
    glVertex3f(wx+neckLength+bodyLength,wy+tailHeight,wz);
    glEnd();
}*/

void lionLeg2() {

    int j;
    //draw circle vertices,
    GLfloat wx = -2.0; GLfloat wy = -1.0;  GLfloat wz = -2.0; GLfloat Rad1 = 60;
    //center at (centerx,centery,wz)

    float centerx = wx + neckLength + bodyLength - legWidth;
    float centery = wy - legHeight - Rad1 / 2.0;

    //drawing the leg
    glColor3f(0, 0, 0);
    glLineWidth(15.0);
    glBegin(GL_LINES);
    glVertex3f(wx + neckLength + bodyLength, wy, wz);
    glVertex3f(wx + neckLength + bodyLength, wy + tailHeight, wz);
    glEnd();
}

// Drawing routine.
void drawScene(void)
{
    //fill background
    glClear (GL_COLOR_BUFFER_BIT);
    
    //return to fresh model view before assembling drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(left(min x), right (max x), bottom(min y), top(max y), -near(min z), -far(max z))
    //glOrtho(-40, 40.0, -40.0, 40.0, 1.0, 20.0);
    if (big)
    {
        glOrtho(-40, 40.0, -40.0, 40.0, -1.0, 20.0);
    }
    else
    {
        glOrtho(-50, 70.0, -50.0, 50.0, -1.0, 20.0);
    }
    //glFrustum(- 40, 40.0, -40.0, 40.0, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    lionHead();
    lionBody();
    lionLeg1(2,8,25);
    lionLeg2();

    glRasterPos3f(5.0, 32.0, 0.0);
    writeBitmapString((void*)font, "Welcome To The Lion's Den");

    glutSwapBuffers();

    glFlush(); //send drawing to the screen
}

// Initialization routine.
void setup(void) 
{
    //DarkOliveGreen background color 
    glClearColor(0.309804, 0.309804, 0.184314, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

/*circularAnnulusesMod.cpp & circleAndMore.cpp  */

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
    case ' ':
        if (isWire == 0) isWire = 1;
        else isWire = 0;
        glutPostRedisplay();
        break;
        case 27:
            exit(0);
            break;
        case 'O':
            if (big == true) big = false;
            else big = true;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press escape to quit" << endl;
    cout << "Press O for parallel view." << endl;
    cout << "Press the space bar to toggle between wireframe and filled for the lower annulus." << endl;
}

// Main routine.
int main(int argc, char **argv) 
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ZOO");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    
    return 0;
}

