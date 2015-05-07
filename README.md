<h1>##Trabalho de Laboratorio de Programação I ##</h1>
Autoras: Ana Clara (github.com/claranobre) e Maria Clara (github.com/mclara-s)

<h1>** PROJETO B.A.R.E.S. **</h1>

<h5>O projeto Basic Arithmetic Expression Evaluator Based On Stacks (B.A.R.E.S.) foi criado com a intenção de abordar os assuntos vistos em sala de aula.</h5>
<h5>Proporcionando o cálculo de operações aritméticas utilizando o método infixo e pósfixo para leitura em fila e empilhamento de dados. Servirá também para verificar se as expressões apresentam os seguintes erros:</h5>
*Constante numerica invalida,Falta operando, Operando inválido, Operador inválido, Falta operador, Fechamento de escopo inválido, Escopo aberto, Divisão por zero.*

<h1>**Execução**</h1>

<h5>O usuário deve entrar no diretório do projeto "LP_Bares" pelo terminal Linux ou Terminal simulador(CYGWIN) do Windows</h5>
<h5>Estando dentro do diretório o usuário deve escrever o comando "make"</h5>
<h5>Ao terminar o comando será criado o objeto executável denominado "bares"</h5>
<h5>Para executá-lo o usuário precisa digitar "./bares"</h5>
<h5>O programa irá ler o documento "expressions.txt" e irá retornar os resultados das expressões listadas, ou erros que forem encontrados em cada expressão.</h5>
<h5>Ao terminar de executar o programa, se caso o usuário quiser testar alguma modificação no código original, na compilação após essa alteração, antes de dar o comando "make" será necessário excluir com o comando *rm bares* o objeto da compilação anterior</h5>
<h5>Caso o usuário só quiser modificar o arquivo "expressions.txt" para testar outras expressões, ele só precisará ir no diretório *src* e editar o arquivo, salvar e executar o programa (./bares). </h5> 

<h1>**Verificação de Vazamento de Memória** </h1>

<h5>Para verificarmos se o nosso algoritmo está com vazamento de memória de dados, utilizamos a ferramenta Valgrind para teste</h5>
<h5>O usuário após compilar e criar o objeto deve escrever no Terminal:</h5>

*valgrind --leak-check=full ./bares*

<h1>**Documentação**</h1>

<h5> Foi utilizada a ferramenta Doxygen para auxiliar na documentação da execução desse projeto, para o usuário visualizar é necessário entrar no diretório "html" e acessar o arquivo index.html, logo a documentação será aberta em modo offline em seu navegador padrão</h5>
