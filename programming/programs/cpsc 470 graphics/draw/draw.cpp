

////////////////////////////////////////////////////////////////////////////
// title:draw.cpp
// author:james peacemaker
// class:CPSC 470j
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:this program is a paint program using openGL
// description:Create a paint program similar to the one shown in class. 
/*
The paint program will have the following iconic task 

  Draw A Circle: The circle can either be filled or wireframe 
  Draw an n sided polygon:	The n sided polygon can either be filled or wireframe 
  Draw Text: Text can be increase or decreased in size. 
  Lines: Lines can either be solid, dashed or dotted 
  Curves:  Given three point draw a curve 
  Rotating Square:	Rotation can be turned on or off 
  
	Attribute Options 
	The options for filling, wireframe can either be a submenu or an actual icon. 
	The line style solid, dashed, dotted must be a submenu option. 
	The text increase or decrease size must be a submenu option. 
	Rotation must be a submenu option 
	
	  Menu must include 
	  quit 
	  clear 
	  increase font size/ decrease font size 
	  Rotation on or off 
	  Color Selection 
	  The fill is optional but must be represented either by a icon or submenu 
*/
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <stdlib.h>
#include <glut.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <math.h>

//set the choices for the mouse function
#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define POINTS 4
#define TEXT 5
#define CURVE 6
#define CIRCLE 7
#define SQUARE 8
#define POLYGON 9
#define CLEAR 10


void mouse(int, 	//button
		   int, 	//state of that buttom (up or down)
		   int, 	//x coordinate
		   int);	//y coordinate
//purpose: the purpose of this function is to take mouse intput and apply it to do useful information
//description: this function does all of the drawing and user interface
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse
//errors:




void key(unsigned char,int,int);
//purpose: the purpose of this function is to take keyboard intput and apply it to do useful information
//description: this function reacts to keyboard input
//preconditions: all parameters exist and an openGl window exists, a keyboard button is used
//postconditions: the program is interupted and responds to user input from the Keyboard
//errors:


void draw(void);
//purpose: the purpose of this function is to draw all of the original content as well as when it is reshaped
//description: 10 boxes are drawn at teh top to to represent drawing icons
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: theprogram is drawn to the screen
//errors:


void myReshape(int, 	//new width of the window
			   int);	//new height of the window
//purpose: the purpose of this function is to redraw the window and resize everything when the window is resized
//description: resizes the window and coordinate system and then calls draw
//preconditions: all parameters exist and an openGl window exists, 
//postconditions: the program is resized and and starts new
//errors:


void init(void);
//purpose: the purpose of this function is to initialize certain openGl variable 
// including the window, the viewport, viewing area
//description: this function stsarts everything
//preconditions: none
//postconditions: the viewing way is set and the screen is cleared
//errors:




void screen_box(int,//x position of the box to be drawn
				int,//y position of the box to be drawn
				int);//size of the box to be drawn
//purpose: the purpose of this function is to draw a certain size box at a given coordinates
//description: it draws a box, that's simple enough
//preconditions: all parameters exist and an openGl window exists, parameters must exist
//postconditions: a given box is drawn to the screen
//errors:


void right_menu(int);//the choice
//purpose: the purpose of this function is to take mouse intput and open a menu when the right button is clicked
//description: gives us options including line width, color, type, and fill. also quit and clear
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse menu
//errors:


void middle_menu(int);
//purpose: not used
//description: not used
//preconditions: not sed
//postconditions: not used
//errors:


void color_menu(int);//selection choice (1..8) depending on color
//purpose: the purpose of this function is to have a menu to select the color of the object to be drawn
//description: this function has 8 choices, primary, and secondary colors as well as white and black
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse
//errors:


void pixel_menu(int);//selection choice. to raise or lower pixel size
//purpose: the purpose of this function is to take mouse intput and apply it to a menu to change line thickness
//description: either doubles the width or cuts it in half
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse menu
//errors:



void fill_menu(int);//menu selection. to fill or not to fill. that is the question
//purpose: the purpose of this function is to take mouse intput from a menu and apply it to select to fill or not
//description: fill or no fill is selected from the menu
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse
//errors:


int pick(int,	//x coordinate
		 int);	//y coordinate
//purpose: the purpose of this function is to take mouse coordnates and to find the are tat they are in
//description: this function is used for icon selection
//preconditions: all parameters exist and an openGl window exists, amouse button is used
//postconditions: the program is interupted and responds to user input from the mouse
//errors:


void printString(char*, //the contents of the string
				 int);	//the length of the string
//purpose: the purpose of this function is to print a string at the bottom of the screen
//description: this function does all of the text at the botom
//preconditions: all parameters exist and an openGl window exists, 
//postconditions: words are output
//errors:


GLint ww=500;		//the window width, initially set to 500
GLint wh=500;		//the window height, initially set to 500
GLfloat size=3.0;	//the width of a line
int draw_mode=0;	//the area representing a drawing choice which is selected by the mouse
int rx; 			//the x raster position used for text
int ry; 			//the y raster position, used for text

GLfloat r=1.0;		//the red value
GLfloat g=1.0;		//the green value
GLfloat b=1.0;		//the blue value
int fill=0; 		//whether or not the polygon will be filled when drawn

void init(void)
{
	glClearColor(0.8,0.8,0.8,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)ww,0.0,(GLdouble)wh,-1.0,1.0);
	//gluOrtho2D(0.0,1.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,ww,wh);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glViewport(0,0,w,h);
	glClearColor(0.8,0.8,0.8,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glFlush();
	
	//gluOrtho2D(0.0,1.0,0.0,1.0);
	ww=w;
	wh=h;
}

void mouse(int btn, int state, int x, int y)
{
	static int count;	//counts # of times mouse is clicked
	static int xp[100]; //holds the x portion of the coordinates
	static int yp[100]; //holds the y portion of the coordinates
	int where;			//holds a position
	double radius;		//holds the value of a radius
	
	if((btn==GLUT_LEFT_BUTTON) && (state==GLUT_DOWN))
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		where=pick(x,y);
		glColor3f(r,g,b);
		
		if (where!=0)
		{
			count=0;
			draw_mode=where;
		}
		else if(draw_mode==LINE)
		{
			if(count==0)
			{
				count++;
				xp[0]=x;
				yp[0]=y;
			}
			else 
			{
				glBegin(GL_LINES);
				glVertex2i(x,wh-y);
				glVertex2i(xp[0],wh-yp[0]);
				glEnd();
				//draw_mode=0;
				count=0;
			}
		}
		else if(draw_mode==RECTANGLE)
		{
			if(count==0)
			{
				count++;
				xp[0]=x;
				yp[0]=y;
			}
			else
			{
				if(fill)
				{
					glBegin(GL_POLYGON);
				}
				else
				{
					glBegin(GL_LINE_LOOP);
				}
				glVertex2i(x,wh-y);
				glVertex2i(x,wh-yp[0]);
				glVertex2i(xp[0],wh-yp[0]);
				glVertex2i(xp[0],wh-y);
				glEnd();
				//draw_mode=0;
				count=0;
			}
			
		}
		else if(draw_mode==TRIANGLE)
		{
			if ((count==0))
			{
				xp[count]=x;
				yp[count]=y;
				count++;
			}
			else
			{
				xp[count]=x;
				yp[count]=y;
				
				glBegin(GL_LINES);
				glVertex2i(xp[count],wh-yp[count]);
				glVertex2i(xp[count-1],wh-yp[count-1]);
				glEnd();
				
				if((count==2))
				{
					if(fill)
					{
						glBegin(GL_POLYGON);
					}
					else
					{
						glBegin(GL_LINE_LOOP);
					}
					for(int i=0;i<=count;i++)
					{
						glVertex2i(xp[i],wh-yp[i]);
					}
					glVertex2i(x,wh-y);
					glEnd();
					draw_mode=0;
					count=0;
				}
				count++;
			}
		}
		else if(draw_mode==POINTS)
		{
			y=wh-y;
			glBegin(GL_POLYGON);
			glVertex2f(x+size,y+size);
			glVertex2f(x-size,y+size);
			glVertex2f(x-size,y-size);
			glVertex2f(x+size,y-size);
			glEnd();	
		}
		else if(draw_mode==TEXT)
		{
			//set raster positions
			rx=x;
			ry=wh-y;
			
			
			glRasterPos2i(rx,ry);
			count=0;
		}
		else if(draw_mode==CURVE)
		{
			if (count==0)
			{
				xp[0]=x;
				yp[0]=y;
				count++;
			}
			else
			{
				glTranslatef(xp[0],wh-yp[0],0.0);
				if(fill)
					glBegin(GL_POLYGON);
				else
					glBegin(GL_LINE_STRIP);
				
				float angle=3.14159;
				int radius=sqrt((x-xp[0])*(x-xp[0])+(y-yp[0])*(y-yp[0]));
				float temp=angle/25;
				for(int i=0;i<26;i++)
				{
					glVertex2f(radius*cos(angle),radius*sin(angle));
					angle=angle-(temp);
				}
				glEnd();
				
				glFlush();
				
				glTranslatef(-xp[0],-(wh-yp[0]),0.0);
				//draw_mode=0;
				count=0;
			}
		}
		else if(draw_mode==CIRCLE)
		{
			if (count==0)
			{
				xp[0]=x;
				yp[0]=y;
				count++;
			}
			else
			{
				glTranslatef(xp[0],wh-yp[0],0.0);
				if(fill)
					glBegin(GL_POLYGON);
				else
					glBegin(GL_LINE_LOOP);
				
				float angle=3.14159;
				int radius=sqrt((x-xp[0])*(x-xp[0])+(y-yp[0])*(y-yp[0]));
				float temp=angle/25;
				for(int i=0;i<51;i++)
				{
					glVertex2f(radius*cos(angle),radius*sin(angle));
					angle=angle-(temp);
				}
				glEnd();
				
				glFlush();
				
				glTranslatef(-xp[0],-(wh-yp[0]),0.0);
				//draw_mode=0;
				count=0;
			}
		}
		else if(draw_mode==SQUARE)
		{
			
			
			
			
			
			
		}
		else if(draw_mode==POLYGON)
		{
			if ((count==0))
			{
				xp[count]=x;
				yp[count]=y;
				count++;
			}
			else
			{
				xp[count]=x;
				yp[count]=y;
				
				glBegin(GL_LINES);
				glVertex2i(xp[count],wh-yp[count]);
				glVertex2i(xp[count-1],wh-yp[count-1]);
				glEnd();
				
				if((xp[0]-x<10)&&(xp[0]-x>-10)&&(yp[0]-y<10)&&(yp[0]-y>-10))
					//if within area of first point then close line loop
				{
					if(fill)
					{
						glBegin(GL_POLYGON);
					}
					else
					{
						glBegin(GL_LINE_LOOP);
					}
					for(int i=0;i<=count;i++)
					{
						glVertex2i(xp[i],wh-yp[i]);
					}
					glVertex2i(x,wh-y);
					glEnd();
					draw_mode=0;
					count=0;
				}
				count++;
			}
		}
		else if(draw_mode==CLEAR){draw();}
		glPopAttrib();
		glFlush();
	}
}


void printString(char *s, int length)
{
	glColor3f(0.7,0.7,0.7);
	glBegin(GL_POLYGON);
	glVertex2f(0.05*ww,0.1*wh);
	glVertex2f(0.05*ww,0.05*wh);
	glVertex2f(0.95*ww,0.05*wh);
	glVertex2f(0.95*ww,0.1*wh);
	glEnd();	
	
	
	glColor3f(0.0,0.0,1.0);
	rx=0.1*ww;
	for(int i=0;i<length;i++)
	{
		glRasterPos2i(rx,0.075*wh);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
		rx=rx+glutBitmapWidth(GLUT_BITMAP_9_BY_15, s[i]);
	}
	glFlush();
	glColor3f(r,g,b);
	
}



int pick(int x, int y)
{
	y=wh-y;
	if(y<wh-ww/10) return NULL;
	else if(x<1*ww/10)
	{
		printString("Draw a line. Make endpoints", 27);
		return LINE;
	}
	else if(x<2*ww/10)
	{
		printString("Draw a Rectangle. Make opposite corners", 51);
		return RECTANGLE;
	}		
	else if(x<3*ww/10)
	{
		printString("Draw a Triangle. Make 3 Vertices", 32);
		return TRIANGLE;
	}
	else if(x<4*ww/10) 
	{
		printString("Draw points. Just Click", 23);
		return POINTS;
	}
	else if(x<5*ww/10)
	{
		printString("Make text. Click and type", 25);
		return TEXT;
	}
	else if(x<6*ww/10)
	{
		printString("Draw a Curve. Make 2 points", 27);
		return CURVE;
	}
	else if(x<7*ww/10)
	{
		printString("Draw a Circle. Make a center and outer point", 44);
		return CIRCLE;
	}
	else if(x<8*ww/10)
	{
		printString("Nevermind", 9);
		return SQUARE;
	}
	else if(x<9*ww/10) 
	{
		printString("Draw a polygon. Make vertices. Connect to end", 45);
		return POLYGON;
	}
	else if(x<10*ww/10)
	{
		printString("Click the screen to Clear", 25);
		return CLEAR;
	}
	else return NULL;
}

void screen_box(int x,int y, int s)
{
	glBegin(GL_QUADS);
	glVertex2i(x,y);
	glVertex2i(x+s,y);
	glVertex2i(x+s,y+s);
	glVertex2i(x,y+s);
	glEnd();
	glFlush();	
	glColor3f(0.0,0.0,0.5);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x,y);
	glVertex2i(x+s,y);
	glVertex2i(x+s,y+s);
	glVertex2i(x,y+s);
	glEnd();
	glFlush();
	glColor3f(r,g,b);
	
}

void right_menu(int id)
{
	if (id==1) exit(0);
	if (id==2) draw();
}

void middle_menu(int id)
{
	//not used
}

void color_menu(int id)
{
	if(id==1)	//red
	{
		r=1.0;
		g=0.0;
		b=0.0;
	}
	if(id==2)	//green
	{
		r=0.0;
		g=1.0;
		b=0.0;
	}
	if(id==3)	//blue
	{
		r=0.0;
		g=0.0;
		b=1.0;
	}
	if(id==4)	//cyan
	{
		r=0.0;
		g=1.0;
		b=1.0;
	}
	if(id==5)	//magenta
	{
		r=1.0;
		g=0.0;
		b=1.0;
	}
	if(id==6)	//yellow
	{
		r=1.0;
		g=1.0;
		b=0.0;
	}
	if(id==7)	//white
	{
		r=1.0;
		g=1.0;
		b=1.0;
	}
	if(id==8)	//black
	{
		r=0.0;
		g=0.0;
		b=0.0;
	}
}

void fill_menu(int id)
{
	if(id==1)
	{
		fill = 1;
	}
	else 
	{
		fill=0;
	}
}


void pixel_menu(int id)
{
	if (id==1)//increase size
	{
		size=size*2;
		glLineWidth(size);
	}
	else if(size>1)//decrease size
	{
		size=size/2;
		glLineWidth(size);
	}
}



void line_menu(int id)
{
	if (id==1)//solid line
	{
		glLineStipple(1,0xFFFF);
		glEnable(GL_LINE_STIPPLE);
	}
	else if(id==2)//dotted line
	{
		glLineStipple(1,0x3333);
		glEnable(GL_LINE_STIPPLE);
	}
	else if(id==3)//dashed line
	{
		glLineStipple(1,0xFF00);
		glEnable(GL_LINE_STIPPLE);
	}
}



void key(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:
		exit(0); /*exit on esc*/
		break;
	default:
		break;
	}
	if(draw_mode!=TEXT)
	{return;}
	glRasterPos2i(rx,ry);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, key);
	rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, key);
}

void draw(void)
{
	glLineStipple(1,0xFFFF);
	glEnable(GL_LINE_STIPPLE);
	
	
	int shift=0;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	//draw the icons at the top
	glColor3f(0.8,0.8,0.8);
	screen_box(0*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(1*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(2*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(3*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(4*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(5*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(6*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(7*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(8*ww/10,wh-ww/10,ww/10);
	
	glColor3f(0.8,0.8,0.8);
	screen_box(9*ww/10,wh-ww/10,ww/10);
	
	
	glColor3f(0.0,0.0,0.0);
	
	//draw pictures in the boxes for icons
	glBegin(GL_LINES);
	glVertex2i(wh/40,wh-ww/20);
	glVertex2i(wh/40+ww/20,wh-ww/20);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex2i(1*ww/10+ww/40,wh-ww/100);
	glVertex2i(2*ww/10-ww/40,wh-ww/100);
	glVertex2i(2*ww/10-ww/40,wh-ww/10+ww/100);
	glVertex2i(1*ww/10+ww/40,wh-ww/10+ww/100);
	glEnd();
	
	
	glBegin(GL_TRIANGLES);
	glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
	glVertex2i(ww/5+ww/20,wh-ww/40);
	glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
	glEnd();
	
	
	glTranslatef(5.5*ww/10,wh-ww/20,0.0);
	glBegin(GL_LINE_STRIP);
	float angle=3.14159;
	int radius=10;
	float temp=angle/25;
	for(int i=0;i<26;i++)
	{
		glVertex2f(radius*cos(angle),radius*sin(angle));
		angle=angle-(temp);
	}
	glEnd();
	glFlush();
	glTranslatef(-(5.5*ww/10),-(wh-ww/20),0.0);
	
	glTranslatef(6.5*ww/10,wh-ww/20,0.0);
	glBegin(GL_POLYGON);
	for(i=0;i<51;i++)
	{
		glVertex2f(radius*cos(angle),radius*sin(angle));
		angle=angle-(temp);
	}
	glEnd();
	glFlush();
	glTranslatef(-(6.5*ww/10),-(wh-ww/20),0.0);
	
	
	
	glBegin(GL_POLYGON);
	glVertex2i(8*ww/10+ww/40,wh-ww/10+ww/40);
	glVertex2i(8*ww/10+ww/20,wh-ww/40);
	glVertex2i(8*ww/10+3*ww/40,wh-ww/10+ww/40);
	glVertex2i(9*ww/10-ww/40,wh-ww/100);
	
	glEnd();
	
	
	glBegin(GL_LINES);
	glVertex2i(9*ww/10+ww/40,wh-ww/100);
	glVertex2i(10*ww/10-ww/40,wh-ww/10+ww/100);
	glVertex2i(9*ww/10+ww/40,wh-ww/10+ww/100);
	glVertex2i(10*ww/10-ww/40,wh-ww/100);
	glEnd();
	
	
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2i(3*ww/10+ww/20, wh-ww/20);
	glEnd();
	
	
	
	glRasterPos2i(2*ww/5, wh-ww/20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
	glRasterPos2i(2*ww/5+shift,wh-ww/20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
	shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
	glRasterPos2i(2*ww/5+shift+shift,wh-ww/20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	
	
	
	
	
	//draw rectangle for display at bottom
	glColor3f(0.7,0.7,0.7);
	glBegin(GL_POLYGON);
	glVertex2f(0.05*ww,0.1*wh);
	glVertex2f(0.05*ww,0.05*wh);
	glVertex2f(0.95*ww,0.05*wh);
	glVertex2f(0.95*ww,0.1*wh);
	glEnd();	
	glColor3f(r,g,b);
	
	printString("Click on an icon above to start drawing", 41);
	
	
	glFlush();
	glColor3f(r,g,b);
	glPopAttrib();
	glFlush();
	glPushMatrix();
}

int main (int argc, char** argv)
{//begin main
	int c_menu;
	int p_menu;
	int f_menu;
	int l_menu;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(50,50);
	glutCreateWindow("draw");
	
	//create color menu
	c_menu=glutCreateMenu(color_menu);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Cyan",4);
	glutAddMenuEntry("Magenta",5);
	glutAddMenuEntry("Yellow",6);
	glutAddMenuEntry("White",7);
	glutAddMenuEntry("Black",8);
	
	//create pixel size menu
	p_menu=glutCreateMenu(pixel_menu);
	glutAddMenuEntry("increase pixel size",1);
	glutAddMenuEntry("decrease pixel size",2);
	
	//create fill menu
	f_menu=glutCreateMenu(fill_menu);
	glutAddMenuEntry("fill on", 1);
	glutAddMenuEntry("fill off", 2);
	
	//create line type menu
	l_menu=glutCreateMenu(line_menu);
	glutAddMenuEntry("solid", 1);
	glutAddMenuEntry("dotted", 2);
	glutAddMenuEntry("dashed", 3);
	
	glutCreateMenu(middle_menu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	
	//right button menu
	glutCreateMenu(right_menu);
	glutAddSubMenu("Colors",c_menu);
	glutAddSubMenu("Pixel Size",p_menu);
	glutAddSubMenu("Fill",f_menu);
	glutAddSubMenu("Line Type",l_menu);
	glutAddMenuEntry("quit",1);
	glutAddMenuEntry("clear",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}




