#pragma once
#include <iterator>

template<typename T>
class MyIterator
	: public std::iterator <std::bidirectional_iterator_tag, T>
{
	template <typename T> friend class CMyArray;
public:
	MyIterator();
	MyIterator(MyIterator const& otherIt);
	MyIterator& operator=(MyIterator const& otherIt);
	bool operator==(MyIterator const& otherIt)const;
	bool operator!=(MyIterator const& otherIt)const;
	T& operator*()const;
	T* operator->()const;
	MyIterator& operator++();
	MyIterator const operator++(int);
	MyIterator& operator--();
	MyIterator const operator--(int);
private:
	MyIterator(T* p);
	T* m_pointer;
};

template <typename T>
MyIterator<T>::MyIterator(T* p)
	: m_pointer(p)
{
}

template <typename T>
MyIterator<T>::MyIterator()
	: m_pointer(nullptr)
{
}

template <typename T>
MyIterator<T>::MyIterator(MyIterator const& otherIt)
	: m_pointer(otherIt.m_pointer)
{
}

template <typename T>
MyIterator<T>& MyIterator<T>::operator=(MyIterator const& otherIt)
{
	m_pointer = otherIt.m_pointer;
	return *this;
}

template <typename T>
bool MyIterator<T>::operator==(MyIterator const& otherIt) const
{
	return m_pointer == otherIt.m_pointer;
}

template <typename T>
bool MyIterator<T>::operator!=(MyIterator const& otherIt) const
{
	return m_pointer != otherIt.m_pointer;
}

template <typename T>
T& MyIterator<T>::operator*() const
{
	return *m_pointer;
}

template <typename T>
T* MyIterator<T>::operator->() const
{
	return m_pointer;
}

template <typename T>
MyIterator<T>& MyIterator<T>::operator++()
{
	++m_pointer;
	return *this;
}

template <typename T>
MyIterator<T> const MyIterator<T>::operator++(int)
{
	class MyIterator
		<T> temp(*this);
	++*this;
	return temp;
}

template <typename T>
MyIterator<T>& MyIterator<T>::operator--()
{
	--m_pointer;
	return *this;
}

template <typename T>
MyIterator<T> const MyIterator<T>::operator--(int)
{
	MyIterator<T> temp(*this);
	--*this;
	return *this;
}