# III Desafio em Otimização com Metaheurística
- **Nome da equipe:** The Otimization Hunter:  Metaheuristics
- **Equipe:** Enzo Moura de Rezende e Pedro Paulo Gomes do Carmo

## 1. Introdução

O Problema de Job Shop envolve um conjunto de jobs (trabalhos) que devem ser processados por um conjunto de máquinas, cada um com uma sequência fixa de operações. Cada operação deve ser processada por uma máquina específica durante um tempo específico.
O objetivo é encontrar a sequência de operações nas máquinas de forma a minimizar o tempo total necessário para concluir todos os jobs (makespan), obedecendo às restrições de precedência e disponibilidade das máquinas.

## 2. Descrição do Hardware e Software Utilizados

**Hardware:**
- Processador: Intel Core i5 4ª geração.
- Memória RAM: 8 GB.
- Armazenamento: SSD 256 GB.

**Software:**
- Sistema Operacional: Ubuntu 18.04 LTS.
- Linguagem de Programação: C++.
- Bibliotecas Utilizadas:
  - `bits/stdc++.h` para o uso de estruturas de dados, rand e srand.

## 3. Instâncias Utilizadas

As instâncias empregadas nos experimentos são as fornecidas pela comissão organizadora, correspondendo ao Problema de Empacotamento Unidimensional (_Bin Packing_). As instâncias estão disponíveis no seguinte link:(https://drive.google.com/drive/folders/1Nyv_E_bHiubAvDVJXY5vvWFIbvHTzAU4?usp=sharing)

## 4. Descrição Detalhada da Metaheurística

### 4.1. GRASP (Greedy Randomized Adaptive Search Procedure)
O GRASP constrói soluções iterativamente, escolhendo elementos de uma Lista de Candidatos Restritos (RCL) que contém os elementos mais promissores em cada passo. A aleatoriedade na escolha dentro da RCL permite explorar o espaço de busca e escapar de ótimos locais.

### 4.2. VNS (Variable Neighborhood Search)
O VNS explora o espaço de busca de forma sistemática, alternando entre diferentes estruturas de vizinhança. Essa estratégia permite escapar de ótimos locais e refinar a solução obtida pelo GRASP.

### 4.3. Híbrido GRASP-VNS
Na implementação híbrida, o GRASP gera uma solução inicial de boa qualidade, que é então refinada pelo VNS. A combinação dessas duas técnicas busca explorar a capacidade de gerar soluções iniciais diversificadas do GRASP e a capacidade de exploração local do VNS.

### 4.4 Fundamentação Teórica

Utilizamos uma abordagem híbrida que combina o **GRASP** (_Greedy Randomized Adaptive Search Procedure_) com a **VNS** (_Variable Neighbourhood Search_) para resolver o Problema de Empacotamento Unidimensional (_Bin Packing_). O GRASP é responsável por gerar uma solução inicial, enquanto o VNS refina as últimas partes da solução para reduzir o desperdício de espaço, minimizando a altura da empacotagem.

### 4.5 Implementação e Adaptações

O algoritmo foi implementado seguindo as diretrizes do artigo "GRASP-VNS hybrid for the Strip Packing Problem"[1]. Na fase de construção, a lista de candidatos restritos é gerada para permitir a escolha aleatória de elementos promissores. A fase de busca local utiliza o VNS para refinar as soluções.

**Adaptações:**
- O algoritmo foi ajustado para obter a junção da Meta-Heuristica Grasp com a VNS.
- Implementamos a aleatoriedade com base em seed de tempo.
- Implementamos uma função de ajuste de contorno para melhorar a eficiência no empacotamento.

### 4.6 Variações Testadas

Foram testadas diferentes variações do valor do parâmetro **α** que controla a seleção de elementos na lista de candidatos restritos (RCL) do GRASP:
- **α = 0**: Melhor restrição.
- **α = 1**: Ajuste com uma abordagem gulosa.
- **α = 0.6**: Seleção mais relaxada de candidatos em relação a gulosa.

### 4.7 Justificativa para as Escolhas

A escolha pelo híbrido GRASP-VNS se baseia em sua robustez e bom desempenho em problemas de otimização combinatória. A combinação do GRASP para gerar soluções iniciais diversificadas com a capacidade de busca local do VNS busca um equilíbrio entre exploração e intensificação.

### 4.8 Parâmetros Utilizados

- **Número de iterações (niter):** 100 iterações para garantir a convergência.
- **Tamanho da lista de candidatos restritos (RCL):** Baseada em uma fração **α** dos melhores candidatos.
- **Tamanho da vizinhança (VNS):** Vizinhanças variando de **k = 1** a **k = 100**, aumentando progressivamente com a dificuldade do problema.

## 5. Resultados

Os resultados obtidos pelo GRASP-VNS, GRASP puro e VNS puro são apresentados na tabela abaixo. O desempenho do GRASP-VNS foi superior em relação aos outros dois algoritmos em termos de otimização, principalmente para instâncias maiores. 

| Instância | GRASP | VNS | GRASP-VNS |
|-----------|-------|-----------|--------|
|    Exemplo do Edital    | 4 | 4 | 3 |
| BPP_50_50_0.1_0.7_0.txt | 30 | 39 | 26 |
| BPP_50_75_0.2_0.8_7.txt | 34 | 42 | 29 |
| BPP_100_75_0.1_0.7_8.txt | 48 | 72 | 42 |
|BPP_200_150_0.1_0.7_4.txt | 104 | 164 | 91 |
| BPP_1000_50_0.1_0.7_5.txt | 456 | 827 | 444 |
| BPP_1000_1000_0.2_0.8_5.txt | 616 | 984 | 588 |
| HARD0.txt | 62 | 154 | 60 |
| N1W4B1R7.txt| 6 | 12 | 6 |
| N2W3B1R2.txt | 16 | 56 | 15 |
| N3W3B1R8.txt | 29 | 87 | 30 |
| Falkenauer_t60_00.txt | 23 | 34 | 22 |
| Falkenauer_t249_00.txt | 110 | 224 | 91 |
| Falkenauer_u500_00.txt | 240 | 439 | 217 |
| Falkenauer_u1000_09.txt | 450 | 768 | 437 |
| 201_2500_DI_22.txt | 83 | 139 | 70 |
| 402_10000_DI_32.txt | 155 | 275 | 145 |
| 600_20000_DI_31.txt | 246 | 422 | 217 |
| 801_40000_DI_33.txt | 313 | 593 | 289 |
| 1002_80000_NR_19.txt | 395 | 711 | 362 |

## 6. Discussão

O GRASP-VNS apresentou um desempenho ligeiramente superior em termos de otimização para o problema de Bin Packing, superando tanto o GRASP puro quanto o VNS puro na maioria das instâncias testadas. A sinergia entre a capacidade de gerar soluções iniciais diversificadas do GRASP e a busca local eficiente do VNS contribuiu para o bom desempenho do algoritmo híbrido.

## 7. Conclusões
A utilização do algoritmo híbrido GRASP-VNS se mostrou uma estratégia eficaz para a resolução do problema de Bin Packing. Os resultados obtidos demonstram o potencial da técnica para encontrar soluções de alta qualidade em um tempo computacional razoável.

## 8. Referências
- [1] Beltrán, J. D., Calderón, J. E., Cabrera, R. J., Pérez, J. A. M., & Moreno-Vega, J. M. (2004). **GRASP-VNS hybrid for the Strip Packing Problem**. In Proceedings of the 4th Metaheuristics International Conference (pp. 417-421).
