/*
    Esse programa é referente ao exercicio proposto pela estácio
    no curso de engenharia de software.
    
    Considerações sobre o primeiro trabalho.

    Infelizmente não consegui realizar o primeiro exercicio a tempo 
    e colocar disponibilizado no git, pois estava programando 2 soluções
    no trabalho e como unico programador da area eu perdi o prazo de 
    submeter a resposta.

    Me perdoe por essa falha e conto com a compreensão de todos.

    Sobre o programa:
        -   Vou colocar todos os comentários em português para facilitar a
            vida do avaliador, contudo usualmente eu escreveria em inglês.

    Considerações sobre o desafio:

    1 - Implementar a lógica de comparação entre duas cartas, considerando 
        diferentes atributos numéricos.
    
    2 - Permitir ao jogador escolher entre diferentes atributos para a 
        comparação através de menus interativos.
    
    3 - Evoluir em complexidade ao longo dos três desafios:
    
    4 - Comparação de cartas com base em um único atributo utilizando if e if-else.
    
    5 - Comparação de cartas com múltiplos atributos usando operadores lógicos 
        e estruturas de decisão aninhadas e encadeadas (if-else if), além da 
        implementação de menus com switch.
    
    6 - Comparação de cartas com base em dois atributos, utilizar o operador
        ternário e integrando todas as estruturas de decisão aprendidas para 
        criar uma lógica mais complexa.
*/
// Importo o header file do standard input e output da linguagem.
#include <stdio.h>

// Macro para fazer o try cast
#ifndef trycast
#define trycast(value, type) ((type)(value))
#endif

// Macro para colocar o número maximo de cartas
#ifndef MAX_CARDS
#define MAX_CARDS 2
#endif

// Definição de uma estrutura para guardar o controle de fluxo.
struct cflow {
    int main;
    int menu;
    int i;
};
// Definição da estrutura que vai guardar as cartas super trunfo.
struct tcard {
    char state;     // Estado
    char code[4];   // Codigo da carta
    char city[500]; // cidade
    int population; // população
    float area;     // area
    float pib;      // PIB
    int points;     // Pontos turisticos
    float pibcapt;   // Pib per capta
    float densp;     // Desinsidade populacional
};

// Prototipo da função para evitar warnings de compiladores antigos.
int _strlen(char *s);
void push(struct tcard arr[], int *size, struct tcard value, int capacity);
void compare(struct tcard value1, struct tcard value2, int *option);
void _pCard(struct tcard value);

// Um dicionário dos textos a serem exibidos.
char label[30][200] = {
    "Cadastramento carta Super Trunfo!",
    "Para sair do programa pressione 0 ou CTRL + C de seu teclado",
    "Para inserir uma nova carta pressione 1",
    "Informe a sigla da carta, uma letra maiuscula entre A e H:",
    "Anotado!",
    "Não foi fornecido a instrução correta, tente novamente",
    "Informe um número de 1 a 4 para o codigo da carta(digitos):",
    "Informe uma cidade que pode conter até 500 caracteres de texto:",
    "Informe a quantidade de habitantes dessa cidade (digitos):",
    "Informe a area total dessa cidade em km (decimal):",
    "Informe o pib dessa cidade (decimal):",
    "Informe a quantidade de pontos turisticos dessa cidade(digitos):",
    "Cartas Armazenadas ",
    "Digite opções comparativas das cartas:",
    "Opção 1 para população",
    "Opção 2 para área",
    "Opção 3 para pib",
    "Opção 4 para Densidade populacional",
    "Opção 5 para Pib per capta",
    "Qualquer outra opção não informada anteriormente o programa será encerrado.",
    "Card Vencedor:",
    "Obrigado por jogar! :)",
    "Empate!"
};


// Função principal.
int main() {
    struct cflow control;
    struct tcard card;
    struct tcard cards[MAX_CARDS];
    int count = 0;  
    
    char textArt[10][120] = {
        "                 ---                 ",
        "               -------               ",
        "            --------------           ",
        "          ---   SUPER   ---          ",
        "            --------------           ",
        "               -------               ",
        "                 ---                 ",
        "_____________________________________",
        "|              TRUNFO               |",
        "|___________________________________|"
    };
    for (control.i = 0; control.i < 10; control.i++) {
        printf("%s\n", textArt[control.i]);
    }
    // Algumas formatações de saida como new line ou tab foram adicionadas
    // Em algumas partes o uso do alerta também foi utilizado
    printf("%s\n%s\n%s\n", label[0], label[1], label[2]);
    
    scanf(" %d", &control.main);
    do {
        if (control.main == 1) {
            printf("%s\n", label[3]);
            scanf(" %c", &card.state);        
            if ((trycast(card.state, int) >= 65) && (trycast(card.state, int) <= 72)) {
                printf("\a%s\n", label[6]);

                int code = 0;
                scanf("%d", &code);

                if ((code >= 1) && (code <= 4)) {
                    card.code[0] = card.state;
                    card.code[1] = '0';
                    card.code[2] = '0' + code;
                    card.code[3] = '\0';

                    printf("\a%s\n", label[7]);
                    scanf(" %499[^\n]", card.city);

                    if (_strlen(card.city) > 0) {
                        printf("\a%s\n", label[8]);
                        scanf("%d", &card.population);

                        if (card.population >= 0) {
                            printf("\a%s\n", label[9]);
                            scanf("%f", &card.area);

                            if (card.area >= 0) {
                                printf("\a%s\n", label[10]);
                                scanf("%f", &card.pib);

                                if (card.pib >= 0) {
                                    printf("\a%s\n", label[11]);
                                    scanf("%d", &card.points);

                                    if (card.points >= 0) {
                                        card.densp = (card.area > 0.0f) ? ((float)card.population / card.area) : 0.0f;
                                        card.pibcapt = (card.population > 0) ? (card.pib / card.population) : 0.0f;
                                        
                                        if (count < MAX_CARDS) {
                                            push(cards, &count, card, MAX_CARDS);
                                            printf("\a%s\n", label[4]);
                                        }
                                        
                                        if (count == MAX_CARDS)
                                            control.main = 0;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    printf("\a%s\n", label[5]);
                }
            } else {
                printf("\a%s\n", label[5]);
            }
        } 
        else {
            control.main = 0;
        }
    } while (control.main);

    if (count > 0) {
        printf("\n%s (%d):\n",  label[12], count);
        for (control.i = 0; control.i < count; control.i++) {
            _pCard(cards[control.i]);
        }
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",  label[13], label[14], label[15],
                                                label[16], label[17], label[18],
                                                label[19]);
        do {
            scanf(" %d", &control.menu);
            if (control.menu > 0 && control.menu < 6) {
                compare(cards[0], cards[1], &control.menu);
            }
            else {
                control.menu = 0;
            }
        } while (control.menu);
    }
    printf("%s\n", label[21]);
    return 0;
}

/*
    Foi colocado com underscore, pois já existe uma função embutida 
    em c que faz isso, mas fiz uma gracinha para o avaliador.
    Essa função conta o numero de caracteres em um vetor de caracteres 
    utilizando ponteiros e operações entre ponteiros.
    Esse exemplo é contido no manual C Programming Language de 1970 se 
    não estou enganado tem esse exemplo.
*/
int _strlen(char *s) {
    char *p = s;
    while (*p != '\0') {
        p++;
    }
    return p - s;
}
void _pCard(struct tcard value) {
    printf("%s - %s | População: %d | Área: %.2f | PIB: %.2f | Pontos Turísticos: %d | Pib per Capta: %.2f | Densidade Populacional: %.2f \n", value.code, 
                                                                                                                                               value.city, 
                                                                                                                                               value.population,
                                                                                                                                               value.area, 
                                                                                                                                               value.pib, 
                                                                                                                                               value.points,
                                                                                                                                               value.pibcapt,
                                                                                                                                               value.densp);
} 
void compare(struct tcard value1, struct tcard value2, int *option) {
    switch (*option) {
        case 1:
            if (value1.population > value2.population) _pCard(value1);
            else if (value2.population > value1.population) _pCard(value2);
            else printf("%s\n", label[21]);
            break;
        case 2:
            if (value1.area > value2.area) _pCard(value1);
            else if (value2.area > value1.area) _pCard(value2);
            else printf("%s\n", label[21]);
            break;
        case 3:
            if (value1.pib > value2.pib) _pCard(value1);
            else if (value2.pib > value1.pib) _pCard(value2);
            else printf("%s\n", label[21]);
            break;
        case 4:
            if (value1.densp > value2.densp) _pCard(value1);
            else if (value2.densp > value1.densp) _pCard(value2);
            else printf("%s\n", label[21]);
            break;
        case 5:
            if (value1.pibcapt > value2.pibcapt) _pCard(value1);
            else if (value2.pibcapt > value1.pibcapt) _pCard(value2);
            else printf("%s\n", label[21]);
            break;                                 
        default:
            break;
    }
}
void push(struct tcard arr[], int *size, struct tcard value, int capacity) {
    if (*size >= capacity) {
        return;
    }
    arr[*size] = value;
    (*size)++;
}
