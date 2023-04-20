#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkPrimo(long long num)
{
  if (num < 2)
  {
    return false;
  }
  else if (num == 2)
  {
    return true;
  }
  else if (num % 2 == 0)
  {
    return false;
  }
  else
  {
    for (int i = 3; i * i <= num; i += 2)
    {
      if (num % i == 0)
      {
        return false;
      }
    }
    return true;
  }
}

bool descobreRelativamentePrimo(long long coeficienteEuler, long long p, long long q, long long e)
{
  long long i = 2;
  while (i <= coeficienteEuler)
  {
    if (coeficienteEuler % i != 0 && checkPrimo(i) && i != p && i != q)
    {
      if (i == e)
      {
        return true;
      }
    }
    i++;
  }
  return false;
}

void chavePublica()
{
  FILE *chave_publica;
  long long p, q, n, e, coeficienteEuler;

  printf("Digite o 1° numero primo: ");
  scanf("%llu", &p);

  checkPrimo(p);

  while (!checkPrimo(p))
  {
    printf("Digite o 1° numero primo válido: ");
    scanf("%llu", &p);
  }

  printf("Digite o 2° numero primo: ");
  scanf("%llu", &q);
  checkPrimo(q);

  while (!checkPrimo(q))
  {
    printf("Digite o 2° numero primo válido: ");
    scanf("%llu", &q);
  }

  n = p * q;
  coeficienteEuler = (p - 1) * (q - 1);

  printf("\n\nAgora digite um expoente relativamente primo a %lld:\n", coeficienteEuler);
  scanf("%lld", &e);

  while (!checkPrimo(e) || !descobreRelativamentePrimo(coeficienteEuler, p, q, e))
  {
    printf("\n\nDigite um expoente relativamente primo a %lld válido:\n", coeficienteEuler);
    scanf("%lld", &e);
  }

  chave_publica = fopen("public_key.txt", "w");
  fprintf(chave_publica, "Sua chave pública: (%llu, %llu)", n, e);
  fclose(chave_publica);
}

int main()
{
  int escolha = 0;

  printf("DIGITE UM DOS NÚMEROS:\n1 - Gerar chave pública\n2 - Encriptar\n3 - Desencriptar\n");

  scanf("%d", &escolha);

  while (escolha != 1 && escolha != 2 && escolha != 3)
  {
    printf("Número inválido, tente novamente!\n");
    scanf("%d", &escolha);
  }

  if (escolha == 1)
  {
    chavePublica();
  }

  return 0;
}