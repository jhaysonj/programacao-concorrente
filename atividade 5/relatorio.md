nome: jhayson de brito jales
dre: 120059038

# atividade 1

## questão 2
O TAD lista implementado nesses arquivos poderia ser compartilhado por threads de um programa concorrente? Com qual finalidade e de que forma?

Sim, o tipo abstrato de dados lista implementado nos arquivos list_int.h e linked_list.c pode ser compartilhado por threads em um programa concorrente. A finalidade de compartilhar essa estrutura de dados entre threads é permitir que elas acessem e manipulem uma lista de inteiros de forma segura e coordenada.

Existem várias maneiras de usar essa implementação de lista em um programa concorrente, dentre elas temos:

1) Acesso e manipulação concorrentes: Várias threads podem acessar e manipular a lista "ao mesmo tempo".

2) Divisão de trabalho: As threads podem ser designadas para realizar diferentes operações na lista, como inserção, exclusão ou busca. Cada thread seria responsável por uma parte específica da lista, permitindo operações concorrentes em diferentes seções da estrutura de dados.

3) Processamento paralelo: Se a lista for grande e as operações forem intensivas em CPU, as threads podem ser usadas para processar várias partes da lista em paralelo, aumentando a eficiência do programa.

obs: Para todos os itens listados acima, precisamos garantir a consistência dos dados, utilizando mecanismos de sincronização, como mutexes, para evitar condições de corrida.


## Questão 4
4. O que poderia acontecer se o programa nao implementasse exclusão mútua no acesso as operações da lista encadeada?
O não tratamento de sessões críticas pode levar à corrida de dados.
Vamos considerar um cenário em que duas threads estão tentando inserir elementos na lista encadeada simultaneamente, sem uso de exclusão mútua. 
Isso pode levar a uma condição de corrida onde os resultados das operações são imprevisíveis e inconsistentes.

Suponha que temos as seguintes threads:

Thread 1: Esta thread insere o valor 10 na lista.

Thread 2: Esta thread insere o valor 20 na lista.

Sem exclusão mútua, as operações de inserção podem ser executadas simultaneamente, e a ordem exata em que as instruções são executadas pode variar entre as threads e entre diferentes execuções do programa. 
Vamos examinar um cenário possível:
    **Thread 1:**
        A thread verifica que a lista está vazia.
        A thread começa a inserir o valor 10 na lista.
        Antes de concluir a inserção, a execução da thread é interrompida.

    **Thread 2:**
        A thread verifica que a lista ainda está vazia.
        A thread começa a inserir o valor 20 na lista.
        A thread completa a inserção do valor 20.
        A lista agora contém apenas o valor 20.

    Thread 1 (continuação):
        A execução da Thread 1 é retomada.
        A thread completa a inserção do valor 10 na lista.
        Agora a lista contém apenas o valor 10, pois o valor 20 inserido pela Thread 2 foi sobrescrito.

Neste cenário, devido à falta de exclusão mútua, a inserção concorrente dos valores 10 e 20 resultou em um estado inconsistente da lista. 
A ordem em que as operações de inserção foram concluídas determinou o conteúdo final da lista, e isso pode variar de uma execução para outra, resultando em resultados imprevisíveis e não determinísticos.


## questão 6
6. O que acontece com o tempo de execuc ̧ao do programa quando aumentamos o número de threads? Por que isso ocorre?
Conforme aumentamos o número de threads aumentamos o tempo de execução do programa. Dentre os motivos que levam ao maior tempo de execução, temos:

1) Concorrência de Acesso: Com um número maior de threads competindo pelo acesso à lista, há um aumento na contenção pelo uso de recursos compartilhados, como o acesso ao mutex que controla o acesso à lista. Isso pode levar a um aumento no tempo de espera para adquirir bloqueios de exclusão mútua e, consequentemente, a um aumento na latência das operações.

2) Overhead de Contexto: Cada thread adicionada ao programa introduz um certo overhead de criação, gerenciamento e troca de contexto. Com um grande número de threads, o sistema operacional precisa alternar entre elas com mais frequência, o que pode consumir mais tempo de CPU e recursos do sistema.


# Atividade 2

## questão 4
4. Em quais cenarios o uso do  rwlock pode ser mais vantajoso que o uso do lock de exclusao mútua?
De forma geral, são os cenários onde as operações de leitura são mais frequentes que as operações de escrita. 
Se o programa tem uma taxa alta de operações de leitura em comparação com as operações de escrita, o rwlock pode ser mais eficiente. Isso ocorre porque o rwlock permite que várias threads realizem operações de leitura simultaneamente, diminuindo a concorrência de acesso aos recursos compartilhados, sem que haja corrida de dados, permitindo assim um melhor uso dos recursos.


# atividade 3
## questão 2
2. Em que tipo de aplicação concorrente o padrão de sincronização coletiva com barreira precisa ser usado?
De forma geral, o padrão de sincronização coletiva com barreira é comumente usado em aplicações concorrentes onde é necessário garantir que um conjunto de threads atinja um ponto de sincronização antes de continuar sua execução. 
Este padrão é particularmente útil em situações onde as threads precisam coordenar suas atividades em etapas distintas do processo e onde o avanço para a próxima etapa depende da conclusão de todas as threads na etapa atual.


