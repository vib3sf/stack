#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

template <class>
class ArrayStack;

#include "stack.h"
#include <stdlib.h>
#include <iostream>

template <class T>
struct Node
{
	T data;
	Node *next;

	Node(T data);
};

template <class T>
Node<T>::Node(T data) : data(data), next(0)
{  }

template <class T>
class ListStack : public Stack<T>
{
	private:
		Node<T> *first;
		virtual void Print(std::ostream& os) const;
		void RecursivePrint(const Node<T> *node) const;
		virtual ListStack<T> *Clone() const;

	public:
		ListStack();
		ListStack(const ListStack& l);
		ListStack(ArrayStack<T> a);
		~ListStack();

		virtual void Push(T elem);
		virtual T Peek() const;
		virtual T Pop(); 
};

template <class T>
ListStack<T>::ListStack() : first(0)
{  }

template <class T>
ListStack<T>::ListStack(const ListStack& l) :
	Stack<T>(l), first(l.first ? new Node(l.first->data) : 0)
{
	Node<T> *tmp = first;

	if(first)
		for(Node<T> *node = l.first->next; node; node = node->next, tmp = tmp->next)
			tmp->next = new Node<T>(node->data);
}

template <class T>
ListStack<T>::~ListStack<T>()
{
	Node<T> *next;
	for(Node<T> *node = first; node; node = next)
	{
		next = node->next;
		delete node;
	}
}

template <class T>
void ListStack<T>::Push(T elem)
{
	Node<T> *node = new Node<T>(elem);
	if(!first)
		first = node;
	else 
	{
		node->next = first;
		first = node;
	}

	this->len++;
}

template <class T>
T ListStack<T>::Peek() const
{
	return first != 0 ? first->data : 0;
}

template <class T>
T ListStack<T>::Pop()
{
	if(this->IsEmpty())
		throw "ListStack is empty.\n";

	Node<T> *tmp = first;
	T data_tmp = tmp->data;

	first = first->next;
	delete tmp;

	this->len--;
	return data_tmp;
}

template <class T>
void ListStack<T>::Print(std::ostream& os) const
{
	RecursivePrint(first);
}

template<class T>
void ListStack<T>::RecursivePrint(const Node<T> *node) const
{
	if(node)
		RecursivePrint(node->next);
	else
		return;
	
	std::cout << node->data << ' ';

	if(node == first)
		std::cout << '\n';
}

template <class T>
ListStack<T> *ListStack<T>::Clone() const
{
	return new ListStack(*this);
}

#endif
