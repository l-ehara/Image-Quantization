#include <math.h>
#include <string.h>		// para usar strings
#include "include/SOIL.h"

// Rotinas para acesso da OpenGL
#include "opengl.h"

// Variáveis globais a serem utilizadas:

// Dimensões da imagem de entrada
int sizeX, sizeY;

// Imagem de entrada
Image24 pic;

// Imagem de 8 bits
Image8 pic8;

// color array with count variable
RGB8_count *unique_colors;    
int unique_count;

// Modo de exibição atual
int modo;

// Protótipos
void load(char* name, Image24* pic);
void process();

// Carrega uma imagem para a struct Img
void load(char* name, Image24* pic)
{
    int chan;
    pic->pixels = (RGB8*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->pixels)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int in_unique_colors(RGB8 color)
{
    for(int i = 0; i < unique_count; i++)
    {
        if (pic.pixels[i].r == color.r &&
            pic.pixels[i].g == color.g &&
            pic.pixels[i].b == color.b)
        {
            return 1;
        }
    }
    return 0;
}

void sort_colors(RGB8_count *array)
{
    for (int i = 0; i < unique_count-1; i++)
    {
        for (int j = 0; j < unique_count; j++)
        {
            if (array[i].count < array[j].count)
            {
                RGB8_count temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }   
    }
}

void setPalette()
{
    for (int i = 0; i < 256; i++)
    {
        pic8.pal[i].r = unique_colors[i].r;
        pic8.pal[i].g = unique_colors[i].g;
        pic8.pal[i].b = unique_colors[i].b;
    }
}

// Função principal de processamento: ela deve chamar outras funções
// quando for necessário
void process()
{
    // EXEMPLO: preenche a imagem 8 bits com pixels de cores diversas
    // 24-bit
    unsigned int pos = 0;
    unsigned char r = 0;
    for(int y = 0; y < sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (in_unique_colors(pic.pixels[pos]) == 0)
            {
                unique_colors[unique_count].r = pic.pixels[pos].r;
                unique_colors[unique_count].g = pic.pixels[pos].g;
                unique_colors[unique_count].b = pic.pixels[pos].b;
                unique_colors[unique_count].count = 0;
                unique_colors[unique_count].count++;
                unique_count++;
            }
            pos++;
        }
    }
    pos = 0;
    r = 0;
    double div = 256;
    int last = 0;
    for(int y = 0; y < sizeY; y++) {
        if (y >= sizeY / div + last)
        {   
            last = sizeY / div;
            div--;
            r++;
        }

        for(int x=0; x<sizeX; x++) {
            pic8.pixels[pos] = r;
            pos++;
        }
    }
    
    sort_colors(unique_colors);
    printf("Sorted\n");
    setPalette();

    // TODO ----------------------------------------

    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
}

int main(int argc, char** argv)
{
    if(argc == 1) {
        printf("colors [image file]\n");
        exit(1);
    }

    // Inicialização da janela gráfica
    init(argc,argv);

    load(argv[1], &pic);
    sizeX = pic.width;
    sizeY = pic.height;

    // Aloca memória para imagem de 8 bits
    pic8.width  = sizeX;
    pic8.height = sizeY;
    pic8.pixels = (unsigned char*) malloc(sizeX * sizeY);

    modo = IMG24;

    unique_count = 0;
    unique_colors = malloc(sizeX * sizeY * sizeof(RGB8_count));

    // Aplica processamento inicial
    process();

    printf("unique_count: %d\n", unique_count);

    // Não retorna... a partir daqui, interação via teclado e mouse apenas, na janela gráfica
    glutMainLoop();
    return 0;
}
