/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

GLfloat angle, fAspect;
int raio = 8;
static int numeroDeLados = 16;

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
        default:
            break;

    }
    cout << "Raio = " << raio << endl;
    glutPostRedisplay();
}

void LabelStroke(char c, float h, bool left, bool top, float x, float y, float z){
    float scale = h / ( 119.05f + 33.33f );
    float xo = x;
    float yo = y;

    if ( left ){
        int w = glutStrokeWidth(GLUT_STROKE_ROMAN, c );
        xo -= h * (float)w / ( 119.05f + 33.33f );
    }
    if ( top )
        yo -= h * (float)119.05f / ( 119.05f + 33.33f );

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
        glTranslatef(xo, yo, z);
        glScalef(scale, scale, scale);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
}

void Eixos(float lado){
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glVertex3f( lado, 0.0, 0.0);
        glVertex3f( -lado, 0.0, 0.0);
        glVertex3f(0.0, lado, 0.0);
        glVertex3f(0.0, -lado, 0.0);
        glVertex3f(0.0, 0.0, lado);
        glVertex3f(0.0, 0.0, -lado);
    glEnd();

    float size = 1.0f;
    LabelStroke( 'X', size, true,  true,  lado, 0.0f, 0.0f );
    LabelStroke( 'Y', size, true,  true,  0.0f, lado, 0.0f );
    LabelStroke( 'Z', size, true,  true,  0.0f, 0.0f, lado );
}

void ripa(float lado, bool red){
    if(red)
        glColor3f(0.2, 0, 0);
    else
        glColor3f(0, 0, 0.2);

    glPushMatrix();
        glScalef(0.2, 0.05, 1);
        glutSolidCube(lado);
    glPopMatrix();
}

/* Program entry point */
void Inicializa (void){

    GLfloat luzAmbiente[4]={0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4]={0.7, 0.7, 0.7, 1.0};// "cor"
	GLfloat luzEspecular[4]={0.1, 0.1, 0.1, 1};// "brilho"

	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={0.4,0.4,0.4,0.4};
	GLint especMaterial = 1;

 	// Especifica que a cor de fundo da janela ser� Verde
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);

	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=40; //em angulo 45
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(){
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angle,fAspect,0.1,500); //0.1, 500

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	gluLookAt(17, 9, 17, 0,0,0, 0,1,0);
}

static void resize(GLsizei w, GLsizei h){
	// Para previnir uma divis�o por zero
	if (h == 0)
        h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

float anguloInterno(){
    return ((numeroDeLados - 2) * 180) / (float)numeroDeLados;
}

static void desenha(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float L, delta;
    bool red = true;

    L = 2*raio*sin(((360/numeroDeLados)/2)*M_PI/180); //DESCOBRE QUAL TEM QUE SER O TAMANHO DA RIPA
    delta = 0.1*L; //10% de L
    L+=delta;

    Eixos(L);

    for(int n=0; n < numeroDeLados; n++){
        glPushMatrix();
            glRotatef(n*360/numeroDeLados, 0, 0, 1);
            glRotatef(90, 0, 1, 0);
            glTranslatef(0, 0, raio);//TRANSLADA O TAMANHO DO RAIO
            glRotatef(anguloInterno()/2, 1, 0, 0); //ROTACIONA
            glTranslatef(0, 0, -(L/2 - delta/2)); //TRANSLADA X, METADE DO TAMANHO DA RIPA, MAS DEIXA UM DELTA SOBRANDO

            red = (red) ? false : true;
            ripa(L, red);
        glPopMatrix();
    }

    glutSwapBuffers();
}

int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("Hexadec�gono");

    glutInitWindowPosition(10,10);

    glutDisplayFunc(desenha);
    glutReshapeFunc(resize); //chamado qnd o tamanho da janela � alterado
    glutKeyboardFunc(eventoDeTeclado);

    // Inicializa par�metros de rendering
    Inicializa();
    glutMainLoop();

    return EXIT_SUCCESS;
}
