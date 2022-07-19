/*  Este exemplo mostra como especificar as dimens�es de uma viewport usando a fun��o glViewport()
 *
 *  A viewport pode ser  definida com as dimens�es da janela de interface ou com outras dimes�es
 *  compat�veis com a janela de interface
 */

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


/* Inicializa��o de estados*/
void init(){
    // cor de fundo - amarela
    glClearColor( 100, 100, 0, 0 );
}
/* Fun��es projetadas para tratar as diferentes classes de eventos */


void Atualiza_desenho(void){

    // limpa a janela com o amarelo
    glClear ( GL_COLOR_BUFFER_BIT );
    // define a viewport, deve ser antes da gluOrtho2D
    glViewport(0,0,150,150);
    // seleciona a matrix PROJECTION
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,50.0,-10.0,40.0); // esta fun��o tamb�m define a window
    // seleciona a cor azul
    glColor3f( 0, 0, 1 );
    glRectf(0.0,0.0,10.0,30.0);
    // desenho
    //glutSwapBuffers();
    glFlush();
}

void Teclado( unsigned char tecla, int x, int y){
    switch (tecla){
        case 27 :
        case 'q':
            exit(0);
        break;
    }
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,50);
	glutInitWindowSize(300,300);
	glutCreateWindow("Viewport default");
	glutDisplayFunc(Atualiza_desenho);
	glutKeyboardFunc (Teclado);
	init();
	glutMainLoop();
    return 0;
}


