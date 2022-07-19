/*  Este exemplo mostra o uso default de glViewport()
 *  Quando a viewport n�o � especificada em uma aplica��o OpenGL ent�o
 *  ela � definida com as dimens�es da janela de interface
 */
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


/* Inicializa��o de estados*/
void init(){
    // cor de fundo - amarela
    glClearColor( 100, 100, 0, 0 );
}
/* Fun��es projetadas para tratar as diferentes classes de eventos */
/*void Atualiza_tamanho(int largura, int altura){
    glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D (-30.0f, 30.0f, -30.0f, 30.0f);
}*/

void draw(){
    // limpa a janela com o amarelo
    glClear ( GL_COLOR_BUFFER_BIT );
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

/*void Atualiza_desenho(void){


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
		glVertex2f(-20.0,-20.0);
		glVertex2f( 0.0,10.0);
        glVertex2f( 20.0,-20.0);
	glEnd();
	glFlush();
}*/

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
	//glutDisplayFunc(Atualiza_desenho);
    glutDisplayFunc(draw);

	//glutReshapeFunc(Atualiza_tamanho);
	glutKeyboardFunc (Teclado);
	init();
	glutMainLoop();
    return 0;
}

