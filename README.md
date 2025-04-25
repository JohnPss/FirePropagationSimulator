# Documentação do Projeto de Simulação de Espalhamento de Fogo e Movimento de Animais

## Introdução

Este projeto implementa uma simulação que modela a propagação de fogo em uma matriz que representa um ambiente em 2D, enquanto um animal tenta se mover dentro desse ambiente. O objetivo principal é observar a interação entre o fogo e o animal, além de registrar a trajetória do animal e as mudanças no ambiente à medida que o fogo se espalha.

A simulação utiliza uma estrutura de dados que representa o ambiente, onde diferentes células podem ser árvores, água, áreas queimadas ou áreas vazias. O código é implementado em **C++** e é estruturado em várias classes e arquivos que encapsulam as funcionalidades específicas.

---

## Metodologia

A metodologia implementada no projeto é dividida em várias etapas:

### Estrutura de Dados

- A classe `MatrixStruct` é usada para armazenar informações sobre a matriz do ambiente, como:
  - Coordenadas iniciais (`initial_x`, `initial_y`)
  - Número de linhas (`rows`) e colunas (`columns`)
  - A própria matriz (`matrix`)

### Espalhamento de Fogo

- A classe `Fire` é responsável pela lógica de propagação do fogo.
- O método `spreadIteration` é invocado em cada iteração da simulação, verificando as células vizinhas e atualizando o estado delas com base na lógica de propagação.

### Movimento do Animal

- A classe `Animal` controla o movimento do animal no ambiente.
- A lógica aplicada considera:
  - Áreas seguras onde o animal pode se mover
  - Registro da trajetória
  - Número de passos dados

### Tratamento de Entrada e Saída

- A classe `FileReader` lida com a entrada e saída de dados:
  - Leitura do estado inicial da matriz a partir de um arquivo
  - Escrita dos resultados da simulação em outro arquivo

### Simulação

- A classe `Simulation` coordena a interação entre as classes `Fire` e `Animal`.
- Invoca os métodos adequados em cada iteração e registra o estado da matriz no arquivo de saída.

### Utilização de Direções e Prioridades

- Direções de movimento e prioridades de terrenos são definidas e utilizadas tanto para:
  - O movimento do animal
  - A propagação do fogo
- Considerando sempre as possíveis direções de risco.

---

## Estudo de Caso / Resultados

A simulação foi testada com diferentes configurações, onde o ambiente foi inicializado com diversas disposições de árvores e água. Os resultados mostraram que o comportamento do fogo e do animal era sensível à configuração inicial da matriz.

### Os dados coletados foram analisados em relação a:

- A taxa de propagação do fogo em áreas densamente arborizadas em comparação com áreas com água.
- A capacidade do animal de encontrar rotas seguras para evitar áreas em chamas.

Os resultados são documentados com um **log** que mostra:

- A trajetória do animal
- O progresso do fogo

As saídas são gravadas em um arquivo `output.dat` para referência futura.

---

## Conclusão

A simulação demonstrou com sucesso a interação entre o fogo e o animal em um ambiente bidimensional. A implementação permitiu visualizar claramente:

- A propagação do fogo
- O movimento do animal diante de diversas condições

As possibilidades de extensões futuras, como a inclusão de vento e outros fatores ambientais, foram identificadas como áreas para melhorias.

---

## Referências


---

## Modo de Compilação

Para compilar e executar o projeto, siga os passos abaixo:



