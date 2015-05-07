<h1>##Trabalho de Laboratorio de Programação I ##</h1>
Autoras: Ana Clara e Maria Clara

<h1>** PROJETO B.A.R.E.S. **</h1>

<h5>O projeto Basic Arithmetic Expression Evaluator Based On Stacks (B.A.R.E.S.) foi criado com a intenção de abordar os assuntos vistos em sala de aula.</h5>
<h5>Proporcionando o cálculo de operações aritméticas utilizando o método infixo e pósfixo para leitura em fila e empilhamento de dados. Servirá também para verificar se as expressões apresentam os seguintes erros:</h5>
*Constante numerica invalida,Falta operando, Operando inválido, Operador inválido, Falta operador, Fechamento de escopo inválido, Escopo aberto, Divisão por zero.*

<h1>**Execução**</h1>

<h5>O usuário deve entrar no diretório do projeto "LP_Bares" pelo terminal Linux ou Terminal simulador(CYGWIN) do Windows</h5>
<h5>Estando dentro do diretório o usuário deve escrever o comando "make"</h5>
<h5>Ao terminar o comando será criado o objeto executável denominado "bares"</h5>
<h5>Para executá-lo o usuário precisa digitar "./bares"</h5>
<h5>O programa irá ler o documento "expressions.txt" e irá retornar os resultados das expressões listadas, ou erros que forem encontrados em casa expressão.</h5>

<h1>**Verificação de Vazamento de Memória** </h1>

<h5>Para verificarmos se o nosso algoritmo está com vazamento de memória de dados, utilizamos a ferramenta Valgrind para teste</h5>
<h5>O usuário após compilar e criar o objeto deve escrever no Terminal:</h5>

*valgrind --leak-check=full ./bares*
