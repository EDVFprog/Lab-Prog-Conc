# Atividade 3

Conforme a descrição do laboratório 2 foram confeccionados 2 programas para o cálculo de produto vetorial,entre 2 vetores de tamanho N, que utilizavam diferentes abordagens de programação. O primeiro "prod_vet_seq.c" é organizado no formato sequencial enquanto *"prod_vet_conc.c"* é organizado por meio de T threads utilizando o formato concorrente.
Assim foram gerados 3 arquivos testes com diferentes valores de N para que ao longo do laboratório possa-se comparar os resultados obtidos por meio da variação. Esta variação foi calculada utilizando a seguinte fórmula:

$`e = |\frac{(v_s- v_c)}{v_s}|`$

Os casos teste denominados casos teste1,teste2,teste3 tem N igual a 10,100,10000 respectivamente. Assim, fixou-se um valor de T de threads igual a 5 para compararmos a variação de resultado. Obtendo assim, os seguintes resultados:


*Cenário em que T= 5* 

*  No primeiro caso, N=10, obtivemos a seguinte variação 0.00000003154638983377629099. 
* No caso N=100 obtenemos a seguinte variação 0.00000001380717018592476631.
* No caso N=10000 obtivemos a seguinte variação 0.00000028985760481375193094.
  
  *Cenário em que T=N*
  
* No primeiro caso, N=10 e T=10, obtivemos a seguinte variação 0.00000003154638983377629099.
* No caso N=100 e T=100, obtivemos a seguinte variação 0.00000003154638983377629099.
* No caso N=10000 e T=10000 obtivemos a seguinte variação 0.00000144533901041673132209.
  
Podemos assim, concluir que a utilização de threads para essa tarefa talvez não seja a mais adequada pois, ao usarmos a paralelização foram
introduzidos pequenos erros de arredondamento devido às operações realizadas.
Além disso,observa-se que  ao aumentarmos o número de threads, T=N, a variação  *e* parece aumentar
também.
