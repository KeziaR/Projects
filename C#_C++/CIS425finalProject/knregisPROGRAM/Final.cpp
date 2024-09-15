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

*Interactions :

*/
////////////////////////////////////////////////

#include <cmath>
//for sin, cos
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324
#define N 40.0 // Number of vertices on the boundary of the disc.
#define R 1.0
#define r -0.5
#define ROOT3 1.73205081
#define ONEBYROOT3 0.57735027
#define TREE 2
#define RATIO 0.85 // Growth ratio = length of tree sub-branch to length of branch.
#define ANGLE 40 // Angle between the two tree sub-branches.

using namespace std;  //need for string

static float Xangle = 30.0, Yangle = 330.0, Zangle = 0.0; // Angles to rotate canoe.
static int step = 0; // Step number

static int p = 10; // Number of grid columns.
static int q = 6; // Number of grid rows
static float* vertices = NULL; // Vertex array of the mapped sample on the table.

int wrap = 1;
static unsigned int texture[3]; // Array of texture indices.

//mouse clicking
bool sconeL = false; //true if selected
bool sconeR = false;
int height, width;
bool selecting = false;
int xClick, yClick;  //coordinates of mouseclick

GLuint startList;

static float valX = 0, valY = 0, valZ = 0;
static float angle = 0;  //angle facing
static float stepsize = 5.0;  //step size
static float turnsize = 10.0; //degrees to turn
static int isCollision = 0;
static GLUquadricObj* qobj; // Create a pointer to a quadric object.

//canoeMotion
static float moveshade = 0.0f; // Animated?
static float movement = .07f;
static float shademove = 0.0f;
static bool shadeup = true;
static int big = true; 
double scaleX, scaleY;
static float rot = 0.0;


int seeCone = 1;//MJB
int seeCir = 1;
static float spotAngle = 10.0; // Spotlight cone half-angle.
static float spotExponent = 2.0; // Spotlight exponent = attenuation.
float red = 1.0, ge = 1.0, b = 1.0;


float origin[] = { 0.0, 0.0, 0.0, 1.0 };


// Control points for the final step.
static float controlPoints4[6][4][3] =
{
    {{0.0, 2.75, 5.0}, {0.0, 0.0, 5.0}, {0.0, 0.0, 5.0}, {0.0, 2.75, 5.0}},
    {{-1.0, 2.75, 3.0}, {-0.25, 0.0, 3.0}, {0.25, 0.0, 3.0}, {1.0, 2.75, 3.0}},
    {{-1.5, 2.75, 1.0}, {-0.25, 0.0, 1.0}, {0.25, 0.0, 1.0}, {1.5, 2.75, 1.0}},
    {{-1.5, 2.75, -1.0}, {-0.25, 0.0, -1.0}, {0.25, 0.0, -1.0}, {1.5, 2.75, -1.0}},
    {{-1.0, 2.75, -3.0}, {-0.25, 0.0, -3.0}, {0.25, 0.0, -3.0}, {1.0, 2.75, -3.0}},
    {{0.0, 2.75, -5.0}, {0.0, 0.0, -5.0}, {0.0, 0.0, -5.0}, {0.0, 2.75, -5.0}}
};



// Struct of bitmap file.
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char* data;
};


static float controlPoints[6][3] =
{
    { -4.0, -2.0, 0.0}, { -3.0, 2.0, -5.0}, { -1.0, -1.0, 2.0},
    {0.0, 2.0, -2.0}, {3.0, -3.0, 1.0}, { 4.0, 0.0, -1.0}
};

/*
interpolateTextures.cpp

lines 56-103

*/

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile* getBMPData(string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;

    // Read input file name.
    ifstream infile(filename.c_str(), ios::binary);

    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char*)&offset, 4);

    // Get the header size of the bitmap.
    infile.read((char*)&headerSize, 4);

    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read((char*)&bmp->sizeX, 4);
    infile.read((char*)&bmp->sizeY, 4);

    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];

    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char*)bmp->data, size);

    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i + 2];
        bmp->data[i + 2] = temp;
    }

    return bmp;
}

/*
interpolateTextures.cpp

lines 149-175

*/

// Load external textures.
void loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile* image[1];

    // Load the textures.
    image[0] = getBMPData("Textures/ripple.bmp");

    // Bind trees image to texture index[0]. 
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image[0]->sizeX, image[0]->sizeY,
        GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);


    
}

/*
Election.Cpp
previous project

*/

void walls() {

    glPushMatrix();
    float matAmbAndDifCol1[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol1);
    glPopMatrix();

    //back wall
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glColor3f(0.0, 1.0, 0.8);
    glVertex3f(-40, -10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, 10, 25);
    glVertex3f(-40, 10, 25);


    glPushMatrix();
    float matAmbAndDifCol2[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol2);
    glPopMatrix();

    // front wall
    glColor3f(0.0, 1.0, 0.8);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-40, -10, -25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, 10, -25);
    glVertex3f(-40, 10, -25);


    glPushMatrix();
    float matAmbAndDifCol3[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol3);
    glPopMatrix();

    // right wall
    glColor3f(0.0, 1.0, 0.8);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(10, 10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, 10, -25);



    /*glPushMatrix();
    float matAmbAndDifCol4[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol4);
    glPopMatrix();

    // left wall
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40, 10, 25);
    glVertex3f(-40, -10, 25);
    glVertex3f(-40, -10, -25);
    glVertex3f(-40, 10, -25);
    glPopMatrix();*/

    glEnd();


}

/*
Election.Cpp
previous project

*/

void wallWindow() {

    glPushMatrix();
    float matAmbAndDifCol4[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol4);
    glPopMatrix();


    // bottom wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-40, -5, 25);
    glVertex3f(-40, -10, 25);
    glVertex3f(-40, -10, -25);
    glVertex3f(-40, -5, -25);
    glPopMatrix();


    glPushMatrix();
    float matAmbAndDifColb[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifColb);
    glPopMatrix();

    // right wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-40, 10, -25);
    glVertex3f(-40, -10, -25);
    glVertex3f(-40, -10, -5);
    glVertex3f(-40, 10, -5);
    glPopMatrix();

    glPushMatrix();
    float matAmbAndDifColc[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifColc);
    glPopMatrix();


    // top wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-40, 10, 25);
    glVertex3f(-40, 5, 25);
    glVertex3f(-40, 5, -25);
    glVertex3f(-40, 10, -25);
    glPopMatrix();

    glPushMatrix();
    float matAmbAndDifCold[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCold);
    glPopMatrix();


    // left wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-40, 10, 25);
    glVertex3f(-40, -10, 25);
    glVertex3f(-40, -10, 15);
    glVertex3f(-40, 10, 15);
    glPopMatrix();



    glEnd();


}

/*
Collector.cpp
previous project

*/

void canoeMotion(int val) {

    rot += movement;
    glutPostRedisplay(); // Request display update
    glutTimerFunc(16, canoeMotion, 0); // Schedule next update (approximately 60 FPS)

}

/*
Election.cpp/ blendRectangles2.cpp
previous project
and
lines: 55-67
*/

void shade() {

    glPushMatrix();
    float matAmbAndDifCola[] = { 1.0, 1.0, 1.0, 0.1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCola);
    glPopMatrix();

    glPushMatrix();
    // glEnable(GL_BLEND);
     //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 0.0, 0.0, 0.5); // Translucent: alpha value = 0.5.


    //shade down
    glBegin(GL_QUADS);
   // glColor3f(1.0, 0.0, .2);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(-40, 5, 15);
    glVertex3f(-40, -5, 15);
    glVertex3f(-40, -5, -5);
    glVertex3f(-40, 5, -5);
    glPopMatrix();

    //shade up
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, .2);
    glVertex3f(-40, 5, 15);
    glVertex3f(-40, 3, 15);
    glVertex3f(-40, 3, -5);
    glVertex3f(-40, 5, -5);
    glPopMatrix();






    glEnd();

}

/*
Election.cpp
*/

void walls2() {

    glPushMatrix();
    float matAmbAndDifCol1[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol1);
    glPopMatrix();

    //back wall
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-40, -10, 10);
    glVertex3f(10, -10, 10);
    glVertex3f(10, -15, 10);
    glVertex3f(-40, -15, 10);


    glPushMatrix();
    float matAmbAndDifCol2[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol2);
    glPopMatrix();

    // front wall
    glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-40, -10, -10);
    glVertex3f(10, -10, -10);
    glVertex3f(10, -15, -10);
    glVertex3f(-40, -15, -10);


   

    /*// right wall
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-40, -15, 10);
    glVertex3f(10, -10, 10);
    glVertex3f(10, -10, -10);
    glVertex3f(-40, -15, -10);




    /*glPushMatrix();
    float matAmbAndDifCol4[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol4);
    glPopMatrix();

    // left wall
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40, -10, 20);
    glVertex3f(10, -10, 20);
    glVertex3f(10, -10, -20);
    glVertex3f(-40, -10, -20);
    glPopMatrix();*/

    glEnd();


}

/*
Election.cpp
*/

void floor() {

    int i;
    float z;

    glPushMatrix();
    float matAmbAndDifCol5[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol5);
    glPopMatrix();

    //floor up
    glBegin(GL_QUADS);
    glColor3f(.32, 0.5, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-40, -10, 25);
    glVertex3f(10, -10, 25);
    glVertex3f(10, -10, 10);
    glVertex3f(-40, -10, 10);
    glEnd();

    glPushMatrix();
    float matAmbAndDifCol6[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol6);
    glPopMatrix();
     //floor down
    glBegin(GL_QUADS);
    glColor3f(.32, 0.5, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-40, -10, -25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, -10, -10);
    glVertex3f(-40, -10, -10);
    glEnd();

    glPushMatrix();
    float matAmbAndDifCol7[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol7);
    glPopMatrix();

    //floor left
    glBegin(GL_QUADS);
    glColor3f(.32, 0.5, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-40, -10, -25);
    glVertex3f(-25, -10, -25);
    glVertex3f(-25, -10, 25);
    glVertex3f(-40, -10, 25);
    glEnd();

    glPushMatrix();
    float matAmbAndDifCol8[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol8);
    glPopMatrix();

    //floor right
    glBegin(GL_QUADS);
    glColor3f(.32, 0.5, 1.0);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5, -10, -25);
    glVertex3f(10, -10, -25);
    glVertex3f(10, -10, 25);
    glVertex3f(-5, -10, 25);
    glEnd();





}

/*
Election.cpp
*/

void floor2() {

    int i;
    float z;

    glPushMatrix();
    float matAmbAndDifCol9[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol9);
    glPopMatrix();

    //floor
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_QUADS);
     glColor3f(.89, 0.59, 1.0);
     glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-40, -15, -10);
    glTexCoord2f(1.0, 1.0); glVertex3f(10, -15, -10);
    glTexCoord2f(1.0, 0.0); glVertex3f(10, -15, 10);
    glTexCoord2f(0.0, 0.0); glVertex3f(-40, -15, 10);
    glEnd();
    glPopMatrix(); 

  
  


} 


/*
Eclipse.cpp / remade/ gluQuadrics.cpp
lines: 49,78-81
*/

void moon() {

    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    glPushMatrix();
    float matAmbAndDifCold[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCold);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glNormal3f(0.0, 0.0, 1.0);
    glTranslatef(-17.0, 0.0, 0.0);
    glTranslatef(0.0, -18.0, -22.0);
    //glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(-55.0, 15.0, 25.0);
    gluSphere(quad, 5.9, 20, 8);
    glPopMatrix();
    //glutSwapBuffers();

    glPushMatrix();
    float matAmbAndDifCole[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCole);
    glPopMatrix();

    // Under sphere
    glColor3f(0.8, 0.498039, 0.196078);
    glPushMatrix();
    glTranslatef(-17.0, 0.0, 0.0);
    glTranslatef(-3.0, -20.0, -25.0);
    //glRotatef(angle, 1.0, 0.0, 0.0);
    glTranslatef(-60.0, 15.0, 25.0);
    gluSphere(quad, 8, 20, 8);
    glPopMatrix();
    //glutSwapBuffers();
    glEnd();

//________________________________________________________________

    float origin[] = { 0.0, 0.0, 0.0, 1.0 };
    float matAmbAndDifLeftCube[] = { 0.9, 0.0, 0.0, 1.0 };
    float matAmbAndDifMiddleCube[] = { 0.0, 0.0, 0.9, 1.0 };
    // Some light property vectors.
    float lightAmb0[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
//________________________________________________________________

    // Some light properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);


    glEnable(GL_LIGHT0); // Enable particular light source.
    glEnable(GL_LIGHTING);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb0); // Global ambient light.
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.


    //glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);//lightbulb color
    glPushMatrix();
    glTranslated(-64, -5, 0);
    //glutSolidSphere(2, 10, 10);  //at the origin
    glLightfv(GL_LIGHT0, GL_POSITION, origin);//build the light at origin, too
    glPopMatrix();
    //glEnable(GL_LIGHTING);
 
    

}



void ceiling() {

    glPushMatrix();
    float matAmbAndDifCol5[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol5);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(-40, 10, -25);
    glVertex3f(10, 10, -25);
    glVertex3f(10, 10, 25);
    glVertex3f(-40, 10, 25);
    glEnd();
}



//draw the table - a top and four legs
void lightScone()

/*glTranslatef(-17.0, 0.0, 0.0);
glTranslatef(0.0, -18.0, -22.0);
//glRotatef(angle, 1.0, 0.0, 0.0);
glTranslatef(-55.0, 15.0, 25.0);
*/
{
    glPushMatrix();
    glColor3f(1, .5, .8);
    glTranslatef(-33.0, 4.0, 4.0);
    glTranslatef(2.0, -4.0, 4.0);
    glTranslatef(2.0, 4.0, -33.0);
    glRotatef(90.0, 90.0, 0.0, 0.0);
    gluCylinder(qobj, 0.5, 0.5, 1.0, 15, 5);
    glPopMatrix();
    glEnd();

    

    glPushMatrix();
    glColor3f(.8, .5, 1);
    glTranslatef(-7.0, 4.0, 4.0);
    glTranslatef(2.0, -4.0, 4.0);
    glTranslatef(2.0, 4.0, -33.0);
    glRotatef(90.0, 90.0, 0.0, 0.0);
    gluCylinder(qobj, 0.5, 0.5, 1.0, 15, 5);
    glPopMatrix();
    glEnd();


//___________________________________________________________________________________
    float lightPos1[] = { 0.0, 3.0, 0.0, 1.0 }; // Spotlight position.
    float spotDirection1[] = { 0.0, -1.0, 0.0 }; // Spotlight direction.
    float lightDifAndSpec1[] = { red, ge, b, 1.0 };  //MJB

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);//MJB
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);//MJB

    
    glPushMatrix();
    if (seeCone)
    {
       seeCone = !seeCone;

        glPushMatrix();
        glDisable(GL_LIGHTING);
        glTranslatef(-7.0, 4.0, 4.0);
        glTranslatef(2.0, -7.0, 4.0);
        glTranslatef(2.0, 4.0, -33.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glutWireCone(3.0 * tan(spotAngle / 180.0 * PI), 3.0, 20, 20);
        glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();
        glDisable(GL_LIGHTING);
        glTranslatef(-33.0, 4.0, 4.0);
        glTranslatef(2.0, -7.0, 4.0);
        glTranslatef(2.0, 4.0, -33.0);
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glutWireCone(3.0 * tan(spotAngle / 180.0 * PI), 3.0, 20, 20);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    // Spotlight properties including position.   **LIGHTING**
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotAngle);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);

    glPopMatrix();

}
/*NaiveColorPickingDemo.cpp
lines: 54-83
*/


void identifyObject(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    //printed only for demonstration
    cout << "R: " << (int)pixel[0] << endl;
    cout << "G: " << (int)pixel[1] << endl;
    cout << "B: " << (int)pixel[2] << endl;
    cout << endl;
    //clear past picks
    sconeL = false;
    sconeR = false;

    if ((int)pixel[0] == 255 && (int)pixel[1] == 255 && (int)pixel[2] == 555)
    {
        sconeL = true;
    }
    else if ((int)pixel[0] == 255 && (int)pixel[1] == 123 && (int)pixel[2] == 0)
    {
        sconeR = true;
    }
}

// Function computes the x co-ordinate of the sectional curve in terms of the
// length t measured from one end of the curve.
float xc(float t)
{
    if (t <= 4.0) return t;
    else if (t <= 5.0) return 4.0;
    else if (t <= 8.0) return 9.0 - t;
    else if (t <= 22.0) return 1.0;
    else if (t <= 31.0) return t - 21.0;
    else if (t <= 32.0) return 10.0;
    else                  return 42.0 - t;
}

// Function computes the y co-ordinate of the sectional curve in terms of the
// length t measured from one end of the curve.
float yc(float t)
{
    if (t <= 4.0) return -8.0;
    else if (t <= 5.0) return t - 12.0;
    else if (t <= 8.0) return -7.0;
    else if (t <= 22.0) return t - 15.0;
    else if (t <= 31.0) return 7.0;
    else if (t <= 32.0) return t - 24.0;
    else                  return 8.0;
}

// Fuctions to map the grid vertex (u_i,v_j) to the mesh vertex (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)) on the table.
float f(int i, int j)
{
    return (xc((float)i / p * 42.0) * cos((-1 + 2 * (float)j / q) * PI));
}

float g(int i, int j)
{
    return (yc((float)i / p * 42.0));
}

float h(int i, int j)
{
    return (xc((float)i / p * 42.0) * sin((-1 + 2 * (float)j / q) * PI));
}

// Routine to fill the vertex array with co-ordinates of the mapped sample points.
void fillVertexArray(void)
{
    int i, j, k;

    k = 0;
    for (j = 0; j <= q; j++)
        for (i = 0; i <= p; i++)
        {
            vertices[k++] = f(i, j);
            vertices[k++] = g(i, j);
            vertices[k++] = h(i, j);
        }
}





void drawScene(void)
{
    //fill background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    //glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     //gluLookAt(5, 20, 50,2,1, 9, 0, 1, 0);
     //glFrustum(5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

     // Place camera.
    gluLookAt(valX, valY, valZ, valX + sin(angle * PI / 180),
        valY, valZ + cos(angle * PI / 180), 0, 1, 0);
    // ______________________________________________________

    /*glPushMatrix();
    glTranslatef(moveshade, 0.0f, 0.0f);
    if (shadeup) {
        //shade down
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, .2);
        glVertex3f(-40, 5, 15);
        glVertex3f(-40, -5, 15);
        glVertex3f(-40, -5, -5);
        glVertex3f(-40, 5, -5);
        glPopMatrix();

    }

    else {
        //shade up
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, .2);
        glVertex3f(-40, 5, 15);
        glVertex3f(-40, 3, 15);
        glVertex3f(-40, 3, -5);
        glVertex3f(-40, 5, -5);
        glPopMatrix();
    }
    shade();
    glPopMatrix();*/

    static float canoeRotation = 0.0;

// ______________________________________________________

    walls();
    walls2();
    ceiling();
    floor();
    //floor2();
    wallWindow();
    moon();
    //shade();
    lightScone();


    

// ______________________________________________________

    glEnable(GL_TEXTURE_2D);  // Enable texturing
    glBindTexture(GL_TEXTURE_2D, texture[0]);  // Bind the texture
    floor2();  // Render the textured floor
    glDisable(GL_TEXTURE_2D);
 // ______________________________________________________
// light under bed
    if (seeCir)
    {
        seeCir = !seeCir;

        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);//lightbulb color
        glPushMatrix();
        glTranslated(-15, 5, -5);
        glutSolidSphere(1, 10, 10);  //at the origin
        glLightfv(GL_LIGHT2, GL_POSITION, origin);//build the light at origin, too
        glPopMatrix();
        glEnable(GL_LIGHTING);

    }

// ______________________________________________________
 /*
 table.cpp
 */

// Table
    int  i, j;
    vertices = new float[3 * (p + 1) * (q + 1)]; // Dynamic array allocation with new value of p and q. 

    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    fillVertexArray();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Make the approximating triangular mesh.

    glPushMatrix();
    float matAmbAndDifCol5[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifCol5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.50, 0.50, 0.46);
    glScalef(0.4,0.4, 0.4);
    glTranslatef(-45.0, 4.0, 4.0);
    glTranslatef(2.0, -25.0, 4.0);
    glTranslatef(2.0, 4.0, -60.0);
    for (j = 0; j < q; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= p; i++)
        {
            glArrayElement((j + 1) * (p + 1) + i);
            glArrayElement(j * (p + 1) + i);
        }
        glEnd();
    }
    glPopMatrix();

// ______________________________________________________

    glDepthMask(false);
    //bed();
    shade();
    glDepthMask(true);

    //identifyObject(xClick, yClick);
// ______________________________________________________

//draw everything to the buffer, but don't display it, to check clicking
    /*if (selecting)
    {
        lightScone();
        identifyObject(xClick, yClick);
    }
    //draw everything, possibly with results of clicking
    else
    {
        lightScone();
        glutSwapBuffers();
    }*/
// ______________________________________________________
    glPushMatrix();
    glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints4[0][0]);
    glPopMatrix();


    glPushMatrix();
    glScalef(0.4,0.4, 0.4);
    glTranslatef(-45.0, 4.0, 4.0);
    glTranslatef(2.0, -45.0, 4.0);
    glTranslatef(2.0, 4.0, -5.0);
    glRotatef(canoeRotation, 0.0, 1.0, 0.0); 
    canoeRotation += movement;
    // Make a mesh approximation of the Bezier surface.
    glColor3f(0.81, 0.50, 0.46);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glDisable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.t
// ______________________________________________________

    glutSwapBuffers();
    glFlush();
}





// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        red = 1.0; ge = 0.0; b = 0.0;
        glutPostRedisplay();
        break;
    case 'g':
        red = 0.0; ge = 1.0; b = 0.0;
        glutPostRedisplay();
        break;
    case 'b':
        red = 0.0; ge = 0.0; b = 1.0;
        glutPostRedisplay();
        break;
    case 27: // Escape key
        exit(0);
        break;
    default:
        break;
    }

    float lightDifAndSpec1[] = { red, ge, b, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

    glutPostRedisplay();
}

void mouseControl(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT)
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_LIGHTING);


        selecting = true;
        xClick = x;
        yClick = height - y; //for mouse vs window coordinates

        glEnable(GL_LIGHTING);

        glutPostRedisplay();

    }
}

void specialKeyInput(int key, int x, int y)
{
/*
spotlightModified.cpp
*/

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
    glClearColor(0, 0, 0, 0.0);
    //glClearColor(0.309804, 0.309804, 0.184314, 0.0);
    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glEnable(GL_NORMALIZE);  // normalize vectors for proper shading

   
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Create texture index array.
    glGenTextures(1, texture);
    // Load external textures.
    loadExternalTextures();

    qobj = gluNewQuadric();

    glMap1f(GL_MAP1_VERTEX_3, 2.0, 1.0, 3, 6, controlPoints[0]);
    glEnable(GL_MAP1_VERTEX_3);

   

    glEnableClientState(GL_VERTEX_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


//___________________________________________________________
//moon
// Some light property vectors.

/*
lightAndMaterial2.cpp
lines: 110-129
*/
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec[] = { .5, .5, .5, 1.0 };
    float globAmb[] = { 0.08, 0.08, 0.08, 1.0 };

    // Some light properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);


    glEnable(GL_LIGHT0); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

    // Material property vectors for all objects

    float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matShine[] = { 30.0 };

    // Material properties for all objects
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);



//___________________________________________________________
//spotlight
/*
spotlightModified.cpp
lines: 60-96
*/
float lightAmb1[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDifAndSpec1[] = { red, ge, b, 1.0 };  //MJB


// Light properties.   **LIGHTING**
glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);

glEnable(GL_LIGHT1); // Enable particular light source.

glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.

// below lights
// Some light property vectors.
float lightAmb2[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDifAndSpec2[] = { 1.0, 1.0, 1.0, 1.0 };


// Some light properties.
glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb2);
glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec2);
glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec2);


glEnable(GL_LIGHT2); // Enable particular light source.




}
// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "press esc to exit" << endl;
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
    glutCreateWindow("Final");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(16, canoeMotion, 0);
    glViewport(0, 0, 640, 480);
    glutMainLoop();


    return 0;
}