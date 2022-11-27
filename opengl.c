#include "opengl.h"
#include <string.h>

// Dimensões da imagem de entrada
extern int sizeX, sizeY;

// Imagem de entrada
extern Image24 pic;

// Imagem de 8 bits
extern Image8 pic8;

extern RGB8_count *unique_colors;

// Auxiliar para exibição
RGB8* pixels;

// Texid
GLuint tex;

// Escala de exibição da imagem
float scale;

extern int modo;

extern void process();

#define LARGURA_JAN 1024
#define ALTURA_JAN 768

// ************************************************************
//
// A PARTIR DESTE PONTO, O PROGRAMA NÃO DEVE SER ALTERADO
//
// A NÃO SER QUE VOCÊ SAIBA ***EXATAMENTE*** O QUE ESTÁ FAZENDO
//
// ************************************************************
void init(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);

    // Define o tamanho da janela gráfica do programa
    glutInitWindowSize(LARGURA_JAN, ALTURA_JAN);
    glutCreateWindow("Quantizador 24-8");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    scale = 1.0f;    // escala inicial de exibição
    pixels = NULL;
}

void reshape(int w, int h)
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    gluOrtho2D(0, w, 0, h);

    // Set the clipping volume
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Reconstrói a textura da imagem de saída quando algum parâmetro
// for alterado
void buildTex()
{
    if(tex == -1) {
        glGenTextures(1, &tex);
    }

    int tam = pic.width*pic.height;

    if(pixels == NULL)
        // Aloca mem. para imagem auxiliar
        pixels = malloc(sizeof(RGB8) * tam);

    glBindTexture(GL_TEXTURE_2D, tex);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    memset(pixels, 0, sizeof(RGB8)*tam);

    if(modo == IMG24) {
        // Modo de 24 bits: apenas copia a imagem
        memcpy(pixels, pic.pixels, sizeof(RGB8)*tam);
    }
    else if(modo == IMG8) {

        // Passa por todos os pixels
        for(int pos=0; pos<tam; pos++) {
            // Obtem a cor da palheta
            RGB8 color = pic8.pal[pic8.pixels[pos]];
            // E atribui na imagem auxiliar de 24 bits
            pixels[pos].r = color.r;
            pixels[pos].g = color.g;
            pixels[pos].b = color.b;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

void display()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Fundo de tela preto
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    int glut_width  = glutGet(GLUT_WINDOW_WIDTH);
    int glut_height = glutGet(GLUT_WINDOW_HEIGHT);

    float offsetx, offsety;

    // Calcula offsets para centralizar imagem
    offsetx = glut_width/2 - sizeX*scale/2;
    offsety = glut_height/2 - sizeY*scale/2;

    glColor3ub(255, 255, 255);  // cinza claro

    glPushMatrix();
    // Posiciona e aplica escala na imagem
    glTranslatef(offsetx, offsety, 0);
    glScalef(scale,scale,1.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);

    glTexCoord2f(0,1);
    glVertex2f(0,0);

    glTexCoord2f(1,1);
    glVertex2f(sizeX,0);

    glTexCoord2f(1,0);
    glVertex2f(sizeX, sizeY);

    glTexCoord2f(0,0);
    glVertex2f(0,sizeY);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Exibe a tela
    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
  switch( key ) {
    case 27:
      free(pic.pixels);
      free(pic8.pixels);
      free(pixels);
      free(unique_colors);
      exit(1);
      break;
    case '1':
        printf("24 bits\n");
        modo = IMG24;
        buildTex();
        glutPostRedisplay();
        break;
    case '2':
        printf("8 bits - palheta\n");
        modo = IMG8;
        buildTex();
        glutPostRedisplay();
        break;
  }
}

void mouse(int button, int state, int x, int y)
{
    // printf("%d %d %d\n",button,x,y);
    if(button == 3)
        scale -= 0.02;
    else if(button == 4)
        scale += 0.02;
    glutPostRedisplay();
}


