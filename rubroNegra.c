#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "producao.h"
#include "rubroNegra.h"

Producao* criarProducaoRB(int codigo, Data data, Fardo fardo, int qtDeFardos, float duracao) {
    Producao *newProducao = (Producao*)malloc(sizeof(Producao));
    if (!newProducao) return NULL;
    newProducao->codigo = codigo;
    newProducao->dataProducao = data;
    newProducao->tipoDeFardo = fardo;
    newProducao->qtDeFardos = qtDeFardos;
    newProducao->duracao = duracao;
    newProducao->left = newProducao->right = newProducao->parent = NULL;
    newProducao->color = 0; // Nova produção começa como Red

    return newProducao;
}

NodeRN *createNode(Producao *chave, arvore *T) {
    NodeRN *ptr = (NodeRN *) malloc(sizeof(NodeRN));
    if (!ptr) {
        return NULL;
    }
    ptr->prod = chave;
    ptr->cor = RUBRO;
    ptr->esq = ptr->dir = ptr->pai = T->sentinela;
    return ptr;
}


NodeRN *createSentinela() {
    NodeRN *ptr = (NodeRN *)malloc(sizeof(NodeRN));
    if (!ptr) {
        return NULL;
    }
    ptr->prod = NULL;
    ptr->cor = NEGRO;
    ptr->esq = ptr->dir = ptr->pai = NULL;
    return ptr;
}


arvore *createArvore() {
    arvore *T = (arvore *)malloc(sizeof(arvore));
    if (!T) {
        return NULL;
    }

    T->sentinela = createSentinela();
    if (!T->sentinela) {
        free(T);
        return NULL;
    }

    T->raiz = T->sentinela;
    return T;
}


NodeRN *searchRN(arvore *T, NodeRN *root, int ch) {
    if (root == T->sentinela) {
        return NULL;
    }
    if (ch == root->prod->codigo) {
        return root; // Nó encontrado
    }
    if (ch < root->prod->codigo) {
        return searchRN(T, root->esq, ch); // Buscar na subárvore esquerda
    }
    return searchRN(T, root->dir, ch); // Buscar na subárvore direita

}

void RotacaoEsq(arvore *T, NodeRN *arv) {
    NodeRN *aux = arv->dir;
    arv->dir = aux->esq;
    if (aux->esq != T->sentinela) {
        aux->esq->pai = arv;
    }
    aux->pai = arv->pai;
    if (arv->pai == T->sentinela) {
        T->raiz = aux;
    } else if (arv == arv->pai->esq) {
        arv->pai->esq = aux;
    } else {
        arv->pai->dir = aux;
    }
    aux->esq = arv;
    arv->pai = aux;
}


void RotacaoDir(arvore *T, NodeRN *arv) {
    NodeRN *aux = arv->esq;
    arv->esq = aux->dir;
    if (aux->dir != T->sentinela) {
        aux->dir->pai = arv;
    }
    aux->pai = arv->pai;
    if (arv->pai == T->sentinela) {
        T->raiz = aux;
    } else if (arv == arv->pai->dir) {
        arv->pai->dir = aux;
    } else {
        arv->pai->esq = aux;
    }
    aux->dir = arv;
    arv->pai = aux;
}


void insertFixup(arvore *T, NodeRN *z) {
    while (z->pai->cor == RUBRO) {
        // Verifica se o pai de z está à esquerda
        if (z->pai == z->pai->pai->esq) {
            NodeRN *tio = z->pai->pai->dir;

            // Caso o tio seja rubro
            if (tio->cor == RUBRO) {
                z->pai->cor = NEGRO;
                tio->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                z = z->pai->pai;
            } else {
                // Caso o tio seja negro
                if (z == z->pai->dir) {
                    z = z->pai;
                    RotacaoEsq(T, z);
                }
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                RotacaoDir(T, z->pai->pai);
            }
        } else {
            // Espelho do caso acima com tio à esquerda
            NodeRN *tio = z->pai->pai->esq;

            if (tio->cor == RUBRO) {
                z->pai->cor = NEGRO;
                tio->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    RotacaoDir(T, z);
                }
                z->pai->cor = NEGRO;
                z->pai->pai->cor = RUBRO;
                RotacaoEsq(T, z->pai->pai);
            }
        }
    }
    T->raiz->cor = NEGRO;
}

void insertRN(arvore *T, Producao *prod) {
    NodeRN *novoNo = createNode(prod, T);
    NodeRN *pai = T->sentinela;
    NodeRN *root = T->raiz;

    while (root != T->sentinela) {
        pai = root;
        if (novoNo->prod->codigo == root->prod->codigo) {
            printf("\nID da Produção já inserido no banco de dados!\n");
            return;
        } else if (novoNo->prod->codigo < root->prod->codigo) {
            root = root->esq;
        } else {
            root = root->dir;
        }
    }

    novoNo->pai = pai;

    if (pai == T->sentinela) {
        T->raiz = novoNo;
    } else if (novoNo->prod->codigo < pai->prod->codigo) {
        pai->esq = novoNo;
    } else {
        pai->dir = novoNo;
    }

    insertFixup(T, novoNo);
}

void repointRN(arvore *T, NodeRN *auxa, NodeRN *auxb) {
    if (auxa->pai == T->sentinela) {
        T->raiz = auxb;
    } else if (auxa == auxa->pai->esq) {
        auxa->pai->esq = auxb;
    } else {
        auxa->pai->dir = auxb;
    }
    if (auxb != T->sentinela) {
        auxb->pai = auxa->pai;
    }
}


NodeRN *sucessorRN(arvore *T, NodeRN *suc) {
    while (suc->esq != T->sentinela) {
        suc = suc->esq;
    }
    return suc;
}


void deleteFixup(arvore *T, NodeRN *arv){
    NodeRN *aux;

    while((arv != T->raiz) && (arv->cor == NEGRO)){
        if(arv == arv->pai->esq){       //Caso o arv esteja na esquerda
            aux = arv->pai->dir;
            if(aux->cor ==  RUBRO){       //Caso o no "aux" seja rubro
                aux->cor = NEGRO;       //E necessario a troca de cores entre os nos de referencia
                arv->pai->cor = RUBRO;
                RotacaoEsq(T,arv->pai);
                aux = arv->pai->dir;
            }
            if((aux->esq->cor == NEGRO) && (aux->dir->cor == NEGRO)){   //Caso o "aux" seja negro e os dois filhos dele sejam negros
                aux->cor = RUBRO;                                       //Deixa o "aux" como rubro
                arv = arv->pai;
            }
            else{
                if(aux->dir->cor == NEGRO){     //Caso "aux" seja negro seu filho esquerdo e rubro e o direito e negro
                    aux->esq->cor = NEGRO;      //Troca-se as cores entre "aux" e seu filho esquerdo
                    aux->cor = RUBRO;
                    RotacaoDir(T,aux);          //Executa a rotacao direita no aux sem violar nenhuma das propriedades rubro-negras
                    aux = arv->pai->dir;
                }
                aux->cor = arv->pai->cor;   //Caso o "aux" seja negro e seu filho a direita seja rubro
                arv->pai->cor = NEGRO;      //Altera a cor do pai e do aux para negro
                aux->dir->cor = NEGRO;
                RotacaoEsq(T,arv->pai);     //Executa a rotacao esquerda no pai sem violar nenhuma das propriedades rubro-negras
                arv = T->raiz;
            }
        }
        else{           //De forma analoga, realiza-se de forma oposta para caso o arv esteja a direita
            aux = arv->pai->esq;
            if(aux-> cor == RUBRO){ //CASO 1
                aux->cor = NEGRO;
                arv->pai->cor = RUBRO;
                RotacaoDir(T,arv->pai);
                aux = arv->pai->esq;
            }
            if((aux->esq->cor == NEGRO) && (aux->dir->cor == NEGRO)){   //CASO 2
                aux->cor = RUBRO;
                arv = arv->pai;
            }
            else{
                if(aux->dir->cor == NEGRO){ //CASO 3
                    aux->esq->cor = NEGRO;
                    aux->cor = RUBRO;
                    RotacaoEsq(T,aux);
                    aux = arv->pai->esq;
                }
                aux->cor = arv->pai->cor;   //CASO 4
                arv->pai->cor = NEGRO;
                aux->dir->cor = NEGRO;
                RotacaoDir(T, arv->pai);
                arv = T->raiz;
            }
        }
    }
    arv->cor = NEGRO;
}

void deleteRN(arvore *T, int ch) {
    NodeRN *busca = searchRN(T, T->raiz, ch);
    if (busca == NULL) {
        printf("\nProdução procurada não foi encontrada para a remoção\n");
        return;
    }

    NodeRN *auxa, *auxb = busca;
    int corOriginal = auxb->cor;

    if (busca->esq == T->sentinela) {
        auxa = busca->dir;
        repointRN(T, busca, busca->dir);
    } else if (busca->dir == T->sentinela) {
        auxa = busca->esq;
        repointRN(T, busca, busca->esq);
    } else {
        auxb = sucessorRN(T, busca->dir);
        corOriginal = auxb->cor;
        auxa = auxb->dir;

        if (auxb->pai == busca) {
            auxa->pai = auxb;
        } else {
            repointRN(T, auxb, auxb->dir);
            auxb->dir = busca->dir;
            auxb->dir->pai = auxb;
        }
        repointRN(T, busca, auxb);
        auxb->esq = busca->esq;
        auxb->esq->pai = auxb;
        auxb->cor = busca->cor;
    }

    if (busca != auxb) {
        free(busca);
    }
    if (corOriginal == NEGRO) {
        deleteFixup(T, auxa);
    }
}

void printRN(arvore *T, NodeRN *root, int nivel) {
    if (root == T->sentinela) return;

    for (int i = 0; i < nivel; i++) printf("\t");

    char cor[6];
    if (root->cor == NEGRO) {
        strcpy(cor, "NEGRO");
    } else {
        strcpy(cor, "RUBRO");
    }

    printf("[%i] [%s]\n", root->prod->codigo, cor);
    printRN(T, root->esq, nivel + 1);
    printRN(T, root->dir, nivel - 1);
}
