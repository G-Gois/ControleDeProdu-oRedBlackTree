#ifndef _H_RUBRONEGRA
#define _H_RUBRONEGRA
#include "types.h"
#include "producao.h"

#include<stdio.h>
#include<stdlib.h>


#define RUBRO 1
#define NEGRO 0


//Funções de criar produção e nó com valor de produção.
Producao* criarProducaoRB(int codigo, Data data, Fardo fardo, int qtDeFardos, float duracao);
NodeRN *createNode(Producao *chave, arvore *T);


//Função de criação de nó sentinela
NodeRN *createSentinela();


//Criar arvore
arvore *createArvore();

//Procura nó com base no codigo
NodeRN *searchRN(arvore *T, NodeRN *root, int ch);

/*Rotação simples a esquerda: Considerando o pivô o nó a direita do parâmetro passado, rotacionamos em torno dele
para a esquerda, trocando os apontamentos e suas cores de tal forma que o pivô receba a cor de seu pai e o mesmo
se torna rubro*/

void RotacaoEsq(arvore *T, NodeRN *arv);

/*Rotação simples a direita: Considerando o pivô o nó a esquerda do parâmetro passado, rotacionamos em torno dele
para a direita, trocando os apontamentos e suas cores de tal forma que o pivô receba a cor de seu pai e o mesmo
se torna rubro*/
void RotacaoDir(arvore *T, NodeRN *arv);

/*Metodo auxiliar cuja funcionalidade se baseia em verificar e manipular as condiçoes de arvore rubro-negra,
utilizando de rotações ou apenas trocando as cores dos nós*/
void insertFixup(arvore *T, NodeRN *root);

/*Função que realiza a chamada da inserção de um objeto do tipo Produção na chave caso possível. Sua funcionalidade
se resume a manter a cor da raiz sempre negra para respeitar as leis da árvore rubro-negra, além de mostrar para
o usuario caso a inserção realmente tenha sido efetuada*/
void insertRN(arvore *T, Producao *prod) ;

/*Funcao que realiza reapontamentos necessarios para a remocao de um no*/
void repointRN(arvore *T, NodeRN *auxa, NodeRN *auxb);

/*Funcao que busca o sucessor de um no, sendo o sucessor o filho mais a esquerda da subarvore direita de uma arvore*/
NodeRN *sucessorRN(arvore *T, NodeRN *suc);

/*Funcao que auxilia a funcao deleteRN avaliando e reestabelecendo as propriedades de uma arvore RN no no inserido*/
void deleteFixup(arvore *T, NodeRN *arv);

/*Funcao que remove um no de umar arvore RN*/
void deleteRN(arvore *T, int ch);

/*Impressão completa da árvore, sendo para entendimento, a impressão do id da Produção + a cor do nó*/
void printRN(arvore *T, NodeRN *root, int nivel);

#endif
