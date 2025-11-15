Projeto: Campo Minado
Integrantes: Christiano, Joao Francisco, Gabriel Felicio

Visão Geral do Jogo (resumida)
    O objetivo do Campo Minado é abrir todos os quadrados do tabuleiro que não têm bomba. Você perde se abrir uma bomba. O jogo mostra números nas casas abertas para ajudar a deduzir onde estão as bombas, e o jogador pode marcar os lugares que acha que têm bomba.​​


Estrutura de Dados Utilizada
    Matriz de inteiros (por exemplo, campoBombas[MAX_LINHAS][MAX_COLUNAS]) para representar o tabuleiro.
    Cada informação importante tem sua própria matriz:

    campoBombas: onde as bombas estão (1 = tem bomba, 0 = não tem)
    campoAberto: se a casa já foi aberta pelo jogador (1 = aberta, 0 = fechada)
    campoBandeira: se está marcada por uma bandeira (1 = tem bandeira, 0 = não)
    campoVizinhos: quantas bombas existem nas casas vizinhas

Por que matriz?
    Usar matriz é simples para acessar cada quadrado do tabuleiro (linha e coluna), facilita checar casas vizinhas e é rápida para trabalhar, porque o campo é sempre um retângulo de quadrados.
    Todas as informações do estado do jogo (bomba, números, aberto/fechado, bandeira) podem ser separadas e manipuladas de forma clara.

Preenchimento da Estrutura de Dados
    Posição das minas:
    O programa sorteia posições aleatórias para cada bomba.
    Antes de colocar uma, verifica se já há bomba na posição. Repete até todas as bombas serem posicionadas.

Contagem de minas vizinhas:
    Para cada casa do tabuleiro, o programa conta quantas bombas existem nas casas ao lado (incluindo diagonais).
    Esse número é salvo na matriz campoVizinhos.

Fluxo de Entrada de Dados
    O usuário, em cada rodada, informa AÇÃO (R para revelar, F para bandeira), LINHA (número), e COLUNA (letra), tudo separados.
    O programa verifica se a ação está correta, se os números são válidos conforme o tamanho do tabuleiro, e se a letra da coluna existe. Se algo estiver errado, pede novamente até digitar certo, mostrando uma mensagem do tipo "Opção inválida".

Visualização para o Usuário
    O tabuleiro aparece desenhado no terminal, com números para linhas e letras para colunas.

Cada célula pode ter:
    ~ : casa fechada (não aberta)
    F : bandeira do jogador
    número 1-8 : quantidade de bombas ao redor (em casa aberta)
    espaço em branco : casa aberta sem bombas vizinhas
    X : bomba explodida (só aparece ao perder o jogo)

O jogo sempre exibe o estado mais atualizado a cada jogada, facilitando saber onde está seguro e onde é suspeito de bomba.
