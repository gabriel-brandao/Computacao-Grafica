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

float angle, fAspect;
float raio = 8.72;
bool aumentaRaio = true;
float oldTempo;

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
    glutPostRedisplay();
}

void idle(){
    const double newTempo = glutGet(GLUT_ELAPSED_TIME); //pega o tempo em milisegundo, desde o init até o momento
    float deltaTempo = (newTempo - oldTempo) / 1000.0; //transforma para segundos

    const double a = deltaTempo*1.2; //a cada segundo o raio aumenta em 1.2 o raio

        if(aumentaRaio){
            raio += a;
            if(raio >= 11.12) //limite máximo para o tamanho do raio
                aumentaRaio = false;
        }
        else
         if(!aumentaRaio){
            raio -= a;
            if(raio <= 6.32) //limite mínimo para o tamanho do raio
                aumentaRaio = true;
         }

    oldTempo = newTempo; //armazena o tempo atual para desconta-lo e não acumular na velocidade da animação
    glutPostRedisplay();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void){
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,5,40); //0.1, 500
	//glFrustum(-2, 2, -1.5, 1.5, 5, 40);


	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(15, 12, 20, 0,0,0, 0,1,0); //(20,80,200, 0,0,0, 0,1,0);
	//gluLookAt(0, 0, 30, 0,0,0, 0,1,0); // PLANO XY (fovy 60)
	//gluLookAt(30, 0, 0, 0,0,0, 0,1,0); // PLANO YZ (fovy 60)
}

void resize(GLsizei w, GLsizei h){
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
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

void ripa(float lado, int cor){

    switch(cor){
        case 0:
            glColor3f(0.2, 0, 0);
            break;
        case 1:
            glColor3f(0.2, 0.2, 0);
            break;
        case 2:
            glColor3f(0, 0.2, 0);
            break;
        case 3:
            glColor3f(0.2, 0, 0.2);
            break;
        case 4:
            glColor3f(0, 0, 0.2);
            break;
        case 5:
            glColor3f(0, 0.2, 0.2);
            break;
        default:
            break;
    }

    glPushMatrix();
        glScalef(0.2, 0.05, 1);
        glutSolidCube(lado);
    glPopMatrix();
}

void estrelaDe8PontasRipas(float lado, float alpha, int cor1, int cor2){
    //coloca a ponta extrema PRIMARIA de CIMA
    glPushMatrix();
        glRotatef(alpha, 1, 0, 0);
        glTranslatef(0, 0, -lado/2);
        ripa(lado, cor1);
    glPopMatrix();

    //coloca ponta extrema PRIMARIA de BAIXO
    glPushMatrix();
        glRotatef(-alpha, 1, 0, 0);
        glTranslatef(0, 0, -lado/2);
        ripa(lado, cor2);
    glPopMatrix();
}

void desenhaEstrela(float L, float alpha, float anguloCentral, float raioVermelho, int cor1, int cor2){
    for(int i = 0; i < 8; i ++)    {
        glPushMatrix();
            glRotatef(i*(2*anguloCentral), 0, 0, 1);
            glTranslatef(raioVermelho, 0, 0);
            glRotatef(90, 0, 1, 0);
            estrelaDe8PontasRipas(L, alpha, cor1, cor2);
        glPopMatrix();
    }
}

void desenhaEstrelaTripla(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float L = 3.12;
    float raioVermelho = raio - L;

    float A = 22.5;//anguloCentral em graus

    ///Lei dos Senos
    //1º descobrir alpha
    float senB = raioVermelho*sin(A*M_PI/180) / L;
    float B = asin(senB)*180/M_PI; //converte para graus
    B = 180 - B; //pega o angulo obtuso
    float alpha = 180 - (A + B);

    Eixos(L);

    glPushMatrix();
        desenhaEstrela(L, alpha, A, raioVermelho, 0, 0);
        glRotatef(-90, 1, 0, 0);
        desenhaEstrela(L, alpha, A, raioVermelho, 2, 2);
        glRotatef(-90, 0, 1, 0);
        desenhaEstrela(L, alpha, A, raioVermelho, 4, 4);
    glPopMatrix();

    glutSwapBuffers();
}

void Inicializa (void){

    GLfloat luzAmbiente[4]={0.2, 0.2, 0.2, 1.0};
	GLfloat luzDifusa[4]={0.7, 0.7, 0.7, 1.0};// "cor"
	GLfloat luzEspecular[4]={0.1, 0.1, 0.1, 1};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	GLfloat especularidade[4]={0.4,0.4,0.4,0.4}; // Capacidade de brilho do material
	GLint especMaterial = 1;

 	// Especifica que a cor de fundo da janela será Verde
	glClearColor(0.0f, 0.5f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);// Habilita o modelo de colorização de Gouraud
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade); // Define a refletância do material
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial); // Define a concentração do brilho

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente); // Ativa o uso da luz ambiente

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	glEnable(GL_COLOR_MATERIAL); // Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_LIGHTING); //Habilita o uso de iluminação
	glEnable(GL_LIGHT0); // Habilita a luz de número 0
	glEnable(GL_DEPTH_TEST); // Habilita o depth-buffering

    angle=40; //em angulo 45
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutCreateWindow("Estrela Tripla 8 Pontas 3D - v2");
    glutInitWindowPosition(10,10);

    glutDisplayFunc(desenhaEstrelaTripla);
    glutReshapeFunc(resize); //chamado qnd o tamanho da janela é alterado
    glutKeyboardFunc(eventoDeTeclado);
    glutIdleFunc(idle);

    Inicializa(); // Inicializa parâmetros de rendering
    glutMainLoop();

    return 0;
}
