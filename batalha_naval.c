/*
    Desafio de batalha naval da Estácio.

    Atenção !!!
    
      Foi compilado e testado em uma maquina virtual Linux Ubuntu Server, e foi utilizado o terminal em fullscreen a tela fica melhor.
      E também não vai quebrar a cadeia de caracteres na representação grafica do programa.

      Um grafico 2D baseado em text art ASCII.

    Conceitos abordados, matriz, estrutura, vetor de estrutura, "variavel" pre precessor, conceitos de ifndef def, ponteiros
    números hexadecimal no programa diretamente, dicionários, menu interativo, algumas validações elegantes.

    Resumindo um programa simples e uma solução elegante.

    Utilizei alguns dos conceitos que já fiz no xadrez e apliquei nesse também similarmente 
    devido a matriz então o printar do board é a mesma coisa.
    funçao de mover a peça é muito similar também quase a mesma coisa.
    Tem algumas diferenças no layout e o conceito de dicionário e similar fiz bem modular então consegui aproveitar a logica de muita coisa
    dos desafios antigos.

    Espero que os avaliadores gostem do programa!

*/

#include <stdio.h>

// Algumas constantes pre processamento
#ifndef MAX_SHIPS
#define MAX_SHIPS 0x8
#endif
#ifndef MAX_GRIDCELL
#define MAX_GRIDCELL 0xa
#endif
#ifndef MAX_LINEART
#define MAX_LINEART 0x5
#endif

// Dicionário das saidas de texto
char label[20][200]             = {
                                    "Bem vindo ao trabalho de batalha naval para Estácio.\n",                               //0
                                    "Utilize os controles numéricos para navegar entre as opções.\n",                       //1
                                    "Para sair do jogo: 0\n",                                                               //2
                                    "Para mover uma peça: 2\n",                                                             //3
                                    "Qual navio gostaria de mover? Valores entre (0 e 7)\n",                                                      //4
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

// Padrão das artes em text art
char _artShip[MAX_LINEART][32] = {
    "________________",
    "|     _/_/_    |",
    "|____/_____|__ |",
    "|l============||",
    "________________",
};
char _artBlank[MAX_LINEART][32] = {
    "________________",
    "|    ~~ ~~~   ~|",
    "|~ ~~~~  ~~  ~~|",
    "|   ~~  ~~~ ~~ |",
    "________________",
};

// Struct para o navio e as ações da rotina principal
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
void movePiece(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p, short int *newX, short int *newY); // move uma peça
void placeAllPieces(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p); // coloca todas as peças em uma posição padrão
void printBoard(struct ship *p);  // faz o print da grid
void shipFormation(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p, short int *type); // faz a formação dos navios conforme seu tipo

// Logica principal
int main () {
    int board[MAX_GRIDCELL][MAX_GRIDCELL]       = {};
    struct action   main;
    struct ship     ships[MAX_SHIPS];

    // Coloca as peças no tabuleiro
    placeAllPieces(board, ships);
    
    printf("%s%s",  label[0], label[1]);
    
    do {
        printf("%s%s%s%s", label[2], label[3], label[9], label[14]);
        scanf("%hd", &main.control);
        
        // Veja o controle se deseja printar o tabuleiro
        if (main.control == 0x1) {
            printBoard(ships);
        }
        // Inicia o processo de perguntar qual peça movimentar
        else if (main.control == 0x2) {
            printf("%s", label[4]);            
            scanf("%hd", &main.dship);
        
            // qual peça deseja movimentar
            if (main.dship >= 0x0 && main.dship < MAX_GRIDCELL) {
                printf("%s", label[5]);
                scanf("%hd", &main.dxp);
                
                //  pega as coordenadas da matriz eixo X
                if ((main.dxp >= 0x0) && (main.dxp < MAX_GRIDCELL)) {
                    printf("%s", label[6]);
                    scanf("%hd", &main.dyp);
                    
                    //  pega as coordenadas da matriz eixo Y
                    if ((main.dyp >= 0x0) && (main.dyp < MAX_GRIDCELL)) {
                        movePiece(board, &ships[main.dship], &main.dxp, &main.dyp); // Move a peça
                        printf("%s", label[9]);
                        scanf("%hd", &main.control); // Busca proximo controle principal
                        if (main.control == 0x1) {
                            // Imprime o tabuleiro
                            printBoard(ships);
                        }
                    } 
                }
            }
        }
        // Processo de formação dos navios
        else if (main.control == 0x3) {
            printf("%s%s%s%s", label[10], label[11], label[12], label[13]);
            scanf("%hd", &main.ftype);
            
            // valida se está dentro dos parametros esperados            
            if  (main.ftype > 0x0 && main.ftype <= 0x3) {
                // faz a formação dos navios
                shipFormation(board, ships, &main.ftype);
                printf("%s", label[9]);
                scanf("%hd", &main.control); // Busca proximo controle principal
                if (main.control == 0x1) {
                    // Imprime o tabuleiro
                    printBoard(ships);
                }
            }
        }
    } while (main.control);
    return (0x0);
}
// Coloca todas as peças em uma região padrão
void placeAllPieces(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p) {
    // busca o vetor de navios e coloca eles em uma posição inicial    
    for (int i = 0x0; i < MAX_SHIPS; i++) {
        p[i].id = i;
        p[i].xp = i;
        p[i].yp = 0x0;
        board[p[i].xp][p[i].yp] = p[i].id + 1;
        p[i].art = _artShip;
    }
}
// Move a peça
void movePiece(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p, short int *newX, short int *newY) {
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
    for (int y = MAX_GRIDCELL; y >= 0x0; y--) {
        for (int line = 0x0; line < MAX_LINEART; line++) { // cada navio tem 5 linhas
            for (int x = 0x0; x < MAX_GRIDCELL; x++) {     // cada uma das colunas
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
void shipFormation(int board[MAX_GRIDCELL][MAX_GRIDCELL], struct ship *p, short int *type) {
    // limpa toda a formação do tabuleiro
    for (int x = 0x0; x < MAX_GRIDCELL; x++)
        for (int y = 0x0; y < MAX_GRIDCELL; y++)
            board[x][y] = 0x0;

    /*
        Define uma matriz de habilidades todas de cabeça para baixo.
        Pois o print da tela é feito de baixo para cima no loop, logo eu inverti a ordem das coisas para 
        sempre ele mostrar a posição do eixo (x,y) como aprendemos no ginasio com o plano.
        
        5|
        4|
        3|
        2|
        1|__|__||__||__||__|    
          1  2   3   4   5
        
        ele sempre printa:
        
        1|
        2|
        3|
        4|
        5|__|__||__||__||__|    
          1  2   3   4   5
        
        então invertemos para sempre ele colocar o 0 em baixo pois não existe - x tela ou -y de forma real
        sempre começa positiva no monitor, logo os eixos do centro são considerados em calculo, como -x ou -y da posição real
        da matriz

    */
    // Cone
    short int h1[MAX_GRIDCELL][MAX_GRIDCELL] = {
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
    // Cruz
    short int h2[MAX_GRIDCELL][MAX_GRIDCELL] = {
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
    // Octaedro
    short int h3[MAX_GRIDCELL][MAX_GRIDCELL] = {
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
    // Valida cada tipo de habilidade e manda buscar de uma matriz especifica
    switch(*type) {
        case 0x1:
            for (int i = 0x0; i < MAX_SHIPS; i++) {
                // Variavel de controle para saber se ele já moveu esse navio
                int placed = 0x0;
                // Varre o loop enquanto não moveu na posição correta
                for (int xaxis = 0x0; xaxis < MAX_GRIDCELL && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < MAX_GRIDCELL; yaxis++) {
                        // Verifica se a matriz tem 1 e se tiver um ele precisa colocar um navio nessa posição
                        if (h1[xaxis][yaxis] == 0x1) {
                            // Inverti os eixos para corresponder o que já expliquei acima;
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h1[xaxis][yaxis] = 0x0; // marca que foi utilizado liberando os espaços
                            placed = 0x1;
                            break;
                        }
                    }
                }
            }
            break;
        // Em diante a logica é a mesma então não tem necessidade de exemplificar a unica diferença seria a matriz de referência
        case 0x2:
            for (int i = 0x0; i < MAX_SHIPS; i++) {
                int placed = 0x0;
                for (int xaxis = 0x0; xaxis < MAX_GRIDCELL && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < MAX_GRIDCELL; yaxis++) {
                        if (h2[xaxis][yaxis] == 0x1) {
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h2[xaxis][yaxis] = 0x0; // marca que foi utilizado liberando os espaços
                            placed = 0x1;
                            break;
                        }
                    }
                }
            }
            break;        
        case 0x3:
            for (int i = 0x0; i < MAX_SHIPS; i++) {
                int placed = 0x0;
                for (int xaxis = 0x0; xaxis < MAX_GRIDCELL && !placed; xaxis++) {
                    for (int yaxis = 0x0; yaxis < MAX_GRIDCELL; yaxis++) {
                        if (h3[xaxis][yaxis] == 0x1) {
                            short int nx = yaxis;
                            short int ny = xaxis;
                            movePiece(board, &p[i], &nx, &ny);
                            h3[xaxis][yaxis] = 0x0; // marca que foi utilizado liberando os espaços
                            placed = 0x1;
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
