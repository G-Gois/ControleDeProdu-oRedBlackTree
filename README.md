# ControleDeProducaoRedBlackTree
Sistema de Controle de produção de feno utilizando arvore RedBlack e metodo de pesquisa inOrder escrito em C.

Para rodar o sistema buildar utilizando o gcc o seguinte comando:
  gcc -o main main.c producao.c rubroNegra.c -g2


Caracteristicas do sistema:
O sistema utilizou o sistema de arvores redblack para construção de uma arvore parcialmente balanceada para salvar dados baseados em uma chave de ID.
O sistema faz a verificação de todo input necessario, incluindo:
  Verificação de ChaveID já existente na inserção.
  Vericicação de Data avançada, verificando se a quantidade de dias informados para o mês existe (considerando anos bisextos), se o valor do mês está entre 1-12 e se os inputs foram passados corretamente.
  Verificação de numero positivo para dados numericos de produção
  Verificação se o tipo de cultivar é valido (Considerando apenas a inclusão de cultivares Tifton 85, Florakirk, Jiggs e Coastcross)
  Verificação se o tipo de feno é valido (Considerando tipos A, B ou C)
O sistema utilizou as operações de busca InOrder para todas suas operações de busca, sejam com filtro ou não.


Possiveis melhorias para o futuro:
-Melhorar a legibilidade da Main, talvez criando funções para os menus necessarios.
-Foi criado um arquivos Types.h para resolver um problema de declaração das structs serem intedependentes, mas é possivel resolver esse problema declarando corretamente as chamadas de producao.h e rubroNegra.h utilizando #ifndef
