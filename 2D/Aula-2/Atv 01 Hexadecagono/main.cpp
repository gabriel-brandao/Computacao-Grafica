/*
TECLA -/+: diminui ou aumenta o raio do poligono
TELCA A/S: diminui ou aumenta o numero de lados do poligono
TECLA Q: sai do programa

Gabriel B Brandão !!
*/
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

int raio = 8;
int numeroDeLados = 16;

void atualizaTamanho(int width, int height){
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.5*raio, 1.5*raio, -1.5*raio, 1.5*raio);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
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

 void circulo (){
    glColor3f(0.0,0.0,0.0);

    float teta;

    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i++){ //360 pontos (a cada 1º um ponto)
            teta = i*PI/180; //tranforma para rad
            glVertex2f(0 + 1*cos(teta), 0 + 1*sin(teta)); //cria um circulo com centro (0,0) e raio 1
        }
    glEnd();
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

float anguloInterno(){
    return ((numeroDeLados - 2) * 180) / (float)numeroDeLados;
}

void pregos(){
    glClear(GL_COLOR_BUFFER_BIT);

    circulo();

    float teta;
        for(int i = 0; i < numeroDeLados; i ++){
            teta = i*360/numeroDeLados; //++22,5º

            glPushMatrix();
                glRotatef(teta, 0, 0, 1);
                glTranslatef(raio*cos(teta*PI/180), raio*sin(teta*PI/180), 0);
                glScalef(0.1, 0.1, 1);

                circulo();
            glPopMatrix();
        }
    glutSwapBuffers();
}

void atualizaDesenho(){
    glClear(GL_COLOR_BUFFER_BIT);

    float L, delta;
    bool red = true;

    L = 2*raio*sin(((360/numeroDeLados)/2)*PI/180); //DESCOBRE QUAL TEM QUE SER O TAMANHO DA RIPA
    delta = 0.1*L; //10% de L
    L+=delta;

    Eixos();
        glPushMatrix();
            glTranslatef(raio, 0.0, 0.0);//TRANSLADA O TAMANHO DO RAIO
            glRotatef(180 - anguloInterno()/2, 0, 0, 1); //ROTACIONA
            glTranslatef(L/2 - delta/2, 0.0, 0.0); //TRANSLADA X, METADE DO TAMANHO DA RIPA, MAS DEIXA UM DELTA SOBRANDO

            retangulo(L, red);

            for(int n=0; n < numeroDeLados-1; n++){
                glTranslatef(L/2, 0.0, 0.0); //TRANSLADA X, METADE DO TAMANHO DA RIPA
                glRotatef(180 - anguloInterno(), 0, 0, 1); ///22.5º
                glTranslatef(L/2 - delta/2, 0.0, 0.0);

                red = (red) ? false : true;
                retangulo(L, red);
            }
        glPopMatrix();

    //pregos();
    glutSwapBuffers();
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
            if(raio < 15)
            raio ++;
            break;
        case '-':
            if(raio > 1)
                raio --;
            break;
        case 's':
        case 'S':
            if(numeroDeLados < 180)
                numeroDeLados++;
            break;
        case 'a':
        case 'A':
            if(numeroDeLados > 3)
                numeroDeLados --;
            break;

        default:
            break;

    }
    cout << "Raio = " << raio << endl;
    cout << "Numero de ripas: " << numeroDeLados << endl;
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

        glutCreateWindow("Hexadecagono");

        glutReshapeFunc(atualizaTamanho);
        glutDisplayFunc(atualizaDesenho);
        glutKeyboardFunc(eventoDeTeclado);
        glutIdleFunc(idle);

        glClearColor(1,1,0.8,1);
    glutMainLoop();

    return 0;
}
