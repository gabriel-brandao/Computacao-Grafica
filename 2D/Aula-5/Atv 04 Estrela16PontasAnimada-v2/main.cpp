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
    float fi = 22.5; //anguloCentral em graus

    // variaveis para baskara assumindo as eq I e II:
    float a = 1 + pow(tan(fi*M_PI/180), 2);
    float b = -2*(raio - L);
    float c = raio*(raio - 2*L);
    float deltaBaskara = pow(b,2) - 4 * a * c;

    float x1 = (-1*b + pow(deltaBaskara, 0.5)) / (2*a);
    float y1 = x1 * tan(fi*M_PI/180);

    float x2 = (-1*b - pow(deltaBaskara, 0.5)) / (2*a);
    float y2 = x2 * tan(fi*M_PI/180);

    //descoberta dos vetores u e v:
    float x, y;
    float u[2];
    float v[2];

    //pega o ponto que esta mais proximo da origem e cria os vetores u e v:
    if((pow(x1,2) + pow(y1,2)) <= (pow(x2,2) + pow(y2,2))){
        x = x1;
        y = y1;
    }
     else{
        x = x2;
        y = y2;
     }

    u[0] = 0 - x0;
    u[1] = 0 - y0;
    v[0] = x - x0;
    v[1] = y - y0;

    //decobre angulo entre os vetores u e v:
    float A = (u[0]*v[0] + u[1]*v[1]) / (sqrt((pow(u[0], 2) + pow(u[1], 2))) * sqrt((pow(v[0], 2) + pow(v[1], 2))));
    float alpha = acos(A)*180/M_PI; // converte para graus;

    for(int j = 0; j < 2; j++){
      glPushMatrix();
        glRotatef(fi*j, 0, 0, 1);
        for(int i = 0; i < 8; i ++){
            glPushMatrix();
                glRotatef(i*(2*fi), 0, 0, 1);
                glTranslatef(raioVermelho, 0, 0);
                //estrelaDe8Pontas(raioVerde, alpha);
                estrelaDe8PontasRipas(L, alpha);
                ponto();
            glPopMatrix();
        }
      glPopMatrix();
    }
    glutSwapBuffers();

}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

        glutCreateWindow("Estrela de 8 Pontas Animada-v2");

        glutReshapeFunc(atualizaTamanho);
        glutDisplayFunc(atualizaDesenhoEstrela);
        glutKeyboardFunc(eventoDeTeclado);
        glutIdleFunc(idle);

        glClearColor(1,1,0.8,1);
    glutMainLoop();

    return 0;
}
