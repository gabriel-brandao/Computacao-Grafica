
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>


/* Fun��es  tratamento de eventos  */

static void tamanho(int width, int height)
{
    printf("\nevento de redimensionamento...\n");
}

static void janela(void)
{

    printf("\nevento de desenho...\n");
}


static void tecla(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;


        default:
                    printf("\nevento de teclado\n");
            break;
    }
}

static void seta(int tecla, int x, int y)
{

  switch ( tecla ) {
    case GLUT_KEY_UP:
      printf("\nSeta para cima...\n");
      break;
    case GLUT_KEY_DOWN:
      //glutReshapeWindow ( 640, 480 );
      printf("\n Seta para baixo...\n");
      break;
  }
}

static void mouse(int botao, int estado, int x, int y)
{

    switch ( botao ) {
        case GLUT_LEFT_BUTTON:
          printf("\n Bot�o esquerdo...\n");
          break;
        case GLUT_MIDDLE_BUTTON:
          printf("\n Bot�o do meio...\n");
          break;
      }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE );

    glutCreateWindow("Programa 01 - mapeamento de eventos");

    //registra fun��o callback para tratar evento de redimensionamento de janela
    glutReshapeFunc(tamanho);
    //registra fun��o callback para tratar evento de desenho
    glutDisplayFunc(janela);
    //registra fun��o callback para tratar evento de teclado
    glutKeyboardFunc(tecla);
    //registra fun��o callback para tratar evento de teclado-setas
    glutSpecialFunc(seta);
    //registra fun��o callback para tratar evento de mouse
    glutMouseFunc(mouse);
    //define a cor de limpeza da janela como sendo a branca
    glClearColor(1,1,1,1);
    //Inicia tratamento de eventos
    glutMainLoop();

    return 0;
}
