#include "producao.h"
#include "rubroNegra.h"
#include <string.h>
#include <stdbool.h>
void consultarProducao(NodeRN *root, Data data, arvore *T) {
    if (root == T->sentinela) return;

    // Supondo que a comparação de datas seja feita por uma função comparaDatas
    if (comparaDatas(root->prod->dataProducao, data) == 0) {
        // Exibe os detalhes da produção
        printf("Código: %d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f\n",
               root->prod->codigo,
               root->prod->tipoDeFardo.cultivar,
               root->prod->tipoDeFardo.tipoDeFeno,
               root->prod->qtDeFardos,
               root->prod->duracao);
    }

    consultarProducao(root->esq, data, T);
    consultarProducao(root->dir, data, T);
}

void inserirProducao(arvore *T, Producao *novaProducao) {
    if (T == NULL || novaProducao == NULL) return;

    NodeRN *novoNo = createNode(novaProducao, T); // Considerando que createNode já foi definida
    if (novoNo == NULL) {
        return;
    }

    insertRN(T, novoNo->prod);

}


void alterarProducao(arvore *T, int codigo, Producao *dadosAtualizados) {
    if (T == NULL || dadosAtualizados == NULL) return;

    NodeRN *node = searchRN(T, T->raiz, codigo);
    if (node != NULL) {
        // Atualiza os dados da produção
        node->prod->dataProducao = dadosAtualizados->dataProducao;
        node->prod->tipoDeFardo = dadosAtualizados->tipoDeFardo;
        node->prod->qtDeFardos = dadosAtualizados->qtDeFardos;
        node->prod->duracao = dadosAtualizados->duracao;
    } else {
        printf("Produção com código %d não encontrada.\n", codigo);
    }
}


void excluirProducao(arvore *T, int codigo) {
    if (T == NULL) return;

    deleteRN(T, codigo);
}

void listarProducoes(NodeRN *root, arvore *T) {
    if (root == T->sentinela) return;

    // Exibe informações da produção atual
    printf("Código: %d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f\n",
           root->prod->codigo,
           root->prod->tipoDeFardo.cultivar,
           root->prod->tipoDeFardo.tipoDeFeno,
           root->prod->qtDeFardos,
           root->prod->duracao);

    // Chamadas recursivas para subárvores esquerda e direita
    listarProducoes(root->esq, T);
    listarProducoes(root->dir, T);
}


void liberarMemoria(NodeRN *root, arvore *T) {
    if (root == T->sentinela) return;

    liberarMemoria(root->esq, T);
    liberarMemoria(root->dir, T);

    free(root->prod); // Libera a memória alocada para a produção
    free(root);       // Libera a memória alocada para o nó
}

void consultarProducaoPorPeriodo(NodeRN *root, Data inicio, Data fim, arvore *T) {
    if (root == T->sentinela) return;

    if (comparaDatas(root->prod->dataProducao, inicio) >= 0 && comparaDatas(root->prod->dataProducao, fim) <= 0) {
        printf("Código: %d, Data: %d/%d/%d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f horas\n",
               root->prod->codigo,
               root->prod->dataProducao.dia, root->prod->dataProducao.mes, root->prod->dataProducao.ano,
               root->prod->tipoDeFardo.cultivar,
               root->prod->tipoDeFardo.tipoDeFeno,
               root->prod->qtDeFardos,
               root->prod->duracao);
    }

    consultarProducaoPorPeriodo(root->esq, inicio, fim, T);
    consultarProducaoPorPeriodo(root->dir, inicio, fim, T);
}


void consultarPorCultivar(NodeRN *root, const char *cultivar, arvore *T) {
    if (root == T->sentinela) return;

    if (strcmp(root->prod->tipoDeFardo.cultivar, cultivar) == 0) {
        printf("Código: %d, Data: %d/%d/%d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f horas\n",
               root->prod->codigo,
               root->prod->dataProducao.dia, root->prod->dataProducao.mes, root->prod->dataProducao.ano,
               root->prod->tipoDeFardo.cultivar,
               root->prod->tipoDeFardo.tipoDeFeno,
               root->prod->qtDeFardos,
               root->prod->duracao);
    }

    consultarPorCultivar(root->esq, cultivar, T);
    consultarPorCultivar(root->dir, cultivar, T);
}

void consultarPorTipoDeFeno(NodeRN *root, char tipoDeFeno, arvore *T) {
    if (root == T->sentinela) return;

    if (root->prod->tipoDeFardo.tipoDeFeno == tipoDeFeno) {
        printf("Código: %d, Data: %d/%d/%d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f horas\n",
               root->prod->codigo,
               root->prod->dataProducao.dia, root->prod->dataProducao.mes, root->prod->dataProducao.ano,
               root->prod->tipoDeFardo.cultivar,
               root->prod->tipoDeFardo.tipoDeFeno,
               root->prod->qtDeFardos,
               root->prod->duracao);
    }

    consultarPorTipoDeFeno(root->esq, tipoDeFeno, T);
    consultarPorTipoDeFeno(root->dir, tipoDeFeno, T);
}

void inicializaEstatisticas(Estatisticas *est) {
    est->totalFardos = 0;
    est->totalProducoes = 0;
    est->somaDiametros = 0.0f;
    est->contadorTipoA = est->contadorTipoB = est->contadorTipoC = 0;
    est->contadorTifton85 = est->contadorFlorakirk = est->contadorJiggs = est->contadorCoastcross = 0;
}

void analiseEstatistica(NodeRN *root, arvore *T, Data inicio, Data fim, Estatisticas *est) {
    if (root == T->sentinela) return;

    // Verifique se a data da produção está no intervalo
    if (comparaDatas(root->prod->dataProducao, inicio) >= 0 && comparaDatas(root->prod->dataProducao, fim) <= 0) {
        est->totalFardos += root->prod->qtDeFardos;
        est->somaDiametros += root->prod->tipoDeFardo.diametro;
        est->totalProducoes++;

        // Contagem por tipo de feno
        if (root->prod->tipoDeFardo.tipoDeFeno == 'A') est->contadorTipoA++;
        else if (root->prod->tipoDeFardo.tipoDeFeno == 'B') est->contadorTipoB++;
        else if (root->prod->tipoDeFardo.tipoDeFeno == 'C') est->contadorTipoC++;

        // Contagem por cultivar
        if (strcmp(root->prod->tipoDeFardo.cultivar, "Tifton 85") == 0) est->contadorTifton85++;
        else if (strcmp(root->prod->tipoDeFardo.cultivar, "Florakirk") == 0) est->contadorFlorakirk++;
        else if (strcmp(root->prod->tipoDeFardo.cultivar, "Jiggs") == 0) est->contadorJiggs++;
        else if (strcmp(root->prod->tipoDeFardo.cultivar, "Coastcross") == 0) est->contadorCoastcross++;
    }

    analiseEstatistica(root->esq, T, inicio, fim, est);
    analiseEstatistica(root->dir, T, inicio, fim, est);
}

void exibirEstatisticas(const Estatisticas *est) {
    printf("Total de produções no período: %d\n", est->totalProducoes);
    printf("Total de fardos produzidos: %d\n", est->totalFardos);
    printf("Diâmetro médio dos fardos: %.2f\n", est->totalProducoes > 0 ? est->somaDiametros / est->totalProducoes : 0);

    // Exibindo a porcentagem de cada tipo de feno
    printf("Percentual de Feno Tipo A: %.2f%%\n", est->totalProducoes > 0 ? (est->contadorTipoA * 100.0 / est->totalProducoes) : 0);
    printf("Percentual de Feno Tipo B: %.2f%%\n", est->totalProducoes > 0 ? (est->contadorTipoB * 100.0 / est->totalProducoes) : 0);
    printf("Percentual de Feno Tipo C: %.2f%%\n", est->totalProducoes > 0 ? (est->contadorTipoC * 100.0 / est->totalProducoes) : 0);

    // Exibindo a distribuição por cultivar
    printf("Distribuição por Cultivar:\n");
    printf("Tifton 85: %d\n", est->contadorTifton85);
    printf("Florakirk: %d\n", est->contadorFlorakirk);
    printf("Jiggs: %d\n", est->contadorJiggs);
    printf("Coastcross: %d\n", est->contadorCoastcross);
}

int comparaDatas(Data d1, Data d2) {
    if (d1.ano < d2.ano) {
        return -1;
    } else if (d1.ano > d2.ano) {
        return 1;
    } else { // Anos iguais
        if (d1.mes < d2.mes) {
            return -1;
        } else if (d1.mes > d2.mes) {
            return 1;
        } else { // Meses iguais
            if (d1.dia < d2.dia) {
                return -1;
            } else if (d1.dia > d2.dia) {
                return 1;
            } else { // Dias iguais
                return 0;
            }
        }
    }
}

int comparaDatasIguais(Data d1, Data d2) {
    if (d1.ano == d2.ano && d1.mes == d2.mes && d1.dia == d2.dia) {
        return 0; // Datas iguais
    }
    return 1; // Datas diferentes
}

void listarProducoesPorData(NodeRN *root, Data data, arvore *T) {
    if (root == T->sentinela) return;

    // Se a data da produção for igual à data especificada
    if (comparaDatasIguais(root->prod->dataProducao, data) == 0) {
        // Exibir detalhes da produção
        printf("Código: %d, Data: %d/%d/%d, Cultivar: %s, Tipo de Feno: %c, Qtde de Fardos: %d, Duração: %.2f horas\n",
               root->prod->codigo,
               root->prod->dataProducao.dia, root->prod->dataProducao.mes, root->prod->dataProducao.ano,
               root->prod->tipoDeFardo.cultivar,
               root->prod->tipoDeFardo.tipoDeFeno,
               root->prod->qtDeFardos,
               root->prod->duracao);
    }

    // Continuar a busca nas subárvores
    listarProducoesPorData(root->esq, data, T);
    listarProducoesPorData(root->dir, data, T);
}

// Função para verificar se o ano é bissexto
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Função para verificar se a data é válida
bool isValidDate(Data data) {
    if (data.ano < 0 || data.mes < 1 || data.mes > 12 || data.dia < 1) return false;
    int daysInMonth[] = {31, isLeapYear(data.ano) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return data.dia <= daysInMonth[data.mes - 1];
}

// Função para verificar se o tipo de feno é válido
bool isValidFenoType(char tipoDeFeno) {
    return tipoDeFeno == 'A' || tipoDeFeno == 'B' || tipoDeFeno == 'C';
}

// Função para verificar se um número é positivo
bool isPositiveNumber(float number) {
    return number > 0;
}
bool isValidCultivar(char *cultivar) {
    return strcmp(cultivar, "Tifton") == 0 || strcmp(cultivar, "Florakirk") == 0 || strcmp(cultivar, "Jiggs") == 0 || strcmp(cultivar, "Coastcross") == 0;
}