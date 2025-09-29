#include <stdio.h>

#define trycast(value, type) ((type)(value))
#define MAX_CARDS 100

int _strlen(char *s);

struct cflow {
    int main;
    int inner;
};

struct tcard {
    char state;
    char code[3];
    char city[500];
    int population;
    float area;
    float pib;
    int points;
};

int main() {
    struct cflow control;
    struct tcard card;
    struct tcard cards[MAX_CARDS];
    int count = 0;

    char label[12][200] = {
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
    };

    printf("%s\n\t%s\n\t%s\n", label[0], label[1], label[2]);

    do {
        scanf(" %d", &control.main);

        if (control.main == 1) {
            printf("\t%s\n", label[3]);
            scanf(" %c", &card.state);

            if ((trycast(card.state, int) >= 65) && (trycast(card.state, int) <= 72)) {
                printf("\a\t%s\n", label[4]);
                printf("\a\t%s\n", label[6]);

                int code = 0;
                scanf("%d", &code);

                if ((code >= 1) && (code <= 4)) {
                    card.code[0] = card.state;
                    card.code[1] = '0';
                    card.code[2] = '0' + code;
                    card.code[3] = '\0';

                    printf("\a\t%s\n", label[4]);
                    printf("\a\t%s\n", label[7]);
                    scanf(" %499[^\n]", card.city);

                    if (_strlen(card.city) > 0) {
                        printf("\a\t%s\n", label[4]);
                        printf("\a\t%s\n", label[8]);
                        scanf("%d", &card.population);

                        if (card.population >= 0) {
                            printf("\a\t%s\n", label[4]);
                            printf("\a\t%s\n", label[9]);
                            scanf("%f", &card.area);

                            if (card.area >= 0) {
                                printf("\a\t%s\n", label[4]);
                                printf("\a\t%s\n", label[10]);
                                scanf("%f", &card.pib);

                                if (card.pib >= 0) {
                                    printf("\a\t%s\n", label[4]);
                                    printf("\a\t%s\n", label[11]);
                                    scanf("%d", &card.points);

                                    if (card.points >= 0) {
                                        printf("\a\t%s\n", label[4]);

                                        if (count < MAX_CARDS) {
                                            cards[count++] = card;
                                            printf("\t%s\n", label[3]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    printf("\a\t%s\n", label[5]);
                }
            } else {
                printf("\a\t%s\n", label[5]);
            }
        } else {
            control.main = 0;
        }
    } while (control.main);

    printf("\nStored cards (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("%s - %s | Pop: %d | Area: %.2f | PIB: %.2f | Points: %d\n",
               cards[i].code, cards[i].city, cards[i].population,
               cards[i].area, cards[i].pib, cards[i].points);
    }

    return 0;
}

int _strlen(char *s) {
    char *p = s;
    while (*p != '\0') {
        p++;
    }
    return p - s;
}
