#ifndef STACK_H
#define STACK_H

#include <ostream>

template <class T>
class Stack
{
	protected:
		int len;

		virtual void Print(std::ostream& os) const = 0;

	public:
		virtual Stack<T> *Clone() const = 0;
		virtual void Push(T elem) = 0;
		virtual T Pop() = 0; 
		virtual T Peek() const = 0;

		Stack();
		Stack(int len);
		Stack(const Stack& q);
		virtual ~Stack() {}

		inline int Len() const;
		inline bool IsEmpty() const;
		void Charge(T elem, int count);
		void Clear();
		void Reverse();
		const Stack& operator+=(const T& t);

		template <class U>
		friend std::ostream& operator<< (std::ostream& os, const Stack<U>& q);
};

template <typename T>
Stack<T>::Stack() : len(0)
{  }

template <typename T>
Stack<T>::Stack(const Stack &q) : len(q.len)
{  }

template <typename T>
Stack<T>::Stack(int len) : len(len)
{  }

template <typename T>
inline int Stack<T>::Len() const
{
	return len;
}

template <typename T>
inline bool Stack<T>::IsEmpty() const
{
	return len == 0;
}

template <typename T>
const Stack<T>& Stack<T>::operator+=(const T& t)
{
	Push(t);
	return *this;
}

template <typename T>
void Stack<T>::Charge(T elem, int count)
{
	for(int i = 0; i < count; i++)
		Push(elem);
}

template <typename T>
void Stack<T>::Clear()
{
	while(!IsEmpty())
		Pop();
}

template <typename T>
void Stack<T>::Reverse()
{
	Stack<T> *clone = Clone();

	Clear();
	while(!clone->IsEmpty())
		Push(clone->Pop());

	delete clone;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& q)
{
    q.Print(os);
    return os;
}

#endif
