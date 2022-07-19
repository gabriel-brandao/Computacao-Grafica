#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/* Fun��es projetadas para tratar as diferentes classes de eventos */
void Atualiza_tamanho(int largura, int altura){
    glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D (-30.0f, 30.0f, -30.0f, 30.0f);
}

void Atualiza_desenho(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
//glRectf(-20.0,-20.0,20.0,20.0);
    glBegin(GL_TRIANGLES);
    //glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-20.0,-20.0);
		glVertex2f( 0.0,10.0);
        glVertex2f( 20.0,-20.0);
	glEnd();
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
	glutCreateWindow("sem tratamento de Razao de Aspecto - ");
	glutDisplayFunc(Atualiza_desenho);
	glutReshapeFunc(Atualiza_tamanho);
	glutKeyboardFunc (Teclado);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
    return 0;
}
