
/*  Este exemplo mostra como trabalhar com multiplas viewport
 *
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
    // define a primeira viewport, deve ser antes da gluOrtho2D
    glViewport(0,0,150,150);
    // seleciona a matrix PROJECTION
    glMatrixMode(GL_PROJECTION);
    // inicializa com a matriz identidade
    glLoadIdentity();
    gluOrtho2D(0.0,50.0,-10.0,40.0); // esta fun��o tamb�m define a window
    // seleciona a cor azul
    glColor3f( 0, 0, 1 );
    glRectf(0.0,0.0,10.0,30.0);

    // define a segunda viewport
    glViewport(150,150,150,150);
    // seleciona a matrix PROJECTION
    glMatrixMode(GL_PROJECTION);
    // inicializa com a matriz identidade
    glLoadIdentity();
    gluOrtho2D(0.0,50.0,-10.0,40.0); // esta fun��o tamb�m define a window
    // seleciona a cor vermelha
    glColor3f( 0, 0, 1 );
    glRectf(0.0,0.0,10.0,30.0);
    // desenho
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
	glutCreateWindow("Exemplo com duas Viewport");
	glutDisplayFunc(Atualiza_desenho);
	glutKeyboardFunc (Teclado);
	init();
	glutMainLoop();
    return 0;
}



