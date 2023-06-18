/*
    NOTE: While running the program some compilers need to add linker -lm for some functions used
    gcc analogClock.c -lGL -lGLU -lglut -lm
*/

#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int windowSize_x = 800;
int windowSize_y = 800;
int start_from = 0;

typedef struct{
    float hand_movement;
    int max_height;
    int max_width;
}Hand;

Hand hour;

Hand minute;

Hand second;

typedef struct
{
    float x;
    float y;
}Circle;

Circle myCricle;
void draw_circle (int);

void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);// Set display-window color to white.
    glMatrixMode(GL_PROJECTION);// Set projection parameters.    
    gluOrtho2D(0.0, windowSize_x, 0.0, windowSize_y);
}

void draw_circle (int r) {
    glColor3f(0.250980 , 0.709804 , 0.678431);
    
    //wrting brand name
    glRasterPos2f(-25 , windowSize_y / 7);
    char brand[] = "fastTrack";
    int len_brand = strlen(brand);
    for(int i = 0; i  < len_brand; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, brand[i]);        
    }

    //drawing the outercircle
    glLineWidth((GLfloat)7.0);
    for(int i = 0, j = 1; i < 360; i++, j++){
        glBegin(GL_LINES);

            float x = r * cos(i * M_PI / 180);
            float y = r * sin(i * M_PI / 180);

            glVertex2f( x, y);

            x = r * cos(j * M_PI / 180);
            y = r * sin(j * M_PI / 180);
            
            glVertex2f(x, y);
      
        glEnd();
    }

    for(int i = 0, j = 3; i < 360; i+=30, j--){
        //drawing lines after 30degrees
        glColor3f(0.250980 , 0.709804 , 0.678431);
        glBegin(GL_LINES);
            float x = r * cos(i * M_PI / 180);
            float y = r * sin(i * M_PI / 180);
            glVertex2f( x, y);

            x = (r - windowSize_x / 30) * cos(i * M_PI / 180);
            y = (r - windowSize_x / 30) * sin(i * M_PI / 180);

            glVertex2f( x, y);

        glEnd();

        x = (r - windowSize_x / 20) * cos(i * M_PI / 180);
        y = (r - windowSize_x / 20) * sin(i * M_PI / 180);

        glColor3f (0.678, 0.847, 0.902);// Set line segment color to green.
        glRasterPos2f(x, y);

        //writing numbers at respective positions
        void * font = GLUT_BITMAP_HELVETICA_18;
        if(j % 3 == 0){
            font = GLUT_BITMAP_TIMES_ROMAN_24;
        }

        if(j < 10){
            glutBitmapCharacter(font, j + '0');    
        }
        else{
            
            glRasterPos2f(x - 10, y - 10);
            glScalef(5 , 5 , 1);
            glutBitmapCharacter(font, '1');
            glutBitmapCharacter(font, j - 10 + '0');
            glScalef(0.2 , 0.2 , 1);
        }


        if(j == 1){
            j = 13;
        }
    }


    //drawing lines every 6 degrees denoting one second
    glLineWidth((GLfloat)3.0);
    glColor3f(0.250980 , 0.709804 , 0.678431);

    for(int i = 0; i < 360; i+=6){
        glBegin(GL_LINES);
            float x = r * cos(i * M_PI / 180);
            float y = r * sin(i * M_PI / 180);
            glVertex2f( x, y);

            x = (r - windowSize_x / 60) * cos(i * M_PI / 180);
            y = (r - windowSize_x / 60) * sin(i * M_PI / 180);

            glVertex2f( x, y);

        glEnd();
    }

    glLineWidth(1.0f);
    glFlush();

}

void drawInnerCircle(float r, float x, float y) {
    float i = 0.0f;
    glColor3f(0.529412 , 0.807843 , 0.921569);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center
        for(i = 0.0f; i <= 360; i++)
            glVertex2f(r*cos(M_PI * i / 180.0) + x, r*sin(M_PI * i / 180.0) + y);    
    glEnd();
    glFlush();

}

void draw_hand(Hand myHand , int i){
    glRotatef(-i * myHand.hand_movement , 0 , 0 , 1);
    glBegin(GL_POLYGON);
            glVertex2f(myHand.max_width , -myHand.max_height / 20);
            glVertex2f(myHand.max_width , myHand.max_height - 10);
            glVertex2f(0 , myHand.max_height);
            glVertex2f(-myHand.max_width , myHand.max_height - 10);
            glVertex2f(-myHand.max_width , -myHand.max_height / 20);
            glVertex2f(-myHand.max_width + (myHand.max_width * 0.2) , -40 * 1.1);
            glVertex2f(-myHand.max_width + (myHand.max_width * 0.3) , -40 * 1.2);
            glVertex2f(-myHand.max_width + (myHand.max_width * 0.4) , -40 * 1.3);
            glVertex2f(0, -40 * 1.3);
            glVertex2f(-myHand.max_width + (myHand.max_width * 1.6), -40 * 1.3);
            glVertex2f(-myHand.max_width + (myHand.max_width * 1.7), -40 * 1.2);
            glVertex2f(-myHand.max_width + (myHand.max_width * 1.8), -40 * 1.1);
    glEnd();
    glRotatef(i * myHand.hand_movement , 0 , 0 , 1);
    drawInnerCircle(20 , 0 , 0);
    glFlush( );
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);// Clear display window.
    glTranslatef(windowSize_x / 2, windowSize_y / 2, 0);
    draw_circle(windowSize_x / 3);
    drawInnerCircle(20 , 0 , 0);

    hour.max_width = (windowSize_x) * 0.0125;;
    hour.max_height = (windowSize_y / 3) * 0.5;

    minute.max_width = (windowSize_x) * 0.00625;
    minute.max_height = (windowSize_y / 3) * 0.75;
    
    second.max_width = (windowSize_x) * 0.003125;
    second.max_height = (windowSize_y / 3) * 1.0;

    glFlush();

    for(long i = start_from; 1; i++){

        sleep(1);
        glClear(GL_COLOR_BUFFER_BIT);// Clear display window.

        glColor3f (0.678, 0.847, 0.902);// Set line segment color to green.
        draw_circle(windowSize_x / 3);
        glFlush();

        //hour hand 
        glColor3f (0.678431 , 0.847059 , 0.901961);// Set line segment color to green.
        draw_hand(hour , i);

        //minute hand
        glColor3f(0.274510 , 0.549020 , 0.705882);
        draw_hand(minute , i);
        
        //seconds hand
        glColor3f (0.0, 0.0, 1.0);// Set line segment color to green.
        draw_hand(second , i);
        
    }  
}
int main (int argc, char** argv)
{
    hour.hand_movement = 0.00833333333;
    minute.hand_movement = 0.1;
    second.hand_movement = 6;

    time_t myTime;
    struct tm* curr_time;
    myTime = time(NULL);
    curr_time = localtime(&myTime);

    int hh = curr_time->tm_hour;
    int mm = curr_time->tm_min;
    int ss = curr_time->tm_sec;

    if(hh > 12){
        hh = hh - 12;
    }
    start_from = hh * 3600;
    start_from = start_from + mm * 60;
    start_from = start_from + ss;

    glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (windowSize_x, windowSize_y);// Set display-window width and height.    
    glutCreateWindow("An Example OpenGL Program"); // Create display window.
    init();// Execute initialization procedure.
    glutDisplayFunc(display);// Send graphics to display window.
    glutMainLoop();// Display everything and wait.    
}



