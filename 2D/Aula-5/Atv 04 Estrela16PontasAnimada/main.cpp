/*
TECLA -/+: diminui ou aumenta o raio do poligono
TECLA Q: sai do programa

A DEDUÇÃO DOS RESULTADOS PRESENTES NESTE PROGRAMA ESTA BREVEMENTE RELATADO NO ARQUIVO REDME DESTE PROJETO!!

Gabriel B Brandão !!
*/
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
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
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(0, 0);
    glEnd();
}

vector <float> pontoMedio(float Ax, float Ay, float Bx, float By){
    vector <float> Pm (2);

    Pm[0] = (Ax + Bx) / 2;
    Pm[1] = (Ay + By) / 2;
    return Pm;
}

float leiDosSenos_PHI(float c, float gama, float b){
    /* Aplicando lei dos senos:

    (c / sen(gama)) = ( b /  sen (AS))

        sen(AS) = (b/c) * sen (gama)
        AS = ArcSen(sen (AS))

        Obs.: AS - angulo secundario
        Obs.: a lei dos cossenos sempre retorna um angulo AGUDO
     */

     float AS = asin((b/c)*sin(gama*M_PI/180))*180/M_PI; //converte para graus
     return 180 - (gama + AS);
}

void estrelaDe8Pontas (float R, float alpha){
    vector <float> Pm (2);
    Pm = pontoMedio(0.0, 0.0, R*cos((180-alpha)*M_PI/180), R*sin((180-alpha)*M_PI/180));
    float phi = leiDosSenos_PHI(R, alpha+22.5, R/2);

    glLineWidth(3);
    glColor3f(0.0,1.0,0.0);

    glPushMatrix();
        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(R*cos((180-alpha)*M_PI/180), R*sin((180-alpha)*M_PI/180));
        glEnd();

        ///PES DE CIMA (ponto extremo secundario)
        glPushMatrix();
            glTranslatef(Pm[0], Pm[1], 0);
            glBegin(GL_LINES);
                glVertex2f(0.0, 0.0);
                glVertex2f(R*cos((180-(phi+alpha))*M_PI/180), R*sin((180-(phi+alpha))*M_PI/180));
            glEnd();
        glPopMatrix();

        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(R*cos((180+alpha)*M_PI/180), R*sin((180+alpha)*M_PI/180));
        glEnd();

        ///PES DE BAIXO
        glPushMatrix();
            glTranslatef(Pm[0], -Pm[1], 0);
            glBegin(GL_LINES);
                glVertex2f(0.0, 0.0);
                glVertex2f(R*cos(-1*(180-(phi+alpha))*M_PI/180), R*sin(-1*((180-(phi+alpha))*M_PI/180)));
            glEnd();
        glPopMatrix();

    glPopMatrix();
    glLineWidth(1);
}

void estrelaDe8PontasRipas(float L, float alpha){
    vector <float> Pm (2);
    Pm = pontoMedio(0.0, 0.0, L*cos((180-alpha)*M_PI/180), L*sin((180-alpha)*M_PI/180));
    float phi = leiDosSenos_PHI(L, alpha+22.5, L/2);

    //prego na EMENDA da PONTA PRIMARIA
    ponto();

    //coloca a ponta extrema PRIMARIA de CIMA
    glPushMatrix();
        glRotatef(-alpha, 0, 0, 1);
        glTranslatef(-L/2, 0, 0);
        retangulo(L, true);
        //prego na PONTA da ripa PRIMARIA de cima
            glTranslatef(-L/2, 0, 0);
            ponto();
    glPopMatrix();

    //coloca ponta extrema PRIMARIA de BAIXO
    glPushMatrix();
        glRotatef(alpha, 0, 0, 1);
        glTranslatef(-L/2, 0, 0);
        retangulo(L, false);
    glPopMatrix();

    //coloca ponta extrema SECUNDARIA de CIMA
    glPushMatrix();
        glTranslatef(Pm[0], Pm[1], 0);
        glRotatef(180-(phi + alpha), 0, 0, 1);
            //prego no MEIO da ripa SECUNDARIA de cima
            glPushMatrix();
                glTranslatef(0.1, 0, 0);
                ponto();
            glPopMatrix();

        glTranslatef(L/2, 0, 0);
        retangulo(L, false);
            //prego na PONTA da ripa SECUNDARIA de cima
            glTranslatef(L/2-0.1, 0, 0);
            ponto();
    glPopMatrix();

    //coloca ponta extrema SECUNDARIA de BAIXO
    glPushMatrix();
        glTranslatef(Pm[0], -Pm[1], 0);
        glRotatef(-1*(180-(phi + alpha)), 0, 0, 1);
            //prego no MEIO da ripa SECUNDARIA de baixo
            glPushMatrix();
                glTranslatef(0.1, 0, 0);
                ponto();
            glPopMatrix();

        glTranslatef(L/2, 0, 0);
        retangulo(L, true);
    glPopMatrix();
}

void atualizaDesenhoEstrela(){
    glClear(GL_COLOR_BUFFER_BIT);

    Eixos();

    float L = 3.12;
    float raioVerde = L;
    float raioVermelho = raio - L;

    float A = 22.5;//anguloCentral //em graus

    ///Lei dos Senos
    //1º descobrir alpha
    float senB = raioVermelho*sin(A*M_PI/180) / L;
    float B = asin(senB)*180/M_PI; //converte para graus
    B = 180 - B; //pega o angulo obtuso
    float alpha = 180 - (A + B);

    for(int i = 0; i < 8; i ++)    {
        glPushMatrix();
        glRotatef(i*(2*A), 0, 0, 1);
        glTranslatef(raioVermelho, 0, 0);
        //estrelaDe8Pontas(raioVerde, alpha); //raioVerde é o mesmo que L
        estrelaDe8PontasRipas(L, alpha);
        glPopMatrix();
    }
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Estrela de 16 Pontas Animada");

    glutReshapeFunc(atualizaTamanho);
    glutDisplayFunc(atualizaDesenhoEstrela);
    glutKeyboardFunc(eventoDeTeclado);
    glutIdleFunc(idle);

    glClearColor(1,1,0.8,1);
    glutMainLoop();

    return 0;
}
