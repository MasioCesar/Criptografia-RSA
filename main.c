#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ULL unsigned long long 
#define MAX 1000000

ULL exp_mod_rapida(ULL base, ULL exp, ULL mod) {
    ULL resultado = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            resultado = (resultado * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return resultado;
}

long long int calcular_chave_privada(ULL e, ULL phi) {
    long long int d = 0;
    long long int x1 = 0, x2 = 1, y1 = 1, y2 = 0;
    long long int q, r, x, y, phi_inicial = phi;
    while (phi != 0) {
        q = e / phi;
        r = e % phi;
        x = x2 - q * x1;
        y = y2 - q * y1;
        e = phi;
        phi = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }

    d = x2;
    if (d < 0){
        for (int i = 1;d < 0;i++){
            d += phi_inicial*i;
        }
    }

    return d;
}

bool checkPrimo(unsigned long long num) {
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

unsigned long long calculaMDC(unsigned long long totienteEuler, unsigned long long e) {
  unsigned long long resto;
  while (e != 0) {
    resto = totienteEuler % e;
    totienteEuler = e;
    e = resto;
  }
  return totienteEuler;
}

bool descobreRelativamentePrimo(unsigned long long totienteEuler, unsigned long long p, unsigned long long q, unsigned long long e){
  if (calculaMDC(totienteEuler, e) == 1 && e != p && e != q) {
    return true;
  } else {
    return false;
  }
}

void chavePublica() {
  FILE *chave_publica;
  unsigned long long p, q, n, e, totienteEuler;
  
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
  char mensagem[MAX];
  int mensagemEncriptada;
  ULL n, e;
  FILE *arquivoEncriptado = fopen("mensagemEncriptada.txt", "w");

  printf("Digite a mensagem a encriptar: ");
  scanf(" %[^\n]", mensagem);

  printf("Digite a chave publica (N e E): ");
  scanf("%llu%llu", &n, &e);

  for(int i = 0; i < strlen(mensagem); i++) {
    if (mensagem[i] == ' ') {
      mensagemEncriptada = exp_mod_rapida(28, e, n);
      
      fprintf(arquivoEncriptado, "%d ", mensagemEncriptada);
    } else {
      mensagemEncriptada = exp_mod_rapida((int)mensagem[i] - 63, e,n);
      fprintf(arquivoEncriptado, "%d ", mensagemEncriptada);
    }
  }
  
  fclose(arquivoEncriptado);
}


void desencriptar(){
    FILE *mensagemEncriptada;
    FILE *mensagemDesencriptada;
    mensagemEncriptada = fopen("mensagemEncriptada.txt", "r");
    mensagemDesencriptada = fopen("mensagemDesencriptada.txt", "w");
    unsigned long long num, p, q, n;
    long long int d, phi, e;
  
    printf("\nDigite o P: ");
    scanf("%llu", &p);

    printf("\nDigite o Q: ");
    scanf("%llu", &q);
  
    printf("\nDigite o E: ");
    scanf("%lld", &e);
  
    phi = (p-1)*(q-1);
  
    d = calcular_chave_privada(e, phi);
    n = p * q;
    
    while (fscanf(mensagemEncriptada, "%llu", &num) != EOF){
        
        char caracter;
        int decripted_num = exp_mod_rapida(num, d, n);
        
        if (decripted_num == 28){
            caracter = 32;
        }
        else {
            caracter = decripted_num + 63;
        }
        fprintf(mensagemDesencriptada,"%c", caracter);
    }
    fclose(mensagemDesencriptada);
    fclose(mensagemEncriptada);
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
