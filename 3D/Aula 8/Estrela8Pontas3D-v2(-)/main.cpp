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

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

GLfloat angle, fAspect;
//static float lado = 16.0;
float raio = 8.72;
/* GLUT callback Handlers */

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
    glutPostRedisplay();
}

void LabelStroke(char c, float h, bool left, bool top, float x, float y, float z){
    float scale = h / ( 119.05f + 33.33f );
    float xo = x;
    float yo = y;
    if ( left )
    {
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
        glColor3f(1, 0, 0);
    else
        glColor3f(0, 0, 1);

    //glutWireCube(lado);
    glPushMatrix();
        //glScalef(0.2, 0.05, 1);
        glScalef(1, 0.05, 0.2);
        //glutWireCube(lado);
        glutSolidCube(lado);
    glPopMatrix();
}

/* Program entry point */
void Inicializa (void){

    GLfloat luzAmbiente[4]={0.1, 0.1, 0.1, 1.0};
	GLfloat luzDifusa[4]={1, 1, 1, 1.0};// "cor" GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; //efeito degrade
	GLfloat luzEspecular[4]={0.1, 0.1, 0.1, 1.0};// "brilho" GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};

	GLfloat posicaoLuz[4]={-100.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={0.4, 0.4, 0.4, 1}; //GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLfloat especMaterial = 0.9; //GLfloat especMaterial = 60;

 	// Especifica que a cor de fundo da janela será Verde
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	// Define a concentração do brilho
    glMaterialf(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=40; //em angulo 45
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.1,500); //0.1, 500
	//glFrustum(-10, 10, -10, 10, 0.1, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(10, 7, 15, 0,0,0, 0,1,0); //(20,80,200, 0,0,0, 0,1,0); (fovy 10)
	//gluLookAt(0, 0, 30, 0,0,0, 0,1,0); // PLANO XY (fovy 60)
	//gluLookAt(30, 0, 0, 0,0,0, 0,1,0); // PLANO YZ (fovy 60)
}

static void resize(GLsizei w, GLsizei h){
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
    //fAspect = 1;
	EspecificaParametrosVisualizacao();
}

void estrelaDe8PontasRipas(float lado, float alpha){




       //coloca a ponta extrema PRIMARIA de CIMA
    glPushMatrix();
        glRotatef(-alpha, 0, 1, 0);
        glTranslatef(-lado/2, 0, 0);
        ripa(lado, true);
        //prego na PONTA da ripa PRIMARIA de cima
            glTranslatef(-lado/2, 0, 0);
            //ponto();
    glPopMatrix();

    //coloca ponta extrema PRIMARIA de BAIXO
    glPushMatrix();
        glRotatef(alpha, 0, 1, 0);
        glTranslatef(-lado/2, 0, 0);
        ripa(lado, false);
    glPopMatrix();

}

static void desenha(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float L = 3.12;
    float raioVerde = L;
    float raioVermelho = raio - L;

    float A = 22.5;//anguloCentral em graus

    Eixos(L);





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
                glRotatef(90, 1, 0, 0);

                //estrelaDe8Pontas(raioVerde, alpha); //raioVerde é o mesmo que L
                estrelaDe8PontasRipas(L, alpha);
            glPopMatrix();
        }







    ripa(L, true);

    glutSwapBuffers();
}


/*

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
*/

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("Cubo-v2");

    //glutInitWindowPosition(10,10);

    glutDisplayFunc(desenha);
    glutReshapeFunc(resize); //chamado qnd o tamanho da janela é alterado
    glutKeyboardFunc(eventoDeTeclado);

    /*
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
*/
    // Inicializa parâmetros de rendering
    Inicializa();
    glutMainLoop();

    return EXIT_SUCCESS;
}
