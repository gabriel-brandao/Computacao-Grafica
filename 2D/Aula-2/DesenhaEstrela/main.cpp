
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/* Eixos Ox e Oy */
void Eixos()
{
    glBegin(GL_LINES);
		glVertex2f(0.0,-1.0);
		glVertex2f( 0.0, 1.0);
		glVertex2f( 1.0,0.0);
        glVertex2f( -1.0,0.0);
	glEnd();
}
/* Objeto estrela */
void Estrela(void){ //desenha Estrela
    glBegin(GL_LINE_LOOP);
		glVertex2f( 0.0,0.35);
		glVertex2f( 0.05,0.1);
        glVertex2f( 0.3,0.1);
		glVertex2f( 0.1,0.0);
        glVertex2f( 0.2,-0.2);
        glVertex2f( 0.0,-0.06);
        glVertex2f( -0.2,-0.2);
		glVertex2f( -0.1,0.0);
        glVertex2f( -0.3,0.1);
        glVertex2f( -0.05,0.1);
	glEnd();
}

void Atualiza_desenho(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// inicializa a matriz modelview
    glClear(GL_COLOR_BUFFER_BIT); //Limpa janela

    glColor3f(0.0f, 0.0f, 0.0f); //Cor dos eixos
    Eixos();

    glColor3f(1.0f, 0.0f, 0.0f); //Cor da estrela
    Estrela();

    glTranslatef(0.7,0.0,0.0); //C=CT
    glColor3f(0.0f, 0.0f, 1.0f);
    Estrela();

    glRotatef(10,0,0,1);//C=CTR
    glScalef(0.5,0.5,1);//C=CTS
    glColor3f(0.0f, 1.0f, 0.0f);
    Estrela();

	glFlush(); // processa as rotinas OpenGL o mais rapido possivel
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
	glutInitWindowSize(300,300);
	glutCreateWindow("Transformacoes Geometricas");
	glutDisplayFunc(Atualiza_desenho);
	glutKeyboardFunc (Teclado);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Cor de fundo
	glutMainLoop();
    return 0;
}




