////////////////////////////////////////////////////////////////////////////
// title:jetfighter.cpp
// author:james peacemaker
// class:CPSC 470j
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose: this program create a fighter jet that can fly around using the keyboard
// description: they fighter plane can fly around using the keyboard.
// 4 on the number pad is left
// 6 on the number pad is right
// 8 on the number pad is to pitch up (back on the joystick)
// 2 on the number pad is to pitch down (forward on the joystick)
// 7 on the number pad is to roll left
// 9 on the number pad is to roll right
// + is used to go forward/faster
// - is to used to go backwards/slower
// 0 resets the original view of the plane
/*

  You can only re-use program three scene if you get prior permission from me.  I will out of town for spring break so either write me an email before Saturday or  when we get back from break otherwise assume you are to create a new scene (better be safe then sorry). 
  
    Either reuse or create and render an interesting scene using OpenGL.  You must use double buffering, rotation, translation, and scale for this assignment. 
    
      In this scene you are to create a variety of different light sources and materials.  You must have the following types of lights in your program. 
      
        Ambient light that represents night and day 
        Spotlight (Cannot see light source) that prominently features one part of your scene (not a blank wall) 
        Lamp Light or internal light (must be able to see light source).  Meaning that the use must be able to turn the light on and off and the light source has to be visible within the scene.  Examples christmas lights, a lamp post, a lightning bug, moon...... 
        Material which must appear in your scene 
        A shiny material such as brass, gold, silver. 
        A plastic material. 
        A flat material such as slat. 
        . 
*/
////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

//#include <gl.h>
//#include <glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <time.h>
#include <math.h>
#include <process.h>
#include <fstream.h>

#define BMP 5
#define RGB 3

static GLuint texName[2];
static GLint fogMode;



int currenttexture;
bool freelook;

const int width = 128;
const int height = 128;

static GLubyte rawimage[width*height*BMP];
static GLubyte RGBimage[width][height][RGB];
static GLubyte RGBimage2[width][height][RGB];



//converts the first bmp image into the stone texture
void convertImage(char filename[],const int width,const int height)
{
    const int databytes = width*height*RGB;
    int bytes = 0;
    ifstream infile(filename,ios::in);
    if (filename==0)
    {
        cout<<"File Not Found";
    }
    while( infile >> rawimage[bytes++] )
        ;//read in the image to a buffer
    
    bytes--;
    
    int index = (bytes - databytes);
    
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            RGBimage[i][j][2] = rawimage[index++];
            RGBimage[i][j][1] = rawimage[index++];
            RGBimage[i][j][0] = rawimage[index++];
        }
    }
}


//converts the the bmp star into a texture image
void convertImage2(char filename[],const int width,const int height)
{
    const int databytes = width*height*RGB;
    int bytes = 0;
    ifstream infile(filename,ios::in);
    if (filename==0)
    {
        cout<<"File Not Found";
    }
    while( infile >> rawimage[bytes++] )
        ;//read in the image to a buffer
    
    bytes--;
    
    int index = (bytes - databytes);
    
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            RGBimage2[i][j][2] = rawimage[index++];
            RGBimage2[i][j][1] = rawimage[index++];
            RGBimage2[i][j][0] = rawimage[index++];
        }
    }
}




double posX=0;
double posY=0;
double posZ=0;


double posX10=0;
double posY10=0;
double posZ10=0;
double posX9=0;
double posY9=0;
double posZ9=0;
double posX8=0;
double posY8=0;
double posZ8=0;
double posX7=0;
double posY7=0; 
double posZ7=0;
double posX6=0;
double posY6=0; 
double posZ6=0;
double posX5=0;
double posY5=0;
double posZ5=0;
double posX4=0;
double posY4=0;
double posZ4=0;
double posX3=0;
double posY3=0;
double posZ3=0;
double posX2=0;
double posY2=0; 
double posZ2=0;
double posX1=0;
double posY1=0; 
double posZ1=0;


double pi=3.141592;

double rotateX;//holds the rotation around the x axis
double rotateY;//holds the rotation around the y axis
double rotateZ;//holds the rotation around the z axis
double jump;//holds the value of the planes speed


GLUquadricObj *qobj;//quadratic

void save_image();
const int STRLEN = 100;
typedef char STR[STRLEN];
int Win[2];     // window (x,y) size



void Pause(time_t wait)
{
    time_t start_time = time(0);
    time_t elapse_time = time(0) -start_time;
    while(elapse_time < wait)
    {
        elapse_time = time(0) - start_time;
    }
}



//////////////////////////////////////////////////////
//    PROC: glut_key_action()
//    DOES: this function gets called for any keypresses
//////////////////////////////////////////////////////
void glut_key_action(unsigned char key, int x, int y)
{
    
    switch (key)
    {
    case 'l':
        freelook=!freelook;
        break;  
    case '0'://start over
        rotateX=0;
        rotateY=0;
        rotateZ=0;
        posX=0;
        posY=0;
        posZ=0;
        posX1=0;
        posY1=0;
        posZ1=0;
        posX2=0;
        posY2=0;
        posZ2=0;
        posX3=0;
        posY3=0;
        posZ3=0;
        posX4=0;
        posY4=0;
        posZ4=0;
        posX5=0;
        posY5=0;
        posZ5=0;
        
        jump=0;
        break;
    case 27://exit
        exit(0);
        break;
    case 'q'://exit
        exit(0);
        break;
        
    case 's'://save the image
        save_image();
        //glutPostRedisplay();
        break;
        
    case 'e':
        glEnable(GL_FOG);
        break;
    case 'r':
        glDisable(GL_FOG);
        break;
    case 'f':
    case 'F':
        if (fogMode == GL_EXP) {
            fogMode = GL_EXP2;
            printf ("Fog mode is GL_EXP2\n");
        }
        else if (fogMode == GL_EXP2) {
            fogMode = GL_LINEAR;
            printf ("Fog mode is GL_LINEAR\n");
        }
        else if (fogMode == GL_LINEAR) {
            fogMode = GL_EXP;
            printf ("Fog mode is GL_EXP\n");
        }
        glFogi (GL_FOG_MODE, fogMode);
        glutPostRedisplay();
        break;
        
        
    default:
        break;
    }
    
    switch (key) 
    {
    case '2'://pitch up
        rotateX = int(rotateX + 6) % 360;
        //glutPostRedisplay();
        break;
    case '8'://pitch down
        rotateX = int(rotateX - 4) % 360;
        //glutPostRedisplay();
        break;
    case '4'://turn left
        rotateY = int(rotateY + 4) % 360;
        //glutPostRedisplay();
        break;
    case '6'://turn right
        rotateY = int(rotateY - 4) % 360;
        //glutPostRedisplay();
        break;
    case '7'://roll left
        rotateZ = int(rotateZ + 8) % 360;
        //glutPostRedisplay();
        break;
    case '9'://roll right
        rotateZ = int(rotateZ - 8) % 360;
        //glutPostRedisplay();
        break;
    case '-'://go backwards
        jump=jump+0.3;
        //glutPostRedisplay();
        break;
    case '+'://go forward
        jump=jump-0.3;
        //glutPostRedisplay();
        break;
    }
    
    
    
    
    
    
    
}

/////////////////////////////////////////
//  PROC:   save_image
//  DOES:   saves the current image to a ppm file
/////////////////////////////////////////
void save_image()
{
    FILE *fp;
    STR fname;
    const maxVal=255;
    register int y;
    unsigned char *pixels;
    
    strcpy(fname,"scene.ppm");
    printf("Saving image %s: %d x %d\n", fname,Win[0],Win[1]);
    fp = fopen(fname,"wb");
    if (!fp) {
        printf("Unable to open file '%s'\n",fname);
        return;
    }
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", Win[0], Win[1]);
    fprintf(fp, "%d\n", maxVal);
    
    pixels = new unsigned char [3*Win[0]];
    for ( y = Win[1]-1; y>=0; y-- ) {
        glReadPixels(0,y,Win[0],1,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) pixels);
        fwrite(pixels, 3, Win[0], fp);
    }
    fclose(fp);
}

/*  planes for texture coordinate generation  */
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
/*********************************************************
PROC: myinit()
DOES: performs most of the OpenGL intialization -- don't change
**********************************************************/
void myinit(void)
{
    //glLoadIdentity();
    freelook=false;
    glClearColor (0.3, 0.3, 0.3, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    
    //the first texture
    currenttexture=0;
    convertImage("stone.bmp",width,height );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glGenTextures(2, texName);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, RGBimage);//&checkImage[0][0][0]
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND); //BLEND
    
    
    //the second texture
    currenttexture=1;
    convertImage2("star.bmp",width,height );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, RGBimage2);//&checkImage[0][0][0]
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //BLEND
    
    
    qobj = gluNewQuadric();
    
    
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[] = { 0.25, 0.2, 0.2, 1.5 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat position[] = { -90.0, 100.0, 30.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    //a yellowish lamplight
    GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse1[] = { 1.5, 1.5, 1.0, 1.5 };
    GLfloat specular1[] = { 2.0, 2.0, 1.4, 1.0 };
    //GLfloat diffuse1[] = { 0.5, 0.5, 0.4, 1.5 };
    //GLfloat specular1[] = { 5.0, 5.0, 4, 1.0 };
    
    
    GLfloat position1[] = { -10.0, 5.0, -30.0, 1.0 };
    GLfloat spotdirection1[] = {0.0,-1.0,0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdirection1);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 132);
    
    
    /*a redish spotlight*/
    GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse2[] = { 0.0, 0.0, 0.0, 1.5 };
    GLfloat specular2[] = { 0.8, 0.8, 1.2, 1.0 };
    GLfloat position2[] = { 7.0, 0.0, -30.0, 1.0 };
    GLfloat spotdirection2[] = {-7+posX,1+posY,30+posZ};
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotdirection2);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 32);
    
    
    //first thruster light
    GLfloat ambient3[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse3[] = { 0.1, 0.1, 0.1, 1.5 };
    GLfloat spotdirection3[] = {0,0,1};
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotdirection3);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 40);
    
    //second thruster light
    GLfloat ambient4[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse4[] = { 0.1, 0.1, 0.1, 1.5 };
    GLfloat spotdirection4[] = {0,0,1};
    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotdirection4);
    glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 40);
    
    
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat local_view[] = { 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    
    //    glFrontFace (GL_CW); /**/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    
    
    
    glEnable(GL_FOG);
    {
        GLfloat fogColor[4] = {0.3, 0.3, 0.3, 1};
        
        fogMode = GL_EXP;
        glFogi (GL_FOG_MODE, fogMode);
        glFogfv (GL_FOG_COLOR, fogColor);
        glFogf (GL_FOG_DENSITY, 0.015);
        glHint (GL_FOG_HINT, GL_DONT_CARE);
        glFogf (GL_FOG_START, 0.0);
        glFogf (GL_FOG_END, 200.0);
    }
    glClearColor(0.3, 0.3, 0.3, 1);  /* fog color */
    gluLookAt(0,5,10,(posX-posX10),(posY-posY10),(posZ-posZ10),0,1,0);
    
    
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    /*glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);  
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(1.5);
    */
  }
  
  
  /*********************************************************
  PROC: set_colour();
  DOES: draws a teapot of the given colour -- don't change
  **********************************************************/
  void set_colour(float r, float g, float b)
  {
      float ambient = 0.2;
      float diffuse = 0.7;
      float specular = 0.9;
      GLfloat mat[4];
      /**** set ambient lighting parameters ****/
      mat[0] = ambient*r;
      mat[1] = ambient*g;
      mat[2] = ambient*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_AMBIENT, mat);
      
      /**** set diffuse lighting parameters ******/
      mat[0] = diffuse*r;
      mat[1] = diffuse*g;
      mat[2] = diffuse*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);
      
      /**** set specular lighting parameters *****/
      mat[0] = specular*r;
      mat[1] = specular*g;
      mat[2] = specular*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
      glMaterialf (GL_FRONT, GL_SHININESS, 5);
  }
  
  
  
  
  
  /*********************************************************
  PROC: set_colour();
  DOES: sets the color, material, ambience, diffusion, specular
  **********************************************************/
  
  void set_colour_mat(float r,      //red
      float g,      //green
      float b,      //blue
      float ambient,    //ambient lighting parameter
      float diffuse,    //diffuse lighting parameter
      float specular, //speular lighting parameter
      float shiny)  //the material's shinyness
  {
      
      GLfloat mat[4];
      /**** set ambient lighting parameters ****/
      mat[0] = ambient*r;
      mat[1] = ambient*g;
      mat[2] = ambient*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_AMBIENT, mat);
      
      /**** set diffuse lighting parameters ******/
      mat[0] = diffuse*r;
      mat[1] = diffuse*g;
      mat[2] = diffuse*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);
      
      /**** set specular lighting parameters *****/
      mat[0] = specular*r;
      mat[1] = specular*g;
      mat[2] = specular*b;
      mat[3] = 1.0;
      glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
      glMaterialf (GL_FRONT, GL_SHININESS, shiny);
  }
  
  
  
  void set_colour_trans(float r,        //red
      float g,      //green
      float b,      //blue
      float a,        //alpha
      float ambient,    //ambient lighting parameter
      float diffuse,    //diffuse lighting parameter
      float specular, //speular lighting parameter
      float shiny)  //the material's shinyness
  {
      
      GLfloat mat[4];
      /**** set ambient lighting parameters ****/
      mat[0] = ambient*r;
      mat[1] = ambient*g;
      mat[2] = ambient*b;
      mat[3] = ambient*a;
      glMaterialfv (GL_FRONT, GL_AMBIENT, mat);
      
      /**** set diffuse lighting parameters ******/
      mat[0] = diffuse*r;
      mat[1] = diffuse*g;
      mat[2] = diffuse*b;
      mat[3] = diffuse*a;
      glMaterialfv (GL_FRONT, GL_DIFFUSE, mat);
      
      /**** set specular lighting parameters *****/
      mat[0] = specular*r;
      mat[1] = specular*g;
      mat[2] = specular*b;
      mat[3] = specular*a;
      glMaterialfv (GL_FRONT, GL_SPECULAR, mat);
      glMaterialf (GL_FRONT, GL_SHININESS, shiny);
  }
  
  
  
  
  
  /*********************************************************
  PROC: display()
  DOES: this gets called by the event handler to draw
  the scene, so this is where you need to build
  your scene -- make your changes and additions here
  
    Add other procedures if you like.
  ********************************************************************************************/
  void display(void)
  {
      
	   
      float temp1;
      float temp2;
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
      
      /* glClearColor (red, green, blue, alpha         */
      /* Ignore the meaning of the 'alpha' value for now */
      glClearColor(0.3,0.3,0.3,1);   /* set the background colour */
      /* OK, now clear the screen with the background colour */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      ////////////////////////////////////////////////////////////////////begin airport
      
      glPushMatrix();
      glTranslatef(0,-2,0);
      
      //main body
      //grass (slate)
      //i had to split it up into peices so it would shade properly
      
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
      glPushMatrix();
      set_colour(0.05,0.2,0.0);
      glTranslatef(25,-2,-25);  
      glScalef(50,1,50);       
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glPopMatrix();
      
      glPushMatrix();
      set_colour(0.05,0.3,0.0);
      glTranslatef(-25,-2,-25); 
      glScalef(50,1,50);       
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glTranslatef(0,0,-1);
      glutSolidCube(1.0);
      glPopMatrix();
      
      
      //runwaypavement (more slate)
      glPushMatrix();
      set_colour(0.25,0.25,0.25);
      //set_colour_mat(0.25,0.25,0.25,0.1,5,5,7);
      
      
      glBindTexture(GL_TEXTURE_2D, texName[0]);
      glEnable(GL_TEXTURE_2D);
      
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, 20); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, 20); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, 10); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, 10);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, 10); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, 10); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, 0); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, 0);
      glEnd();
      
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, 0); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, 0); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -10); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -10);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -10); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -10); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -20); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -20);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -20); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -20); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -30); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -30);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -30); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -30); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -40); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -40);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -40); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -40); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -50); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -50);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -50); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -50); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -60); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -60);
      glEnd();
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -60); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -60); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -70); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -70);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -70); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -70); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -80); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -80);
      glEnd();
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -80); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -80); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -90); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -90);
      glEnd();
      
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -90); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -90); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -110); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -110);
      glEnd();
      
      
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -110); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -110); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -140); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -140);
      glEnd();
      
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -140); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -140); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -160); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -160);
      glEnd();
      
      
      
      glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(6,-1.45, -160); 
      glTexCoord2f(0, 10); glVertex3f(-6,-1.45, -160); 
      glTexCoord2f(3, 10); glVertex3f(-6,-1.45, -200); 
      glTexCoord2f(3, 0); glVertex3f(6,-1.45, -200);
      glEnd();
      glDisable(GL_TEXTURE_2D);
      glPopMatrix();    
      
      //yellow line
      glPushMatrix();
      set_colour(0.7,0.7,0.2);
      glTranslatef(6,-1.89,-80);      
      glScalef(0.5,1,200);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      //yellow line
      glPushMatrix();
      set_colour(0.7,0.7,0.2);
      glTranslatef(-6,-1.89,-80);    
      glScalef(0.5,1,200);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      //yellow strips
      glPushMatrix();
      set_colour(0.7,0.7,0.2);
      glTranslatef(0,-1.89,0);  
      glScalef(0.5,1,10);    
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glTranslatef(0,0,-2);  
      glutSolidCube(1.0);
      glPopMatrix();
      
      //begin tower
      set_colour(0.3,0.3,0.3);
      glPushMatrix();
      glTranslatef(-20,4,-80); 
      glScalef(4,12,10);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      //main building
      set_colour(0.3,0.3,0.3);
      glPushMatrix();
      glTranslatef(-25,1,-80); 
      glScalef(10,5,50);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      //main building roof
      set_colour(0.1,0.1,0.1);
      glPushMatrix();
      glTranslatef(-25,3,-80); 
      glScalef(12,1,52);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      
      
      //lightpost
      set_colour(0.0,0.0,0.0);
      glPushMatrix();
      glTranslatef(-10,1,-30); 
      glScalef(0.25,6,0.25);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-10,4,-30);  
      glScalef(1.5,0.5,1.5);       
      
      GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
      glClipPlane (GL_CLIP_PLANE0, eqn);
      glEnable (GL_CLIP_PLANE0);
      glutSolidSphere(0.7, 20,10);
      glDisable (GL_CLIP_PLANE0);
      glTranslatef(0,-1.5,0);   
      
      glScalef(0.8,0.8,0.8);       
      
      set_colour(0.9,0.9,0.5);
      GLdouble eqn2[4] = {0.0, -1.0, 0.0, 0.0};
      glClipPlane (GL_CLIP_PLANE0, eqn2);
      glEnable (GL_CLIP_PLANE0);
      glutSolidSphere(0.7, 20,10);
      glDisable (GL_CLIP_PLANE0);
      
      glPopMatrix();
      
      glPushMatrix();
      set_colour(1,1,0.8);
      glTranslatef(-10,3.6,-30);      
      glScalef(1.0,0.75,1.0);      
      glutSolidCube(1.0);
      glPopMatrix();
      
      glPopMatrix();
      
      
      
      
      
      
      
      //this is the math for determining the position of the plane relative to it's last position
      //i had lots of problems with this and there is probably a much easier way to do it
      
      
      
      posX10=posX9;
      posY10=posY9;
      posZ10=posZ9;
      posX9=posX8;
      posY9=posY8;
      posZ9=posZ8;
      posX8=posX7;
      posY8=posY7;
      posZ8=posZ7;
      posX7=posX6;
      posY7=posY6;  
      posZ7=posZ6;
      posX6=posX5;
      posY6=posY5;  
      posZ6=posZ5;
      posX5=posX4;
      posY5=posY4;
      posZ5=posZ4;
      posX4=posX3;
      posY4=posY3;
      posZ4=posZ3;
      posX3=posX2;
      posY3=posY2;
      posZ3=posZ2;
      posX2=posX1;
      posY2=posY1;  
      posZ2=posZ1;
      posX1=posX;
      posY1=posY;   
      posZ1=posZ;
      
      
      
      posY=posY-(jump*sin(pi*(rotateX/360.0)));
      posX=posX+(sin(pi*(rotateY/360.0))*(cos(pi*(rotateX/360.0))*jump));
      if (rotateY>90&&rotateY<270) temp1=0-cos(pi*(rotateY/360.0));
      else temp1=cos(pi*(rotateY/360.0));
      if (rotateX>90&&rotateX<270) temp2=0-cos(pi*(rotateX/360.0));
      else temp2=cos(pi*(rotateX/360.0));
      posZ=posZ+temp1*temp2*jump;
      //posZ=posZ+(cos(pi*(rotateY/360.0))*(cos(pi*(rotateX/360.0))*jump));
      
      glLoadIdentity();
      
      gluLookAt(4,0,10,(posX-posX10),(posY-posY10),1.5*(posZ-posZ10),0,1,0);
      
      
      
      
      
      glPushMatrix();
      
      glTranslatef(posX,posY-2,posZ);
      glRotatef ((GLfloat) rotateX, 1.0, 0.0, 0.0);
      glRotatef ((GLfloat) rotateY, 0.0, 1.0, 0.0);
      glRotatef ((GLfloat) rotateZ, 0.0, 0.0, 1.0);
      
      
      glTranslatef(0,0,-10);
      //set the cockpit color to a bluish chrome material
      
      
      
      
      
      // i couldn't get the wings (or any other polygons) to shade properly so i made them black
      set_colour_mat(0.1,0.1,0.1,0.1,0.1,0.1,7);
      
      //left wing
      
      //add the star decals to the wings
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texName[1]);
      
      glBegin(GL_QUADS);
      //glBegin (GL_POLYGON);
      glTexCoord2f(0, 0); glVertex3f(-2, 0.0, 4);
      glTexCoord2f(0, 2); glVertex3f(-2, 0.0, 10);
      glTexCoord2f(3, 2); glVertex3f(-8, 0.0, 11);
      glTexCoord2f(3, 0); glVertex3f(-7.5, 0.0, 9); 
      glEnd();
      
      //right wing
      glBegin (GL_QUADS);
      glTexCoord2f(0, 0); glVertex3f(2, 0.0, 4); 
      glTexCoord2f(0, 2); glVertex3f(2, 0.0, 10); 
      glTexCoord2f(3, 2); glVertex3f(8, 0.0, 11); 
      glTexCoord2f(3, 0); glVertex3f(7.5, 0.0, 9); 
      glEnd();
      glDisable(GL_TEXTURE_2D);
      
      
      //set jet fighter color to grey "plastic"
      set_colour_mat(0.8,0.8,0.8,0.0,0.8,0.4,7);
      //nose cone
      glPushMatrix();
      glTranslatef(0,0,-3);
      glRotatef (180, 1.0, 0.0, 0.0);
      glutSolidCone(1.0, 4.0,20,8);
      glPopMatrix();
      
      //base front
      glPushMatrix();
      glTranslatef(0,0,-3);  
      gluCylinder(qobj, 1.0, 1.0, 5.0, 20, 3);
      glPopMatrix();
      
      //base 
      glPushMatrix();
      glTranslatef(0,0,0);  
      gluCylinder(qobj, 1.0, 1.0, 5.0, 20, 2);
      glPopMatrix();
      
      //base back tapered
      glPushMatrix();
      glTranslatef(0,0,5);  
      gluCylinder(qobj, 1.0, 0.5, 3.0, 20, 5);
      glPopMatrix();
      
      //main body
      glPushMatrix();
      glTranslatef(0,0,7);  
      glScalef(4,1,8);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      //tail
      glPushMatrix();
      glTranslatef(0,0,12);  
      glScalef(2,1,4);     
      glutSolidCube(1.0);
      glPopMatrix();
      
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
      //left thruster
      glPushMatrix();
      glTranslatef(1.5,0,11);    
      gluCylinder(qobj, 0.75, 0.75, 4.0, 20, 5);
      set_colour_mat(0.1,0.1,0.1,0.1,0.1,0.1,7);
      gluCylinder(qobj, 0.749, 0.74, 4.0, 20, 5);
      set_colour_mat(0.8,0.8,0.8,0.0,0.8,0.4,7);glPopMatrix();
      
      glPushMatrix();
      glTranslatef(1.5,0,7);      
      gluCylinder(qobj, 0.25, 0.75, 4.0, 20, 5);
      glPopMatrix();
      
      //right thruster
      glPushMatrix();
      glTranslatef(-1.5,0,11);  
      
      gluCylinder(qobj, 0.75, 0.75, 4.0, 20, 5);
      set_colour_mat(0.1,0.1,0.1,0.1,0.1,0.1,7);
      gluCylinder(qobj, 0.749, 0.74, 4.0, 20, 5);
      set_colour_mat(0.8,0.8,0.8,0.0,0.8,0.4,7);
      
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(-1.5,0,7);    
      gluCylinder(qobj, 0.25, 0.75, 4.0, 20, 5);
      glPopMatrix();
      //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
      
      
      //once again polygons set to black
      set_colour_mat(0.1,0.1,0.1,0.1,0.1,0.1,7);
      //left back wing
      glBegin (GL_POLYGON);
      glVertex3f(-2.25, 0.0, 12); 
      glVertex3f(-2.25, 0.0, 15); 
      glVertex3f(-4, 0.0, 16); 
      glVertex3f(-4, 0.0, 14.5); 
      glEnd();
      
      glBegin (GL_POLYGON);
      glVertex3f(-1.5,0.75, 12); 
      glVertex3f(-1.5,0.75, 15); 
      glVertex3f(-1.5,2.5, 16); 
      glVertex3f(-1.5,2.5, 14.5);
      glEnd();
      
      //right back wing
      glBegin (GL_POLYGON);
      glVertex3f(2.25, 0.0, 12); 
      glVertex3f(2.25, 0.0, 15); 
      glVertex3f(4, 0.0, 16); 
      glVertex3f(4, 0.0, 14.5);
      glEnd();
      
      glBegin (GL_POLYGON);
      glVertex3f(1.5,0.75, 12); 
      glVertex3f(1.5,0.75, 15); 
      glVertex3f(1.5,2.5, 16); 
      glVertex3f(1.5,2.5, 14.5);
      glEnd();
      
      //rear of the thrusters. darker segmented cylinders
      glShadeModel(GL_FLAT);
      
      glPushMatrix();
      set_colour_mat(0.3,0.3,0.32,0,0.5,0.8,5);
      glTranslatef(-1.5,0,14);  
      gluCylinder(qobj, 0.75, 0.5, 2.0, 20, 5);
      glPopMatrix();
      
      glPushMatrix();
      glTranslatef(1.5,0,14);    
      set_colour_mat(0.3,0.3,0.32,0,0.5,0.8,5);
      gluCylinder(qobj, 0.75, 0.5, 2.0, 20, 5);
      glPopMatrix();
      
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
      
      glShadeModel(GL_SMOOTH);
      //glowing fire inside the thrusters, gets brighter the more speed
      glPushMatrix();
      set_colour_mat(0.5*jump,0.25*jump,0.02*jump,0.5*jump,0.5*jump,0.5*jump,1);
      glTranslatef(-1.5, 0, 14);
      GLfloat position3[] = {0,0,0};
      glLightfv(GL_LIGHT3, GL_POSITION, position3);
      GLfloat specular3[] = { -0.2*jump, -0.1*jump, -0.05*jump, 1.0 };
      glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
      GLfloat diffuse3[] = { 0.0*jump, 0.0*jump, 0.0*jump, 1.5 };
      glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
      
      
      glutSolidSphere(0.7, 20,10);
      glPopMatrix();
      
      glPushMatrix();
      //set_colour_mat(1,0.5,0.0,1,1,1,1);
      glTranslatef(1.5, 0, 14);
      
      GLfloat position4[] = {0,0,0};
      glLightfv(GL_LIGHT4, GL_POSITION, position4);
      GLfloat specular4[] = { -0.2*jump, -0.1*jump, -0.5*jump, 1.0 };
      glLightfv(GL_LIGHT4, GL_SPECULAR, specular4);
      GLfloat diffuse4[] = { 0.0*jump, 0.0*jump, 0.0*jump, 1.5 };
      glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse4);
      glutSolidSphere(0.7, 20,10);
      glPopMatrix();
      
      
      
      set_colour_trans(0.5,0.5,0.6,5,0.0,0.1,1.3,5);
      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      
      //cockpit front
      glPushMatrix();
      glTranslatef(0,1,0);
      glRotatef (180, 1.0, 0.0, 0.0);
      glutSolidCone(0.75, 3.0,20,8);
      glPopMatrix();
      
      //cockpit back
      glPushMatrix();
      glTranslatef(0,1,1.99);
      glutSolidCone(0.75, 3.0,20,8);
      glPopMatrix();
      
      //cockpit middle
      glPushMatrix();
      glTranslatef(0,1,0);  
      gluCylinder(qobj, 0.75, 0.75, 2.05, 20, 5);
      glPopMatrix();
      glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      
     
      
      //Pause(0.01);
      glPopMatrix();
      
      


	  glPushMatrix();
	  glTranslatef(posX,-2.9,posZ);
      //glRotatef ((GLfloat) rotateX, 1.0, 0.0, 0.0);
      glRotatef ((GLfloat) rotateY, 0.0, 1.0, 0.0);
      //glRotatef ((GLfloat) rotateZ, 0.0, 0.0, 1.0);
      
	  glTranslatef(0,0,-10);
      
	  //shadow!
	  glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      
	  //wings
	  set_colour_trans(0.0,0.0,0.0,3,0.0,0.1,1.3,5);
      glBegin(GL_QUADS);
      glVertex3f(-2, 0.0, 4);
      glVertex3f(-2, 0.0, 10);
      glVertex3f(-8, 0.0, 11);
      glVertex3f(-7.5, 0.0, 9); 
      glEnd();
      
      glBegin (GL_QUADS);
      glVertex3f(2, 0.0, 4); 
      glVertex3f(2, 0.0, 10); 
      glVertex3f(8, 0.0, 11); 
      glVertex3f(7.5, 0.0, 9); 
      glEnd();
      
		
		//left back wing
      glBegin (GL_POLYGON);
      glVertex3f(-2.25, 0.0, 12); 
      glVertex3f(-2.25, 0.0, 15); 
      glVertex3f(-4, 0.0, 16); 
      glVertex3f(-4, 0.0, 14.5); 
      glEnd();
      
      
      //right back wing
      glBegin (GL_POLYGON);
      glVertex3f(2.25, 0.0, 12); 
      glVertex3f(2.25, 0.0, 15); 
      glVertex3f(4, 0.0, 16); 
      glVertex3f(4, 0.0, 14.5);
      glEnd();
      
	
	  //nose
	  glBegin(GL_POLYGON);
      glVertex3f(-0.75, 0.0, 2);
      glVertex3f(-0.75, 0.0, -2);
      glVertex3f(0, 0.0, -5.5);
      glVertex3f(0.75, 0.0, 0);
      glVertex3f(0.75, 0.0, -2); 
      glEnd();
      
	  

	  //body
	  glBegin(GL_QUADS);
      glVertex3f(-2, 0.0, 2);
      glVertex3f(-2, 0.0, 10);
      glVertex3f(2, 0.0, 10);
      glVertex3f(2, 0.0, 2); 
      glEnd();
      
	  glBegin(GL_QUADS);
      glVertex3f(-2.25, 0.0, 10);
      glVertex3f(-2.25, 0.0, 16);
      glVertex3f(2.25, 0.0, 16);
      glVertex3f(2.25, 0.0, 10); 
      glEnd();
      
	  //thrusters
	  glBegin(GL_QUADS);
      glVertex3f(-0.9, 0.0, 16);
      glVertex3f(-1, 0.0, 17);
      glVertex3f(-2.15, 0.0, 17);
      glVertex3f(-2.25, 0.0, 16); 
      glEnd();

	  glBegin(GL_QUADS);
      glVertex3f(0.9, 0.0, 16);
      glVertex3f(1, 0.0, 17);
      glVertex3f(2.15, 0.0, 17);
      glVertex3f(2.25, 0.0, 16); 
      glEnd();


	  glDepthMask(GL_TRUE);
      glDisable(GL_BLEND);
      
	  glPopMatrix();
      

      
      
      
      glutPostRedisplay();
      glutSwapBuffers();
      
}

/*********************************************************
PROC: myReshape()
DOES: handles the window being resized -- don't change
**********************************************************/
void myReshape(int w, int h)
{
    
    Win[0] = w;
    
    Win[1] = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*** this defines the field of view of the camera   ***/
    /*** Making the first 4 parameters larger will give ***/
    /*** a larger field of view, therefore making the   ***/
    /*** objects in the scene appear smaller            ***/
    glFrustum(-0.2,0.2,-0.1,0.1,0.5,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*** this sets the virtual camera          ***/
    /*** gluLookAt( x,y,z,   x,y,z   x,y,z );  ***/
    /***            camera  look-at camera-up  ***/
    /***            pos'n    point   vector    ***/
    
    /*** place camera at (x=4, y=6, z=20), looking at origin,
    y-axis being up         ***/
    //  gluLookAt(4,6,20,0,0,0,0,1,0);
    gluLookAt(posX,posY,posZ,0,0,-10,0,1,0);
    
}

/*********************************************************
PROC: main()
DOES: calls initialization, then hands over control
to the event handler, which calls 
display() whenever the screen needs to be redrawn
**********************************************************/
int main(int argc, char** argv)
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (10, 30);
    
    glutInitWindowSize(780,390);
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc (myReshape);
    glutKeyboardFunc( glut_key_action );
    
    printf("An OpenGL Still Life\n");
    printf("Press 's' to save image\n");
    printf("Press 'q' to quit\n");
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;         // never reached
}

