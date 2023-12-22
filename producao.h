#ifndef PRODUCAO_H
#define PRODUCAO_H
#include "types.h"
#include "rubroNegra.h"
#include <stdbool.h>


//Funções diretas Produção
void consultarProducao(NodeRN *root, Data data, arvore *T) ;
void inserirProducao(arvore *T, Producao *novaProducao) ;
void alterarProducao(arvore *T, int codigo, Producao *dadosAtualizados) ;
void excluirProducao(arvore *T, int codigo) ;
void listarProducoes(NodeRN *root, arvore *T) ;
void liberarMemoria(NodeRN *root, arvore *T) ;
void consultarProducaoPorPeriodo(NodeRN *root, Data inicio, Data fim, arvore *T);
void consultarPorCultivar(NodeRN *root, const char *cultivar, arvore *T) ;
void consultarPorTipoDeFeno(NodeRN *root, char tipoDeFeno, arvore *T) ;
void listarProducoesPorData(NodeRN *root, Data data, arvore *T);


//Funções para Analise estatistica
void inicializaEstatisticas(Estatisticas *est);
void analiseEstatistica(NodeRN *root, arvore *T, Data inicio, Data fim, Estatisticas *est);
void exibirEstatisticas(const Estatisticas *est) ;


//Utils
int comparaDatas(Data d1, Data d2) ;
bool isLeapYear(int year) ;
bool isValidDate(Data data) ;
bool isValidFenoType(char tipoDeFeno);
bool isPositiveNumber(float number) ;
bool isValidCultivar(char *cultivar);
#endif
