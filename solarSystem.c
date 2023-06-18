/*
    NOTE: While running the program some compilers need to add linker -lm for some functions used
    therefore the command for compiling the program
    gcc analogClock.c -lGL -lGLU -lglut -lm
*/

/* group members:

    M S Chaitanya Kumar 20mcme20
    A Karthikeya    20mcme09

*/


#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include<time.h>
#include<math.h>

typedef struct{
    int x;
    int y;
    float ang;
    float ang_incr;

    float x_colr;
    float y_colr;
    float z_colr;
}Planet;

Planet solarPlanets[8];

void bubbleSort(Planet [] , int);
void drawTrajectories(double r);
double computeDistance(Planet a);


void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
}
 
//Called when the window is resized
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(40.0, (double)w / (double)h, 1.0, 200.0);

}
 
float _angle = 0.0f;
 

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, 0.0f, -20.0f);


    //rotating the sun
    glRotatef(_angle, 0.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);

    //drawing the sun
    int radius = 1;
    glutSolidSphere(radius,20,20);

    glRotatef(-_angle, 0.0f, 1.0f, 1.0f);

    //drawing the planets
    for(int i = 0; i < 8; i++){
        drawTrajectories(computeDistance(solarPlanets[i]));
    }    

    //moving the panets according to the speeds set
    for(int i = 0; i < 8; i++){

        //for a cross view, setting the rotating axis as (0 , 1 , 1) and setting each planet color;
        glRotatef(solarPlanets[i].ang, 0.0f, 1.0f, 1.0f);
        glColor3f(solarPlanets[i].x_colr , solarPlanets[i].y_colr , solarPlanets[i].z_colr);
        
        //making planets move only in the plane perpendicular to the axis of rotaion
        float z = solarPlanets[i].y;
        glTranslatef(solarPlanets[i].x ,  z , -z);
        glutSolidSphere(0.25,20,20);
        glTranslatef(-solarPlanets[i].x, -z, z);

        glRotatef(-solarPlanets[i].ang, 0.0f, 1.0f, 1.0f);

        //if planets have completed onle complete rotaion, then again setting the current angle as zero
        solarPlanets[i].ang += solarPlanets[i].ang_incr;

        if (solarPlanets[i].ang > 360) {
            solarPlanets[i].ang -= 360;
        }


    }
    
    glutSwapBuffers();
}

void drawTrajectories(double r){
    glLineWidth((GLfloat)3.0);
    glRotatef(-45 , 1.0f , 0.0f , 0.0f);
    for(int i = 0, j = 1; i < 360; i++, j++){
        glBegin(GL_LINES);

            float x = r * cos(i * M_PI / 180);
            float y = r * sin(i * M_PI / 180);

            glVertex2f(x, y);

            x = r * cos(j * M_PI / 180);
            y = r * sin(j * M_PI / 180);
            
            glVertex2f(x, y);
  
        glEnd();
    }
    glRotatef(45 , 1.0f , 0.0f , 0.0f);
    glLineWidth(1.0f);
}

//after every  100 milli seconds this function is called and sun is rotated by 1.5 degrees. (as glutTimerFunc is called every 100msec)
void update(int value) {
    _angle += 1.5f;
    if (_angle > 360) {
        _angle -= 360;
    }
 
    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}
 

int main(int argc, char** argv) {

    
    //setting each planets RGB
    float colour_x[] = {0.39   ,0.38   ,0.62   ,0.25   ,0.88   ,0.88   ,0.58   ,0.58 };
    float colour_y[] = {0.58   ,0.51   ,0.89   ,0.32   ,0.76   ,0.87   ,0.77   ,0.21 };
    float colour_z[] = {0.93   ,0.71   ,0.75   ,0.68   ,0.43   ,0.68   ,0.45   ,0.33 };

    srand(time(0));
    for(int i = 0; i < 8; i++){

        solarPlanets[i].x = i + 2;
        solarPlanets[i].y = 0;

        solarPlanets[i].x_colr = colour_x[i];
        solarPlanets[i].y_colr = colour_y[i];
        solarPlanets[i].z_colr = colour_z[i];

    }

    // bubbleSort(solarPlanets , 8);

    //setting angle of rotaion for every planet as planets closer moves faster compared to planets far away
    for(int i = 0; i < 8; i++){
        solarPlanets[i].ang = 0;
        solarPlanets[i].ang_incr = 1.0 - 0.12 * i;   
        // solarPlanets[i].ang_incr = 1.0;   
    }

    //generating random numbers for setting the initial positions(angle at which it shall start) of the planet
    //as it uses random numbres for position of planets they start at different position every time compiled and run
    srand(time(0));
    // int start = ((rand() % 180) + 1) + 180;
    int start = rand() % 10000;
    printf("start = %d\n", start);
    for(int i = 0; i < 8; i++){
        solarPlanets[i].ang = start * solarPlanets[i].ang_incr;  
    }


    for(int i = 0; i < 8; i++){
        printf("%f   ", solarPlanets[i].ang_incr);
    }

    // printf("hi\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
 
    //Create the window
    glutCreateWindow("Rotating 3D Cuboid");
    initRendering();
 
    //Set handler functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
 
    //setting a timer to update the positions after every 100msec
    glutTimerFunc(100, update, 0);
 
    glutMainLoop();
}


void swap(Planet* xp, Planet* yp)
{
    Planet temp = *xp;
    *xp = *yp;
    *yp = temp;
}

double computeDistance(Planet a){
    int dsq = a.x * a.x + a.y * a.y;
    return sqrt(dsq);
}

void bubbleSort(Planet arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        for (j = 0; j < n - i - 1; j++)
            if (computeDistance(arr[j]) > computeDistance(arr[j + 1]))
                swap(&arr[j], &arr[j + 1]);
}

