#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void ImageProcessFunction(const int line, const int column, unsigned short int matriz[][column], short int mask) {

    unsigned short int matrizScanning[mask][mask];
	unsigned int maskCalc = (int) (mask/2);
	// percorrendo a matriz 
	for (int a=0; a < (line - (2 * maskCalc)); a++) {
		for (int b=0; b < (column - (2 * maskCalc)); b++) {
			
			//  bloco com o valor a ser alterado
			for (int i=a; i<mask+a; i++) {
				for(int j=b; j<mask+b; j++) {
					matrizScanning[i-a][j-b] = matriz[i][j];
				}
			}

			// função para ordenar os valores da matriz de escaneamento
			qsort(matrizScanning, (mask * mask), sizeof(int), toCompare);
			
			// setando o valor da matriz para a mediana dos valores ordenados
			matriz[a + (mask/2)][b + (mask/2)] = matrizScanning[(mask/2)][(mask/2)];
		}
	}
}

int toCompare(const void *p1, const void *p2) {
    if (*(int*)p1 > *(int*)p2)
	    return 1;
    else if (*(int*)p1 < *(int*)p2)
        return -1;
    return 0;
}