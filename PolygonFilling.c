#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>

typedef struct EdgeNode{
    int y_max_vertex;
    int x_of_y_min;
    float inverseSlope;
}EdgeNode;

typedef struct Coordinate{
    int x;
    int y;
}Coordinate;

typedef struct LLNode{
    EdgeNode val;
    struct LLNode* next;
}LLNode;

Coordinate* myCord;
int len_myCord = 0;
LLNode** activeEdgeTable;
int len_activeEdgeTable = 0;
int ymin = 0, ymax = 0;

int max(int , int);
int xOfyMin(Coordinate a , Coordinate b);
float calculateInverseSlope(Coordinate a , Coordinate b);
LLNode* sortAndAddLLNode(LLNode* head , LLNode* toAdd);
LLNode* sortAndAdd(LLNode* head , EdgeNode myEdgeNode);
int min(int a , int b);
void drawAlternativeAndUpdate(LLNode *head, int y);
void swapEdgeNode(LLNode* a , LLNode* b);
void start(void);
void start2(void);

void init (void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);// Set display-window color to white.
    
    glMatrixMode(GL_PROJECTION);// Set projection parameters.    
    gluOrtho2D(0.0, 15.0, 0.0, 20.0);
}

int main(int argc , char** argv){
	start();
	start2();
    glutInit(&argc, argv);// Initialize GLUT.    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// Set display mode.    
    glutInitWindowPosition(50, 100);// Set top-left display-window position.    
    glutInitWindowSize (400, 300);// Set display-window width and height.    
    glutCreateWindow("An Example OpenGL Program"); // Create display window.
    init();// Execute initialization procedure.
    // glutDisplayFunc(start2);// Send graphics to display window.
    glutMainLoop();// Display everything and wait.     
}


void start(){
    int noOfNodes;
    printf("Enter number of nodes\n");
    scanf("%d", &noOfNodes);

    ymin = 0, ymax = 0;
    myCord = malloc(sizeof(Coordinate) * noOfNodes);
    len_myCord = noOfNodes;

    for(int i = 0; i < noOfNodes; i++){
        scanf("%d" , &myCord[i].x);
        scanf("%d" , &myCord[i].y);

        if(i == 0){
            ymin = myCord[i].y;
            ymax = myCord[i].y;
            continue;
        }
        if(ymin > myCord[i].y){
            ymin = myCord[i].y;
        }

        if(ymax < myCord[i].y){
            ymax = myCord[i].y;
        }
    }

    printf("Printing Nodes\n");
    for(int i = 0; i < noOfNodes; i++){
        printf("%d %d\n", myCord[i].x, myCord[i].y);
    }

    printf("ymin = %d ymax = %d\n", ymin , ymax);

    activeEdgeTable = malloc(sizeof(LLNode*) * (ymax - ymin + 1));
    len_activeEdgeTable = (ymax - ymin + 1);

    for(int i = 0; i < ymax - ymin + 1; i++){
        activeEdgeTable[i] = NULL;
        printf("i = %d, activeEdgeTable[i] = %p\n", i , activeEdgeTable[i]);
    }
    printf("\n");

    for(int i = 0; i < noOfNodes; i++){
        printf("i = %d\n", i);
        EdgeNode myEdgeNode;
        myEdgeNode.y_max_vertex = max(myCord[i].y - ymin , myCord[(i + 1) % noOfNodes].y - ymin);
        printf("myEdgeNode.y_max_vertex = %d\n", myEdgeNode.y_max_vertex);

        myEdgeNode.x_of_y_min = xOfyMin(myCord[i] , myCord[(i + 1) % noOfNodes]);
        printf("myEdgeNode.x_of_y_min = %d\n", myEdgeNode.x_of_y_min);

        myEdgeNode.inverseSlope = calculateInverseSlope(myCord[i], myCord[(i + 1) % noOfNodes]);
        printf("myEdgeNode.inverseSlope = %f\n", myEdgeNode.inverseSlope);
        printf("min(myCord[i].y - ymin , myCord[(i + 1)  noOfNodes].y - ymin) = %d\n", min(myCord[i].y - ymin , myCord[(i + 1) % noOfNodes].y - ymin));
        if(min(myCord[i].y - ymin , myCord[(i + 1) % noOfNodes].y - ymin) == myEdgeNode.y_max_vertex){
            continue;
        }
        activeEdgeTable[min(myCord[i].y - ymin , myCord[(i + 1) % noOfNodes].y - ymin)] = sortAndAdd(activeEdgeTable[min(myCord[i].y - ymin , myCord[(i + 1) % noOfNodes].y - ymin)] , myEdgeNode);
        printf("return\n");
    }

    printf("hi\n");
    for(int i = 0; i < ymax - ymin; i++){
        printf("i = %d\n", i);
        LLNode* temp = activeEdgeTable[i];
        while(temp!= NULL){
            printf("ymx = %d xmin = %d inverseSlope = %f\n" , temp->val.y_max_vertex , temp->val.x_of_y_min , temp->val.inverseSlope);
            temp = temp->next;
        }
    }
}

void start2(){

    for(int i = 0; i < len_activeEdgeTable; i++){
        printf("i===========%d\n", i);
        drawAlternativeAndUpdate(activeEdgeTable[i] , i + ymin);
        // and add to above
        if(i == len_activeEdgeTable){
            break;
        }
        LLNode* temp = activeEdgeTable[i];
        while(temp != NULL){
            activeEdgeTable[i] = temp->next;
            temp->next = NULL;
            // printf("temp->val.y_max_vertex = %d temp->val.x_of_y_min = %d temp->val.inverseSlope = %f\n", temp->val.y_max_vertex, temp->val.x_of_y_min , temp->val.inverseSlope);
            if(temp->val.y_max_vertex == i + 1){
                //eat 5star do nothing
            }
            else{   
                activeEdgeTable[i + 1] = sortAndAddLLNode(activeEdgeTable[i + 1] , temp);
            }

            temp = activeEdgeTable[i];
        }

        LLNode* subs = activeEdgeTable[i + 1];
        while(subs != NULL){
            printf("ymax = %d xmin = %d 1/m = %f\n" , subs->val.y_max_vertex , subs->val.x_of_y_min , subs->val.inverseSlope);
            subs = subs->next;
        }

        printf("\n");

    }
    
}

void drawAlternativeAndUpdate(LLNode *head, int y){
    if(head == NULL){
        return;
    }

    // check isSorted
    LLNode* t_curr = head->next;
    LLNode* t_prev = head;
    while(t_curr != NULL){
        if(t_prev->val.x_of_y_min > t_curr->val.x_of_y_min){
            //swap EdgeNode;
            swapEdgeNode(t_prev , t_curr);
        }
        t_prev = t_curr;
        t_curr = t_curr->next;
    }


    LLNode* current = head;
    LLNode* follow = head->next;

    while(current != NULL && follow != NULL){
        //fill points
        printf("DRAWN LINE BETWEEN (%d , %d), (%d , %d)\t", current->val.x_of_y_min , y , follow->val.x_of_y_min , y);
        // glBegin(GL_LINES);// Specify line-segment geometry.
        //  glVertex2i (current->val.x_of_y_min , y);
        //  glVertex2i (follow->val.x_of_y_min, y);
        // glEnd( );

        //update nodes
        current->val.x_of_y_min += current->val.inverseSlope;
        follow->val.x_of_y_min += follow->val.inverseSlope;

        current = follow->next;
        if(current == NULL){
            break;
        }
        follow = current->next;
    }
    printf("\n");

}

void swapEdgeNode(LLNode* a , LLNode* b){
    EdgeNode standBy;
    standBy.y_max_vertex = a->val.y_max_vertex;
    standBy.x_of_y_min = a->val.x_of_y_min;
    standBy.inverseSlope = a->val.inverseSlope;

    a->val.y_max_vertex = b->val.y_max_vertex;
    a->val.x_of_y_min = b->val.x_of_y_min;
    a->val.inverseSlope = b->val.inverseSlope;

    b->val.y_max_vertex = standBy.y_max_vertex;
    b->val.x_of_y_min = standBy.x_of_y_min;
    b->val.inverseSlope = standBy.inverseSlope;
}

int max(int a , int b){
    if(a >= b){
        return a;
    }
    return b;
}

int min(int a , int b){
    if(a <= b){
        return a;
    }
    return b;
}


int xOfyMin(Coordinate a , Coordinate b){
    if(a.y <= b.y){
        return a.x;
    }
    return b.x;
}

float calculateInverseSlope(Coordinate a , Coordinate b){
    printf("(%d , %d), (%d , %d)\n", a.x , a.y , b.x , b.y);
    int delX = a.x - b.x;
    int delY = a.y - b.y;
    if(delX == 0 || delY == 0){
        return 0;
    }
    printf("delX = %d , delY = %d\n", delX , delY);
    float mInv = (float)delX / delY;
    return mInv;
}


LLNode* sortAndAddLLNode(LLNode* head , LLNode* toAdd){
    printf("IN sort And Add LL Node\n");
    int val = toAdd->val.x_of_y_min;
    toAdd->next = NULL;

    if(head == NULL){
        toAdd->next = NULL;
        return toAdd;
    }

    if(head->val.x_of_y_min > toAdd->val.x_of_y_min){
        toAdd->next = head;
        return toAdd;
    }

    LLNode* temp = head;
    LLNode* prev = head;

    int flag = 0;
    while(temp != NULL){
        if(temp->val.x_of_y_min > toAdd->val.x_of_y_min){
            flag = 1;
            toAdd->next = temp;
            prev->next = toAdd;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if(flag == 0){
        prev->next = toAdd;
    }

    return head;
    
}

LLNode* sortAndAdd(LLNode* head , EdgeNode myEdgeNode){
    printf("in sortAndAdd and head %p\n", head);
    EdgeNode* m_edgeNode = (EdgeNode*) malloc(sizeof(EdgeNode));
    m_edgeNode->y_max_vertex = myEdgeNode.y_max_vertex;
    m_edgeNode->x_of_y_min = myEdgeNode.x_of_y_min;
    m_edgeNode->inverseSlope = myEdgeNode.inverseSlope;

    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->val = *m_edgeNode;
    newNode->next = NULL;


    if(head == NULL){
        return newNode;
    }


    if(head->val.x_of_y_min > myEdgeNode.x_of_y_min){
        printf("head > val\n");
        newNode->next = head;
        head = newNode;

        LLNode* temp = head;
        while(temp != NULL){
            printf("%d->", temp->val.x_of_y_min);
            temp = temp->next;
        }
        printf("\n");
        return head;
    }

    LLNode* temp = head;
    LLNode* prev = head;


    printf("Traversing\n");
    int flag = 0;
    while(temp != NULL){
        printf("hi\n");
        if(temp->val.x_of_y_min > myEdgeNode.x_of_y_min){   
            flag = 1;
            newNode->next = temp;
            prev->next = newNode;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("hello\n");
    if(flag == 0){
        prev->next = newNode;
    }

    return head;
}