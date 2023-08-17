#pragma once

#include <algorithm>
#include <memory>

#include "ListIterator.h"
#include "ListException.h"

template<class T>
class List {

	template<class Container>
	friend class ListIterator;

private:

	struct Node {
		T	data;
		Node* prev;
		Node* next;
	};

	Node* head;
	Node* tail;

public:

	using value_type				= T;
	using reference					= T&;
	using const_reference			= const T&;

	using data_type					= Node;
	using reference_data_type		= Node&;
	using const_reference_data_type = const Node&;
	
	using iterator					= ListIterator<List>;
	using const_iterator			= ListIterator<List<const T>>;

private:
	void returnTo()
	{
		while (head->prev)
			head = head->prev;
		tail = head;
		while (tail->next)
			tail = tail->next;
	}

public:

	List() noexcept :
		head(nullptr),
		tail(nullptr) {};

	// Добавить буферную функцию

	/*explicit */ List(size_t count) :
		head(nullptr),
		tail(nullptr)
	{
		if (count < 0)
			throw ListException(ListException::BAD_SIZE);

		Node* cur_elem		= head;
		Node* cur_prev_elem = nullptr;

		for (size_t i = 0; i < count; i++)
		{
			cur_elem		= new Node;
			cur_elem->data	= T();
			cur_elem->prev	= cur_prev_elem;

			if (i)
				cur_prev_elem->next = cur_elem;

			cur_elem->next = nullptr;

			if (!i)
				head = cur_elem;

			cur_prev_elem	= cur_elem;
			cur_elem		= cur_elem->next;
		}
		tail = cur_prev_elem;
	};

	explicit List(iterator beg, iterator end) :
		head(nullptr),
		tail(nullptr)
	{
		Node* cur_elem		= head;
		Node* cur_prev_elem = nullptr;

		for (auto it = beg; it != end; ++it)
		{
			cur_elem		= new Node;
			cur_elem->data	= *it;
			cur_elem->prev	= cur_prev_elem;
			
			if (it != beg)
				cur_prev_elem->next = cur_elem;
			
			cur_elem->next	= nullptr;

			if (it == beg)
				head = cur_elem;

			cur_prev_elem	= cur_elem;
			cur_elem		= cur_elem->next;
		}
		tail = cur_prev_elem;
	}
	
	List(std::initializer_list<T> list) :
		head(nullptr),
		tail(nullptr)
	{
		Node* cur_elem = head;
		Node* cur_prev_elem = nullptr;

		for (auto it = list.begin(); it != list.end(); ++it)
		{
			cur_elem		= new Node;
			cur_elem->data	= *it;
			cur_elem->prev	= cur_prev_elem;
			
			if (it != list.begin())
				cur_prev_elem->next = cur_elem;
			
			cur_elem->next = nullptr;

			if (it == list.begin())
				head = cur_elem;

			cur_prev_elem	= cur_elem;
			cur_elem		= cur_elem->next;
		}
		tail = cur_prev_elem;
	}

	List(const List& list) :
		head(nullptr),
		tail(nullptr)
	{
		// TEST_REQUIRED

		if (!list.head)
			return;

		head		= new Node;

		head->data	= list.head->data;
		head->next	= nullptr;
		head->prev	= nullptr;

		tail = head;

		Node* cur_out = list.head->next;
		Node* cur_in = head;

		while (cur_out)
		{
			cur_in->next = new Node;
			
			Node* cur_in_next = cur_in->next;
			cur_in_next->prev = cur_in;
			cur_in_next->data = cur_out->data;

			cur_in	= cur_in->next;
			cur_out = cur_out->next;
		}
		cur_in->next = nullptr;
		tail = cur_in;
	}

	List(List&& list) noexcept :
		head(nullptr),
		tail(nullptr)
	{
		// TEST_REQUIRED

		if (!list.head)
			return;

		head = list.head;
		tail = list.tail;

		Node* cur_out	= list.head->next;
		Node* cur_in	= head;

		list.head = nullptr;
		list.tail = nullptr;

		while (cur_out)
		{
			cur_in->next = cur_out;

			Node* cur_in_next = cur_in->next;
			cur_in_next->prev = cur_in;
			cur_in_next->data = cur_out->data;

			cur_in = cur_in->next;
			cur_out = cur_out->next;
		}

		cur_in->next	= nullptr;
		tail			= cur_in;
	}

	~List() /*noexcept*/
	{
		if (!head)
			return;

		Node* temp = head->next;
		
		while (temp)
		{
			delete head;
			head = temp;
			temp = temp->next;
		}
	}

	List& operator = (List& list)
	{
		List temp(list);
		(*this) = std::move(temp);
		return *this;
	}

	List& operator = (List&& list) noexcept
	{
		// TEST_REQUIRED

		if (head = nullptr, tail = nullptr, !list.head)
			return *this;

		head = list.head;
		tail = list.tail;

		Node* cur_out = list.head->next;
		Node* cur_in = head;

		list.head = nullptr;
		list.tail = nullptr;

		while (cur_out)
		{
			cur_in->next = cur_out;

			Node* cur_in_next = cur_in->next;
			cur_in_next->prev = cur_in;
			cur_in_next->data = cur_out->data;

			cur_in = cur_in->next;
			cur_out = cur_out->next;
		}

		cur_in->next = nullptr;
		tail = cur_in;

		return *this;
	}

	void pushBack(const_reference data_in = value_type())
	{
		if (!head)
		{
			head		= new Node;
			head->next	= nullptr;
			head->prev	= nullptr;
			head->data	= data_in;
			tail		= head;
			return;
		}

		tail->next		= new Node;
		Node* prev_tail = tail;

		tail		= tail->next;
		tail->prev	= prev_tail;
		tail->next	= nullptr;
		tail->data	= data_in;
	}

	void pushBack(T&& data_in)
	{
		if (!head)
		{
			head		= new Node;
			head->next	= nullptr;
			head->prev	= nullptr;
			head->data	= std::move(data_in);
			tail		= head;
			return;
		}

		tail->next		= new Node;
		Node* prev_tail = tail;

		tail		= tail->next;
		tail->prev	= prev_tail;
		tail->next	= nullptr;
		tail->data	= std::move(data_in);
	}

	void popBack()
	{
		if (!head)
			throw ListException(ListException::BAD_POP);

		if (!head->next)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node* del	= tail;
		tail		= tail->prev;
		tail->next	= nullptr;
		delete del;
	}

	void pushFront(const_reference data_in = value_type())
	{
		if (!head)
		{
			head		= new Node;
			head->next	= nullptr;
			head->prev	= nullptr;
			head->data	= data_in;
			tail		= head;
			return;
		}

		Node* new_head = new Node;
		new_head->data = data_in;
		new_head->next = head;
		new_head->prev = nullptr;

		head->prev	= new_head;
		head		= new_head;
	}

	void pushFront(value_type&& data_in)
	{
		if (!head)
		{
			head		= new Node;
			head->next	= nullptr;
			head->prev	= nullptr;
			head->data	= data_in;
			tail		= head;
			return;
		}

		Node* new_head = new Node;
		new_head->data = std::move(data_in);
		new_head->next = head;
		new_head->prev = nullptr;

		head->prev	= new_head;
		head		= new_head;
	}

	void popFront()
	{
		if (!head)
			throw ListException(ListException::BAD_POP);

		if (!head->next)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		Node* del	= head;
		head		= head->next;
		head->prev	= nullptr;
		delete del;
	}

	iterator insert(iterator pos, const_reference elem)
	{
		if (!(bool)pos)
			throw ListException(ListException::BAD_ELEMENT);

		auto elem_prev	= pos.ptr->prev;
		auto new_elem	= new Node{ elem, pos.ptr->prev, pos.ptr };

		if (elem_prev)
			elem_prev->next = new_elem;
		pos.ptr->prev	= new_elem;

		returnTo();

		return --iterator(pos);
	}

	iterator insert(iterator pos, iterator beg, iterator end)
	{
		iterator result(pos);
		
		for (auto it = beg; it != end; ++it)
		{
			if (it != beg)
				this->insert(pos, *it);
			else
				result = this->insert(pos, *it);
		}

		return result;
	}

	iterator erase(iterator pos)
	{
		if (pos == begin())
			head = head->next;

		auto del_elem	= pos.ptr;
		auto prev_elem	= pos.ptr->prev;
		auto next_elem	= pos.ptr->next;

		prev_elem->next = next_elem;
		next_elem->prev = prev_elem;

		auto result = ++iterator(pos);
		delete del_elem;

		returnTo();

		return result;
	}

	constexpr bool empty() const
	{
		return static_cast<bool>(!head);
	}

	constexpr size_t size() const noexcept
	{
		size_t size		= -1;
		Node* cur_elem	= head;

		while (++size, cur_elem)
			cur_elem = cur_elem->next;

		return size;
	}

	void clear() noexcept
	{
		if (!head)
			return;

		Node* temp = head->next;

		while (temp)
		{
			delete head;
			head = temp;
			temp = temp->next;
		}
		head = nullptr;
		tail = nullptr;
	}

	void resize(size_t size)
	{
		size_t old_size = this->size() + 1;

		if (old_size > size + 1)
			while(--old_size, old_size > size)
				this->popBack();
		else
		{
			old_size -= 2;
			while (++old_size, old_size < size)
				this->pushBack();
		}
	}
	
	iterator begin() noexcept
	{
		return iterator(*this);
	}

	iterator end() noexcept
	{
		return iterator(List<T>());
	}
};