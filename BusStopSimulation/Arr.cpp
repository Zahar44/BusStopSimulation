#include "Arr.h"
template <class T>
class Arr
{
private:
	template <class T>
	struct Node
	{
		T value = 0;
		Node<T>* next = nullptr;
		Node<T>* prev = nullptr;
	};
	Node<T>* head;
	Node<T>* tail;
	size_t _size;

	Node<T>* getNode()
	{
		return tail;
	}
	Node<T>* getNode(size_t id)
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

public:
	Arr() : head(nullptr), tail(nullptr), _size(0)
	{
	}
	Arr(const T& obj) : Arr()
	{
		push_back(obj);
	}
	~Arr()
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

	void push_back(const T& obj)
	{
		if (!_size)
			head = tail = new Node<T>{ obj };
		else
			tail = tail->next = new Node<T>{ obj, nullptr, tail };
		_size++;
	}
	void push_front(const T& obj)
	{
		if (head == nullptr)
			head = tail = new Node<T>{ obj };
		else
			head = head->prev = new Node<T>{ obj, head, nullptr };
		_size++;
	}
	void insert(size_t ind, const T& obj)
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
	void erase(size_t ind)
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
	size_t size() const { return _size; }

	T& operator[] (int id)
	{
		return getNode(id)->value;
	}

};