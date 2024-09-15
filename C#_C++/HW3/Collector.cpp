///////////////////////////////////////////////
/*Official Name : Kezia Regis
*
* Call me : Kezia
*
* E - mail : knregis@syr.edu
*
*Assignment:  Assignment 2
*
*Environment / Compiler : Visual Studio Community 2022
*
*Date submitted : 3/20/24
*
*References :
// This was for the clouds so that it could move side to side
https://www.youtube.com/watch?v=aG62XiGcpzI&list=PLyzBkpylU13JxDHJJ57mQESlWUQ16sR1x
// This was supposed to be for the wings 
https://www.youtube.com/watch?v=Z3IdSTlzPMc&list=PLXY4_qxp8fUeIMnZIisboZGifEQt0rCAk&index=1
*Interactions :
/*
cout << "Interaction:"
  "Press N N to view from the north" 
"Press E to view from the east" 
"Press S to view from the south" 
"Press W to view from the west" 
"Press w for flapping wings" 
"Press 1 for left flower to grow/shrink." 
"Press 2 for middle flower to grow/shrink." 
"Press 3 for right flower to grow/shrink." 
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
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.
static float square_color[3] = { 1.0, 0.0, 0.0 }; // Color of the square.
static GLsizei width, height;
static float angle = 0.0;

static int facing = 0;

static int big = true; // true or false
static int big1 = true; // true or false
static int big2 = true; // true or false
double scaleX, scaleY;


static float isAnimate = 0.0f; // Animated?
static float speed = 0.2f;
//static int animationPeriodclouds = 100;

static float movewing = 0.0f; // Animated?
static float movement = .07f;
static float wingmove = 0.0f;
static bool wingup = true;

static int t = 0;
static float startX, startY, startZ;//starting point for this leg of trip
static float middleX, middleY, middleZ;//middle point for this leg of trip
static float endX, endY, endZ; //ending point for this leg of trip
static float Px = 2, Py = 3, Pz = 3;
static float Rx = 1, Ry = 2, Rz = 2;
static float Qx = 10, Qy = 5, Qz = 30;
static float Vx, Vy, Vz; //vector from P to Q
static float Mx = 0, My = 0, Mz = 0; //partial vector in direction of V
static int leg = 1; //leg 1 is from P to Q, leg 2 is from Q to P

/* movefromPtoQ.cpp
lines: 40-52*/

//Assign starting and ending points for this leg.
//Computer the vector from start to end.
void assignEndpointsMakeVector(
    float Px, float Py, float Pz,
    float Qx, float Qy, float Qz, float Rx, float Ry, float Rz)
{
    startX = Px;
    startY = Py;
    startZ = Pz;
    middleX = Rx;
    middleX = Ry;
    middleX = Rz;
    endX = Qx;
    endY = Qy;
    endZ = Qz;
    Vx = endX - startX;
    Vy = endY - startY;
    Vz = endZ - startZ;


}

/* movefromPtoQ.cpp
lines: 100-125*/

void increaseVector(void)
{
    //check if time for a new leg
    if (t == 10 && leg == 1) //go back
    {
        t = 0;
        leg = 2;
        assignEndpointsMakeVector(Qx, Qy, Qz, Rx, Ry, Rz, Px, Py, Pz);

    }
    
    else if (t == 10 && leg == 2) //go forward
    {
        t = 0;
        leg = 1;
        assignEndpointsMakeVector(Px, Py, Pz, Rx, Ry, Rz, Qx, Qy, Qz);
    }



    //update partial vector
    t++;
    Mx = t / 10.0 * Vx;
    My = t / 10.0 * Vy;
    Mz = t / 10.0 * Vz;

    //some output for debugging
//    std::cout<< t<<' ' << leg << std::endl;
//    std::cout<< Mx << ' ' << My << ' ' << Mz << std::endl;

    glutPostRedisplay();
}



/* https://www.dropbox.com/s/ofkl27jqg1q50mo/source%20code.txt?dl=0 & MJBclownW2timers.cpp
* 
lines: 40-52*/

void cloudmotion(int value) {
    if (isAnimate > 1.0)
        isAnimate = -1.0f;

    isAnimate += speed;

    glutPostRedisplay();
    glutTimerFunc(100,cloudmotion, 0);
    //glutPostRedisplay();

}

/* https://www.dropbox.com/s/ofkl27jqg1q50mo/source%20code.txt?dl=0 
GLfloat position2 = 0.0f;
GLfloat speed2 = 0.004f;
void cloud(int value) {
    if(position2 > 1.0)
        position2 =-1.0f;
    position2 += speed2;
    glutPostRedisplay();
    glutTimerFunc(100, cloud, 0);

& MJBclownW2timers.cpp 
& animateMan1.cpp
*
lines: 40-52*/

void wingmotion(int value) {
    if (wingup && movewing > 1.0f) {
        wingup = false;
    }
    else if (!wingup && movewing < -1.0f) {
        wingup = true;
    }

    if (wingup) {
        movewing += movement;
    }
    else {
    movewing -= movement;
    }
    glutPostRedisplay();
    glutTimerFunc(100, wingmotion, 0);

}

/* My Eclipse.cpp & MJBBasicTransformations.cpp
lines: 105-110*/

void BeeHead() {
    glColor3f(1.0, 0.92, 0.28);
    glPushMatrix();
    glTranslatef(2, 10, 9);
    glutSolidSphere(1.5, 10, 8);
    glPopMatrix();
    glEnd();
}
 
/*My Eclipse.cpp& MJBBasicTransformations.cpp
lines : 105 - 110 */

void BeeTummy() {

    glColor3f(1.0, 0.97, 0.4);
    glPushMatrix();
    glTranslatef(4, 10, 9);
    glutSolidSphere(2.0, 10, 8);
    glPopMatrix();
    glEnd();
}

/*My Eclipse.cpp& MJBBasicTransformations.cpp
lines : 105 - 110 */

void BeeStinger() {

    //glColor3f(0, 0, 0);
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(6, 10, 9);
    glRotatef(-47, 0.0, -60.0, -2.0);
    glutWireCone(.2, 1.3, 15, 30);
    glPopMatrix();
    glEnd();
}
  
  /*My Eclipse.cpp& MJBBasicTransformations.cpp
lines : 105 - 110 */

void BeeProboscis() {

    glColor3f(.72, .45, 0.2);
    glPushMatrix();
    glTranslatef(1, 10, 9);
    glRotatef(120.0, 0.0, -60.0, -10.0);
    glutWireCone(0.2, 5.0, 15, 30);
    glPopMatrix();
    glEnd();
}

/* wolf.cpp
lines : 117 - 144 */
    
void BeeWings() {

    GLfloat wx = -6.0; GLfloat wy = 33.0;  GLfloat wz = -10.0; GLfloat Rad1 = 10;
    static float bodyLength = 10.0;
    static float neckLength = 3;
    static float legHeight = 7;
    static float legWidth = 3;
    static float tailHeight = 10;
    static float Radius = 4;
    static int nv = 10;


    // --------------------------------------

    glColor3f(0.75, 0.75, 0.75);
    //left back paw
    //compute center of left back paw
    float centerx = wx + neckLength + bodyLength - legWidth;
    float centery = wy - legHeight - Radius / 2.0;
    int j;

    //draw circle paw with nv vertices,
    //center at (centerx,centery,wz)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(centerx, centery, wz);
    for (j = 0; j <= nv; j++)
    {
        glVertex3f(Radius * cos((float)(j) / nv * 2 * PI) + centerx,
            Radius * sin((float)(j) / nv * 2 * PI) + centery,
            wz);
    }
    glEnd();
}

/* inspired by https://www.dropbox.com/s/ofkl27jqg1q50mo/source%20code.txt?dl=0 :
lBegin(GL_POLYGON);
    glColor3ub(34,139,34);
    glVertex2f(-0.5f,0.64f);
    glVertex2f(-0.52f,0.62f);
    glVertex2f(-0.58f,0.6f);
    glVertex2f(-0.55f, 0.63f);
    glVertex2f(-0.58f,0.66f);
    glVertex2f(-0.52f,0.66f);
    glVertex2f(-0.52f, 0.72f);
    glVertex2f(-0.5f,0.69f);///
    glVertex2f(-0.48f,0.72f);
    glVertex2f(-0.48f, 0.66f);
    glVertex2f(-0.42f,0.66f);
    glVertex2f(-0.45f,0.63f);
    glVertex2f(-0.42f, 0.6f);
    glVertex2f(-0.48f,0.62f);
    glEnd();*/

 void Leaf(void) 
 {

     /* glColor3f(0.2, 1.0, 0.7);
    glPushMatrix();
    glTranslatef(2, 10, 9);
    glutSolidSphere(1.5, 10, 8);
    //glTranslatef(3, 9, 9);
    glPopMatrix();
    //glutSwapBuffers();
    //glEnd();*/

     glColor3f(0.7, 1.0, 0.0);
     glPointSize(5.0f);
     glBegin(GL_POINTS);
     glVertex3f(-4,8,4); 
     glVertex3f(-4, 5, 4); 
     glVertex3f(-6, 10, 4); 
     glVertex3f(-1, 8, 4); 
     glVertex3f(-1, 5, 4); 
     glVertex3f(1, 3, 4); 
     glEnd();

     glColor3f(0.7, 1.0, 0.0);
     glBegin(GL_POLYGON);

     glVertex3f(-6, 10, 4);
     glVertex3f(-4, 5, 4);
     glVertex3f(1, 3, 4);

     glVertex3f(-4, 5, 4);
     glVertex3f(1, 3, 4);

     glVertex3f(-1, 5, 4);
     glVertex3f(-1, 8, 4);
     glVertex3f(-1, 5, 4);
     glVertex3f(-1, 8, 4);

     glVertex3f(-4, 8, 4);
     glVertex3f(-1, 8, 4);
     glVertex3f(-4, 8, 4);
     glVertex3f(-6, 10, 4);

     glVertex3f(1, 3, 4);
     glVertex3f(-4, 8, 4);
     glVertex3f(-6, 10, 4);

     glEnd();

     glColor3f(0.13, 0.55, 0.13);
     glLineWidth(10.0);
     glBegin(GL_LINES);
     glVertex2f(-6, 5);
     glVertex2f(-4.9, -5);
     glEnd();
     
     
 }
    
 /* wolf.cpp
lines : 117 - 144 */

 void Cloud1(void)
 {
     GLfloat wx = 2.0; GLfloat wy = 36.0;  GLfloat wz = -10.0; GLfloat Rad1 = 10;
     static float bodyLength1 = 10.0;
     static float neckLength1 = 3;
     static float legHeight1 = 7;
     static float legWidth1 = 3;
     static float tailHeight1 = 10;
     static float Radius1 = 2;
     static int nv1 = 10;


     // --------------------------------------

     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centerx = wx + neckLength1 + bodyLength1 - legWidth1;
     float centery = wy - legHeight1 - Radius1 / 2.0;
     int j;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centerx, centery, wz);
     for (j = 0; j <= nv1; j++)
     {
         glVertex3f(Radius1 * cos((float)(j) / nv1 * 2 * PI) + centerx,
             Radius1 * sin((float)(j) / nv1 * 2 * PI) + centery,
             wz);
     }
     glEnd();

     GLfloat tx = 4.0; GLfloat ty = 37.0;  GLfloat tz = -10.0; GLfloat Rad2 = 15;
     static float bodyLength2 = 10.0;
     static float neckLength2 = 3;
     static float legHeight2 = 7;
     static float legWidth2 = 3;
     static float tailHeight2 = 10;
     static float Radius2 = 3;
     static int nv2 = 10;


     // --------------------------------------
           //draw circle feet of given color
     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centert = tx + neckLength2 + bodyLength2 - legWidth2;
     float centerk = ty - legHeight2 - Radius2 / 2.0;
     int k;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centert, centerk, tz);
     for (k = 0; k <= nv2; k++)
     {
         glVertex3f(Radius2 * cos((float)(k) / nv2 * 2 * PI) + centert,
             Radius2 * sin((float)(k) / nv2 * 2 * PI) + centerk,
             tz);
     }
     glEnd();
 
     GLfloat sx = 6.0; GLfloat sy = 37.0;  GLfloat sz = -10.0; GLfloat Rad3 = 10;
     static float bodyLength3 = 10.0;
     static float neckLength3 = 3;
     static float legHeight3 = 7;
     static float legWidth3 = 3;
     static float tailHeight3 = 10;
     static float Radius3 = 2;
     static int nv3 = 10;


     // --------------------------------------
           //draw circle feet of given color
     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centers = sx + neckLength3 + bodyLength3 - legWidth3;
     float centerl = sy - legHeight3 - Radius3 / 2.0;
     int l;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centers, centerl, wz);
     for (l = 0; l <= nv3; l++)
     {
         glVertex3f(Radius3 * cos((float)(l) / nv3 * 2 * PI) + centers,
             Radius3 * sin((float)(l) / nv3 * 2 * PI) + centerl,
             sz);
     }
     glEnd();
 }





 void Cloud2(void)
 {
     GLfloat ax = -22.0; GLfloat ay = 34.0;  GLfloat az = -10.0; GLfloat Rad4 = 10;
     static float bodyLength4 = 10.0;
     static float neckLength4 = 3;
     static float legHeight4 = 7;
     static float legWidth4 = 3;
     static float tailHeight4 = 10;
     static float Radius4 = 2.3;
     static int nv4 = 10;


     // --------------------------------------
           //draw circle feet of given color
     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centera = ax + neckLength4 + bodyLength4 - legWidth4;
     float centerm = ay - legHeight4 - Radius4 / 2.0;
     int m;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centera, centerm, az);
     for (m = 0; m <= nv4; m++)
     {
         glVertex3f(Radius4 * cos((float)(m) / nv4 * 2 * PI) + centera,
             Radius4 * sin((float)(m) / nv4 * 2 * PI) + centerm,
             az);
     }
     glEnd();


     GLfloat bx = -20.0; GLfloat by = 35.0;  GLfloat bz = -10.0; GLfloat Rad5 = 10;
     static float bodyLength5 = 10.0;
     static float neckLength5 = 3;
     static float legHeight5 = 7;
     static float legWidth5 = 3;
     static float tailHeight5 = 10;
     static float Radius5 = 3;
     static int nv5 = 10;


     // --------------------------------------
           //draw circle feet of given color
     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centerb = bx + neckLength5 + bodyLength5 - legWidth5;
     float centerg = by - legHeight5 - Radius5 / 2.0;
     int g;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centerb, centerg, bz);
     for (g = 0; g <= nv5; g++)
     {
         glVertex3f(Radius5 * cos((float)(g) / nv5 * 2 * PI) + centerb,
             Radius5 * sin((float)(g) / nv5 * 2 * PI) + centerg,
             bz);
     }
     glEnd();

     GLfloat cx = -24.0; GLfloat cy = 34.0;  GLfloat cz = -10.0; GLfloat Rad6 = 10;
     static float bodyLength6 = 10.0;
     static float neckLength6 = 3;
     static float legHeight6 = 7;
     static float legWidth6 = 3;
     static float tailHeight6 = 10;
     static float Radius6 = 2.5;
     static int nv6 = 10;


     // --------------------------------------
           //draw circle feet of given color
     glColor3f(1.0, 1.0, 1.0);
     //left back paw
     //compute center of left back paw
     float centerc = cx + neckLength6 + bodyLength6 - legWidth6;
     float centeri = cy - legHeight6 - Radius6 / 2.0;
     int i;

     //draw circle paw with nv vertices,
     //center at (centerx,centery,wz)
     glBegin(GL_TRIANGLE_FAN);
     glVertex3f(centerc, centeri, cz);
     for (i = 0; i <= nv6; i++)
     {
         glVertex3f(Radius6 * cos((float)(i) / nv6 * 2 * PI) + centerc,
             Radius6 * sin((float)(i) / nv6 * 2 * PI) + centeri,
             cz);
     }
     glEnd();
 }



 void Flowers1(void)
 {
     float R = 1.5;
     float X = 11;
     float Y = 4;
     int numVertices = 6.5;
     float t = 0;
     int i;

  
     glLineWidth(5);
     glColor3f(1.0, 0.0, 0.0);  
     glBegin(GL_LINE_LOOP);
     for (i = 0; i < numVertices; ++i)  
     {

         glVertex3f(R * cos(t), R * sin(t), 0.5);  
         t += 2 * PI / numVertices;  
     }
     glEnd();

    
 }

 void Stem1(void)
 {

     glColor3f(0.13, 0.55, 0.13);
     glLineWidth(10.0);
     glBegin(GL_LINES);
     glVertex2f(3, 4);
     glVertex2f(3, -4);
     glEnd();

 }


void Flowers2(void)
{
    float R = 1.5;
    float X = 7;
    float Y = 6;
    int numVertices = 6.5;
    float t = 0;
    int i;

     glLineWidth(5);
     glColor3f(0.0, 1.0, 0.0);
     glBegin(GL_LINE_LOOP);
     for (i = 0; i < numVertices; ++i)
     {

         glVertex3f(R * cos(t), R * sin(t), 0.5);
         t += 2 * PI / numVertices;
     }
     glEnd();

    //green
    /*glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(8, 4, 6);*/
    

}

/* previous project - myzoo.cpp
lines: 287-293 */

void Stem2(void)
{

    glColor3f(0.13, 0.55, 0.13);
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glVertex2f(7, 6);
    glVertex2f(6.4, -6);
    glEnd();

}


void Flowers3(void)
{
    float R = 1.5;
    float X = 3;
    float Y = 4;
    int numVertices = 6.5;
    float t = 0;
    int i;

    glLineWidth(5);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < numVertices; ++i)
    {

        glVertex3f(R * cos(t), R * sin(t), 0.5);
        t += 2 * PI / numVertices;
    }
    glEnd();

    //blue
    /*glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3f(6, 4, 4);
    glEnd();*/
}

void Stem3(void)
{

    glColor3f(0.13, 0.55, 0.13);
    glLineWidth(10.0);
    glBegin(GL_LINES);
    glVertex2f(11, 4.2);
    glVertex2f(10, -4.8);
    glEnd();

}

void drawScene(void)
{
    //fill background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //North
    gluLookAt(5, 5, 20, 4, 8, 9, 0, 1, 0);

/* LegoLookAt.cpp
lines: 50-64 */

// ----------------------------------------------------
// Changes perspective
    if (facing == 'N')
    {
        gluLookAt(5, 5, 20, 4, 8, 9, 0, 1, 0);
    }
    else if (facing == 'E') {
        gluLookAt(-13, 10, 10,4, 8, 9,0, 1, 0);
    }
    else if (facing == 'S') {
        gluLookAt(5, 5, -8, 4, 8, 9,  0, 1, 0);
    }
    else if (facing == 'W') {
        gluLookAt(20, 10, 9, 4, 8, 9, 0, 1, 0);
    }

    /* boxWScaling.cpp lines: 39-44 & */
// ----------------------------------------------------
// Shrinks/ Widens flower1 

   glPushMatrix();
   glTranslatef(11, 4, 0);
   if (big) {
       glScalef(0.5, 0.5, 0.5);
        
    }

    else {
       glScalef(1, 1, 1);
    }
    Flowers1();
    glPopMatrix();
   

    glPushMatrix();
    glTranslatef(7, 6, 0);
    if (big1) {
        
        glScalef(0.5, 0.5, 0.5);
    }
    else {
        glScalef(1, 1, 1);
    }
    Flowers2();
    glPopMatrix();
    

    glPushMatrix();
    glTranslatef(3, 4, 0);
    if (big2) {
        glScalef(0.5, 0.5, 0.5);
    }
    else {
        glScalef(1, 1, 1); 
    }
    Flowers3();
    glPopMatrix();
    
   


// -----------------------------------------------------
// bee wings movement 
    glPushMatrix();
    glTranslatef(movewing, 0.0f, 0.0f);
    BeeWings();
    glPopMatrix();
  
// -----------------------------------------------------


// -----------------------------------------------------
// Animates clouds
    glPushMatrix();
    glTranslatef(isAnimate, 0.0f, 0.0f);
    Cloud1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(isAnimate, 0.0f, 0.0f);
    Cloud2();
    glPopMatrix();
  
// -----------------------------------------------------
// Moves bee to leaf
    BeeHead();
    BeeWings();
    BeeTummy();
    BeeStinger();
    BeeProboscis();

// -----------------------------------------------------

    BeeHead();
    BeeTummy();
    BeeStinger();
    BeeProboscis();
    
    Leaf();
    //Cloud1();
    //Cloud2();
    //Cloud3();
    //Cloud4();
    //Cloud5();
    //Cloud6();
    //Flowers1(scaleX,scaleY);
    //Flowers2();
    //Flowers3();
    Stem1();
    Stem2();
    Stem3();
 
glutSwapBuffers();
glFlush();
}

// Initialization routine.
void setup(void)
{
    //background color 
    glClearColor(0.309804, 0.309804, 0.184314, 0.0);


}


void resizeBee(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 5, 40);
    glMatrixMode(GL_MODELVIEW);

}


void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN)
        speed += 5;
    if (key == GLUT_KEY_UP) 
        if (speed > 5) 
            speed -= 5;
    glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'w':
        movewing = !movewing;
        break;
    case ' ':
        if (isAnimate) 
            isAnimate = 0;
        else 
            isAnimate = 1;
        glutPostRedisplay();
        break;
    case 'N':
        facing = 'N';
        glutPostRedisplay();
        break;
    case 'E':
        facing = 'E';
        glutPostRedisplay();
        break;
    case 'S':
        facing = 'S';
        glutPostRedisplay();
        break;
    case 'W':
        facing = 'W';
        glutPostRedisplay();
        break;
    case '1':
        big = !big;
        glutPostRedisplay();
        break;
    case '2':
        big1 = !big1;
        glutPostRedisplay();
        break;
    case '3':
        big2 = !big2;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press N N to view from the north" << endl;
    cout << "Press E to view from the east" << endl;
    cout << "Press S to view from the south" << endl;
    cout << "Press W to view from the west" << endl;
    cout << "Press w for flapping wings" << endl;
    cout << "Press 1 for left flower to grow/shrink." << endl;
    cout << "Press 2 for middle flower to grow/shrink." << endl;
    cout << "Press 3 for right flower to grow/shrink." << endl;
    cout << "Press the up and down arrow keys to speed up/slow down the cloud." << endl;



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
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bee Collecting Pollen");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeBee);
    glutKeyboardFunc(keyInput); 
    glutTimerFunc(30, cloudmotion, 0);
    glutTimerFunc(30, wingmotion, 0);
    glutMainLoop();


    return 0;
}