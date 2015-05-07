#ifndef __BARES__
	#define __BARES__

#include <iostream>
#include <cctype>
#include <math.h>
#include "token.hpp"
#include "stack.hpp"
#include "queue.hpp"

using namespace std;
/**
 * @class Classe Bares
*/
class Bares{
	private:
		Token T;
		Queue<Token> infix, posfix;
		int result;

	public:
	Bares();
	~Bares();	
/**
* função para indicar quais operadores são reconhecidos
* @param string
* @return retorna verdadeiro se o parâmetro lido for reconhecido da lista, falso caso não.
*/	
	bool isOperator(string);
/**
* verificando se o arquivo está vazio
* caso não, fazer a leitura das expressões e números até o fim do arquivo
* @param string verifica expressões (operandos e operadores)
* @return retorna falso se a lista estiver vazia, caso contrário, retorna verdadeiro se a string for dígito
*/	
	bool isNumber(string);
/**
* função para chamada do tratamento de erro
* @param int
* @param Token
* @return função void
*/
	void errors(int, Token);
/**
* verifica se a string lida é válida como dígito (operador ou constante)
* @param char para receber operador ou constante
* @return retorna 1 se a variável char for válida como dígito, caso não, retorna 2
*/
	int type(char);
/**
* verifica se a string lida é válida como dígito numérico
* @param string verifica dígito numérico
* @return retorna 1 se string for dígito numérico, caso não, retorna 2
*/
	int type(string);
/**
* utilizando a tokenização verifica o arquivo por linha verificando se existem os erros 1 a 5
* @param string verifica operandos
* @param string verifica operadores
* @return retornará 0 se não tiver erros, caso contrário, retornará o número equivalente ao erro defenido peló método "erros"
*/
	int testaErros1a5(string, string);
/**
* @param string
* @return verifica o erro 2 no início da expressão e no final; 
* irá retornar o erro, se existir, qual coluna que se encontra, caso não irá fazer o procedimento de tokenização da lista
*/		
	int tokenizacao (string);
/**
* indicação da prioridade dos operandos 
* @param string verifica operandos para calcular na prioridade informada
* @return irá retornar a prioridade do operador lido para auxiliar na pilha
*/
	int prioridade(string);
/**
* função para empilhar usando o método pós fixo transformando a expressão
* @return retorna cada operando ou operador da lista em pilha na forma posfixa
*/
	int transformaParaPos();
/**
* função para calcular as expressões matemáticas
* @param int valor numerico inicial
* @param int proximo valor numerico
* @param Token
* @return retorna o resultado da operação lida na lista
*/
	bool calcula(int, int, Token);	
/**
* função para encontrar o resultado da expressão
* @param string recebe operadores e operandos
* @return retorna o resultado da operação da pilha que está na forma posfixa
*/
	bool calculaPosF(string);
/**
* função para mostrar o resultado da função calcula
* @return retorna resultado da operação
*/
	int getResult();
};

#include "../src/bares.cpp"
#endif