#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

int xmin, ymin, xmax, ymax;
float a,b,x,y;
int p1 = 9999, q1 = 9999, p2 = 9999, q2 =9999;


void get_points(int x, int y)
{
	if (p1 == 9999 && q1 == 9999)
	{
		p1 = x;
		q1 = y;
	}

	else
	{
		p2 = x;
		q2 = y;
	}

}

bool check_position(int x, int y)
{
	if(x < xmin)
		return false;
	else if( x > xmax)
		return false;
	else if(y < ymin)
		return false;
	else if(y > ymax)
		return false;
	else
		return true;
}

bool check_intersection(int x, int y)
{
	if((y == ymax && x < xmax + 1 && x > xmin - 1) || 
		(y == ymin && x < xmax + 1 && x > xmin - 1) ||
		(x == xmin && y < ymax + 1 && y > ymin - 1) ||
		(x == xmax && y < ymax + 1 && y > ymin - 1) )
	{
		return true;
	}
	else
		return false;

}

void myDisplay(void)
{
 
	float len=abs(x-a);
	if(abs(y-b)>len)
	{
		len=abs(y-b);
	}
	float xi=(x-a)/len;
	float yi=(y-b)/len;
	float x=a;
	float y=b;

	for(int i=1;i<len;i++)
	{

		if(p2 != 9999 && q2 != 9999)
			break;

		if (check_position(x,y) == true)
		{
				
			if(i == 1)
			{
				get_points(x,y);
			}
			
			if ( i != 1 && i != len-1 && check_intersection(x,y) == true )
			{
			
				get_points(x,y);
			
			}

			if(i == len -1)
			{
				get_points(x,y);

			}
		}


		x=x+xi;
		y=y+yi;

	}
	
	glClear (GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glColor3f (0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymin);
	glVertex2i(xmax,ymin);
	glVertex2i(xmax, ymax);
	glVertex2i(xmin,ymax);
	glEnd();
	
	if(p1 != 9999 && p2 != 9999 && q1 != 9999 && q2 != 9999)
	{
		glBegin(GL_LINES);
		glVertex2i(p1,q1);
		glVertex2i(p2,q2);
		glEnd();
	}

	glFlush ();
}


void myInit (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (800, 600);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("my first attempt");

	cout << "Enter Minimum window co-ordinates:- ";
	cin >> xmin;
	cin >> ymin;
	cout << "Enter Maximun window co-ordinates:- ";
	cin >> xmax;
	cin >> ymax;

	cout << "Enter co-ordinates of first point of line:- ";
	cin >> a;
	cin >> b;
	cout << "Enter co-ordinates of second point of line:- ";
	cin >> x;
	cin >> y;

	glutDisplayFunc(myDisplay);
	myInit ();
	glutMainLoop();
}
