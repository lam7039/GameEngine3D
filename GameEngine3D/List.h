#ifndef LIST_H
#define LIST_H

#include "std.h"

template <class T>
struct Node {
	T item;
	Node *next;
};

template <class T>
class List {
public:
	List();
	SE_API void Add(T item);
	SE_API void Remove(int i);
	//void Remove(T *item);
	SE_API T Get(int i);
	//T Get(T* item);
	SE_API int Count();
	~List();
private:
	Node<T> *m_root;
	Node<T> *m_conductor;
	int m_count;
};

#endif
