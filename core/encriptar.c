#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../utils.h"

#define ULL unsigned long long 
#define MAX 1000000

//create a function to encrypt a file using RSA
void encriptar() {
  char mensagem[MAX];
  char mensagemEncriptada[MAX];
  ULL n, e;
  FILE *arquivoEncriptado = fopen("mensagemEncriptada.txt", "w");

  printf("Digite a mensagem a encriptar: ");
  scanf(" %[^\n]", mensagem);

  printf("Digite a chave publica (N e E): ");
  scanf("%llu%llu", &n, &e);

  for(int i = 0; i < strlen(mensagem); i++) {
    mensagem[i] = (char)exponenciacaoModularRapida(e,n, (int)mensagem[i]);
    strcat(mensagemEncriptada, &mensagem[i]);
  }
  fprintf(arquivoEncriptado, "%s", mensagemEncriptada);
  fclose(arquivoEncriptado);
}

