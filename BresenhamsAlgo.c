#include<stdio.h>
#include <GL/glut.h>

int x_origin = 400;
int y_origin = 300;

int x1 , x2 , y1 , y2;

void init (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);// Set display-window color to white.
    
    glMatrixMode(GL_PROJECTION);// Set projection parameters.    
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}


void lineSegment (void)
{
	glClear(GL_COLOR_BUFFER_BIT);// Clear display window.
    glColor3f (0.0, 0.2, 0.2);// Set line segment color to green

    //Drawing the origin for reference
    glBegin(GL_POINTS);
		int y_axis = 100;
		for(int i = 0; i < 300; i++){
			glVertex2f(y_axis , i);
		}
		int x_axis = 75;
		for(int i = 0; i < 400; i++){
			glVertex2f(i , x_axis);
		}

	glEnd( );


	int x = x1 + x_origin / 4 , y =  y1 + y_origin / 4;

	int delX = abs(x2 - x1);
	int delY = abs(y2 - y1);
	int flag = 0;

	int s1 = (x2 - x1) / delX;
	int s2 = (y2 - y1) / delY;

	if(delY > delX){
		int temp = delX;
		delX = delY;
		delY = temp;
		flag = 1;
	}

	int p = 2 * delY - delX;

	glBegin(GL_POINTS);
		glVertex2f (x , y);
	
		for(int i = 0; i < delX; i++){
			if(flag == 1){
				if(p < 0){
					y += s2;
					p += 2 * delY;
				}
				else{
					x += s1;
					y += s2;
					p += 2 * delY  - 2 * delX;
				}
			}
			else{
				if(p < 0){
					x += s1;
					p += 2 * delY;
				}
				else{
					x += s1;
					y += s2;
					p += 2 * delY  - 2 * delX;
				}
			}
			
			glVertex2f (x , y);		
		}

	glEnd( );
    glFlush( );
}

int main(int argc, char** argv){

	// int x1 , y1;
	printf("Enter x1, y1 \n");
	scanf("%d%d", &x1, &y1);

	// int x2 , y2;
	printf("Enter x2, y2 \n");
	scanf("%d%d", &x2, &y2);

	glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (x_origin, y_origin);// Set display-window width and height.    
    glutCreateWindow("Bresenham's Algorithm"); // Create display window.
    init();// Execute initialization procedure.
    glutDisplayFunc(lineSegment);// Send graphics to display window.
    glutMainLoop();// Display everything and wait.   
}