#ifndef UTILS_H
#define UTILS_H

#define ULL unsigned long long 

bool isPrimeNumber(unsigned long long int number);
ULL calculaMDC(ULL totienteEuler, ULL e);
ULL exponenciacaoModularRapida(ULL e, ULL n, ULL m);
int intToAscii(int number); 
bool descobreRelativamentePrimo(ULL totienteEuler, ULL p, ULL q, ULL e);
#endif


