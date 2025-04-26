### Caso de Teste: Com Aplicação do Vento

Este caso de teste valida o comportamento da propagação do fogo e da movimentação do animal quando a influência do vento é ativada. No arquivo Config.cpp, a configuração de vento está habilitada, e as direções do vento são definidas como Norte (cima) e Oeste (esquerda).

Arquivo Config.cpp:
```cpp
const int MAX_ITERATIONS = 1000;
const bool WIND_ENABLED = true;
// Índices: 0 = Norte (cima), 1 = Sul (baixo), 2 = Oeste (esquerda), 3 = Leste (direita)
const bool WIND_DIRECTIONS[4] = {true, false, true, false};
```