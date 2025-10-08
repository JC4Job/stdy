/*
    Esse programa foi feito para fazer o desafio do xadrex do curso de engenharia de software

    Premissas:

        Você deverá criar um único programa em C que simule o movimento de três peças: Torre, Bispo e Rainha. Para cada peça, utilize uma estrutura de repetição diferente (for, while ou do-while) para simular seu movimento. O programa deverá imprimir no console a direção do movimento a cada casa percorrida pela peça.
 
        Torre: Move-se em linha reta horizontalmente ou verticalmente. Seu programa deverá simular o movimento da Torre cinco casas para a direita.
        Bispo: Move-se na diagonal. Seu programa deverá simular o movimento do Bispo cinco casas na diagonal para cima e à direita. Para representar a diagonal, você imprimirá a combinação de duas direções a cada casa (ex: "Cima, Direita").
        Rainha: Move-se em todas as direções. Seu programa deverá simular o movimento da Rainha oito casas para a esquerda.
    
    Considerções do aluno e autor.

    Apesar do modelo especificado ser mais simples eu incrementei a logica para ficar mais bonita e mais robusta.
    Não sou um praticante regular de xadrez, mas achei um desafio interessante.

    Aconselho a executar em um terminal em full screen para não quebrar a cadeia de caracteres.
    Testei utilizando um console da maquina virtual com SSH do programa Putty.
    Se fizer nas mesmas condições o tabuleiro vai ficar bonito e elegante.

    Atenção:
        Sei que a proposta seria utilizar os tipos especificos de loops, mas coloquei no codigo os conceitos,
        mesmo que não utilizados diretamente
        
    Espero que gostem! :D
*/


#include <stdio.h>

char label[20][200]              = {
                                    "Bem vindo ao trabalho de chess para estácio.\n",
                                    "Utilize os controles numéricos para navegar entre as opções.\n",
                                    "Para sair do jogo: 0\n",
                                    "Para mover uma peça: 2\n",
                                    "Qual peça gostaria de mover?\n",
                                    "Para mover a rainha: 1\n",
                                    "Para mover a bispo: 2\n",
                                    "Para mover a torre: 3\n",
                                    "Qual casa gostaria de mover a peça no eixo X? Valores posicionais entre (0 e 7)\n",
                                    "Qual casa gostaria de mover a peça no eixo Y? Valores posicionais entre (0 e 7)\n",
                                    "Gostaria de pintar o tabuleiro?\n",
                                    "Visualização do tabuleiro\n",
                                    "Para visualizar o tabuleiro 1:\n",
                                    "Não há área útil para mover a peça de acordo com seu tipo\n"
};
char _artQueen[20][20]           = {
                                    "____________",
                                    "|     0     |",
                                    "| ||||||||| |",
                                    "|  #######  |",
                                    "|   #####   |",
                                    "|  =======  |",
                                    "|   #####   |",
                                    "| ///////// |",
                                    "| ||||||||| |",
                                    "____________",
                                };

char _artBishop[20][20]          = {
                                    "____________",
                                    "|     0     |",
                                    "|   00000   |",
                                    "|  0000000  |",
                                    "|   00000   |",
                                    "|  =======  |",
                                    "|   #####   |",
                                    "| ///////// |",
                                    "| ||||||||| |",
                                    "____________",
                                };                                 

char _artTower[20][20]           = {
                                    "____________",
                                    "| NNNNNNNNN |",
                                    "| ||||||||| |",
                                    "| ||||||||| |",
                                    "|  #######  |",
                                    "|  #######  |",
                                    "|  #######  |",
                                    "| ///////// |",
                                    "| ||||||||| |",
                                    "____________",
                                };
char _artBlank[20][20]           = {
                                    "____________",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "|          |",
                                    "____________",
                                };

struct piece {
    short int type;           // tipo de peça
    short int xp;             // posição atual no plano do eixo x
    short int yp;             // posição atual no plano do eixo y
    char (*art)[20];   // Recebe a arte correspondente a peça
};
struct action {
    short int control;
    short int dpiece;   // Peça desejada por tipo
    short int dxp;      // Posição desejada eixo x
    short int dyp;      // Posição desejada eixo y
};


// Prototipos
void movePiece(int board[8][8], struct piece *p, short int *newX, short int *newY);
void placeAllPieces(int board[8][8], struct piece *queen, struct piece *bishop, struct piece *tower);
void printBoard(int board[8][8], struct piece *queen, struct piece *bishop, struct piece *tower);
short int isValidMove(struct piece *p, short int newX, short int newY);
short int sabs(short int d);
void exemploFor();
void exemploWhile();
void exemploDoWhile();

// Logica principal
int main () {
    int board[8][8]         = {};
    struct action   main;
    struct piece    queen   = {1, 0, 0, _artQueen};
    struct piece    bishop  = {2, 0, 0, _artBishop};
    struct piece    tower   = {3, 0, 0, _artTower};

    // Coloca as peças no tabuleiro
    placeAllPieces(board, &queen, &bishop, &tower);
    
    printf("%s%s",  label[0], label[1]);
    
    do {
        printf("%s%s%s", label[2], label[3], label[12]);
        scanf("%hd", &main.control);
        if (main.control == 1) {
            printBoard(board, &queen, &bishop, &tower);
        }
        else if (main.control == 2) {
            
            printf("%s%s%s%s", label[4], label[5], label[6], label[7]);
            
            scanf("%hd", &main.dpiece);
        
            if (main.dpiece > 0x0 && main.dpiece < 0x4) {
                printf("%s", label[8]);
                scanf("%hd", &main.dxp);
        
                if ((main.dxp >= 0x0) && (main.dxp < 0x8)) {
                    printf("%s", label[9]);
                    scanf("%hd", &main.dyp);
                    if ((main.dyp >= 0x0) && (main.dyp < 0x8)) {
                        struct piece *selectedPiece = NULL;

                        if (main.dpiece == 1) selectedPiece = &queen;
                        else if (main.dpiece == 2) selectedPiece = &bishop;
                        else if (main.dpiece == 3) selectedPiece = &tower;

                        if (isValidMove(selectedPiece, main.dxp, main.dyp)) {      // Valida se o movimento é valido                      
                            movePiece(board, selectedPiece, &main.dxp, &main.dyp); // Move a peça
                            printf("%s", label[10]);
                            scanf("%hd", &main.control);
                            if (main.control == 1) {
                                // Imprime o tabuleiro
                                printBoard(board, &queen, &bishop, &tower);
                            }
                        } 
                        else {
                            printf("%s", label[13]);  // movimento inválido
                        }
                    }
                    else {

                    }
                }
            }
        }
        

    } while (main.control);
    return (0);
}
// Coloca todas as peças em uma região padrão
void placeAllPieces(int board[8][8], struct piece *queen, struct piece *bishop, struct piece *tower) {
    // Rainha na posição (0, 0)
    queen->xp = 0;
    queen->yp = 0;
    board[queen->xp][queen->yp] = queen->type;

    // Bispo na posição (1, 1)
    bishop->xp = 1;
    bishop->yp = 0;
    board[bishop->xp][bishop->yp] = bishop->type;

    // Torre na posição (2, 2)
    tower->xp = 2;
    tower->yp = 0;
    board[tower->xp][tower->yp] = tower->type;
}
// Move a peça
void movePiece(int board[8][8], struct piece *p, short int *newX, short int *newY) {
    // Remove da posição anterior
    board[p->xp][p->yp] = 0;

    // Faz o update da estrutura
    p->xp = *newX;
    p->yp = *newY;

    board[*newX][*newY] = p->type;
}
// Printa o tabuleiro
void printBoard(int board[8][8], struct piece *queen, struct piece *bishop, struct piece *tower) {
    /*
        Talvez essa seja a logica mais complexa desse programa deixa eu explicar
        Imagine um plano cartesiano em que corresponda à:
        y
        |  ______________________________________________________
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|                                        
        | |     ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|        
        | |  X  ||     ||     ||     ||     ||     ||     ||     |
        | |_____||_____||_____||_____||_____||_____||_____||_____|        
        |_______________________________________________________________
        x(0,7)

        A logica de print da peça seria invertida uma vez de que ele printa 
        da primeira linha para a ultima, portanto o display da grid deverá ser feita 
        da mesma forma

        portanto a cada linha da do plano do eixo Y ele pula uma linha e printa cada 
        uma das colunas com a peça ou o tabuleiro em branco varrendo assim o array 
        principal bidimensional
    */
    // Vamos imprimir o tabuleiro linha por linha (de arte), de cima para baixo
    for (int y = 0x7; y >= 0x0; y--) {
        // Cada peça/arte tem 10 linhas
        for (int line = 0x0; line < 0xa; line++) {
            for (int x = 0x0; x < 0x8; x++) {
                struct piece *p = NULL;

                // Verifica se tem peça na posição atual
                if (queen->xp == x && queen->yp == y) p = queen;
                else if (bishop->xp == x && bishop->yp == y) p = bishop;
                else if (tower->xp == x && tower->yp == y) p = tower;

                if (p != NULL) {
                    printf("%s", p->art[line]);
                } else {
                    printf("%s", _artBlank[line]);
                }
            }
            printf("\n");  // Pula para a próxima linha da arte
        }
    }
}
// Valida o movimento da peça
short int isValidMove(struct piece *p, short int newX, short int newY) {
    short int dx = newX - p->xp;
    short int dy = newY - p->yp;

    // Movimento nulo
    if (dx == 0 && dy == 0) return 0;

    switch (p->type) {
        case 1: // Rainha
            return (dx == 0 || dy == 0 || sabs(dx) == sabs(dy));
        case 2: // Bispo
            return sabs(dx) == sabs(dy);
        case 3: // Torre
            return (dx == 0 || dy == 0);
        default:
            return 0;
    }
}
// Implementação do math abs para short int
short int sabs(short int d) {
    return d < 0 ? -d : d;
}

void _exemploFor() {
    for (int i = 0; i < 5; i++) {
        printf("Exemplo FOR: passo %d\n", i);
    }
}

void exemploWhile() {
    int i = 0;
    while (i < 5) {
        printf("Exemplo WHILE: passo %d\n", i);
        i++;
    }
}

void exemploDoWhile() {
    int i = 0;
    do {
        printf("Exemplo DO-WHILE: passo %d\n", i);
        i++;
    } while (i < 5);
}
