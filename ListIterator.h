#pragma once

#include "ListException.h"

template <class Container>
class ListIterator {

	template<class T>
	friend class List;

public:

	typedef std::input_iterator_tag			iterator_category;
	typedef typename Container::data_type	value_type;
	typedef typename Container::data_type&	reference;
	typedef typename Container::data_type*	pointer;
	typedef ptrdiff_t						difference_type;

private:

	typename Container::data_type* ptr;

private:

	ListIterator(const Container& list) noexcept :
		ptr(list.head) {};

public:

	ListIterator(const ListIterator& ptr_in) noexcept :
		ptr(ptr_in.ptr) {};

	~ListIterator() {};

	ListIterator& operator++()
	{
		if (!ptr)
			throw ListException(ListException::BAD_ELEMENT);

		ptr = ptr->next;
		return *this;
	};

	ListIterator operator++(int) noexcept
	{	return *this;	};

	ListIterator& operator--()
	{
		if (!ptr)
			throw ListException(ListException::BAD_ELEMENT);

		ptr = ptr->prev;
		return *this;
	};

	ListIterator operator--(int) noexcept
	{	return *this;	};

	bool operator != (const ListIterator& iter) noexcept
	{
		return ptr != iter.ptr;
	}

	bool operator == (const ListIterator& iter) noexcept
	{
		return ptr == iter.ptr;
	}
	
	// decltype(auto) .. { return (...) } - return a reference of object : C++14
	/*typename Container::reference */ decltype(auto) operator*() const 
	{	
		if (ptr)
			throw ListException(ListException::BAD_ELEMENT);

		return (ptr->data);	
	};

	ListIterator& operator=(const ListIterator&) noexcept
	{	return *this;		};

	operator bool() const 
	{ 
		// bad_cast
		return static_cast<bool>(ptr);
	}
};