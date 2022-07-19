#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

using namespace std;


/* Fun��es  tratamento de eventos  */

static void Atualiza_tamanho(int Janela_width, int Janela_height)
{
    glViewport(0,0,Janela_width,Janela_height); //1
    glMatrixMode(GL_PROJECTION); //2
    glLoadIdentity(); //3

    gluOrtho2D(-30.0,30.0,-30.0,30.0); //4 ou p/3D

    glMatrixMode(GL_MODELVIEW);//5
    glLoadIdentity();//inicializa matriz com a matriz identidade//6
}

static void Atualiza_desenho(void)
{


    glClear(GL_COLOR_BUFFER_BIT);//Limpa janela //1
    glColor3f(1.0,0.0,0.0); //2

    glBegin(GL_LINE_LOOP);
        glVertex2f(-10.0f,-10.0f);
        glVertex2f(-10.0f,5.0f);
        glVertex2f(0.0f,15.0f);
        glVertex2f(10.0f,5.0f);
        glVertex2f(10.0f,-10.0f);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);//1
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );//4
    glutInitWindowPosition(10,10);//3
    glutInitWindowSize(600,600);//2
    glutCreateWindow("LCG - Desenho 2D");//5
    //registra fun��o callback para tratar evento de redimensionamento de janela
    glutReshapeFunc(Atualiza_tamanho);//6
    //registra fun��o callback para tratar evento de desenho
    glutDisplayFunc(Atualiza_desenho);//7
    //define a cor de limpeza da janela como sendo a branca
    glClearColor(1,1,1,0);//10
    //Inicia tratamento de eventos
    glutMainLoop();//00

    return 0;
}

