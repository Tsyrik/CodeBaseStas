#pragma once
namespace util {
	struct Node;

	class List {
	public:
		void PushBack(int data);
		int PopBack();
		size_t Size();;
		void ShowList();;
	private:
		size_t m_size;
		Node* m_head = nullptr;
		Node* m_tail = nullptr;
	};
}