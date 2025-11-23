#ifndef CALCULADORA_H
#define CALCULADORA_H

// A estrutura Expressao não foi explicitamente pedida para ser usada nas funções,
// mas foi mencionada no PDF original (expressao.h).
// No entanto, as funções exigidas são:
// char * getFormaInFixa(char *Str);
// float getValorPosFixa(char *StrPosFixa);

// Definindo os protótipos das funções exigidas.
char * getFormaInFixa(char *Str); // Retorna a forma inFixa de Str (posFixa)
float getValorPosFixa(char *StrPosFixa); // Calcula o valor de Str (na forma posFixa)

#endif // CALCULADORA_H
