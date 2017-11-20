#ifndef LIST_H
#define LIST_H

#include "std.h"

SE_BEGIN_NAMESPACE

template <class T>
struct Node {
	T item;
	Node *next;
};

template <class T>
class List {
public:
	int m_count;

	List() {
		m_count = 0;
		m_root->next = 0;
		m_root->item = NULL;
		m_conductor = m_root;
	}

	void Add(T* item) {
		if (m_conductor != 0) {
			while (m_conductor->next != 0) {
				m_conductor = m_conductor->next;
			}
			m_conductor->next = new Node;
			m_conductor = m_conductor->next;
			m_conductor->next = 0;
			m_conductor->item = item;
			m_count++;
		}
	}

	T Get(int i) {
		if (m_conductor<T> != 0 && i <= m_count) {
			while (m_conductor->next != 0) {
				m_conductor = m_conductor->next;
			}
			return m_conductor;
		}
		return NULL;
	}

	void Get(T* item) {
		return NULL;
	}

	void Remove(int i) {
		//delete m_conductor;
		//m_count--;
	}

	void Remove(T* item) {
		//delete m_conductor;
		//m_count--;
	}
private:
	Node *m_root<T>;
	Node *m_conductor<T>;
};

SE_END_NAMESPACE

#endif // !LIST_H
