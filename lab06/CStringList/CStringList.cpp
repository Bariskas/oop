#include "stdafx.h"
#include "CStringList.h"
#include <cassert>

using namespace std;

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::Empty() const
{
	return static_cast<bool>(m_size);
}

void CStringList::Append(const std::string & data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else // empty list
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = make_unique<Node>(data, nullptr, move(m_firstNode));
	Node *newFirstNode = newNode.get();
	if (newNode->next)
	{
		newNode->next->prev = newFirstNode;
	}
	else
	{
		m_lastNode = newFirstNode;
	}
	m_firstNode = move(newNode);
	++m_size;
}

void CStringList::Clear()
{
	_Nodeptr _Pnode = this->_Nextnode(this->_Myhead());
	this->_Nextnode(this->_Myhead()) = this->_Myhead();
	this->_Prevnode(this->_Myhead()) = this->_Myhead();
	this->_Mysize() = 0;

	for (_Nodeptr _Pnext; _Pnode != this->_Myhead(); _Pnode = _Pnext)
	{	// delete an element
		_Pnext = this->_Nextnode(_Pnode);
		this->_Freenode(_Pnode);
	}
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

std::string & CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string const & CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}



CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{
}

std::string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}