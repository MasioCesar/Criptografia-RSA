#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

#define ULL unsigned long long 

bool isPrimeNumber(unsigned long long int number){
  if (number < 2) {
    return false;
  }

  for (unsigned long long int i = 2; i <= number / 2; ++i) {
    if (number % i == 0) {
      return false;
    }
  }

  return true;
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

ULL exponenciacaoModularRapida(ULL e, ULL n, ULL m) {
  ULL resultado = 1;
  e = e % m;
  while (e > 0) {
    if (e % 2 == 1) {
      resultado = (resultado * e) % m;
    }
    e = e >> 1;
    e = e * e;
  }
  return resultado;
}

int intToAscii(int number) {
   return '0' + number;
}
