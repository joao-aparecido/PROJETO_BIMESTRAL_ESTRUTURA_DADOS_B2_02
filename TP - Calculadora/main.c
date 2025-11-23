#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

typedef struct {
    int id;
    char posFixa[512];
    char infixaEsperada[512];
    float valorEsperado;
} Teste;

// Tabela de testes do PDF
Teste testes[] = {
    {1, "3 4 + 5 *", "(3+4)*5", 35.0},
    {2, "7 2 * 4 +", "7*2+4", 18.0},
    {3, "8 5 2 4 + * +", "8+(5*(2+4))", 38.0},
    {4, "6 2 / 3 + 4 *", "(6/2+3)*4", 24.0},
    {5, "9 5 2 8 * 4 + * +", "9+(5*(2*(8+4)))", 109.0}, 
    {6, "2 3 + log 5 /", "log(2+3)/5", 0.139794}, 
    {7, "10 log 3 ^ 2 +", "(log10)^3+2", 3.0}, 
    {8, "45 60 + 30 cos *", "(45+60)*cos(30)", 90.9326}, 
    {9, "0.5 45 sen 2 ^ +", "sen(45)^2+0.5", 1.0} 
};


int numTestes = sizeof(testes) / sizeof(Teste);


int float_equals(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

void run_tests() {
    
    printf("TESTES DE VALIDACAO DO AVALIADOR DE EXPRESSOES NUMERICAS\n");
    

    int passed_count = 0;
    float epsilon = 0.01;

    for (int i = 0; i < numTestes; i++) {
        Teste t = testes[i];
        char posFixaCopy[512];
        char posFixaCopy2[512];
        
        // Teste de Avaliação (getValorPosFixa)
        strcpy(posFixaCopy, t.posFixa);
        float valorCalculado = getValorPosFixa(posFixaCopy);
        
        int valor_ok = float_equals(valorCalculado, t.valorEsperado, epsilon);
        
        printf("\n--- Teste %d ---\n", t.id);
        printf("Pos-Fixa: %s\n", t.posFixa);
        printf("Valor Esperado: %.2f (Aprox.)\n", t.valorEsperado);
        printf("Valor Calculado: %.6f\n", valorCalculado);
        printf("Resultado Valor: %s\n", valor_ok ? "PASSOU" : "FALHOU");

        
        strcpy(posFixaCopy2, t.posFixa);
        char *infixaCalculada = getFormaInFixa(posFixaCopy2);
        
        int infixa_ok = 0;
        if (infixaCalculada != NULL) {
            // teste 1:
            if (t.id == 1 && strcmp(infixaCalculada, "(3+4)*5") == 0) {
                infixa_ok = 1;
            } 
            // teste 2:
            else if (t.id == 2 && strcmp(infixaCalculada, "7*2+4") == 0) {
                infixa_ok = 1;
            }
            // teste 3:
            else if (t.id == 3 && strcmp(infixaCalculada, "8+(5*(2+4))") == 0) {
                infixa_ok = 1;
            }
            // teste 4:
            else if (t.id == 4 && strcmp(infixaCalculada, "(6/2+3)*4") == 0) {
                infixa_ok = 1;
            }
            // teste 5:
            else if (t.id == 5 && strcmp(infixaCalculada, "9+(5*(2*(8+4)))") == 0) {
                infixa_ok = 1;
            }
            // teste 6:
            else if (t.id == 6 && strcmp(infixaCalculada, "log(2+3)/5") == 0) {
                infixa_ok = 1;
            }
            // teste 7:
            else if (t.id == 7 && strcmp(infixaCalculada, "(log10)^3+2") == 0) {
                infixa_ok = 1;
            }
            // teste 8:
            else if (t.id == 8 && strcmp(infixaCalculada, "(45+60)*cos(30)") == 0) {
                infixa_ok = 1;
            }
            // teste 9:
            else if (t.id == 9 && strcmp(infixaCalculada, "sen(45)^2+0.5") == 0) {
                infixa_ok = 1;
            }
            
            printf("Infixa Esperada: %s\n", t.infixaEsperada);
            printf("Infixa Calculada: %s\n", infixaCalculada);
            printf("Resultado Infixa: %s\n", infixa_ok ? "PASSOU" : "FALHOU");
            
            free(infixaCalculada);
        } else {
            printf("Infixa Calculada: NULL (Erro na conversao)\n");
            printf("Resultado Infixa: FALHOU\n");
        }
        
        if (valor_ok && infixa_ok) {
            passed_count++;
        }
    }

    
    printf("RESUMO: %d de %d testes passaram.\n", passed_count, numTestes);
    
}

int main() {
    run_tests();
    return 0;
}
