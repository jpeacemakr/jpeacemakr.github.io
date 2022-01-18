////////////////////////////////////////////////////////////////////////////
// title:new.cpp
// author:james peacemaker
// class:CPSC 470j
// e-mail adress:jpeac1ij@mwc.edu
// language:C++
// purpose:randomly generates a maze and then finds the path to the exit
// description:uses openGL to draw the maze and object
////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <stdlib.h>
#include <glut.h>
//#include <D:\Microsoft Visual Studio\VC98\Include\glut.h>
#include <string.h>
#include <time.h>
#include <dos.h>

GLint ww=300;
GLint wh= 300;


//structure for a square element in the maze matrix
struct square
{
	bool top;
	bool bottom;
	bool left;
	bool right;
	bool topbreakable;
	bool bottombreakable;
	bool leftbreakable;
	bool rightbreakable;
	bool visited;
	int sides;
};

struct square maze[11][11];




void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	//gluOrtho2D(0.0,1.0,0.0,1.0);
}

void reshape(int width, int height)
{
	ww=width;
	wh=height;
	glViewport(0,0,(GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	//gluOrtho2D(0.0,1.0,0.0,1.0);
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
}


//checks to see if all array elements have been visited
bool allvisited(void)
{
	int x=0;
	int y=0;
	int numvisited=0;
	while (x<12)
	{
		y=0;
		while (y<12)
		{
			if (maze[x][y].visited==true)
				numvisited++;
			y++;
		}
		x++;
	}
	if (numvisited==100)
		return true;
	else 
		return false;
}



//puts a square in the maze at the coordinates x,y
void putsquare(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.5,0.5,0.5);
	glVertex2f((0.05+(y-1)*(0.09)+0.02),(0.05+(x-1)*(0.09)+0.02));
	glVertex2f((0.05+(y-1)*(0.09)+0.02),(0.05+(x-1)*(0.09)+0.07));
	glVertex2f((0.05+(y-1)*(0.09)+0.07),(0.05+(x-1)*(0.09)+0.07));
	glVertex2f((0.05+(y-1)*(0.09)+0.07),(0.05+(x-1)*(0.09)+0.02));
	glEnd();
	glFlush();
	//sleep(1);
}


//draws the maze
void putmaze(void)
{


	int tempx=0;
	int tempy=0;
	while (tempx<12)
	{
		tempy=0;
		while (tempy<12)
		{
			if ((tempx>=1)&&(tempx<=10)&&(tempy>=1)&&(tempy<=10))
			{
				if(maze[tempx][tempy].left==true)
				{
					//draw a line from [((0.9y)+0.05),((0.9x)+0.05)] to [((0.9(y))+0.05),((0.9(y+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.5,0.5,0.5);
					glVertex2f((0.09*tempy+0.05),(0.09*tempx+0.05));
					glVertex2f((0.09*(tempy+1)+0.05),(0.09*(tempx)+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
					
				}
				
				if(maze[tempx][tempy].right==true)
				{
					//draw a line from [((0.9y)+0.05),((0.9(x+1))+0.05)] to [((0.9(y+1))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.5,0.5,0.5);
					glVertex2f(((0.09*(tempy))+0.05),((0.09*(tempx+1))+0.05));
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}
				
				if(maze[tempx][tempy].bottom==true)
				{
					//draw a line from [((0.9y)+0.05),((0.9x)+0.05)] to [((0.9(y))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.5,0.5,0.5);
					glVertex2f(((0.09*tempy)+0.05),((0.09*tempx)+0.05));
					glVertex2f(((0.09*(tempy))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}
				
				if(maze[tempx][tempy].top==true)
				{
					//draw a line from [((0.9(y+1))+0.05),((0.9x)+0.05)] to [((0.9(y+1))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.5,0.5,0.5);
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*tempx)+0.05));
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}
				if(maze[tempx][tempy].leftbreakable==false)
				{
					//draw a line from [((0.9y)+0.05),((0.9x)+0.05)] to [((0.9(y))+0.05),((0.9(y+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.0,0.0,1.0);
					glVertex2f((0.09*tempy+0.05),(0.09*tempx+0.05));
					glVertex2f((0.09*(tempy+1)+0.05),(0.09*(tempx)+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
					
				}
				
				if(maze[tempx][tempy].rightbreakable==false)
				{
					//draw a line from [((0.9y)+0.05),((0.9(x+1))+0.05)] to [((0.9(y+1))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.0,0.0,1.0);
					glVertex2f(((0.09*(tempy))+0.05),((0.09*(tempx+1))+0.05));
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}
				
				if(maze[tempx][tempy].bottombreakable==false)
				{
					//draw a line from [((0.9y)+0.05),((0.9x)+0.05)] to [((0.9(y))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.0,0.0,1.0);
					glVertex2f(((0.09*tempy)+0.05),((0.09*tempx)+0.05));
					glVertex2f(((0.09*(tempy))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}
				
				if(maze[tempx][tempy].topbreakable==false)
				{
					//draw a line from [((0.9(y+1))+0.05),((0.9x)+0.05)] to [((0.9(y+1))+0.05),((0.9(x+1))+0.05)]
					tempx--;tempy--;
					glBegin(GL_LINES);
					glColor3f(0.0,0.0,1.0);
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*tempx)+0.05));
					glVertex2f(((0.09*(tempy+1))+0.05),((0.09*(tempx+1))+0.05));
					glEnd();
					glFlush();
					tempy++;tempx++;
				}




			}
			tempy++;
		}
		tempx++;
	}
	glFlush();



}








void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	//glPushMatrix();
	
	
	//initialize the maze with all walls up
	int x=0;
	int y=0;
	while (x<12)
	{
		y=0;
		while (y<12)
		{
			maze[x][y].top=true;
			maze[x][y].bottom=true;
			maze[x][y].left=true;
			maze[x][y].right=true;
			maze[x][y].visited=false;
			maze[x][y].sides=4;
			if ((x==1)||(x==11))
				maze[x][y].leftbreakable=false;
			else
				maze[x][y].leftbreakable=true;
			
			if ((x==10)||(x==0))
				maze[x][y].rightbreakable=false;
			else
				maze[x][y].rightbreakable=true;
			
			if ((y==1)||(y==11))
				maze[x][y].bottombreakable=false;
			else
				maze[x][y].bottombreakable=true;
			
			if ((y==10)||(x==0))
				maze[x][y].topbreakable=false;
			else
				maze[x][y].topbreakable=true;
			
			y++;
		}
		x++;
	}

	putmaze();
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	srand(time(0));

	int randnum;
	//time to knock down wall and actually create the maze
	//start at the beginning and break through walls randomly to make a maze
	//until all squares of the matrix are visited
	//doesn't break through a wall when 2 walls of that square are already broken
	x=1;
	y=1;
	maze[x][y].visited=true;
	while (!allvisited())
	{
		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		putmaze();
		putsquare(x,y);

		randnum=(rand()%4)+1;
		if (randnum==1)//move up
		{
			if (maze[x][y].topbreakable==true)
			{
				if (maze[x][y].top==true)
				{
					if ((maze[x][y].sides>1) && (maze[x][y+1].sides>2))
					{
						if(((maze[x][y].left==true)||(maze[x][y+1].left==true)||(maze[x-1][y].top==true))&&((maze[x][y].right==true)||(maze[x][y+1].right==true)||(maze[x+1][y].top==true))) 
						{
							maze[x][y].sides--;
							maze[x][y+1].sides--;
							maze[x][y].top=false;
							maze[x][y+1].bottom=false;
							y++;
							maze[x][y].visited=true;
						}
					}
				}
				else
				{
					y++;
					maze[x][y].visited=true;
				}
			}
		}
		
		
		else if (randnum==2)//move right
		{
			if (maze[x][y].rightbreakable==true)
			{
				if (maze[x][y].right==true)
				{
					if ((maze[x][y].sides>1) && (maze[x+1][y].sides>2))
					{
						if(((maze[x][y].top==true)||(maze[x][y+1].right==true)||(maze[x+1][y].top==true))&&((maze[x][y].bottom==true)||(maze[x+1][y].bottom==true)||(maze[x][y-1].right==true))) 
						{
							maze[x][y].sides--;
							maze[x+1][y].sides--;
							maze[x][y].right=false;
							maze[x+1][y].left=false;
							x++;
							maze[x][y].visited=true;
						}
					}
				}
				else
				{
					x++;
					maze[x][y].visited=true;
				}
			}
		}
		
		else if (randnum==3)//move down
		{
			if (maze[x][y].bottombreakable==true)
			{
				if (maze[x][y].bottom==true)
				{
					if ((maze[x][y].sides>1) && (maze[x][y-1].sides>2))
					{
						if(((maze[x][y].left==true)||(maze[x][y-1].left==true)||(maze[x-1][y].bottom==true))&&((maze[x][y].right==true)||(maze[x+1][y].bottom==true)||(maze[x][y-1].right==true)))
						{
							maze[x][y].sides--;
							maze[x][y-1].sides--;
							maze[x][y].bottom=false;
							maze[x][y-1].top=false;
							y--;
							maze[x][y].visited=true;
						}
					}
				}
				else
				{
					y--;
					maze[x][y].visited=true;
				}
			}
		}
		
		else if(randnum==4)//move left
		{
			if (maze[x][y].leftbreakable==true)
			{
				if (maze[x][y].left==true)
				{
					if ((maze[x][y].sides>1) && (maze[x-1][y].sides>2))
					{
						if(((maze[x][y].top==true)||(maze[x-1][y].top==true)||(maze[x][y+1].left==true))&&((maze[x][y].bottom==true)||(maze[x-1][y].bottom==true)||(maze[x][y-1].left==true)))
						{
							maze[x][y].sides--;
							maze[x-1][y].sides--;
							maze[x][y].left=false;
							maze[x-1][y].right=false;
							x--;
							maze[x][y].visited=true;
						}
					}
				}
				else
				{
					x--;
					maze[x][y].visited=true;
				}
			}
		}
	}
	
	
	
		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		putmaze();
		


	//now it is time to get the cube to the finish
	//start cube at beginning of the maze [1,1] and traverse till it reaches the end [10,10]
	//this part works on the principle that if someone follows along the right wall of a maze 
	//then that person will make it to the exit
	x=1;
	y=1;
	putsquare(x,y);
	int direction=2;
	while (!((x==10)&&(y==10)))
	{
		
		if (direction==2)
		{
			while ((maze[x][y].bottom==true)&&(maze[x][y].right==false))
			{
				x++;//move right
				putsquare(x,y);
			}
			putsquare(x,y);
			if (maze[x][y].bottom==false)
			{
				y--;
				direction=3;
				putsquare(x,y);
				if (maze[x][y].left==false)
				{
					x--;
					direction=4;
					putsquare(x,y);
				}
			}
			else
			{
				direction=1;
			}
		}
		
		
		if (direction==3)
		{
			while ((maze[x][y].left==true)&&(maze[x][y].bottom==false))
			{
				y--;//move down
				putsquare(x,y);
			}
			putsquare(x,y);
			if (maze[x][y].left==false)
			{
				x--;
				direction=4;
				putsquare(x,y);
				if (maze[x][y].top==false)
				{
					y++;
					direction=1;
					putsquare(x,y);
				}
			}
			else
			{
				direction=2;
			}
		}
		
		
		if (direction==4)
		{
			while ((maze[x][y].top==true)&&(maze[x][y].left==false))
			{
				x--;//move left
				putsquare(x,y);
			}
			putsquare(x,y);
			if (maze[x][y].top==false)
			{
				y++;
				direction=1;
				putsquare(x,y);
				if (maze[x][y].right==false)
				{
					x++;
					direction=2;
					putsquare(x,y);
				}
			}
			else
			{
				direction=3;
			}
		}
		
		if (direction==1)
		{
			while ((maze[x][y].right==true)&&(maze[x][y].top==false))
			{
				y++;//move up
				putsquare(x,y);
			}
			putsquare(x,y);
			if (maze[x][y].right==false)
			{
				x++;
				direction=2;
				putsquare(x,y);
				if (maze[x][y].bottom==false)
				{
					y--;
					direction=3;
					putsquare(x,y);
				}
			}
			else
			{
				direction=4;
			}
		}
	}
}

int main (int argc, char** argv)
{//begin main
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(150,150);
	glutCreateWindow("a-maze-ing");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}




