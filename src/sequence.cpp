#include "../headers/sequence.hpp"
#include <iostream>

template <typename TYPE>
Sequence<TYPE>::Sequence() {

}

template <typename TYPE>
Sequence<TYPE>::~Sequence() {
	clear();
}

template <typename TYPE>
Sequence<TYPE>::Sequence(const Sequence<TYPE> &s){
	copy(s);
}

template <typename TYPE>
Sequence<TYPE>& Sequence<TYPE>::operator=(const Sequence<TYPE> &s){
	clear();
	copy(s);
	return *this;
}


template <typename TYPE>
void Sequence<TYPE>::clear(){
	while (isEmpty() == false){
		removeLast();
	}
}

template <typename TYPE>
bool Sequence<TYPE>::isEmpty() {
	if(list.next == nullptr)
		return true;
	else
		return false;
}

template <typename TYPE>
int Sequence<TYPE>::getSize() {
	int count = 0;
	Node *aux = list.next;
	while(aux != nullptr){
		++count;
		aux = aux->next;
	}
	return count;

}

template <typename TYPE>
bool Sequence<TYPE>::addFirst(const TYPE &value) {
	Node *aux = new Node;
	if (aux == nullptr)
		return false;
	if ( isEmpty()){
		list.prev = aux;
		list.next = aux;
	}
	else {
		aux->next = list.next;
		(list.next)->prev = aux;
		list.next = aux;
	}
	aux->data = value;
	return true;
}

template <typename TYPE>
bool Sequence<TYPE>::addLast(const TYPE &value) {
	Node *aux = new Node;
	if (aux == nullptr)
		return false;
	if ( isEmpty()){
		list.next = aux;
		list.prev = aux;
	}
	else{
		aux->prev = list.prev;
		(list.prev)->next = aux;
		list.prev = aux;
	}
	aux->data = value;
	return true;
}


template <typename TYPE>
bool Sequence<TYPE>::add(const TYPE &value, int pos) {
	if (pos <= 0)
		addFirst(value);
	else if (pos > getSize())
		addLast(value);
	else{

		Node *insert = new Node;
		if(insert == nullptr)
			return false;
		int i;
		Node *aux = list.next;
		for (i = 0; i < pos-1; i++){
			aux = aux->next;
		}
		insert->next = aux->next;
		(insert->next)->prev = insert;
		aux->next = insert;
		insert->prev = aux;
		insert->data = value;
	}
	return true;
}

template <typename TYPE>
TYPE Sequence<TYPE>::removeFirst() {	
	TYPE value;
	if (isEmpty()){
		std::cout << "nao ha elementos para remover\n";
		value = list.data;
	}
	else {
		Node *aux = list.next;
		value = aux->data;
		list.next = aux->next;
		if (list.next == nullptr)
			list.prev = nullptr;
		else
			list.next->prev = aux->prev;
		delete(aux);
	}
	return value;
}

template <typename TYPE>
TYPE Sequence<TYPE>::removeLast() {   
	TYPE value;
	if (isEmpty()){
		std::cout << "nao ha elementos para remover\n";
		value = list.data;
	}
	else{
		Node *aux = list.prev;
		value = aux->data;
		list.prev = aux->prev;
		if (list.prev == nullptr)
			list.next =nullptr;
		else
			list.prev->next = aux->next;
		delete(aux);
	}
	return value;
}

template <typename TYPE>
TYPE Sequence<TYPE>::remove(int pos) {
	TYPE value;
	if (isEmpty()){
		std::cout << "nao ha elementos para remover\n";
		value = list.data;
	}
	else if (pos <= 0)
		value = removeFirst();
	else if (pos >= getSize())
		value = removeLast();
	else{
		int i;
		Node *aux = list.next;
		for (i = 0; i < pos; i++){
			aux = aux->next;
		}
		value = aux->data;
		(aux->prev)->next = aux->next;
		(aux->next)->prev = aux->prev;
		delete(aux);
	}
	return value;
}

template <typename TYPE>
TYPE Sequence<TYPE>::getFirst() {
	return list.next->data;
}

template <typename TYPE>
TYPE Sequence<TYPE>::getLast() {
	return list.prev->data;
}

template <typename TYPE>
TYPE Sequence<TYPE>::get(int pos) {
	int i;
	Node *aux = list.next;
	for (i = 0; i < pos; i++){
		aux = aux->next;
	}
	return aux->data;
}

template <typename TYPE>
int Sequence<TYPE>::search(const TYPE &elm) {
	int i;
	Node *aux = list.next;
	for (i = 0; i < getSize(); i++){
		if (aux->data == elm)
			return true;
		aux = aux->next;
	}
	return false;
}

template <typename TYPE>
bool Sequence<TYPE>::isEqual(Sequence<TYPE> &s) {
	Node *aux1 = list.next;
	Node *aux2 = s.list.next;
	
	if(getSize()!= s.getSize())
		return false;
	for (int i = 0; i < getSize(); i++){
		if (aux1->data != aux2->data)
			return false;
		aux1 = aux1->next;
		aux2 = aux2->next;
	}

	return true;
}

template <typename TYPE>
void Sequence<TYPE>::reverse() {
	Node *node = list.prev;
	Node *aux;

	while (node != nullptr) {
		aux = node->next;
		node->next = node->prev;
		node->prev = aux;
		node = node->next;
	}
	aux = list.next;
	list.next = list.prev;
	list.prev = aux;
}

template <typename TYPE>
bool Sequence<TYPE>::isIncreasing(){
	Node *aux = list.next;
	while(aux->next != nullptr){
		if (aux->next->data < aux->data)
			return false;
		aux = aux->next;
	}
	return true;
}

template <typename TYPE>
bool Sequence<TYPE>::isDecreasing(){
	Node *aux = list.next;
	while(aux->next != nullptr){
		if (aux->next->data > aux->data)
			return false;
		aux = aux->next;
	}
	return true;
}

template <typename TYPE>
void Sequence<TYPE>::bounds(TYPE &min, TYPE &max){
	Node *aux = list.next;
	min = max = aux->data;
	
	aux = aux->next;
	while (aux != nullptr){
		if (aux->data < min)
			min = aux->data;
		if (aux->data > max)
			max = aux->data;
		aux = aux->next;
	}
}

template <typename TYPE>
void Sequence<TYPE>::sort() {
	Node *node, *prox;
	int i = 0, j = getSize();
	
	while(i <= j){
		node = list.next;
		prox = node->next;
		while (prox != nullptr){
			if(node->data > prox->data){
				swap(node,prox);
			}
			else
				node = node->next;
			prox = node->next;
		}
		list.prev = node;
		--j;
	}
}

template <typename TYPE>
void Sequence<TYPE>::print() {
	Node *aux = list.next;
	while (aux != nullptr){
		std::cout << aux->data << " ";		
		aux = aux->next;
	}
	std::cout << std::endl;
}