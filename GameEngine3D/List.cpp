#include "List.h"

template<class T>
List<T>::List() {
	m_count = 0;
	m_root = new Node<T>;
	m_root->next = NULL;
	m_root->item = NULL;
	m_conductor = m_root;
}

template<class T>
void List<T>::Add(T item) {
	if (m_conductor != NULL) {
		while (m_conductor->next != NULL) {
			m_conductor = m_conductor->next;
		}
		m_conductor->next = new Node<T>;
		m_conductor = m_conductor->next;
		m_conductor->next = NULL;
		m_conductor->item = item;
		m_count++;
	}
}

template<class T>
void List<T>::Remove(int i) {
	if (i == 0) {
		Node<T> *temp = new Node<T>;
		temp = m_root;
		m_root = m_root->next;
		delete temp;
		m_count--;
		return;
	}
	else if (i == (m_count - 1)) {
		if (m_conductor != NULL) {
			while (m_conductor->next != NULL) {
				m_conductor = m_conductor->next;
			}
			delete m_conductor;
			m_count--;
			return;
		}
	}
	else if (i < (m_count - 1)) {
		if (m_conductor != NULL) {
			Node<T> *temp = new Node<T>;
			int x = 0;
			while (x < i) {
				temp = m_conductor;
				m_conductor = m_conductor->next;
				x++;
			}
			temp->next = m_conductor->next;
			delete m_conductor;
			m_count--;
			return;
		}
	}
	else {
		//log error: position in list doesn't exist
	}
}

/*template<class T>
void List<T>::Remove(T *item) {
	//delete m_conductor;
	//m_count--;
}*/

template<class T>
T List<T>::Get(int i) {
	if (m_conductor != NULL && i < m_count) {
		while (m_conductor->next != NULL) {
			m_conductor = m_conductor->next;
		}
		return m_conductor->item;
	}
	return NULL;
}

/*template<class T>
void List<T>::Get(T *item) {
	return NULL;
}*/

template<class T>
int List<T>::Count() {
	return m_count;
}

template<class T>
List<T>::~List() {
	delete m_root;
}