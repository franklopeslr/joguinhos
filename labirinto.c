/**
    \author Franklin Lopes Jr
    \date Julho de 2018
    \page https://github.com/franklopeslr
    \page https://github.com/franklopeslr/joguinhos
    \brief
    Joguinho de labirinto em ANSI C
    Controles:
    d - esquerda
    a - direita
    w - cima
    s - baixo

    compilar:
    gcc -o labirinto labirinto.c
    ou..
    gcc -o labirinto main.c
*/
#include <stdio.h>
#include <stdlib.h>

struct jogadorT
{
    unsigned int x,y;
} jog;


/** para o loop */
#define UINT register unsigned int

/** caracteres das posicoes */
#define LIVRE 0
#define PAREDE 1
#define FINAL 2
#define JOGADOR 3

/** mapa que é modificado*/
#define TAM_MAPA 20
short unsigned int mapa[TAM_MAPA][TAM_MAPA] = {
{3,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
{1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1},
{1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1},
{1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0},
{1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
{1,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,0,2},
{1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1},
{1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1},
{1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

/** mapa que não é modificado
    tudo que for modificado nesse deve ser
    modificado no outro */
short unsigned int original[TAM_MAPA][TAM_MAPA] = {
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
{1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1},
{1,1,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,1,0,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1},
{1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1},
{1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0},
{1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
{1,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,0,2},
{1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1},
{1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1},
{1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

/** lê o teclado e reposiciona jogador */
void trata_teclado(void);
/** renderiza o mapa */
void desenha_mapa(void);

int main()
{
    char mov;
    jog.x = 0;
    jog.y = 0;

    while(1)
    {

        if( original[jog.x][jog.y] == FINAL )
            break;

        system("clear");
        desenha_mapa();
        trata_teclado();
    }

printf("\
------------------------------------------------\n\
                      FIM!                      \n\
------------------------------------------------\n"
);

    return 0;
}

#define RENDERIZA(caractere) printf("%c ", caractere)
void desenha_mapa(void)
{
    UINT i,j;
    for(i = 0; i < TAM_MAPA; i++)
    {
        for(j = 0; j < TAM_MAPA; j++)
        {
            switch(mapa[i][j])
            {
                case PAREDE:
                    RENDERIZA('x');
                    break;
                case FINAL:
                    RENDERIZA('>');
                    break;

                case JOGADOR:
                    RENDERIZA('o');
                    break;

                case LIVRE:
                    RENDERIZA(' ');

            }

        }

        printf("\n");
    }
}

void trata_teclado(void)
{
    printf(":");
    char mov = getchar();

    /** baixo */
    if( mov == 's' && mapa[jog.x+1][jog.y] != PAREDE )
    {
        mapa[++jog.x][jog.y] = 3;
        mapa[jog.x-1][jog.y] = original[jog.x-1][jog.y];
    }

        /** cima */
    if( mov == 'w' && mapa[jog.x-1][jog.y] != PAREDE )
    {
        mapa[--jog.x][jog.y] = 3;
        mapa[jog.x+1][jog.y] = original[jog.x+1][jog.y];
    }

    /** direita */
    if( mov == 'd' && mapa[jog.x][jog.y+1] != PAREDE )
    {
        mapa[jog.x][++jog.y] = 3;
        mapa[jog.x][jog.y-1] = original[jog.x][jog.y-1];
    }

    /** esquerda */
    if( mov == 'a' && mapa[jog.x][jog.y-1] != PAREDE )
    {
       mapa[jog.x][--jog.y] = 3;
       mapa[jog.x][jog.y+1] = original[jog.x][jog.y+1];
    }


    /** log */
    printf("{%i %i}\n", jog.x, jog.y);
}
