#include <stdio.h>
#include "../utils.h"

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


