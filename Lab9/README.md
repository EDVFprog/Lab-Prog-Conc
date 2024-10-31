# Laboratório 9
Neste laboratório foram respondidas as questões conforme pedido, implementado o código da atividade 2 e da atividade 5
## Atividade 1
2. Ao comentarmos a chamada do Sleep na função, ao se executar o código o mesmo não imprime a mensagem na tela pois, o fluxo da main está terminando antes mesmo que o Olá mundo possa disparado. Quando a main termina
o programa inteiro termina.
## Atividade 2
2. O sleep não foi necessário desta vez pois se utilizou o canal de comunicação.
## Atividade 3 
A finalidade do canal jobs é enviar os jobs enquanto a finalidade do canal done é sinalizar que a tarefa foi terminada.
Se comentarmos a linha 32, gerariamos um deadlock pois a função ficará esperando um novo job, mesmo ele não existindo, isto por que não enviamos o sinal de termino dos jobs.
## Atividade 5
Os valores de M e N são atribuidos dentro da thread.
São utilizados três canais como na atividade 5, um para a lista de números, outro para os números primos encontrados  e outro para a sinalização de finalização da tarefa.
A corretude foi verificada através de prints para analisar a lista de valores e quantidade obtida de valores primos.
