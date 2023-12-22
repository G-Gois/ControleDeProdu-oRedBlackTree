
#ifndef TYPES_H
#define TYPES_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct fardo {
    char cultivar[20];
    char tipoDeFeno;
    int diametro;
} Fardo;



typedef struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardos;
    float duracao;
    struct producao *left, *right, *parent;
    int color; // 0 para Red, 1 para Black
} Producao;


typedef struct no{
    int cor;
    struct no *esq, *dir, *pai;
    Producao *prod;
}NodeRN;

typedef struct tno{
    NodeRN *raiz, *sentinela;
}arvore;



//Tipo Estatisticas vai ser usado para facilitar na hora das contagens estatisticas
typedef struct {
    int totalFardos;
    int totalProducoes;
    float somaDiametros;
    int contadorTipoA;
    int contadorTipoB;
    int contadorTipoC;
    int contadorTifton85;
    int contadorFlorakirk;
    int contadorJiggs;
    int contadorCoastcross;
} Estatisticas;

#endif
