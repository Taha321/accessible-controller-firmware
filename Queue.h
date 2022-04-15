#pragma once

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
	~Queue()
	{
		delete m_Front;
		m_Front = nullptr;
		m_Back = nullptr;
	}

	void enqueue(const T& newItem) 
	{
		node* newNode = new node(newItem);
		if (m_Back != nullptr)
			m_Back->nextItem = newNode;

		else
			m_Front = newNode;

		m_Back = newNode;
		m_Size++;
	}
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
	T dequeue()
	{
		if (m_Front != nullptr)
		{
			T frontItem = m_Front->item;
			node* temp = m_Front;
			m_Front = temp->nextItem;
			if (m_Front == nullptr)
				m_Back = nullptr;

			temp->nextItem = nullptr;
			delete temp;
			m_Size--;
			return frontItem;
		}
    T dummy;
		return dummy;
	}

	bool isEmpty()
	{
		return !m_Size;
	}

	int count()
	{
		return m_Size;
	}

private:
	unsigned int m_Size = 0;
	node* m_Front = nullptr;
	node* m_Back = nullptr;
};
