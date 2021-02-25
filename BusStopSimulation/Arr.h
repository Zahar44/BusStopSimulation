#pragma once
template <class T>
class Arr
{
private:
	template <class T>
	struct Node;
	Node<T>* head;
	Node<T>* tail;
	size_t _size;

	Node<T>* getNode();
	Node<T>* getNode(size_t id);

public:
	Arr();
	Arr(const T& obj);
	~Arr();

	void push_back(const T& obj);
	void push_front(const T& obj);
	void insert(size_t ind, const T& obj);
	void erase(size_t ind);
	size_t size() const;
	T& operator[] (int id);
};

