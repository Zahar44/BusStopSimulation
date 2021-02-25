#include "Arr.h"
#include "Human.h"

template <class T> 
Arr<T>::Arr() : head(nullptr), tail(nullptr), _size(0)
{
}
template <class T> 
Arr<T>::Arr(const T& obj) : Arr()
{
	push_back(obj);
}
template <class T> 
Arr<T>::~Arr()
{
	if (head == nullptr)
		return;
	Node<T>* tmp;
	do
	{
		tmp = head->next;
		delete head;
		head = tmp;
	} while (tmp);
	head = nullptr;
	tail = nullptr;
}

template <class T> 
Arr<T>::Node<T>* Arr<T>::getNode(size_t id)
{
	if (id >= _size)
		return nullptr;

	Node<T>* tmp;


	if (id * 2 <= _size)
	{
		tmp = head;
		while (id)
		{
			tmp = tmp->next;
			id--;
		}
	}
	else
	{
		tmp = tail;
		while (id + 2 <= _size)
		{
			tmp = tmp->prev;
			id++;
		}
	}
	return tmp;
}
template <class T> 
void Arr<T>::push_back(const T& obj)
{
	if (!_size)
		head = tail = new Node<T>{ obj };
	else
		tail = tail->next = new Node<T>{ obj, nullptr, tail };
	_size++;
}
template <class T> 
void Arr<T>::push_front(const T& obj)
{
	if (head == nullptr)
		head = tail = new Node<T>{ obj };
	else
		head = head->prev = new Node<T>{ obj, head, nullptr };
	_size++;
}
template <class T> 
void Arr<T>::insert(size_t ind, const T& obj)
{
	if (!ind)
		push_front(obj);
	if (ind == _size - 1)
		push_back(obj);

	Node<T>* node = getNode(ind);

	node = new Node<T>{ obj, node->next, node->prev };
	node->next->prev = node;
	node->prev->next = node;

}
template <class T> 
void Arr<T>::erase(size_t ind)
{
	Node<T>* node = getNode(ind);

	if (node == head)
	{
		head = node->next;
		delete node;
		_size--;
		return;
	}

	if (node == tail)
	{
		tail = node->prev;
		delete node;
		_size--;
		return;
	}

	if (ind)
		node->prev->next = node->next;
	if (!(ind == _size - 1))
		node->next->prev = node->prev;
	_size--;
	delete node;
}
template <class T> 
T& Arr<T>::operator[] (int id)
{
	return getNode(id)->value;
}

