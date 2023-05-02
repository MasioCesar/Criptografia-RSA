#include <dirent.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "core/encriptar.c"
#include "utils.h"

#define ULL unsigned long long 

void chavePublica() {
  FILE *chave_publica;
  ULL p, q, n, e, totienteEuler;
  
  do {
    printf("Digite o 1° numero primo: ");
    scanf("%llu", &p);
    if (!isPrimeNumber(p)) {
      printf("\nNumero invalido\n");
    }
  }while (!isPrimeNumber(p));
  
  do {
    printf("Digite o 2° numero primo: ");
    scanf("%llu", &q);
    if (!isPrimeNumber(q)) {
      printf("\nNumero invalido\n");
    }
  }while (!isPrimeNumber(q));

  n = p * q;
  totienteEuler = (p-1)*(q-1);

  printf("\n\nAgora digite um expoente relativamente primo a %lld:\n", totienteEuler);
  scanf("%lld", &e);
  
  while (!isPrimeNumber(e) || !descobreRelativamentePrimo(totienteEuler, p, q, e)) {
    printf("\n\nDigite um expoente relativamente primo a %lld válido:\n", totienteEuler);
    scanf("%lld", &e);
  }

  chave_publica = fopen("public_key.txt", "w"); 
  fprintf(chave_publica, "Sua chave pública: (%llu, %llu)", n, e);
  fclose(chave_publica);
}

int main() {
  int escolha=0;

  printf("DIGITE UM DOS NÚMEROS:\n1 - Gerar chave pública\n2 - Encriptar\n3 - Desencriptar\n");
  
  scanf("%d", &escolha);

  while(escolha != 1 && escolha !=2 && escolha !=3){
        printf("Número inválido, tente novamente!\n");
        scanf("%d", &escolha);
  }

  switch (escolha) {
    default:
      printf("Número inválido, tente novamente!\n");
      scanf("%d", &escolha);
      break;
    case 1:
      chavePublica();
      break;
    case 2:
      encriptar();
      break;
    case 3:
      desencriptar(); 
      break;
  }
  
  return 0;
}
