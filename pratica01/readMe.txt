gcc -o exec prog.c -lpthread



ex2:

a)O programa apresenta algum problema relacionado a
concorrência? Qual?

Sim, nas funções creditar e debitar, a variável 'saldo' é lida para ser calculado o valor de 'Saldo_conta' e, após, é alterada para o mesmo valor contido em 'saldo_conta'. Nesse trecho de código, somente uma thread pode estar lendo/escrevendo na variável, pois, se ocorre a seguinte sequencia de execução:

thread_1
saldo_conta = saldo + valor;

thread_2
int saldo_conta = saldo + valor;
saldo = saldo_conta;

thread_1
saldo = saldo_conta;

A thread 2 terá utilizado um valor de 'saldo' desatualizado.
E a thread 1, quando executa  saldo = saldo_conta;, sobrescreverá o valor de saldo calculado pela thread 2.







b)Caso tenha algum problema, apresente uma versão do
programa, com o problema solucionado.
A solução consiste em usar um semáfaro do tipo mutex para tornar o trecho de código da função debitar e creditar uma seção crítica.

sem_wait(&mutex);
int saldo_conta = saldo - valor;
printf("Debitando valor. \n");
printf("O novo valor sera %d. \n", saldo_conta);
saldo = saldo_conta;
sem_post(&mutex);


