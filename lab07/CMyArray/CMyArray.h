#pragma once

#include <algorithm>
#include "CMyIterator.h"
#include <vector>

template <typename T>
class CMyArray
{
	typedef MyIterator<T> iterator;
	typedef MyIterator<const T> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> reverse_const_iterator;
public:
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	CMyArray() = default;

	explicit CMyArray(size_t size)
	{
		if (size > 0)
		{
			m_begin = RawAlloc(size);
			m_end = m_begin + size;
			m_endOfCapacity = m_begin + size;
		}
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			*it = T();
		}
	}

	CMyArray(CMyArray&& arr)
		: m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	CMyArray(std::initializer_list<T>const& initList)
	{
		const auto size = initList.size();
		auto from = initList.begin();
		auto to = initList.end();
		CopyArray(from, to, size);
	}

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		auto from = arr.m_begin;
		auto to = arr.m_end;
		CopyArray(from, to, size);
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T (value);
			++m_end;
		}
	}

	void Resize(size_t size)
	{
		if (size != GetSize())
		{
			if (size < this->GetSize())
			{
				DestroyItems(m_begin + size, m_end);
			}
			else if (size > this->GetSize() && size <= this->GetCapacity())
			{
				auto oldSize = this->GetSize();
				for (auto it = begin() + oldSize; it != begin() + size; ++it)	
				{
					*it = T();
				}
			}
			else if (size > this->GetCapacity())
			{
				CMyArray<T> temp(size);
				try
				{
					CopyItems(m_begin, m_end, temp.m_begin, temp.m_end);
					size_t itemsCountToInit = size - this->GetSize();
					while (itemsCountToInit != 1)
					{
						new (temp.m_end) T();
						++temp.m_end;
					}
					*this = std::move(temp);
				}
				catch (...)
				{
					DeleteItems(temp.m_begin, temp.m_end);
					throw;
				}

			}
			m_end = m_begin + size;
		}
	}

	void Clear()
	{
		DeleteItems(m_begin, m_end);
		m_begin = nullptr;
		m_end = nullptr;
	}

	T & operator[](size_t index)
	{
		if (GetSize() <= index)
		{	
			throw std::out_of_range("index out of range");
		}
		return m_begin[index];
	}

	const T & operator[](size_t index) const
	{
		if (GetSize() <= index)
		{
			throw std::out_of_range("index out of range");
		}
		return m_begin[index];
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	CMyArray& operator=(const CMyArray& arr)
	{
		if (std::addressof(arr) != this)
		{
			CMyArray copy(arr);
			std::swap(m_begin, copy.m_begin);
			std::swap(m_end, copy.m_end);
			std::swap(m_endOfCapacity, copy.m_endOfCapacity);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& arr)
	{
		if (&arr != this)
		{
			DeleteItems(m_begin, m_end);
			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;

			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}

		return *this;
	}

	iterator begin()
	{
		return iterator(m_begin);
	}

	iterator end()
	{
		return iterator(m_end);
	}

	const_iterator begin() const
	{
		return const_iterator(m_begin);
	}

	const_iterator end() const
	{
		return const_iterator(m_end);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(m_end);
	}
	reverse_iterator rend()
	{
		return reverse_iterator(m_begin);
	}

	reverse_const_iterator rbegin() const
	{
		return reverse_const_iterator(m_end);
	}
	reverse_const_iterator rend() const
	{
		return reverse_const_iterator(m_begin);
	}
private:
	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, const T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	void CopyArray(const T* from, const T* to, size_t size)
	{
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(from, to, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};
