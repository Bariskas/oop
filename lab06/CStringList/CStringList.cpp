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
	return m_size == 0;
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
	m_fictiveNode->prev = m_lastNode;
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

void CStringList::Delete(iterator it)
{
	auto node = it.m_node;
	if (node->prev)
	{
		node->prev->next = move(node->next);
	}
}

void CStringList::Clear()
{/*
	_Nodeptr _Pnode = this->_Nextnode(this->_Myhead());
	this->_Nextnode(this->_Myhead()) = this->_Myhead();
	this->_Prevnode(this->_Myhead()) = this->_Myhead();
	this->_Mysize() = 0;

	for (_Nodeptr _Pnext; _Pnode != this->_Myhead(); _Pnode = _Pnext)
	{	// delete an element
		_Pnext = this->_Nextnode(_Pnode);
		this->_Freenode(_Pnode);
	}*/
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

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode.get());
}

CStringList::iterator CStringList::end()
{
	return iterator(m_fictiveNode);
}

CStringList::const_iterator CStringList::begin() const
{
	return const_iterator(m_firstNode.get());
}

CStringList::const_iterator CStringList::end() const
{
	return const_iterator(m_fictiveNode);
}

CStringList::reverse_iterator CStringList::rbegin()
{
	return reverse_iterator(m_fictiveNode);
}

CStringList::reverse_iterator CStringList::rend()
{
	return reverse_iterator(m_firstNode.get());
}

CStringList::reverse_const_iterator CStringList::rbegin() const
{
	return reverse_const_iterator(m_fictiveNode);
}

CStringList::reverse_const_iterator CStringList::rend() const
{
	return reverse_const_iterator(m_firstNode.get());
}
