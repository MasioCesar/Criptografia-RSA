#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define ULL unsinged long long 

bool checkPrimo(ull num) {
  if (num < 2) {
    return false;
  } else if (num == 2) {
    return true;
  } else if (num % 2 == 0) {
    return false;
  } else {
    for (int i = 3; i * i <= num; i += 2) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }
}

ULL calculaMDC(ULL totienteEuler, ULL e) {
  ULL resto;
  while (e != 0) {
    resto = totienteEuler % e;
    totienteEuler = e;
    e = resto;
  }
  return totienteEuler;
}

bool descobreRelativamentePrimo(ULL totienteEuler, ULL p, ULL q, ULL e){
  if (calculaMDC(totienteEuler, e) == 1 && e != p && e != q) {
    return true;
  } else {
    return false;
  }
}

void chavePublica() {
  FILE *chave_publica;
  ULL p, q, n, e, totienteEuler;
  
  printf("Digite o 1° numero primo: ");
  scanf("%llu", &p);
  
  checkPrimo(p);
  
  while (!checkPrimo(p)) {
    printf("Digite o 1° numero primo válido: ");
    scanf("%llu", &p);
  }
  
  printf("Digite o 2° numero primo: ");
  scanf("%llu", &q);
  checkPrimo(q);    

  while (!checkPrimo(q)) {
    printf("Digite o 2° numero primo válido: ");
    scanf("%llu", &q);
  }

  n = p * q;
  totienteEuler = (p-1)*(q-1);

  printf("\n\nAgora digite um expoente relativamente primo a %lld:\n", totienteEuler);
  scanf("%lld", &e);
  
  while (!checkPrimo(e) || !descobreRelativamentePrimo(totienteEuler, p, q, e)) {
    printf("\n\nDigite um expoente relativamente primo a %lld válido:\n", totienteEuler);
    scanf("%lld", &e);
  }

  chave_publica = fopen("public_key.txt", "w"); 
  fprintf(chave_publica, "Sua chave pública: (%llu, %llu)", n, e);
  fclose(chave_publica);
}

void encriptar() {
  char mensagem[255];
  ULL n, e;

  // Pedindo para o usuario digitar o texto a ser encriptado
  // %[^\n] indica que a leitura deve ser feita até que seja encontrado um caractere de quebra de linha
  printf("Digite a mensagem a encriptar: ");
  scanf(" %[^\n]", mensagem);

  printf("Digite a chave publica (N e E): ");
  scanf("%llu%llu", &n, &e);

  
}

void desencriptar() {
  
}

int main() {
  int escolha=0;

  printf("DIGITE UM DOS NÚMEROS:\n1 - Gerar chave pública\n2 - Encriptar\n3 - Desencriptar\n");
  
  scanf("%d", &escolha);

  while(escolha != 1 && escolha !=2 && escolha !=3){
        printf("Número inválido, tente novamente!\n");
        scanf("%d", &escolha);
  }

  if (escolha == 1) {
    chavePublica();
  }
  if (escolha == 2) {
    encriptar();
  }
  if (escolha == 3) {
    desencriptar();
  }
  
  return 0;
}
