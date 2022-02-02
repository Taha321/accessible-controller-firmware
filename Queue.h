#pragma once
#include <iostream>

template <typename T>
class Queue
{
private:
	class node
	{
	public:
		node(const T& newItem)
			:
			item(newItem)
		{}
		~node()
		{
			delete nextItem;
			nextItem = nullptr;
		}
		T item;
		node* nextItem = nullptr;
	};

public:
	Queue() = default;
	Queue( Queue& source)
	{
		delete m_Front;
		m_Front = nullptr;
		m_Back = nullptr;
		
		node* currentNode = source.m_Front;
		for (int i = 0; i < source.Size(); i++)
		{
			Enqueue(currentNode->item);
			currentNode = currentNode->nextItem;
		}
	}
	Queue& operator= ( Queue& source)
	{
		delete m_Front;
		m_Front = nullptr;
		m_Back = nullptr;
		node* currentNode = source.m_Front;
		for (int i = 0; i < source.Size(); i++)
		{
			Enqueue(currentNode->item);
			currentNode = currentNode->nextItem;
		}
		
		return *this;
	}
	Queue(Queue&& source) noexcept
	{
		m_Size = source.m_Size;
		m_Front = source.m_Front;
		m_Back = source.m_Back;
		source.m_Front = nullptr;
		source.m_Back = nullptr;
	}

	Queue& operator= (Queue&& source) noexcept
	{
		m_Size = source.m_Size;
		m_Front = source.m_Front;
		m_Back = source.m_Back;
		source.m_Front = nullptr;
		source.m_Back = nullptr;
		return this;
	}

	~Queue()
	{
		delete m_Front;
		m_Front = nullptr;
		m_Back = nullptr;
	}

	void Enqueue(const T& newItem) 
	{
		node* newNode = new node(newItem);
		if (m_Back != nullptr)
			m_Back->nextItem = newNode;

		else
			m_Front = newNode;

		m_Back = newNode;
		m_Size++;
	}
	bool Dequeue(T& container)
	{
		if (m_Front != nullptr)
		{
			container = m_Front->item;
			node* temp = m_Front;
			m_Front = temp->nextItem;
			if (m_Front == nullptr)
				m_Back = nullptr;

			temp->nextItem = nullptr;
			delete temp;
			m_Size--;
			return true;
		}
		return false;
	}

	bool IsEmpty()
	{
		return !m_Size;
	}

	int Size()
	{
		return m_Size;
	}

private:
	unsigned int m_Size = 0;
	node* m_Front = nullptr;
	node* m_Back = nullptr;
};

