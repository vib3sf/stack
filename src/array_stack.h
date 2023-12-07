#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "stack.h"
#include <iostream>
#include <stdlib.h>

template <class T>
class ArrayStack : public Stack<T>
{
	private:
		int arr_size;
		T *array;

		inline bool IsFull();
		void ResizeArray(int new_size, int cp_size);
		virtual void Print(std::ostream& os) const;
		virtual ArrayStack<T> *Clone() const;

	public:
		ArrayStack();
		ArrayStack(int arr_size);
		ArrayStack(const ArrayStack& a);
		ArrayStack(bool a);
		~ArrayStack();

		virtual void Push(T elem);
		virtual T Pop(); 
		virtual T Peek() const;
};

template <class T>
ArrayStack<T>::ArrayStack() : 
	arr_size(4), array(new T[arr_size])
{ }

template <class T>
ArrayStack<T>::ArrayStack(int arr_size) : 
	Stack<T>(arr_size), arr_size(arr_size), array(new T[arr_size])
{ }

template <class T>
ArrayStack<T>::ArrayStack(const ArrayStack& a) : 
	Stack<T>(a), arr_size(a.arr_size), array(new T[arr_size])
{
	for(int i = 0; i < this->len; i++)
		array[i] = a.array[i];
}

template <class T>
ArrayStack<T>::~ArrayStack()
{
	delete[] array;
}

template <class T>
inline bool ArrayStack<T>::IsFull()
{
	return arr_size == this->len;
}

template <class T>
void ArrayStack<T>::ResizeArray(int new_size, int cp_size)
{
	T *tmp = new T[new_size];
	for(int i = 0; i < cp_size; i++)
		tmp[i] = array[i];

	delete[] array;
	array = tmp;
}

template <class T>
void ArrayStack<T>::Push(T elem)
{
	if(IsFull())
	{
		arr_size *= 2;
		ResizeArray(arr_size, this->len);
	}

	array[this->len] = elem;
	this->len++;
}

template <class T>
T ArrayStack<T>::Peek() const
{
	return this->IsEmpty() ? 0 : array[0];
}

template <class T>
T ArrayStack<T>::Pop()
{
	if(this->IsEmpty())
		throw "ArrayStack is empty.\n";

	T tmp = array[this->len - 1];
	this->len--;

	if(this->len < arr_size / 2)
	{
		arr_size /= 2;
		ResizeArray(arr_size, this->len);
	}

	return tmp;
}

template <class T>
void ArrayStack<T>::Print(std::ostream& os) const
{
	for(int i = 0; i < this->len; i++)
		os << array[i] << ' ';
	os << '\n';
}

template <class T>
ArrayStack<T> *ArrayStack<T>::Clone() const
{
	return new ArrayStack(*this);
}

#endif
