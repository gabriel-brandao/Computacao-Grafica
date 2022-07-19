/*
TECLA -/+: diminui ou aumenta o raio do poligono
TELCA A/S: diminui ou aumenta o numero de lados do poligono
TECLA Q: sai do programa

eq. da reta que forma o raio do Hexagono:
y = x * tan(22.5º) //y - yo = m(x - x0)

eq. da circunferencia VERMELHA:
x^2 + y^2 = (raio - L)^2

eq. da circunferencia VERDE:
(x - x0)^2 + (y - y0)^2 = L^2
C = (x0, y0)

a circunferencia VERDE precisa ter centro no raio da circunferencia VERMELHA assim:
x0 = (raio - L)*cos(teta)
y0 = (raio - L)*sen(teta)

para teta = 0º:
x0 = (raio - L);
y0 = 0;

(x - (raio - L))^2 + (y)^2 = L^2
...
x^2 * (1 + (tan(fi))^2) + x * (-2*(raio - L)) + raio(raio - 2*L) = 0


Para o ponto (x,y) estar contido na circunferencia VERMELHA deve satisfazer a seguinte inequacao:
x^2 + y^2 <= (raio - L)^2


para descobrir angulo entre vetores usar produto escalar:
cos(alfa) = (u . v) / ||u||*||v|| = A
arcos(A) = alfa
________________________________________________________________________________________

todas as formulas foram deduzida usando o geogebra e aplicações de algebra linear e geometria analitica.

Gabriel B Brandão !!
*/
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

float raio = 8;//8
int numeroDeLados = 16;

void atualizaTamanho(int width, int height){
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

 void eixosRetangulo(float l){
    glColor3f(0.0f,0.0f,0.0f);

    glBegin(GL_LINES);
		glVertex2f(0.0,-l);
		glVertex2f( 0.0, l);
		glVertex2f( l,0.0);
        glVertex2f( -l,0.0);
	glEnd();
}

void retangulo(float L, float delta, bool red){
    glPushMatrix();
        glScalef(L, 0.25, 1.0);
        quadrado(red);
    glPopMatrix();
/*
    glPushMatrix();
        glTranslatef(-(L/2-delta/2), 0, 0);
        eixosRetangulo(0.25);
    glPopMatrix();

    glPushMatrix();
        glTranslatef((L/2-delta/2), 0, 0);
        eixosRetangulo(0.25);
    glPopMatrix();
*/
 }

void circulo (float R){
    glColor3f(0.0,0.0,0.0);

    float teta;

    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i++){ //360 pontos (a cada 1º um ponto)
            teta = i*PI/180; //tranforma para rad
            glVertex2f(0 + R*cos(teta), 0 + R*sin(teta)); //cria um circulo com centro (0,0) e raio 1
        }
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

void ponto(){
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(4);
    glBegin(GL_POINTS);
        glVertex2f(0, 0);
    glEnd();
}

void estrelaDe8PontasRipas(float L, float delta, float fi, float alpha){
     //coloca a ripa de cima
     glPushMatrix();
        glRotatef(180-alpha, 0, 0, 1);
        glTranslatef((L/2 - (delta/2)), 0, 0);
        retangulo(L, delta, true);
     glPopMatrix();
    //prego na ponta da ripa de cima
     glPushMatrix();
        glRotatef(180-alpha, 0, 0, 1);
        glTranslatef((L - delta), 0, 0);
        ponto();
     glPopMatrix();
    //coloca ripa de baixo
    glPushMatrix();
        glRotatef(180+alpha, 0, 0, 1);
        glTranslatef((L/2 - (delta/2)), 0, 0);
        retangulo(L, delta, false);
    glPopMatrix();
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
    return ((numeroDeLados - 2) * 180) / (float)numeroDeLados; //graus
}

float anguloCentral(){
    return 360 / (float)numeroDeLados; //graus
}

void atualizaDesenhoHexadecagono(){
    //glClear(GL_COLOR_BUFFER_BIT);

    float L, delta, fi;
    bool red = false;

    L = 2*raio*sin(((360/numeroDeLados)/2)*PI/180); //DESCOBRE QUAL TEM QUE SER O TAMANHO DA RIPA
    delta = 0.25;
    L+=delta;

    fi = anguloCentral();

    Eixos();

    for(int i = 0; i < numeroDeLados; i++){
        glPushMatrix();
            glTranslatef(raio*cos(i*fi*M_PI/180), raio*sin(i*fi*M_PI/180), 0.0);//TRANSLADA O TAMANHO DO RAIO
            ponto();
            glRotatef(180 - anguloInterno()/2 + i*fi, 0, 0, 1); //ROTACIONA
            glTranslatef(L/2 - delta/2, 0.0, 0.0); //TRANSLADA X, METADE DO TAMANHO DA RIPA, MAS DEIXA UM DELTA SOBRANDO
            red = (red == false) ? true : false;
            retangulo(L, delta, red);
        glPopMatrix();
    }

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
            if(raio < 35)
            raio += 0.12;
            break;
        case '-':
            if(raio > 1)
                raio -= 0.12;
            break;
        case 's':
        case 'S':
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

void atualizaDesenhoEstrela(){
    glClear(GL_COLOR_BUFFER_BIT);

    Eixos();

    float L, delta=0;
    L=3.12;
    //bool red = true;
/*
    L = 2*raio*sin(((360/numeroDeLados)/2)*PI/180); //DESCOBRE QUAL TEM QUE SER O TAMANHO DA RIPA
    delta = 0.25; //10% de L
    L+=delta;
*/
    float raioVerde = L;
    float raioVermelho = raio - L;

    //assumindo teta = 0º para o circulo vermelho:
    float x0 = raio - L;
    float y0 = 0;
    float fi = anguloCentral(); //em graus

    // variaveis para baskara:
    float a = 1 + pow(tan(fi*M_PI/180), 2);
    float b = -2*(raio - L);
    float c = raio*(raio - 2*L);
    float deltaBaskara = pow(b,2) - 4 * a * c;

    float numerador, denominador;
    numerador = -1*b + pow(deltaBaskara, 0.5);
    denominador = 2*a;
    float x1 = numerador / denominador;
    float y1 = x1 * tan(fi*M_PI/180);

    numerador = -1*b - pow(deltaBaskara, 0.5);

    float x2 = numerador / denominador;
    float y2 = x2 * tan(fi*M_PI/180);

    //descoberta dos vetores u e v:
    float x, y;
    float u[2];
    float v[2];
    x=x1;
    y=y1;

    //pega o ponto que esta contido no circulo VERMELHO e cria os vetores u e v:
    if(!((pow(x,2) + pow(y,2)) <= pow((raio - L),2))){
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
    cout << alpha << endl;
    for(int i = 0; i < 8; i ++){
        glPushMatrix();
            glRotatef(i*(2*fi), 0, 0, 1);
            glTranslatef(raioVermelho-(delta), 0, 0);
            estrelaDe8Pontas(raioVerde, alpha);
            //estrelaDe8PontasRipas(L, delta, fi, alpha);
            ponto();
        glPopMatrix();
    }

    atualizaDesenhoHexadecagono();
    glutSwapBuffers();

}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

        glutCreateWindow("Estrela de 8 Pontas - v2");

        glutReshapeFunc(atualizaTamanho);
        glutDisplayFunc(atualizaDesenhoEstrela);
        glutKeyboardFunc(eventoDeTeclado);
        glutIdleFunc(idle);

        glClearColor(1,1,0.8,1);
    glutMainLoop();

    return 0;
}
