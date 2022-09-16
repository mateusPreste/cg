#include <GL/glut.h>
#include <iostream>
#include <cmath>

const double PI = 3.141592653589793238463;

typedef struct coordenada
{
    double x;
    double y;
} coordenada;

typedef struct quadrado
{
    coordenada p1;
    coordenada p2;
    coordenada p3;
    coordenada p4;
} quadrado;

double x_pos = -1.0;
double y_pos = 9.0;
double passos = 360;
int pulseInterval = passos;
double currentScale = 1;
double aux;
int cont = 0;

quadrado *q;

quadrado *criaQuadrado ()
{
    quadrado *novo = (quadrado*) malloc(sizeof(quadrado));
    novo->p1.x = x_pos;
    novo->p1.y = y_pos;
    novo->p2.x = x_pos;
    novo->p2.y = y_pos-1.0;
    novo->p3.x = x_pos+1.0;
    novo->p3.y = y_pos-1.0;
    novo->p4.x = x_pos+1.0;
    novo->p4.y = y_pos;
    return novo;
}

coordenada *calculaCentro(quadrado *q1)
{
    coordenada *centro = (coordenada*) malloc(sizeof(coordenada));
    centro->x = (q1->p1.x + q1->p2.x + q1->p3.x + q1->p4.x)/4.0;
    centro->y = (q1->p1.y + q1->p2.y + q1->p3.y + q1->p4.y)/4.0;
    return centro;
}

void desenhaQuadrado (quadrado* q1)
{
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(q1->p1.x, q1->p1.y);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(q1->p2.x, q1->p2.y);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(q1->p3.x, q1->p3.y);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(q1->p4.x, q1->p4.y);
    glEnd();
}

double internalRotation = 0;

double devRotation = 0;

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    coordenada *c = calculaCentro(q);

    glLoadIdentity();

    glTranslatef(-c->x, -c->y, 0);

    devRotation += (360.0/(passos));
    

    glRotatef ((GLfloat) devRotation, 0.0, 0.0, 1.0);

    //glTranslatef(c->x, c->y, 0);  // Move back to original position

    //internalRotation += (360.0*4)/(passos);
    //glRotatef ((GLfloat) -internalRotation, 0.0, 0.0, 1.0);

    //glLoadIdentity();

    glTranslatef(c->x, c->y, 0);  // Move right and into the middle of screen

    desenhaQuadrado(q);

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void inicializa (void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0.0, 200.0, 0.0, 200.0);

    q = criaQuadrado();
}

void translacao_origem(double d1, double d2)
{
    q->p1.x = q->p1.x + d1;
    q->p1.y = q->p1.y + d2;
    q->p2.x = q->p2.x + d1;
    q->p2.y = q->p2.y + d2;
    q->p3.x = q->p3.x + d1;
    q->p3.y = q->p3.y + d2;
    q->p4.x = q->p4.x + d1;
    q->p4.y = q->p4.y + d2;
}

void Multiply(double N[2][2], quadrado *q, double Result[2][4])
{
    double* M[2][4] = {{&(q->p1.x), &(q->p2.x), &(q->p3.x), &(q->p4.x)}, {&(q->p1.y), &(q->p2.y), &(q->p3.y), &(q->p4.y)}};

    for (int I = 0; I < 2; ++I)
    {
        for (int J = 0; J < 4; ++J)
        {
            double SumElements = 0.0f;
            for (int K = 0; K < 2; ++K)
            {
                SumElements += N[I][K] * *(M[K][J]);
            }
            Result[I][J] = SumElements;
        }
    }

    for (int a = 0; a < 2; a++){
        for(int b = 0; b < 4; b++){
            *(M[a][b]) = Result[a][b];
        }
    }
}

double degreeToRad(double degree){
    return (2.0*PI*degree*1.0)/360.0;
}

double currentDegree = 0.0;

#include <stdlib.h> 
#include <cmath>

void timer(int value) {
    cont = cont + 1;
    currentDegree = std::fmod(((360.0/((int)passos))*cont), 90);
    
    glutTimerFunc(1000/144, timer, 0);
    
    coordenada *c = calculaCentro(q);
    
    //if(cont == 1){
    //    cont = 0;
    //    translacao_origem(-c->x, -c->y);
    //
    //
    //    double T [2][2] = {{1/std::pow(escala, 1), 0},{0, 1/std::pow(escala, 1)}};
    //    double result [2][4] = {};
    //    Multiply(T, q, result);
    //
    //    
    //    translacao_origem(c->x, c->y);
    //}
    
    //translacao_origem(-c->x, -c->y);


    //Rotação em volta do proprio eixo
    //double T0 [2][2] = {{cos(degreeToRad(((360.0*4)/(passos)))), -sin(degreeToRad(((360.0*4)/(passos))))}, {sin(degreeToRad(((360.0*4)/(passos)))), cos(degreeToRad(((360.0*4)/(passos))))}};
    //double result0 [2][4] = {};
//
    //Multiply(T0, q, result0);
    
    //rotação em torno do proprio eixo
    //aux = q->p1.x;
    //q->p1.x = (q->p1.x*0.866+q->p1.y*0.5);
    //q->p1.y = (aux*(-0.5)+q->p1.y*0.866);
    //aux = q->p2.x;
    //q->p2.x = (q->p2.x*0.866+q->p2.y*0.5);
    //q->p2.y = (aux*(-0.5)+q->p2.y*0.866);
    //aux = q->p3.x;
    //q->p3.x = (q->p3.x*0.866+q->p3.y*0.5);
    //q->p3.y = (aux*(-0.5)+q->p3.y*0.866);
    //aux = q->p4.x;
    //q->p4.x = (q->p4.x*0.866+q->p4.y*0.5);
    //q->p4.y = (aux*(-0.5)+q->p4.y*0.866);

    // calcula os fatores da matriz de escala usando o angulo atual de inclinação do quadrado
    //double newScaleFactor = (abs((currentDegree/90.0)-0.5)+0.5)/currentScale;

    //currentScale *= newScaleFactor;

    //std::cout << currentScale << " " << currentDegree << std::endl;

    //double T1 [2][2] = {{newScaleFactor, 0},{0, newScaleFactor}};
    //double result1 [2][4] = {};

    //Multiply(T1, q, result1);

    //q->p1.x = q->p1.x * escala;
    //q->p1.y = q->p1.y * escala;
    //q->p2.x = q->p2.x * escala;
    //q->p2.y = q->p2.y * escala;
    //q->p3.x = q->p3.x * escala;
    //q->p3.y = q->p3.y * escala;
    //q->p4.x = q->p4.x * escala;
    //q->p4.y = q->p4.y * escala;
    //translacao_origem(c->x, c->y);
    
    //double T2 [2][2] = {{cos(degreeToRad(360.0/(passos))), sin(degreeToRad(360.0/(passos)))},
                      //{-sin(degreeToRad(360.0/(passos))), cos(degreeToRad(360.0/(passos)))}};
    //double result2 [2][4] = {};

    //Multiply(T2, q, result2);


    //rotacao em volta da origem
    //aux = q->p1.x;
    //q->p1.x = (q->p1.x*0.9659+q->p1.y*0.2588);
    //q->p1.y = (aux*(-0.2588)+q->p1.y*0.9659);
    //aux = q->p2.x;
    //q->p2.x = (q->p2.x*0.9659+q->p2.y*0.2588);
    //q->p2.y = (aux*(-0.2588)+q->p2.y*0.9659);
    //aux = q->p3.x;
    //q->p3.x = (q->p3.x*0.9659+q->p3.y*0.2588);
    //q->p3.y = (aux*(-0.2588)+q->p3.y*0.9659);
    //aux = q->p4.x;
    //q->p4.x = (q->p4.x*0.9659+q->p4.y*0.2588);
    //q->p4.y = (aux*(-0.2588)+q->p4.y*0.9659);
    
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Questao 19");
    inicializa();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}