#include<stdio.h>
#include <GL/glut.h>

int window_size_x = 800;
int window_size_y = 800;

typedef struct{
    int x;
    int y;
}Vertex;

int noOfVertices_viewport = 0;
Vertex *myVertices_viewport = NULL;
int x_min = 0, x_max = 0 , y_min = 0, y_max = 0;

int noOfVertices_polygon = 0;
Vertex *myVertices_polygon = NULL;

int number_of_active_points = 0;
Vertex *active_array_list = NULL;

Vertex giveIntersectionIfOutside(Vertex a , Vertex b);
Vertex giveIntersectionIfInside(Vertex a , Vertex b);
int checkIntersectionIfInside(Vertex , Vertex);
int checkIntersectionIfOutside(Vertex , Vertex);


void init (void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);// Set display-window color to white.
    glMatrixMode(GL_PROJECTION);// Set projection parameters.    
    gluOrtho2D(0.0, window_size_x, 0.0, window_size_y);
}

void draw_polygon(){
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < noOfVertices_polygon; i++){
            printf("%d   %d\n", myVertices_polygon[i].x , myVertices_polygon[i].y);
            glVertex2f(myVertices_polygon[i].x , myVertices_polygon[i].y);
        } 
    glEnd();
    glFlush();
}

void draw_viewport(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glTranslatef(window_size_x / 2 , window_size_y / 2, 0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < noOfVertices_viewport; i++){
            glVertex2f(myVertices_viewport[i].x , myVertices_viewport[i].y);
        } 
    glEnd();
    glFlush();
}


void take_viewport_window_vertices(){
    printf("Enter number of points:\n");
    scanf("%d", &noOfVertices_viewport);

    myVertices_viewport = malloc(sizeof(Vertex) * noOfVertices_viewport);

    scanf("%d", &myVertices_viewport[0].x);
    scanf("%d", &myVertices_viewport[0].y);
    x_max = myVertices_viewport[0].x;
    y_min = myVertices_viewport[0].y;
    x_min = myVertices_viewport[0].x;
    y_max = myVertices_viewport[0].y;

    for(int i = 1; i < noOfVertices_viewport; i++){
        scanf("%d", &myVertices_viewport[i].x);
        scanf("%d", &myVertices_viewport[i].y);

        if(x_min > myVertices_viewport[i].x){
            x_min = myVertices_viewport[i].x;
        }
        if(x_max < myVertices_viewport[i].x){
            x_max = myVertices_viewport[i].x;
        }
        if(y_min > myVertices_viewport[i].y){
            y_min = myVertices_viewport[i].y;
        }
        if(y_max < myVertices_viewport[i].y){
            y_max = myVertices_viewport[i].y;
        }
        
    }
    printf("x_min = %d, x_max = %d , y_min = %d, y_max = %d\n", x_min, x_max , y_min , y_max);
    printf("ended take input viewport\n");

    // for(int i = 0; i < noOfVertices_viewport; i++){
    //     printf("%d   %d\n", myVertices_viewport[i].x , myVertices_viewport[i].y);
    // }

}


void take_input_polygon(){
    printf("Enter number of vertices in polygon:\n");
    scanf("%d", &noOfVertices_polygon);

    myVertices_polygon = malloc(sizeof(Vertex) * noOfVertices_polygon);

    for(int i = 0; i < noOfVertices_polygon; i++){
        scanf("%d", &myVertices_polygon[i].x);
        scanf("%d", &myVertices_polygon[i].y);
    }

   
    printf("Printing vertices \n");
    for(int i = 0; i < noOfVertices_polygon; i++){
        printf("%d   %d\n", myVertices_polygon[i].x , myVertices_polygon[i].y);
    }

    printf("ended take input polygon\n");
}

void draw_polygon_with_collected_points(){
    glColor3f(0.529412 , 0.807843 , 0.921569);
    glBegin(GL_POLYGON);
        for(int i = 0; i < number_of_active_points; i++){
            printf("(%d)-------(%d)\n", active_array_list[i].x , active_array_list[i].y);
            glVertex2f(active_array_list[i].x , active_array_list[i].y);
        } 
    glEnd();
    glFlush();
}

void process_line_segments(){
    active_array_list = malloc(sizeof(Vertex) * noOfVertices_polygon);
    printf("hi");
    int isInside = 0;
    for(int i = 0, j = 0; i < noOfVertices_polygon && j < noOfVertices_polygon; i = (i + 1) % noOfVertices_polygon, j++){
        printf("(%d, %d) to (%d , %d)\n", myVertices_polygon[i].x , myVertices_polygon[i].y , myVertices_polygon[i + 1].x , myVertices_polygon[i + 1].y);
        int flag = 0;
        if(isInside == 1){
            flag = checkIntersectionIfInside(myVertices_polygon[i] , myVertices_polygon[i + 1]);
            printf("flag = %d\n", flag);
            // else{
            printf("Inside\n");
            printf("added point = (%d , %d)\n", myVertices_polygon[i].x , myVertices_polygon[i].y);
            active_array_list[number_of_active_points].x = myVertices_polygon[i].x;
            active_array_list[number_of_active_points].y = myVertices_polygon[i].y;//y intersection
            //add to list
            number_of_active_points++;

            if(flag == 1){
                printf("In to out\n");
                Vertex intersection = giveIntersectionIfInside(myVertices_polygon[i] , myVertices_polygon[i + 1]);
                printf("intersection = (%d, %d)\n", intersection.x , intersection.y);
                active_array_list[number_of_active_points].x = intersection.x;//x intersection
                active_array_list[number_of_active_points].y = intersection.y;//y intersection
                number_of_active_points++;
                draw_polygon_with_collected_points();
                number_of_active_points = 0;
                isInside = 0;
            }
            // }
        }
        if(isInside == 0){
            flag = checkIntersectionIfOutside(myVertices_polygon[i], myVertices_polygon[i + 1]);
            printf("flag = %d\n", flag);
            if(flag == 1){
                printf("Out to In\n");
                Vertex intersection = giveIntersectionIfOutside(myVertices_polygon[i] , myVertices_polygon[i + 1]);
                printf("intersection = (%d, %d)\n", intersection.x , intersection.y);
                active_array_list[number_of_active_points].x = intersection.x;//x intersection
                active_array_list[number_of_active_points].y = intersection.y;//y intersection
                isInside = 1;
                //start adding to list and add intersection point
                number_of_active_points = 1;
            }
            else{
                printf("outside\n");
                continue;
                //continue
            }
        }
    }
}


Vertex giveIntersectionIfOutside(Vertex a , Vertex b){
    Vertex intersection;
    float slope = (float)(a.y - b.y) / (float)(a.x - b.x);
    //check upper 
    if(b.y <= y_max && a.y > y_max){
        intersection.y = y_max;
        intersection.x = (y_max - a.y) / slope + a.x;
    }
    //check right
    if(b.x < x_max && a.x > x_max){
        intersection.x = x_max;
        intersection.y = slope * (x_max - a.x) + a.y;
    }
    //check lower
    if(b.y > y_min && a.y < y_min){
        intersection.y = y_min;
        intersection.x = (y_min - a.y) / slope + a.x;

    }
    //check left
    if(b.x > x_min && a.x < x_min){
        intersection.x = x_min;
        intersection.y = slope * (x_min - a.x) + a.y;
    }

    return intersection;
}

Vertex giveIntersectionIfInside(Vertex a , Vertex b){
    Vertex intersection;
    float slope = (float)(b.y - a.y) / (float)(b.x - a.x);
    //check upper 
    if(a.y <= y_max && b.y > y_max){
        intersection.y = y_max;
        intersection.x = (y_max - b.y) / slope + b.x;
    }
    //check right
    if(a.x < x_max && b.x > x_max){
        intersection.x = x_max;
        intersection.y = slope * (x_max - b.x) + b.y;
    }
    //check lower
    if(a.y > y_min && b.y < y_min){
        intersection.y = y_min;
        intersection.x = (y_min - b.y) / slope + b.x;

    }
    //check left
    if(a.x > x_min && b.x < x_min){
        intersection.x = x_min;
        intersection.y = slope * (x_min - b.x) + b.y;
    }

    return intersection;
}

int checkIntersectionIfOutside(Vertex a , Vertex b){
    if(b.x < x_min || b.x > x_max){
        if(b.y < y_min || b.y > y_max){
            if(b.x < x_min || b.x > x_max){
                if(b.y < y_min || b.y > y_max){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int checkIntersectionIfInside(Vertex a , Vertex b){
    if(a.x >= x_min && a.x <= x_max){
        if(a.y >= y_min && a.y <= y_max){
            if(b.x >= x_min && b.x <= x_max){
                if(b.y >= y_min && b.y <= y_max){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void main_2(){
    printf("calling viewport\n");
    take_viewport_window_vertices();
    printf("calling polygon\n");
    take_input_polygon();

    draw_viewport();
    draw_polygon();

    printf("=====================================");
    process_line_segments();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (window_size_x, window_size_y);// Set display-window width and height.    
    glutCreateWindow("An Example OpenGL Program"); // Create display window.
    init();// Execute initialization procedure.
    glutDisplayFunc(main_2);
    glutMainLoop();// Display everything and wait.    
    
}