#include <stdio.h>

#ifndef MAX_SHIPS
#define MAX_SHIPS 0x8
#endif

char label[20][200]             = {
                                    "Bem vindo ao trabalho de batalha naval para Estácio.\n",                               //0
                                    "Utilize os controles numéricos para navegar entre as opções.\n",                       //1
                                    "Para sair do jogo: 0\n",                                                               //2
                                    "Para mover uma peça: 2\n",                                                             //3
                                    "Qual navio gostaria de mover?\n",                                                      //4
                                    "Qual casa gostaria de mover a peça no eixo X? Valores posicionais entre (0 e 9)\n",    //5
                                    "Qual casa gostaria de mover a peça no eixo Y? Valores posicionais entre (0 e 9)\n",    //6
                                    "Gostaria de pintar o tabuleiro?\n",                                                    //7
                                    "Visualização do tabuleiro\n",                                                          //8
                                    "Para visualizar o tabuleiro 1:\n",                                                     //9
                                    "Qual formação gostaria de escolher?\n",                                                //10
                                    "Para cone: 1\n",                                                                       //11
                                    "Para cruz: 2\n",                                                                       //12
                                    "Para Octaedro: 3\n",                                                                   //13
                                    "Para atribuir uma formação: 3\n",                                                      //14
                                    };
char _artShip[5][32] = {
    "________________",
    "|     _/_/_    |",
    "|____/_____|__ |",
    "|l============||",
    "________________",
};
char _artBlank[5][32] = {
    "________________",
    "|    ~~ ~~~   ~|",
    "|~ ~~~~  ~~  ~~|",
    "|   ~~  ~~~ ~~ |",
    "________________",
};

struct ship {
    short int id;             // identificador unico de cada navio
    short int xp;             // posição atual no plano do eixo x
    short int yp;             // posição atual no plano do eixo y
    char (*art)[32];   // Recebe a arte correspondente a peça
};
struct action {
    short int control;
    short int dship;    // Barco desejado
    short int dxp;      // Posição desejada eixo x
    short int dyp;      // Posição desejada eixo y
    short int ftype;     // Tipo de formação
};


// Prototipos
void movePiece(int board[10][10], struct ship *p, short int *newX, short int *newY);
void placeAllPieces(int board[10][10], struct ship *p);
void printBoard(struct ship *p);
void shipFormation(int board[10][10], struct ship *p, short int *type);
short int sabs(short int d);

// Logica principal
int main () {
    int board[10][10]       = {};
    struct action   main;
    struct ship     ships[MAX_SHIPS];

    // Coloca as peças no tabuleiro
    placeAllPieces(board, ships);
    
    printf("%s%s",  label[0], label[1]);
    
    do {
        printf("%s%s%s%s", label[2], label[3], label[9], label[14]);
        scanf("%hd", &main.control);
        if (main.control == 0x1) {
            printBoard(ships);
        }
        else if (main.control == 0x2) {
            printf("%s", label[4]);            
            scanf("%hd", &main.dship);
        
            if (main.dship >= 0x0 && main.dship < 0xa) {
                printf("%s", label[5]);
                scanf("%hd", &main.dxp);
        
                if ((main.dxp >= 0x0) && (main.dxp < 0xa)) {
                    printf("%s", label[6]);
                    scanf("%hd", &main.dyp);
                    
                    if ((main.dyp >= 0x0) && (main.dyp < 0xa)) {
                        movePiece(board, &ships[main.dship], &main.dxp, &main.dyp); // Move a peça
                        printf("%s", label[9]);
                        scanf("%hd", &main.control);
                        if (main.control == 1) {
                            // Imprime o tabuleiro
                            printBoard(ships);
                        }
                    } 
                }
            }
        }
        else if (main.control == 0x3) {
            printf("%s%s%s%s", label[10], label[11], label[12], label[13]);
            scanf("%hd", &main.ftype);
            
            if  (main.ftype > 0x0 && main.ftype <= 0x3) {
                shipFormation(board, ships, &main.ftype);
                printf("%s", label[9]);
                scanf("%hd", &main.control);
                if (main.control == 1) {
                    // Imprime o tabuleiro
                    printBoard(ships);
                }
            }
        }
    } while (main.control);
    return (0x0);
}
// Coloca todas as peças em uma região padrão
void placeAllPieces(int board[10][10], struct ship *p) {
    for (int i = 0x0; i < MAX_SHIPS; i++) {
        p[i].id = i;
        p[i].xp = i;
        p[i].yp = 0x0;
        board[p[i].xp][p[i].yp] = p[i].id + 1;
        p[i].art = _artShip;
    }
}
// Move a peça
void movePiece(int board[10][10], struct ship *p, short int *newX, short int *newY) {
    // Remove da posição anterior
    board[p->xp][p->yp] = 0x0;

    // Faz o update da estrutura
    p->xp = *newX;
    p->yp = *newY;

    board[*newX][*newY] = p->id;
}
// Printa o tabuleiro
void printBoard(struct ship *p) {
    // printa de baixo para cima
    for (int y = 0xa; y >= 0x0; y--) {
        for (int line = 0x0; line < 0x5; line++) { // cada navio tem 5 linhas
            for (int x = 0x0; x < 0xa; x++) {     // cada uma das colunas
                struct ship *ss = NULL;
                // Procura o navio em sua posição (x,y)
                for (int i = 0x0; i < MAX_SHIPS; i++) {
                    if (p[i].xp == x && p[i].yp == y) {
                        ss = &p[i];
                        // apenas um navio por celula da matriz
                        break;
                    }
                }
                if (ss != NULL)
                    printf("%s", ss->art[line]);   // printa arte do navio
                else
                    printf("%s", _artBlank[line]); // printa linha da agua
            }
            printf("\n"); // pula para a proxima linha para completar o loop da arte
        }
    }
}
// Faz a formação desejada
void shipFormation(int board[10][10], struct ship *p, short int *type) {
    // limpa toda a formação do tabuleiro
    for (int x = 0; x < 10; x++)
        for (int y = 0; y < 10; y++)
            board[x][y] = 0;

    short int h1[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    short int h2[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    short int h3[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    switch(*type) {
        case 0x1:
            for (int i = 0; i < MAX_SHIPS; i++) {
                int placed = 0;
                for (int xaxis = 0x0; xaxis < 0xa && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < 0xa; yaxis++) {
                        if (h1[xaxis][yaxis] == 1) {
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h1[xaxis][yaxis] = 0; // marca que foi utilizado liberando os espaços
                            placed = 1;
                            break;
                        }
                    }
                }
            }
            break;
        case 0x2:
            for (int i = 0; i < MAX_SHIPS; i++) {
                int placed = 0;
                for (int xaxis = 0x0; xaxis < 0xa && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < 0xa; yaxis++) {
                        if (h2[xaxis][yaxis] == 1) {
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h2[xaxis][yaxis] = 0; // marca que foi utilizado liberando os espaços
                            placed = 1;
                            break;
                        }
                    }
                }
            }
            break;        
        case 0x3:
            for (int i = 0; i < MAX_SHIPS; i++) {
                int placed = 0;
                for (int xaxis = 0x0; xaxis < 0xa && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < 0xa; yaxis++) {
                        if (h3[xaxis][yaxis] == 1) {
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h3[xaxis][yaxis] = 0; // marca que foi utilizado liberando os espaços
                            placed = 1;
                            break;
                        }
                    }
                }
            }        
            break;
        default:
            break;
    }
}
