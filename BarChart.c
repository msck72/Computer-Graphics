#include<stdio.h>
#include<string.h>
#include <GL/glut.h>

int windowWidth = 1000;
int windowHeight = 300;


char headings[2][100];

struct node{
    char name[20];
    int height;
}typedef node;

node *dataSpots;

int x1 , y1 , x2 , y2;
int dataCount;
int max = 0;


void quad (void)
{

    glClear(GL_COLOR_BUFFER_BIT);// Clear display window.
    glColor3f (0.0, 0.2, 0.2);// Set line segment color to green
    int x_length = dataCount * 2 * 10 + 20;
    int y_length = max + 0.4 * max;
 
    // Draw a Red 1x1 Square centered at origin
    // printf("gl_polygon = %d\n". GL_POLYGON);

    // glBegin(GL_POLYGON);              // Each set of 4 vertices form a qua // Red
    //     glVertex2i(x1, y1);
    //     glVertex2i(x2 , y2);
    //     glVertex2i(x3 , y3);
    //     glVertex2i(x4 , y4);
    // glEnd();

    // 100 - 10 / (2 * noOfgrams)

    //drawing x axis
    glBegin(GL_LINES);
        glVertex2i (0, 0.3 * max);
        glVertex2i (dataCount * 2 * 10 + 20, 0.3 * max);
    glEnd( );

    //drawing y axis
    glBegin(GL_LINES);
        glVertex2i (10, 0);
        glVertex2i (10, max + 0.4 * max);
    glEnd( );

    int startX = 20;
    int startY = 0.3 * max;
    int width = 10;
    x1 = startX;
    y1 = startY;

    printf("width = %d\n", width);


    //plotting the graph from the data extracted
    for(int i = 0; i < dataCount; i++){
        x2 = x1 + width;
        y2 = y1 + dataSpots[i].height;
        glRectf(x1 , y1 , x2 , y2);

        //writing the input
        glRasterPos2f(x1, y1 - 0.1 * max);
        int len = strlen(dataSpots[i].name);
        for (int j = 0; j < len; j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, dataSpots[i].name[j]);
        }

        x1 += 2 * width;
    }


    //writing the x axis name
    glRasterPos2f(dataCount * 10, 0.1 * max);
    int len = strlen(headings[0]);
    for(int i = 0; i < len; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, headings[0][i]);
    }


    //writing y - axis name
    glPushMatrix();
        //changing font selection, like bold...
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(2.0);


        //rotating the axis
        glRotatef(90, 0, 0, 1);
        //scaling the x and y axis
        float x_scale = 0.00015 * x_length;
        float y_scale = 0.0002 * y_length;

        //transfering the origin , to make the perfect placement
        glTranslatef( (y_length / 3), -8, 0);

        //scaling accordingly to make the constant font size for all the graphs
        glScalef(y_scale , x_scale, 3);
        len = strlen(headings[1]);
        for(int i = 0; i < len; i++){    
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, headings[1][i]); 
        }

    glPopMatrix(); 
    
   glFlush(); 
}

void init (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, dataCount * 2 * 10 + 20, 0.0, max + 0.4 * max);
}

int main(int argc, char** argv){
    if(argc == 1){
        printf("No file given\n");
        return 1;
    }

    FILE* myFile = fopen(argv[1], "r");

    char s;

    for(int j = 0, i = 0; j < 2; j++, i = 0){
        while((s=fgetc(myFile))!= EOF) {
            if(s == '\n'){
                headings[j][i] = '\0';
                break;
            }
            headings[j][i] = s;
            i++;
        }
    }

    fscanf(myFile, "%d", &dataCount);
    
    // node dataSpots[dataCount];
    dataSpots = (node*)malloc(sizeof(node) * dataCount);

    printf("heading 1 is %s\n", headings[0]);
    printf("heading 2 is %s\n", headings[1]);
    printf("data count = %d\n", dataCount);

    char buffer[100];
    int height = 0;
    for(int i = 0; i < dataCount; i++){
        fscanf(myFile, "%s", dataSpots[i].name);

        fscanf(myFile, "%d", &dataSpots[i].height);
        if(max < dataSpots[i].height){
            max = dataSpots[i].height;
        }

        // printf("name = %s, height = %d\n", dataSpots[i].name, dataSpots[i].height);
    }

    for(int i = 0; i < dataCount; i++){
        printf("name = %s, height = %d\n", dataSpots[i].name, dataSpots[i].height);
    }

    glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (windowWidth, windowHeight);// Set display-window width and height.    
    glutCreateWindow("An Example OpenGL Program"); // Create display window.
    init();// Execute initialization procedure.
    glutDisplayFunc(quad);// Send graphics to display window.
    glutMainLoop();// Display everything and wait.   

}

