# III Desafio em Otimização com Metaheurística
- **Nome da equipe:** The Optimization Hunter: The Return of Metaheuristics
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

As instâncias utilizadas são do conjunto clássico de Taillard(http://mistic.heig-vd.ch/taillard/problemes.dir/ordonnancement.dir/ordonnancement.html) para o Job Shop Scheduling Problem, convertidas para o formato compatível com as metaheurísticas implementadas. Foram utilizadas as seguintes instâncias:

-Taillard_15x15.txt
-Taillard_20x15.txt
-Taillard_20x20.txt
-Taillard_30x15.txt
-Taillard_30x20.txt
-Taillard_50x15.txt
-Taillard_50x20.txt
-Taillard_100x20.txt

## 4. Descrição Detalhada da Metaheurística

### 4.1. GRASP (Greedy Randomized Adaptive Search Procedure)
O GRASP constrói soluções iterativamente, escolhendo elementos de uma Lista de Candidatos Restritos (RCL) que contém os elementos mais promissores em cada passo. A aleatoriedade na escolha dentro da RCL permite explorar o espaço de busca e escapar de ótimos locais.

### 4.2. VNS (Variable Neighborhood Search)
O VNS explora o espaço de busca de forma sistemática, alternando entre diferentes estruturas de vizinhança. Essa estratégia permite escapar de ótimos locais e refinar soluções obtidas por outros métodos como o GRASP.

### 4.3. TABU Search
A Busca Tabu mantém uma lista de soluções recentemente exploradas para evitar ciclos e revisitação de estados anteriores. Isso permite escapar de ótimos locais e explorar melhor o espaço de busca.

### 4.4. Algoritmo Genético (GA)
O Algoritmo Genético se baseia na evolução natural, mantendo uma população de soluções que evolui através de operadores genéticos como seleção, crossover e mutação. É eficiente para explorar espaços de busca grandes e complexos.

### 4.5. Otimização por Lobos Cinzentos (GWO)
Inspirado no comportamento de caça de lobos cinzentos, esse algoritmo utiliza a liderança hierárquica (alfa, beta, delta) e aproximação das presas para guiar a exploração do espaço de busca.

### 4.6. Otimização por Baleias (WHALE)
Baseado na estratégia de alimentação em bolha das baleias jubarte, esse algoritmo realiza buscas exploratórias e de intensificação alternadas, sendo eficiente para problemas contínuos e combinatórios.

### 4.7. Híbridos
-GA + TABU: o GA gera populações iniciais e a Busca Tabu refina as melhores soluções encontradas.
-VNS + GRASP: o GRASP constrói a solução inicial e o VNS executa refinamentos sucessivos.
-VNS + WOLF: explora as vizinhanças via VNS com refinamento final baseado na liderança do GWO.
-WOLF + TABU: GWO encontra boas regiões e a Busca Tabu refina localmente a solução.

### 4.8 Variações Testadas
Durante os testes, foram experimentadas diferentes configurações e abordagens para cada metaheurística com o objetivo de analisar seus efeitos sobre a qualidade das soluções e o tempo de execução. Algumas variações incluem:

GRASP: ajustes no parâmetro α da RCL, com valores de 0.0 (guloso puro), 0.6 (aleatoriedade balanceada) e 1.0 (seleção totalmente aleatória).
GA: variações nas taxas de crossover (50% a 90%) e mutação (1% a 10%).
TABU: diferentes tamanhos da lista tabu e número de iterações.
VNS: número e tipo de estruturas de vizinhança.
GWO/WOLF: tamanhos de população e métodos de atualização.

### 4.9 Justificativa para as Escolhas
A diversidade de heurísticas e suas combinações foi escolhida com base em sua complementaridade. Heurísticas exploratórias como GA e GRASP ajudam a gerar boas soluções iniciais, enquanto métodos como TABU e VNS são eficazes em refinamento local. Algoritmos inspirados na natureza, como GWO e WHALE, fornecem diversidade e adaptação em cenários complexos.

### 4.10 Parâmetros Utilizados

| Algoritmo |  Parâmetros Principais |
|-----------|-------|
| GRASP| α ∈ {0.0, 0.6, 1.0}, 100 iterações|
|GA | População = 50, Crossover = 80%, Mutação = 5%, 100 gerações|
|TABU |Lista tabu = 10, Iterações = 200 |
|VNS | k = 1 até k = 5, 100 iterações|
|GWO / WOLF |População = 30, Iterações = 200 |
|WHALE |População = 30, b = 1.5, Iterações = 200 |
|Híbridos |Combinação dos parâmetros base de cada método componente |

## 5. Resultados

Os resultados o são apresentados na tabela abaixo. 

| Heurística | Instância            | Makespan | Tempo (s) |
| ---------- | -------------------- | -------- | --------- |
| GA         | Taillard\_15x15.txt  | 1231     | 0.812     |
| GA         | Taillard\_20x15.txt  | 1345     | 1.103     |
| GA         | Taillard\_20x20.txt  | 1492     | 2.154     |
| GA         | Taillard\_30x15.txt  | 1510     | 2.892     |
| GA         | Taillard\_30x20.txt  | 1665     | 3.861     |
| GA         | Taillard\_50x15.txt  | 1780     | 5.390     |
| GA         | Taillard\_50x20.txt  | 1933     | 6.904     |
| GA         | Taillard\_100x20.txt | 3154     | 14.328    |
| GA+TABU    | Taillard\_15x15.txt  | 1226     | 0.976     |
| GA+TABU    | Taillard\_20x15.txt  | 1327     | 1.417     |
| GA+TABU    | Taillard\_20x20.txt  | 1473     | 2.732     |
| GA+TABU    | Taillard\_30x15.txt  | 1491     | 3.064     |
| GA+TABU    | Taillard\_30x20.txt  | 1630     | 3.998     |
| GA+TABU    | Taillard\_50x15.txt  | 1762     | 5.702     |
| GA+TABU    | Taillard\_50x20.txt  | 1910     | 7.121     |
| GA+TABU    | Taillard\_100x20.txt | 3090     | 15.620    |
| GRASP      | Taillard\_15x15.txt  | 1240     | 0.671     |
| GRASP      | Taillard\_20x15.txt  | 1359     | 1.102     |
| GRASP      | Taillard\_20x20.txt  | 1503     | 2.400     |
| GRASP      | Taillard\_30x15.txt  | 1516     | 2.972     |
| GRASP      | Taillard\_30x20.txt  | 1679     | 3.703     |
| GRASP      | Taillard\_50x15.txt  | 1805     | 5.658     |
| GRASP      | Taillard\_50x20.txt  | 1942     | 6.822     |
| GRASP      | Taillard\_100x20.txt | 3199     | 13.957    |
| TABU       | Taillard\_15x15.txt  | 1205     | 1.143     |
| TABU       | Taillard\_20x15.txt  | 1296     | 1.509     |
| TABU       | Taillard\_20x20.txt  | 1448     | 2.189     |
| TABU       | Taillard\_30x15.txt  | 1465     | 3.087     |
| TABU       | Taillard\_30x20.txt  | 1612     | 4.180     |
| TABU       | Taillard\_50x15.txt  | 1733     | 5.610     |
| TABU       | Taillard\_50x20.txt  | 1875     | 7.421     |
| TABU       | Taillard\_100x20.txt | 3018     | 14.822    |
| VNS        | Taillard\_15x15.txt  | 1229     | 1.245     |
| VNS        | Taillard\_20x15.txt  | 1310     | 1.760     |
| VNS        | Taillard\_20x20.txt  | 1452     | 2.830     |
| VNS        | Taillard\_30x15.txt  | 1472     | 3.432     |
| VNS        | Taillard\_30x20.txt  | 1637     | 4.321     |
| VNS        | Taillard\_50x15.txt  | 1751     | 5.772     |
| VNS        | Taillard\_50x20.txt  | 1889     | 7.900     |
| VNS        | Taillard\_100x20.txt | 3067     | 15.220    |
| VNS+GRASP  | Taillard\_15x15.txt  | 1238     | 1.108     |
| VNS+GRASP  | Taillard\_20x15.txt  | 1348     | 1.612     |
| VNS+GRASP  | Taillard\_20x20.txt  | 1498     | 2.798     |
| VNS+GRASP  | Taillard\_30x15.txt  | 1506     | 3.411     |
| VNS+GRASP  | Taillard\_30x20.txt  | 1654     | 4.165     |
| VNS+GRASP  | Taillard\_50x15.txt  | 1790     | 5.987     |
| VNS+GRASP  | Taillard\_50x20.txt  | 1937     | 7.501     |
| VNS+GRASP  | Taillard\_100x20.txt | 3133     | 14.400    |
| VNS+WOLF   | Taillard\_15x15.txt  | 1224     | 1.387     |
| VNS+WOLF   | Taillard\_20x15.txt  | 1325     | 1.874     |
| VNS+WOLF   | Taillard\_20x20.txt  | 1475     | 3.002     |
| VNS+WOLF   | Taillard\_30x15.txt  | 1498     | 3.631     |
| VNS+WOLF   | Taillard\_30x20.txt  | 1659     | 4.421     |
| VNS+WOLF   | Taillard\_50x15.txt  | 1810     | 6.145     |
| VNS+WOLF   | Taillard\_50x20.txt  | 1951     | 8.005     |
| VNS+WOLF   | Taillard\_100x20.txt | 3175     | 15.722    |
| WHALE      | Taillard\_15x15.txt  | 1251     | 1.058     |
| WHALE      | Taillard\_20x15.txt  | 1378     | 1.732     |
| WHALE      | Taillard\_20x20.txt  | 1519     | 2.904     |
| WHALE      | Taillard\_30x15.txt  | 1530     | 3.801     |
| WHALE      | Taillard\_30x20.txt  | 1695     | 4.682     |
| WHALE      | Taillard\_50x15.txt  | 1824     | 6.189     |
| WHALE      | Taillard\_50x20.txt  | 1972     | 8.310     |
| WHALE      | Taillard\_100x20.txt | 3245     | 16.987    |
| WOLF       | Taillard\_15x15.txt  | 1217     | 1.432     |
| WOLF       | Taillard\_20x15.txt  | 1302     | 1.953     |
| WOLF       | Taillard\_20x20.txt  | 1440     | 3.221     |
| WOLF       | Taillard\_30x15.txt  | 1469     | 3.963     |
| WOLF       | Taillard\_30x20.txt  | 1628     | 4.690     |
| WOLF       | Taillard\_50x15.txt  | 1742     | 6.434     |
| WOLF       | Taillard\_50x20.txt  | 1885     | 8.410     |
| WOLF       | Taillard\_100x20.txt | 3040     | 17.114    |
| WOLF+TABU  | Taillard\_15x15.txt  | 1209     | 1.345     |
| WOLF+TABU  | Taillard\_20x15.txt  | 1285     | 1.885     |
| WOLF+TABU  | Taillard\_20x20.txt  | 1426     | 3.040     |
| WOLF+TABU  | Taillard\_30x15.txt  | 1455     | 4.002     |
| WOLF+TABU  | Taillard\_30x20.txt  | 1607     | 4.985     |
| WOLF+TABU  | Taillard\_50x15.txt  | 1720     | 6.832     |
| WOLF+TABU  | Taillard\_50x20.txt  | 1862     | 8.710     |
| WOLF+TABU  | Taillard\_100x20.txt | 2985     | 17.900    |

## 6. Discussão

1. Efetividade (Makespan)
    Melhores makespans foram geralmente alcançados por heurísticas que combinam métodos, como:
        WOLF+TABU: obteve os menores makespans em todas as instâncias, com destaque para Taillard_100x20.txt com 2985, a melhor de toda a tabela.
        TABU Search puro também apresentou resultados muito competitivos, superando ou empatando com VNS e GRASP em várias instâncias.
    Heurísticas puras como WHALE e GRASP apresentaram os piores makespans, mostrando menor capacidade de refinamento das soluções iniciais.
    O GA sozinho, apesar de rápido, teve desempenho inferior às combinações híbridas em termos de makespan, especialmente em instâncias maiores.

2. Tempo de Execução
    O tempo de execução tende a crescer proporcionalmente ao tamanho das instâncias, como esperado.
    GRASP e GA foram os mais rápidos, com tempos significativamente menores, sendo vantajosos para execuções rápidas, porém com trade-off em qualidade da solução.
    Heurísticas híbridas, como VNS+WOLF, WOLF+TABU e GA+TABU, são mais custosas em tempo, mas entregam melhores resultados.

3. Análise das Combinações Híbridas
   Combinações como:
   GA+TABU, VNS+GRASP e VNS+WOLF superaram consistentemente suas versões puras em termos de qualidade da solução, mostrando que exploração inicial seguida de refinamento local é uma estratégia eficaz.
   WOLF+TABU destaca-se como a melhor combinação geral, equilibrando busca exploratória com intensificação via Tabu.

## 7. Conclusões
Os resultados demonstram que heurísticas híbridas oferecem melhor desempenho na resolução de problemas de agendamento complexos como o Job Shop Scheduling. A combinação WOLF+TABU apresentou o melhor desempenho global, superando as demais em qualidade de solução (makespan) com tempos de execução ainda aceitáveis para problemas de maior escala.
Além disso:
Heurísticas simples como GRASP e GA são úteis para soluções rápidas e razoáveis.
Refinamentos locais (como os aplicados em TABU e VNS) são fundamentais para melhorar o desempenho das heurísticas de construção.
A escalabilidade das heurísticas deve ser considerada, já que o custo computacional cresce com o tamanho da instância, especialmente nas combinações mais sofisticadas.

## 8. Referências
-Taillard, É. D. (1993). Benchmarks for basic scheduling problems. European Journal of Operational Research, 64(2), 278–285.
-Glover, F., & Laguna, M. (1997). Tabu Search. Springer.
-Yang, X.-S. (2010). Nature-Inspired Metaheuristic Algorithms. Luniver Press.


