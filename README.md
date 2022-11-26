# Trabalho 2 Programação de Software Basico
 

## Descrição

O objetivo deste trabalho é a implementação de um algoritmo para quantização de imagens, isto é, redução da quantidade de cores. A principal aplicação desse algoritmo é a redução no espaço de armazenamento de uma imagem, com alguma perda de qualidade. Isso também pode ser bastante útil, por exemplo, na criação de GIFs animados. 

### Funcionamento

 Ao ser iniciado, o programa irá carregar dois arquivos de imagem (origem das cores, e imagem desejada). Para tanto, utilizaremos uma biblioteca simples (integrada no projeto) denominada SOIL.
 
Cada imagem é representada por uma matriz de pontos (pixels), onde cada cor é definida por 3 componentes: vermelho (R), verde (G) e azul (B). Cada uma dessas componentes usualmente é codificada em um byte, o que produz 3 bytes por pixel (24 bits) - ou seja, 16 milhões de possíveis cores. Em outras palavras, as intensidades (R, G, B) variam de 0 a 255, onde 0 é escuro e 255 é claro. 

Após a leitura da imagem, o programa deverá realizar um processo denominado conversão para 8 bits, o que implica em reduzir a quantidade de cores da imagem para no máximo 256 cores. 

## Leitura da Imagem 

O código fornecido inicialmente define duas structs: uma para representar um pixel e outra para representar a imagem inteira. Após a leitura da imagem, os pixels estarão disponíveis no ponteiro pic.pixels: 
```
// Um pixel RGB (24 bits)
typedef struct {
    unsigned char r, g, b;
} RGB8;

// Uma imagem RGB
typedef struct {
    int width, height;
    RGB8* img;            // vetor de pixels
} Image24;

// A imagem
Image24 pic;
...

// Cada pixel está armazenado em pic.img[i], onde i é o índice do pixel.
// Exemplo: acessando os dois primeiros pixels
RGB8 aux1 = pic.img[0];
RGB8 aux2 = pic.img[1];
...
```

## Redução da quantidade de cores 

 Quantização significa reduzir a quantidade de cores. Uma das formas de economizar memória é utilizar uma representação de 8 bits por pixel (um byte) onde a imagem é composta por uma tabela de cores fixa (palheta) e uma sequência de bytes que referenciam essa tabela. Dessa forma, é possível representar até 256 cores diferentes, mas o gasto de memória é muito menor. Por exemplo, imaginando uma imagem de 1024 x 768 pixels:

  *  Imagem em 24 bits: 1024 x 768 x 3 bytes por pixel = 2.359.296 bytes
  * Imagem em 8 bits + palheta: 1024 x 768 + (256 entradas da tabela de cores * 3 bytes) = 787.200 bytes

Há vários algoritmos para realizar esse processo: os mais usuais são os da popularidade e do corte pela mediana. O primeiro algoritmo descobre as cores que mais ocorrem na imagem original, já o segundo é um algoritmo recursivo, que usa uma técnica um pouco mais sofisticada. De qualquer forma, o objetivo no final é preencher essa tabela de cores com as cores mais representativas da imagem original.

  *  Explicações resumidas de diversos algoritmos: [An Overview of Color Quantization Techniques](http://web.cs.wpi.edu/~matt/courses/cs563/talks/color_quant/CQindex.html)
  *  Demonstração interativa: [Color Reduction and Image Dithering](http://micro.magnet.fsu.edu/primer/java/digitalimaging/processing/colorreduction/index.html)

## Operação do programa 

 As seguintes teclas estão disponíveis na aplicação:
Ao ser executado, o programa exibe a imagem original. Pressionando-se as teclas "1" e "2" alterna-se entre a exibição da imagem original (24 bits) e com tabela de cores (8 bits). A tecla "ESC" finaliza o programa.

  *  1: Exibe a imagem original (24 bits)
  *  2: Exibe a imagem com redução de cores (8 bits)
  *  ESC: finaliza a execução


## Authors
Breno Ferro, Gabriel Spiandorello, Lucas Ehara.
