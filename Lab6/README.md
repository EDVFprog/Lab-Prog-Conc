# Atividade 3
Essa atividade tem por objetivo implementar uma versão do rwlock com *prioridade para operação de escrita*. O rwlock é uma implementação do lock específico para o padrão escritor e leitor da biblioteca pthreads.
A atividade foi desenvolvida utilizando o padrão leitor e escritor e modificada para que toda vez que uma escrita for solicitada, novas operações de leitura não poderão começar até que a operação de escrita solicitada seja terminada. Assim o código implementado seguiu os seguintes critérios:
* Os leitores podem ler simultaneamente uma região de memória compartilhada;
* Apenas um escritor pode escrever a cada instante;
* Se um escritor está escrevendo nenhum leitor pode ler esta região de memória compartilhada;
* Se o escritor quiser escrever nenhuma operação de leitura poderá começar até que a escrita seja realizada.
Assim o código foi separado em 2 partes, modularizado para que possamos chamar nossa implementação para ler uma lista encadeada , deletar um valor ou inserir na lista.
Esta atividade foi separada em 3 arquivos, além dos arquivos de lista encadeada, o arquivo leitores_escritores.c, leitores_escritores.h e tarefa.c.
O arquivo leitores_escritores.h é responsável pela definição das funções utilizadas pelo padrão. O arquivo leitores_escritores.c implementa as funções definidas em leitores_escritores.h e por fim o arquivo tarefa.c é responsável pelo monitoramento das operações de ler um valor da lista encadeada, deletá-lo ou inserilo com o auxílio da versão rwlock implementada.
Para compilarmos o nosso código basta dar o comando 'gcc -o read list_int.c leitor_escritor.c tarefa.c ' no terminal

