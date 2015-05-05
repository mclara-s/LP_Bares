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
		//Queue<string> expressions;
		int result;

	public:
	Bares();
	~Bares();	
/**
* função para indicar quais operadores são reconhecidos
* @param string
*/	
	bool isOperator(string);
/**
* verificando se o arquivo está vazio
* caso não, fazer a leitura das expressões e números até o fim do arquivo
* @param string verifica expressões (operandos e operadores)
*/	
	bool isNumber(string);
/**
* função para chamada do tratamento de erro
* @param int
* @param Token
*/
	void errors(int, Token);
/**
* verifica se a string lida é válida como dígito (operador ou constante)
* @param char para receber operador ou constante
*/
	int type(char);
/**
* verifica se a string lida é válida como dígito numérico
* @param string verifica dígito numérico
*/
	int type(string);
/**
* utilizando a tokenização verifica o arquivo por linha verificando se existem os erros 1 a 5
* @param string verifica operandos
* @param string verifica operadores
*/
	int testaErros1a5(string, string);
/**
* @param string
*/		
	int tokenizacao (string);
/**
* indicação da prioridade dos operandos 
* @param string verifica operandos para calcular na prioridade informada
*/
	int prioridade(string);
/**
* função para empilhar usando o método pós fixo transformando a expressão
*/
	int transformaParaPos();
/**
* função para calcular as expressões matemáticas
* @param int valor numerico inicial
* @param int proximo valor numerico
* @param Token
*/
	bool calcula(int, int, Token);	
/**
* função para encontrar o resultado da expressão
* @param string recebe operadores e operandos
*/
	bool calculaPosF(string);
/**
* função para mostrar o resultado da função calcula
*/
	int getResult();
};

#include "../src/bares.cpp"
#endif