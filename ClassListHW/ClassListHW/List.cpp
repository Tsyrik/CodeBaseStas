#include "List.h"
#include <iostream>

struct util::Node {
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

void util::List::PushBack(int data) {
	Node* newNode = new Node{ data };
	if (!m_head) {
		m_head = newNode;
	}
	else {
		m_tail->next = newNode;
		newNode->prev = m_tail;
	}
	m_tail = newNode;
	++m_size;
}

int util::List::PopBack() {
	int data = 0;
	if (m_head) {
		int data = m_tail->data;
		Node* curTail = m_tail;
		if (m_tail->prev) {
			m_tail = m_tail->prev;
			m_tail->next = nullptr;
		}
		else {
			m_tail = nullptr;
			m_head = nullptr;
		}
		delete curTail;
	};
	--m_size;
	return data;
}

size_t util::List::Size() {
	return m_size;
}

void util::List::ShowList() {
	for (Node* cur = m_head; cur; cur = cur->next) {
		std::cout << cur->data << std::endl;
	};
}
;
