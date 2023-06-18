// Group Members :
// M S Chaitanya Kumar 20mcme20
// Sai Dhruva Teja 20mcme03


#include <GL/glut.h>
#include <stdlib.h>
// #include <openglut.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble size = 1;

void drawHouse(){
  //backside
    glColor3f(0.0,0.0,1.0); 
    glBegin(GL_POLYGON);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(-1.0, 1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);
      glVertex3f(1.0, -1.0, -1.0);
    glEnd();


    //door
    glColor3f(1.0,1.0,1.0); 
    glBegin(GL_POLYGON);
      glVertex3f(0.5, 0.5, 1.01);
      glVertex3f(-0.5, 0.5, 1.01);
      glVertex3f(-0.5, -1.0, 1.01);
      glVertex3f(0.5, -1.0, 1.01);
    glEnd();

    //front side
    glColor3f(1.0,0.0,0.0); 
    glBegin(GL_POLYGON);
      glVertex3f(1.0, 1.0, 1.0);
      glVertex3f(-1.0, 1.0, 1.0);
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
    glEnd();

    //right side
    glColor3f(0.0,1.0,0.0); 
    glBegin(GL_POLYGON);
      glVertex3f(1.0, 1.0, 1.0);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(1.0, -1.0, 1.0);
    glEnd();

    //left side
    glColor3f(0.93334,0.9098,0.6667); 
    glBegin(GL_POLYGON);
      glVertex3f(-1.0, 1.0, 1.0);
      glVertex3f(-1.0, 1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, 1.0);
    glEnd();


    //top right slope
    glColor3f(0.823, 0.411764 , 0.11764); 
    glBegin(GL_POLYGON);
      glVertex3f(1.2, 0.8, 1.0);
      glVertex3f(1.2, 0.8, -1.0);
      glVertex3f(0.0, 2.0, -1.0);
      glVertex3f(0.0, 2.0, 1.0);
    glEnd();


    //top left slope
    glColor3f(0.823, 0.411764 , 0.11764); 
    glBegin(GL_POLYGON);
      glVertex3f(-1.2, 0.8, 1.0);
      glVertex3f(-1.2, 0.8, -1.0);
      glVertex3f(0.0, 2.0, -1.0);
      glVertex3f(0.0, 2.0, 1.0);
    glEnd();

    //slab
    glColor3f(0.64705 , 0.1647 , 0.1647); 
    glBegin(GL_POLYGON);
      glVertex3f(-1.0, 1.0, 1.0);
      glVertex3f(1.0, 1.0, 1.0);
      glVertex3f(0.0, 2.0, 1.0);
    glEnd();


    glColor3f(0.64705 , 0.1647 , 0.1647); 
    glBegin(GL_POLYGON);
      glVertex3f(-1.0, 1.0, -1.0);
      glVertex3f(1.0, 1.0, -1.0);
      glVertex3f(0.0, 2.0, -1.0);
    glEnd();
}

void drawSideBars(){
  // glColor3f(0.0,0.0,0.0); 
  glLineWidth(5);
    glBegin(GL_LINE_LOOP);
      glVertex3f(1.0 , 0.0 , 1.0);
      glVertex3f(1.0 , 0.0 , 1.4);
      glVertex3f(-1.0 , 0.0 , 1.4);
      glVertex3f(-1.0 , 0.0 , 1.0);
      glVertex3f(-1.0 , -1.0 , 1.0);
      glVertex3f(-1.0 , -1.0 , 1.4);
      glVertex3f(1.0 , -1.0 , 1.4);
      glVertex3f(1.0 , -1.0 , 1.0);
    glEnd();


    glBegin(GL_POLYGON);
      glVertex3f(-1.0 , -1.0 , 1.0);
      glVertex3f(-1.0 , -1.0 , 1.4);
      glVertex3f(1.0 , -1.0 , 1.4);
      glVertex3f(1.0 , -1.0 , 1.0);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex3f( 1.0, 0.0 , 1.2);
        glVertex3f( 1.0, -1.0 , 1.2);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f( -1.0, 0.0 , 1.2);
        glVertex3f( -1.0 , -1.0 , 1.2);
    glEnd();

    for(float i = -1; i < 1; i = i + 0.1){
      glBegin(GL_LINE_LOOP);
        glVertex3f( i, 0.0 , 1.4);
        glVertex3f( i, -1.0 , 1.4);
      glEnd();
    }
}

void drawGround(){
  // glColor3f(0.13333, 0.54509, 0.13333);
    glColor3f(0.270588 , 0.701961 , 0.443137);

    glBegin(GL_POLYGON);
      glVertex3f(5.0, -1.0, -5.0);
      glVertex3f(-5.0, -1.0, -5.0);
      glVertex3f(-5.0, -1.0, 5.0);
      glVertex3f(5.0, -1.0, 5.0);
    glEnd();

    
    //fencing
    glLineWidth(10);
    glColor3f(0.466667 , 0.533333 , 0.600000); 
    glBegin(GL_LINE_LOOP);
      glVertex3f(5.0, -0.5, -5.0);
      glVertex3f(-5.0, -0.5, -5.0);
      glVertex3f(-5.0, -0.5, 5.0);
      glVertex3f(-1.0, -0.5, 5.0);
      glVertex3f(-1.0, -1.0, 5.0);
      glVertex3f(1.0, -1.0, 5.0);
      glVertex3f(1.0, -0.5, 5.0);
      glVertex3f(5.0, -0.5, 5.0);
    glEnd();

    //gate

    glTranslatef(-1.0 , -1.0 , 5.0);
    glRotatef(45 , 0 , 1 , 0);
    glTranslatef(1.0 , 1.0 , -5.0);

    //left gate
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.0, -1.0, 5.0);
        glVertex3f(-1.0, 0.5, 5.0);
        glVertex3f(0.0, 0.5, 5.0);
        glVertex3f(0.0, -1.0, 5.0);
    glEnd();
    //gate bars
    for(float i = -1.0; i < 0; i += 0.05){
      glBegin(GL_LINE_LOOP);
          glVertex3f(i, 0.5, 5.0);
          glVertex3f(i, -1, 5.0);
      glEnd();
    }
    glTranslatef(-1.0 , -1.0 , 5.0);
    glRotatef(-45 , 0 , 1 , 0);
    glTranslatef(1.0 , 1.0 , -5.0);


    
    glTranslatef(1.0 , -1.0 , 5.0);
    glRotatef(-45 , 0 , 1 , 0);
    glTranslatef(-1.0 , 1.0 , -5.0);


    //right gate
    glBegin(GL_LINE_LOOP);
        glVertex3f(1.0, -1.0, 5.0);
        glVertex3f(1.0, 0.5, 5.0);
        glVertex3f(0.0, 0.5, 5.0);
        glVertex3f(0.0, -1.0, 5.0);
    glEnd();

    //gate bars right
    for(float i = 0.0; i < 1; i += 0.05){
      glBegin(GL_LINE_LOOP);
          glVertex3f(i, 0.5, 5.0);
          glVertex3f(i, -1, 5.0);
      glEnd();
    }

    glTranslatef(1.0 , -1.0 , 5.0);
    glRotatef(45 , 0 , 1 , 0);
    glTranslatef(-1.0 , 1.0 , -5.0);



    glColor3f(0.823, 0.411764 , 0.11764); 
    
    for(float i = 5; i > -5; i -= 0.1){
      if(i < -1 || i > 1){
        glBegin(GL_LINE_LOOP);
          glVertex3f(i, -0.5, 5.0);
          glVertex3f(i, -1, 5.0);
        glEnd();
      }

      glBegin(GL_LINE_LOOP);
        glVertex3f(i, -0.5, -5.0);
        glVertex3f(i, -1, -5.0);
      glEnd();


      glBegin(GL_LINE_LOOP);
        glVertex3f(5.0, -0.5, i);
        glVertex3f(5.0, -1, i);
      glEnd();

      glBegin(GL_LINE_LOOP);
        glVertex3f(-5.0, -0.5, i);
        glVertex3f(-5.0, -1, i);
      glEnd();


      // glBegin(GL_LINE_LOOP);
      //   glVertex3f(i, -0.5, 5.0);
      //   glVertex3f(i, -1, 5.0);
      // glEnd();


      // glBegin(GL_LINE_LOOP);
      //   glVertex3f(i, -0.5, 5.0);
      //   glVertex3f(i, -1, 5.0);
      // glEnd();
    }

}


void drawUpperHouse(){
  glTranslatef(0.5 , 1.5 , 0.0);
  glScalef(0.5 , 0.5 , 0.5);
  glRotatef(90,0.0,1.0,0.0);
  drawHouse();
  drawSideBars();
  glRotatef(-90,0.0,1.0,0.0);
  glScalef(2 , 2 , 2);
  glTranslatef(-0.5 , -1.5 , 0.0);


  glTranslatef(-0.5 , 1.5 , 0.0);
  glScalef(0.5 , 0.5 , 0.5);
  glRotatef(-90,0.0,1.0,0.0);
  drawHouse();
  drawSideBars();
  glRotatef(90,0.0,1.0,0.0);
  glScalef(2 , 2 , 2);
  glTranslatef(0.5 , -1.5 , 0.0);


  glTranslatef(0.0 , 1.95 , 0.60);
  glScalef(0.25 , 0.25 , 0.25);
  drawHouse();
  drawSideBars();
  glScalef(4 , 4 , 4);
  glTranslatef(0.0 , -1.95 , -0.60);
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-10.0);

    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    
    drawHouse();
    drawUpperHouse();
    drawGround();
    
    glFlush();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  
}

void idleFunc(void)
{
    // yRotated += 0.01;
    // xRotated += 0.02;
    display();
}

void mouseFunc(int x, int y)
{
    yRotated = x/2.5;
    xRotated = y/2.5;
    display();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(500,500);
    glutCreateWindow("3D House");
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutPassiveMotionFunc(mouseFunc);
    glutFullScreen();
    glutMainLoop();
    return 0;
}