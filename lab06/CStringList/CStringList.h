#pragma once

#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node() : data(""), prev(nullptr), next(nullptr)
		{};
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};

	template<typename T>
	class CIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		friend CStringList;
		CIterator(Node *node);
	public:
		CIterator() = default;
		CIterator& operator=(const CIterator &other);
		std::string & operator*()const;
		std::string * operator->()const;
		CIterator & operator++();
		CIterator const operator++(int);
		CIterator & operator--();
		CIterator const operator--(int);
		bool operator==(CIterator const& other)const;
		bool operator!=(CIterator const& other) const;
	private:
		Node *m_node = nullptr;
	};

	typedef CIterator<std::string> iterator;
	typedef CIterator<const std::string> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;
public:
	size_t GetSize()const;
	bool Empty()const;
	void Append(const std::string& data);
	void PushFront(const std::string& data);
	void Delete(iterator it);
	void Clear();

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	reverse_const_iterator rbegin() const;
	reverse_const_iterator rend() const;

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode = std::make_unique<Node>();
	Node * m_lastNode = nullptr;
	Node * m_fictiveNode = m_firstNode.get();
};

template<typename T>
CStringList::CIterator<T>::CIterator(Node * node)
	:m_node(node)
{
}

template<typename T>
CStringList::CIterator<T>& CStringList::CIterator<T>::operator=(const CIterator& other)
{
	m_node = other.m_node;
	return *this;
}

template<typename T>
std::string & CStringList::CIterator<T>::operator*() const
{
	return m_node->data;
}

template <typename T>
std::string* CStringList::CIterator<T>::operator->() const
{
	return &(m_node->data);
}

template<typename T>
CStringList::CIterator<T> & CStringList::CIterator<T>::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

template<typename T>
CStringList::CIterator<T> const CStringList::CIterator<T>::operator++(int)
{
	CIterator temp(*this);
	++*this;
	return temp;
}

template<typename T>
CStringList::CIterator<T>& CStringList::CIterator<T>::operator--()
{
	m_node = m_node->prev;
	return *this;
}

template<typename T>
CStringList::CIterator<T> const CStringList::CIterator<T>::operator--(int)
{
	CIterator temp(*this);
	--*this;
	return temp;
}

template<typename T>
bool CStringList::CIterator<T>::operator==(CIterator const& other) const
{
	return m_node == other.m_node;
}

template<typename T>
bool CStringList::CIterator<T>::operator!=(CIterator const& other) const
{
	return m_node != other.m_node;
}