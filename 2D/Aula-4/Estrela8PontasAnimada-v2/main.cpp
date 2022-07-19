/*
TECLA -/+: diminui ou aumenta o raio do poligono
TECLA Q: sai do programa

A DEDUÇÃO DOS RESULTADOS PRESENTES NESTE PROGRAMA ESTA BREVEMENTE RELATADO NO ARQUIVO REDME DESTE PROJETO!!

Gabriel B Brandão !!
*/
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float raio = 8.72;

void atualizaTamanho(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5*raio, 1.5*raio, -1.5*raio, 1.5*raio);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void idle(){
    glutPostRedisplay();
}

void eventoDeTeclado(unsigned char key, int x, int y){
    switch(key){
    case 'q':
    case 'Q':
        exit(0);
        break;
    case '+':
        if(raio < 11.12)
            raio += 0.12;
        break;
    case '-':
        if(raio > 6.32)
            raio -= 0.12;
        break;
    default:
        break;

    }
    cout << "Raio = " << raio << endl;
    //cout << "Alpha Anterior = " << alpha << endl << endl;
}

void Eixos(){
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0,-raio);
        glVertex2f( 0.0, raio);
        glVertex2f( raio,0.0);
        glVertex2f( -raio,0.0);
    glEnd();
}

void quadrado(bool red){
    if(red)
        glColor3f(1.0,0.0,0.0); //VERMELHO
    else
        glColor3f(0.0,0.0,1.0); //AZUL
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.5,-0.5);
        glVertex2f(-0.5,-0.5);
    glEnd();
}

void retangulo(float L, bool red){
    glPushMatrix();
        glScalef(L, 0.25, 1.0);
        quadrado(red);
    glPopMatrix();
}

void ponto(){
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(0, 0);
    glEnd();
}

void estrelaDe8Pontas (float R, float alpha){
    glLineWidth(3);
    glColor3f(0.0,1.0,0.0);

    glPushMatrix();
        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(R*cos((180-alpha)*M_PI/180), R*sin((180-alpha)*M_PI/180));
        glEnd();

        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(R*cos((180+alpha)*M_PI/180), R*sin((180+alpha)*M_PI/180));
        glEnd();
    glPopMatrix();
    glLineWidth(1);
}

void estrelaDe8PontasRipas(float L, float alpha){
    //coloca a ripa de cima
    glPushMatrix();
        glRotatef(180-alpha, 0, 0, 1);
        glTranslatef(L/2, 0, 0);
        retangulo(L, true);
    glPopMatrix();
    //prego na ponta da ripa de cima
    glPushMatrix();
        glRotatef(180-alpha, 0, 0, 1);
        glTranslatef(L, 0, 0);
        ponto();
    glPopMatrix();
    //coloca ripa de baixo
    glPushMatrix();
        glRotatef(180+alpha, 0, 0, 1);
        glTranslatef(L/2, 0, 0);
        retangulo(L, false);
    glPopMatrix();
}

void atualizaDesenhoEstrela(){
    glClear(GL_COLOR_BUFFER_BIT);

    Eixos();

    float L = 3.12;

    float raioVerde = L;
    float raioVermelho = raio - L;

    //assumindo teta = 0º para o circulo vermelho:
    float x0 = raio - L;
    float y0 = 0;
    float fi = 22.5;//anguloCentral(); //em graus

    ///Lei dos Cossenos:
    //*descobrir o tamanho de AB (chamado de c):
    float a = L;
    float b = raioVermelho;
    float c = -1; //((?)-incógnita lado do triangulo (do centro ao ponto B)
    //bhaskara
    float A = 1;
    float B = -2*b*cos(fi*M_PI/180);
    float C = pow(b,2) - pow(a,2);
    float deltaBaskara = pow(B,2) - 4*A*C;

    float c1 = (-1*B + sqrt(deltaBaskara))/2*A;
    float c2 = (-1*B - sqrt(deltaBaskara))/2*A;

    if(c1 > c2) ///sempre o lado de menor tamanho:
        c = c2;
    else
        c = c1;

    //*descobrir o angulo Alpha:
    float cosAlpha = (pow(c,2) - (pow(a,2) + pow(b,2))) / (-2*a*b);
    float alpha = acos(cosAlpha)*180/M_PI; //converte para graus;

    for(int i = 0; i < 8; i ++)    {
        glPushMatrix();
        glRotatef(i*(2*fi), 0, 0, 1);
        glTranslatef(raioVermelho, 0, 0);
        //estrelaDe8Pontas(raioVerde, alpha);
        estrelaDe8PontasRipas(L, alpha);
        ponto();
        glPopMatrix();
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Estrela de 8 Pontas Animada - v2");

    glutReshapeFunc(atualizaTamanho);
    glutDisplayFunc(atualizaDesenhoEstrela);
    glutKeyboardFunc(eventoDeTeclado);
    glutIdleFunc(idle);

    glClearColor(1,1,0.8,1);
    glutMainLoop();

    return 0;
}
