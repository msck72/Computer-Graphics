#include<stdio.h>
#include <GL/glut.h>

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

    int x1 = 10, y1 = 0;
	// printf("Enter x1, y1 \n");
	// scanf("%d%d", &x1, &y1);

	int x2 = 100, y2 = 300;
	// printf("Enter x2, y2 \n");
	// scanf("%d%d", &x2, &y2);

	int delX = x2 - x1;
	int delY = y2 - y1;
	int steps = 0;

	if(abs(delX) >= abs(delY)){
		steps = abs(delX);
	}
	else{
		steps = abs(delY);
	}

	float changeX = (float) delX / (float) steps;
	float changeY = (float) delY / (float) steps;

	// float m = (float)delY / (float)delX;

	float x = x1 + 0.5;
	float y = y1 + 0.5;

	glBegin(GL_POINTS);

		for(int i = 0; i < steps; i++){

			glVertex2f ((int)x , (int)y);		
			x = x + changeX;
			y = y + changeY;
		}
	glEnd( );
    glFlush( );
}

int main(int argc, char** argv){

	glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (400, 300);// Set display-window width and height.    
    glutCreateWindow("An Example OpenGL Program"); // Create display window.
    init();// Execute initialization procedure.
    glutDisplayFunc(lineSegment);// Send graphics to display window.
    glutMainLoop();// Display everything and wait.   
}