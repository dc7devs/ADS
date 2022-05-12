#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// pgmmediana -m N -i input -o output
// pgmmediana N input output
/*
    pgmmediana --> nome do executavel.
    -m --> O tamanho da máscara é um inteiro positivo ímpar, caso não seja informado, o valor default é 3, para uma máscara de 3×3 pixels.
    -i -->  Imagem de imput(a imagem a ser modificada).
    -o --> Imagem de  output(a imagem de saida apos ter aplicado o filtro).
*/

// STRUCT PGM
typedef struct {
    char type[3];
    int line, column, colorVariance;

} tPGM, *tPPGM;

// FUNÇÕES
void openEndVerifyFile(FILE **filePGM, char filePath[], char operation[]);
void hError(char messageError[], _Bool man);

int main(int argc, char *argv[]) {
    FILE *pgmInput, *pgmOutput;
    tPPGM pontTypeStructPGM = calloc(1, sizeof(tPGM));
    int mask=3; // mask default

    openEndVerifyFile(&pgmInput, (argv[2] ? argv[2] : argv[1]), "r");

    // Lendo cada elemento do cabeçalho do arquivo
    fscanf(pgmInput, "%s %d %d %d",
            pontTypeStructPGM->type,
            &pontTypeStructPGM->column,
            &pontTypeStructPGM->line,
            &pontTypeStructPGM->colorVariance
    );

    // Verificação da mascara
    if (argv[2] && (strtol(argv[1], NULL, 10) % 2 != 0))
        mask = strtol(argv[1], NULL, 10);
    else if(argv[2] && (strtol(argv[1], NULL, 10) % 2 == 0)){
        hError("> The mask value must be an odd number", 1);
        exit(1);
    };

    fclose(pgmInput);

    // Lendo os valores da matriz | logica do calculo da mediana deve ser armazenado em aruivo de biblioteca a parte
    // [...]

    free(pontTypeStructPGM);
    return 0;
}

// Função para abrir e vrificar um arquivo
void openEndVerifyFile(FILE **filePGM, char filePath[], char operation[]) {
    if(!(*filePGM = fopen(filePath, operation))) {

        hError("> Error opening file!",  1);
        exit(1);
    }
}

// Função para apresentar erros + o manual
void hError(char messageError[], _Bool man) {
    // ERROR
    printf("\033[1;31m%s\033[0m\n", messageError);

    if(man) {
        // MANUAL
        printf("\n\033[0;37mUsage:  pgmmediana -m N -i input -o output\n\n\033[0m");
        printf("\033[0;37mbasic:\t\tpgmmediana [FILE-INPUT] [FILE-OUTPUT]\n\033[0m");
        printf("\033[0;37mwith mask:\tpgmmediana [ODD-NUMBER-MASK] [FILE-INPUT] [FILE-OUTPUT]\n\033[0m");
    } else;
};
