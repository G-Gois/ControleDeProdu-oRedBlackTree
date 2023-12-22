#include <stdio.h>
#include <string.h>
#include "types.h"
#include "producao.h"
#include "rubroNegra.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    int escolha;
    arvore *T = createArvore();

    do {
        printf("\nMenu:\n");
        printf("1. Incluir Produção\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("5. Listar todos\n");
        printf("6. Análise Estatística\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        clearInputBuffer();

        switch (escolha) {

            case 1: {
                Producao *novaProducao;
                int codigo, qtDeFardos, diametro;
                char cultivar[20], tipoDeFeno;
                float duracao;
                Data data;

                printf("Digite o código da produção: ");
                scanf("%d", &codigo);
                clearInputBuffer();
                if (searchRN(T, T->raiz, codigo) != NULL) {
                    printf("Erro: Código de produção %d já existe.\n", codigo);
                    break;
                }

                printf("Digite a data (dd mm aaaa): ");
                scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
                clearInputBuffer();

                if (!isValidDate(data) || (!isPositiveNumber(data.dia) || !isPositiveNumber(data.mes) || !isPositiveNumber(data.ano))) {
                    printf("Data inválida.\n");
                    break;
                }

                printf("Digite o cultivar (Tifton 85, Florakirk, Jiggs, Coastcross): ");
                scanf("%s", cultivar);
                clearInputBuffer();
                if (!isValidCultivar(cultivar)) {
                    printf("Cultivar inválido.\n");
                    break;
                }

                printf("Digite o tipo de feno (A, B, C): ");
                scanf(" %c", &tipoDeFeno);
                clearInputBuffer();
                if (!isValidFenoType(tipoDeFeno)) {
                    printf("Tipo de feno inválido.\n");
                    break;
                }

                printf("Digite o diâmetro do fardo: ");
                scanf("%d", &diametro);
                clearInputBuffer();
                if (!isPositiveNumber(diametro)) {
                    printf("Valores numéricos devem ser positivos.\n");
                    break;
                }

                printf("Digite a quantidade de fardos: ");
                scanf("%d", &qtDeFardos);
                clearInputBuffer();

                if ( !isPositiveNumber(qtDeFardos)){
                    printf("Valores numéricos devem ser positivos.\n");
                    break;
                }

                printf("Digite a duração (em horas): ");
                scanf("%f", &duracao);
                clearInputBuffer();

                if ( !isPositiveNumber(duracao)) {
                    printf("Valores numéricos devem ser positivos.\n");
                    break;
                }

                Fardo fardo = { .cultivar = "", .tipoDeFeno = tipoDeFeno, .diametro = diametro };
                strcpy(fardo.cultivar, cultivar); // Copiando o cultivar para evitar overflow

                novaProducao = criarProducaoRB(codigo, data, fardo, qtDeFardos, duracao);
                inserirProducao(T, novaProducao);

                printf("Produção incluída com sucesso!\n");
                break;
            }

            case 2: {
                int opcaoConsulta;
                do {
                    printf("Opções de Consulta:\n");
                    printf("1. Consultar Período\n");
                    printf("2. Consultar Cultivar\n");
                    printf("3. Consultar Tipo de Feno\n");
                    printf("4. Voltar ao Menu Principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoConsulta);
                    clearInputBuffer();


                    switch (opcaoConsulta) {
                        case 1: {
                            Data dataInicio, dataFim;
                            printf("Digite a data de início (dd mm aaaa): ");
                            scanf("%d %d %d", &dataInicio.dia, &dataInicio.mes, &dataInicio.ano);
                            clearInputBuffer();
                            if (!isValidDate(dataInicio)|| (!isPositiveNumber(dataInicio.dia) || !isPositiveNumber(dataInicio.mes) || !isPositiveNumber(dataInicio.ano))){
                                printf("Data inválida.\n");
                                break;
                            }


                            printf("Digite a data de fim (dd mm aaaa): ");
                            scanf("%d %d %d", &dataFim.dia, &dataFim.mes, &dataFim.ano);
                            clearInputBuffer();
                            if (!isValidDate(dataFim)|| (!isPositiveNumber(dataFim.dia) || !isPositiveNumber(dataFim.mes) || !isPositiveNumber(dataFim.ano))){
                                printf("Data inválida.\n");
                                break;
                            }


                            consultarProducaoPorPeriodo(T->raiz, dataInicio, dataFim, T);
                            break;
                        }
                        case 2: {
                            char cultivar[20];
                            printf("Digite o cultivar (Tifton 85, Florakirk, Jiggs, Coastcross): ");
                            scanf("%s", cultivar);
                            clearInputBuffer();
                            if (!isValidCultivar(cultivar)) {
                                printf("Cultivar inválido.\n");
                                break;
                            }
                            consultarPorCultivar(T->raiz, cultivar, T);
                            break;
                        }
                        case 3: {
                            char tipoDeFeno;
                            printf("Digite o tipo de feno (A, B, C): ");
                            scanf(" %c", &tipoDeFeno);
                            clearInputBuffer();
                            if (!isValidFenoType(tipoDeFeno)) {
                                printf("Tipo de feno inválido.\n");
                                break;
                            }

                            consultarPorTipoDeFeno(T->raiz, tipoDeFeno, T);
                            break;
                        }
                        case 4:
                            printf("Voltando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção inválida! Por favor, escolha uma opção de 1 a 4.\n");
                    }
                } while (opcaoConsulta != 4);
                break;
            }


            case 3: {
                Data data;
                int codigo;

                printf("Digite a data para alterar produções (dd mm aaaa): ");
                scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
                clearInputBuffer();
                if (!isValidDate(data) || (!isPositiveNumber(data.dia) || !isPositiveNumber(data.mes) || !isPositiveNumber(data.ano))) {
                    printf("Data inválida.\n");
                    break;
                }

                printf("Produções na data %02d/%02d/%04d:\n", data.dia, data.mes, data.ano);
                listarProducoesPorData(T->raiz, data, T);

                printf("Digite o código da produção que deseja alterar: ");
                scanf("%d", &codigo);
                clearInputBuffer();

                Producao *dadosAtualizados = (Producao*) malloc(sizeof(Producao));
                if (dadosAtualizados == NULL) {
                    printf("Erro de alocação de memória.\n");
                    break;
                }

                printf("Digite os novos dados da produção:\n");
                printf("Digite o cultivar: ");
                scanf("%s", dadosAtualizados->tipoDeFardo.cultivar);
                clearInputBuffer();
                if(!isValidCultivar(dadosAtualizados->tipoDeFardo.cultivar)){
                    printf("Cultivar inválido.\n");
                    free(dadosAtualizados);
                    break;
                }
                printf("Digite o tipo de feno (A, B, C): ");
                scanf(" %c", &dadosAtualizados->tipoDeFardo.tipoDeFeno);
                clearInputBuffer();
                if(!isValidFenoType(dadosAtualizados->tipoDeFardo.tipoDeFeno)){
                    printf("Tipo de feno inválido.\n");
                    free(dadosAtualizados);
                    break;
                }
                printf("Digite o diâmetro do fardo: ");
                scanf("%d", &dadosAtualizados->tipoDeFardo.diametro);
                clearInputBuffer();
                if (!isPositiveNumber(dadosAtualizados->tipoDeFardo.diametro)) {
                    printf("Valor numérico deve ser positivo.\n");
                    free(dadosAtualizados);
                    break;
                }
                printf("Digite a quantidade de fardos: ");
                scanf("%d", &dadosAtualizados->qtDeFardos);
                clearInputBuffer();
                if (!isPositiveNumber(dadosAtualizados->qtDeFardos)) {
                    printf("Valor numérico deve ser positivo.\n");
                    free(dadosAtualizados);
                    break;
                }
                printf("Digite a duração (em horas): ");
                scanf("%f", &dadosAtualizados->duracao);
                clearInputBuffer();
                if (!isPositiveNumber(dadosAtualizados->duracao)) {
                    printf("Valor numérico deve ser positivo.\n");
                    free(dadosAtualizados);
                    break;
                }

                alterarProducao(T, codigo, dadosAtualizados);

                free(dadosAtualizados);

                printf("Produção alterada com sucesso!\n");
                break;
            }

            case 4: {
                Data data;
                int codigo;

                printf("Digite a data para excluir produções (dd mm aaaa): ");
                scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
                clearInputBuffer();
                if (!isValidDate(data) || (!isPositiveNumber(data.dia) || !isPositiveNumber(data.mes) || !isPositiveNumber(data.ano))) {
                    printf("Data inválida.\n");
                    break;
                }
                printf("Produções na data %02d/%02d/%04d:\n", data.dia, data.mes, data.ano);
                listarProducoesPorData(T->raiz, data, T);
                clearInputBuffer();

                printf("Digite o código da produção que deseja excluir: ");
                scanf("%d", &codigo);
                clearInputBuffer();

                excluirProducao(T, codigo);

                printf("Produção excluída com sucesso!\n");
                break;
            }

            case 5: {
                printf("Listando todas as produções:\n");
                listarProducoes(T->raiz, T);
                break;
            }

            case 6: {
                Data dataInicio, dataFim;
                Estatisticas estatisticas;

                printf("Digite a data de início (dd mm aaaa): ");
                scanf("%d %d %d", &dataInicio.dia, &dataInicio.mes, &dataInicio.ano);
                clearInputBuffer();
                if (!isValidDate(dataInicio)||!isPositiveNumber(dataInicio.dia) || !isPositiveNumber(dataInicio.mes) || !isPositiveNumber(dataInicio.ano)) {
                    printf("Data inválida.\n");
                    break;
                }
                printf("Digite a data de fim (dd mm aaaa): ");
                scanf("%d %d %d", &dataFim.dia, &dataFim.mes, &dataFim.ano);
                clearInputBuffer();
                if (!isValidDate(dataFim)||!isPositiveNumber(dataFim.dia) || !isPositiveNumber(dataFim.mes) || !isPositiveNumber(dataFim.ano)) {
                    printf("Data inválida.\n");
                    break;
                }

                inicializaEstatisticas(&estatisticas);
                analiseEstatistica(T->raiz, T, dataInicio, dataFim, &estatisticas);
                exibirEstatisticas(&estatisticas);

                break;
            }

            case 7:
                printf("Encerrando o programa.\n");
                liberarMemoria(T->raiz, T);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 7);

    return 0;
}
