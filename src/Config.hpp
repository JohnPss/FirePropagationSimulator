#pragma once

const int MAX_ITERATIONS = 1000;

// Configuração do vento
const bool WIND_ENABLED = false; // Habilita/desabilita a influência do vento

// Índices: 0 = Norte (cima), 1 = Sul (baixo), 2 = Oeste (esquerda), 3 = Leste (direita)
const bool WIND_DIRECTIONS[4] = {true, false, true, false}; // Exemplo: vento sopra para norte e oeste
