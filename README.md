<p align="center">
  <img src="https://github.com/JohnPss/FirePropagationSimulator/blob/main/Images/cover.png" alt="Sublime's custom image"/>
</p>




# Documentação do Projeto de Simulação de Espalhamento de Fogo e Movimento de Animais

## Introdução

Projeto desenvolvido para a disciplina de Algoritmos e Estruturas de Dados (AEDS), do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus V – Divinópolis.  Disciplina ministrada pelo professor Michel Pires.

Este projeto implementa uma simulação que modela a propagação de fogo em uma matriz que representa um ambiente em 2D, enquanto um animal tenta se mover dentro desse ambiente. O objetivo principal é observar a interação entre o fogo e o animal, além de registrar a trajetória do animal e as mudanças no ambiente à medida que o fogo se espalha.

A simulação utiliza uma estrutura de dados que representa o ambiente, onde diferentes células podem ser árvores, água, áreas queimadas ou áreas vazias. O código é implementado em **C++** e é estruturado em várias classes e arquivos que encapsulam as funcionalidades específicas.

---


## 📋 Problema proposto

Implementar um simulador de propagação de incêndios em uma floresta representada por uma matriz **N×M**, onde cada célula pode estar em um dos seguintes estados:  
- `0`: Área vazia (não queima)  
- `1`: Árvore saudável  
- `2`: Árvore em chamas  
- `3`: Árvore queimada (não propaga fogo)  
- `4`: Água



### **Funcionalidades** 

 **🔥Propagação do Incêndio🌳**  
O simulador deve implementar as regras de transição de estados, seguindo a sequência (`1 → 2 → 3`). Deve também suportar dois modos de propagação: o modo **sem vento**, onde o fogo se propaga apenas nas quatro direções ortogonais, e o modo **com vento**, onde as direções de propagação podem ser configuradas no arquivo `config.h`.

 **🦌Movimentação do Animal🐾**  
Durante a simulação, o animal deve se movimentar priorizando as células consideradas seguras, obedecendo a ordem de preferência (`4 > 0/1 > 3`). Quando encontrar uma célula de água (`4`), ele deverá transformá-la em área segura (`0`) e regenerar árvores (`1`) nas casas adjacentes. O animal também contará com um mecanismo de "segunda chance" caso seja atingido pelo fogo.

 **📥Entrada/Saída📤**  
A matriz inicial deve ser lida a partir do arquivo `input.dat`. A cada iteração da simulação, o estado da matriz deve ser salvo em `output.dat`, registrando o avanço da propagação do incêndio. Ao final da execução, um relatório deve ser gerado contendo informações sobre os passos percorridos, a quantidade de água encontrada e o status de sobrevivência do animal.


### **📝Requisitos Técnicos** 
O projeto deve ser desenvolvido em **C/C++**, utilizando boas práticas de organização do código, com separação em pastas (`src`, headers). A compilação deverá ser gerenciada via `Makefile`, e o executável precisa ser compatível com sistemas **Linux**. Também é exigida uma análise de desempenho para comparar as diferentes estratégias de propagação do fogo.

---
## 📂Entrada de Dados

#### **📥Arquivo de Entrada (`input.dat`)**
O arquivo de entrada é estruturado da seunte forma, primeira linha contem o tamanho (NxM) da matriz e a posicao inicial do foco do incendio, as demais linhas representam a matriz.
**Exemplo:**  
  ```  
  5 5 1 1  
  1 1 1 1 4  
  1 2 1 1 1  
  1 1 1 1 4  
  0 0 1 1 1  
  1 4 1 0 4  
  ```

## ⚙️ Arquivo de Configuração (`config.hpp`)

O arquivo `config.hpp` define parâmetros globais para controle da simulação.

#### Configurações Disponíveis
   - `WIND_ENABLED`: Ativa (`true`) ou desativa (`false`) a influência do vento na propagação do fogo.
   - `WIND_DIRECTIONS[4]`: Vetor que especifica as direções permitidas para propagação (índices fixos):  
   - `MAX_ITERATIONS`: Número máximo de ciclos da simulação antes do encerramento automático (valor fixo em 1000).

---

#### Exemplo de Configuração
```cpp
const int MAX_ITERATIONS = 1000;          // Limite de 1000 iterações
const bool WIND_ENABLED = false;          // Vento desativado
const bool WIND_DIRECTIONS[4] = {         // Direções habilitadas:
    true,   // Norte ✔️  
    false,  // Sul ❌  
    false,  // Oeste ❌  
    false   // Leste ❌
};
```


## 📚Metodologia

A metodologia implementada no projeto é dividida em várias etapas:

### 🧩 Estrutura de Dados

- A classe `MatrixStruct` é usada para armazenar informações sobre a matriz do ambiente, como:
  - Coordenadas iniciais (`initial_x`, `initial_y`)
  - Número de linhas (`rows`) e colunas (`columns`)
  - A própria matriz (`matrix`)



### 🐾 Movimento do Animal

A classe `Animal` é responsável, principalmente, pela lógica de movimentação do animal. Nela, são implementados métodos como `moveAnimal`, que concentra a lógica principal de deslocamento.
O animal inicia a simulação buscando uma célula segura, que pode ser:

  - **4**: Água
-   **1**: Árvore saudável  
-   **0**: Área vazia
   

Ele se estabelece na primeira célula segura que encontrar na matriz.

Foi implementada uma regra de movimentação em que o animal analisa as casas adjacentes e verifica suas prioridades. Se houver duas ou mais casas com a maior prioridade entre as adjacentes, a movimentação é escolhida aleatoriamente entre elas. Caso exista apenas uma casa com a maior prioridade, o animal se move automaticamente para essa casa.

```cpp
bool funcao moveAnimal()
	/*Seção do código encarregada de verificar as posições ortogonais e inserir em 
	`candidateCells` aquelas que forem válidas, respeitando os limites da matriz e as 
	prioridades definidas para as células.
*/
	...
	se há candidateCells:
        escolher posição_aleatória em candidateCells
        retorne true
    senão:
        retorne false
```


### 🔥 Espalhar Fogo

A classe `Fire` é responsável por gerenciar a propagação do incêndio na matriz da floresta, seguindo regras de propagação configuráveis (com ou sem vento). Abaixo estão os detalhes técnicos:

```cpp
bool spreadIteration()  
    Se burningQueue vazia → retorna false  
    Para cada célula na fila:  
        Se é a primeira queima:  
            Marca como 2  
            Propaga fogo aos vizinhos (processSpread)  
        Senão:  
            Marca como 3  
    Atualiza fila para próxima iteração  
    Retorna true se houver células restantes  
```

A função  `spreadIteration` controla a evolução do incêndio em uma iteração da simulação. Ela processa as células em chamas armazenadas na fila `burningQueue`, atualizando seu estado: células queimando pela primeira vez são marcadas como `2` (em chamas) e propagam o fogo para vizinhas válidas (via `processSpread`), enquanto células já queimadas são atualizadas para `3` (totalmente queimadas) e removidas do ciclo. Novos focos são armazenados em `nextSpread` e transferidos para `burningQueue`, garantindo a continuidade da propagação na próxima iteração. A função retorna `true` se houver células ativas, mantendo a simulação em execução, ou `false` quando o fogo se extingue. A configuração do vento é aplicada durante a propagação, limitando direções permitidas.

```cpp
void processSpread(x, y):  
    para cada direção em [Norte, Sul, Oeste, Leste] faça:  
        se (VENTO_ATIVO E direção não está em DIRECOES_DO_VENTO):  
            pule esta direção  
        
        newX = x + offsetX[direção]   
        newY = y + offsetY[direção]    
                
        se (newX, newY está dentro dos limites E matriz[newX][newY] == 1):  
            matriz[newX][newY] = 2    
            adicione (newX, newY) à lista nextSpread   
```


	


### 🖨️ Tratamento de Saída de Dados

- A classe `FileReader` lida com a entrada e saída de dados:
  - Leitura do estado inicial da matriz a partir de um arquivo
  - Escrita dos resultados da simulação em outro arquivo


#### **Arquivo de Saída (`output.dat`)**

O arquivo de saída registra a representação da matriz a cada interação, ilustrando a propagação do fogo.

**Exemplo:**  
  ```  
Iteração 1:
  1 2 1 1 4  
  2 2 2 1 1  
  1 2 1 1 4  
  0 0 1 1 1  
  1 4 1 0 4  
  ```

Após o término da propagação do fogo ou ao atingir o número máximo definido de interações, é gerado no arquivo de saída um relatório final com informações sobre o animal.

 **Exemplo:**  
- Caminho percorrido pelo animal (coordenadas em sequência).  
- Passos totais.  
- Número de vezes que encontrou água.  
- Iteração em que foi cercado (se aplicável).  
- Status de sobrevivência (`Sim` ou `Não`).

### 🖥️Simulação

- A classe `Simulation` coordenar a execução da simulação, integrando a propagação do incêndio e a movimentação do animal, além de gerenciar o fluxo de iterações e condições de término.

#### 🎬Inicialização:  
   - Cria os objetos `Fire` (fogo) e `Animal` (animal), carregando a matriz da floresta e definindo parâmetros iniciais.  
   - Abre o arquivo de saída para registro de logs.  

#### 🔄Loop de Iterações:  
   - Executa até atingir o número máximo de iterações (`MAX_ITERATIONS`) ou até o fogo se extinguir.  
   - Etapas por Iteração:  
     - Movimentação do Animal: O animal se move (se ainda estiver vivo).  
     - Propagação do Fogo: Atualiza o estado das células em chamas e registra mudanças.  
     - Verificação de Perigo: Se o animal está em uma célula em chamas, aciona a "segunda chance" de fuga.  

#### 🏁Condições de Término:  
   - Fogo Extinto: Interrompe a simulação se não houver mais células em chamas.  
   - Animal Preso: Registra a iteração em que o animal foi cercado pelo fogo.  

#### Resultados Finais:
   - Salva o mapa de frequência do caminho do animal (`animalPathMap.dat`).  
   - Gera relatório final com métricas de sobrevivência, passos e água encontrada.

Essa classe é o núcleo da simulação, sincronizando todas as componentes e garantindo a execução ordenada das regras definidas no problema.

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

![](Images/simulationGif.gif)

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

