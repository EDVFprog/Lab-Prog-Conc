# Atividade 5
O objetivo desta atividade é confeccionar um programa concorrente com M threads que incremente em 1 os valores de um vetor de tamanho N. De modo que,
todas as threads tenham seu trabalho distribuído de forma mais otimizada possível. Segue o enunciado abaixo.

**Enunciado da atividade:**

Escreva um programa concorrente com M threads, para somar 1 a cada elemento de um vetor de N elementos do tipo inteiro (Para cada elemento ai do vetor, calcular o novo valor ($a_i$ + 1) e escrever o resultado na mesma posição do elemento.) A tarefa completa deverá ser dividida entre as M threads de forma mais balanceada possível (as threads devem receber a mesma carga de trabalho). Os valores de M e N
devem ser informados na chamada do programa.

Assim seguindo o roteiro responderemos as 4 perguntas feitas.

**1** Podemos dividir as tarefas para que as threads recebam a mesma carga de trabalho da seguinte forma: 
calculamos a partição de modo que seja igual o arredondamento para cima da divisão N/M e posteriormente faremos um loop até M onde cada vetor inicializará com o valor de i* partição e terminará como o mínimo entre ( i+-1) * partição e N. Os argumentos passados serão o id da thread, M e o vetor subdividido para cada thread.

Abaixo segue uma explicação de cada função contida no código da atividade.

**Cria_array** Função responsável pela criação do vetor de modo sequencial, de 1 a N.
**somavetor**função responsável por somar o vetor criado em 1, separando  a tarefa para cada thread responsável. Além disso, printa o resultado da soma para cada elemento do vetor para que possa ser feita a verificação.

