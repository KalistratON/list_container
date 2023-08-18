#include <iostream>

#include "List.h"


int main()
{	
	try {
		
		size_t N = 100;
		List<int> list_1;
		List<int> list_2;
		
		list_1.pushBack(N);
		list_2.pushBack(N + 1);
		if (*list_1.begin() != N) std::cout << "Incorrect pushBack() function" << std::endl;
		if (*list_2.begin() != N + 1) std::cout << "Incorrect pushBack() function" << std::endl;

		ListIterator<List<int>> iter_1 = list_1.begin();
		ListIterator<List<int>> iter_2 = list_2.begin();
		
		for (int i = 0; i < N; i++) iter_1 = list_1.insert(iter_1, i);
		list_2.insert(iter_2, list_1.begin(), list_1.end());

		int j = 0;
		for (const auto& it : list_1) if (it != j++) {
			std::cout << "Incorrect insert(iterator, TypeElem) function" << std::endl; break;
		}
		
		j = 0;
		for (const auto& it : list_2) if (it != j++) {
			std::cout << "Incorrect insert(pos, beg, end) function" << std::endl; break;
		}

		list_1.popFront();
		list_2.popFront();
		if (*list_1.begin() != 1) std::cout << "Incorrect popFront() function" << std::endl;
		if (*list_2.begin() != 1) std::cout << "Incorrect popFront() function" << std::endl;

		size_t list_1_size = list_1.size();
		size_t list_2_size = list_2.size();

		list_1.popBack();
		list_2.popBack();
		if (list_1.size() != --list_1_size) std::cout << "Incorrect popBack() function" << std::endl;
		if (list_2.size() != --list_2_size) std::cout << "Incorrect popBack() function" << std::endl;

		list_1.pushFront(0);
		list_2.pushFront(0);
		if (*list_1.begin() != 0) std::cout << "Incorrect pushFront() function" << std::endl;
		if (*list_2.begin() != 0) std::cout << "Incorrect pushFront() function" << std::endl;

		list_1.erase(list_1.begin());
		list_2.erase(list_2.begin());
		if (*list_1.begin() != 1) std::cout << "Incorrect erase() function" << std::endl;
		if (*list_2.begin() != 1) std::cout << "Incorrect erase() function" << std::endl;

		if (list_1.clear(), !list_1.empty()) std::cout << "Incorrect clear() function" << std::endl;
		if (list_2.clear(), !list_2.empty()) std::cout << "Incorrect clear() function" << std::endl;
	}
	catch (const ListException& exc_) {
		
		std::cerr << exc_.what() << std::endl;
		std::cout << "Error of any function" << std::endl;
	}
	catch (const std::bad_alloc&) {
		
		std::cerr << "Error : bad allocation" << std::endl;
		std::cout << "Error of any function" << std::endl;
	}
	catch (const std::bad_cast&) {
		
		std::cerr << "Error : bad cast (to bool probably)" << std::endl;
		std::cout << "Error of any function" << std::endl;
	}
	catch (const std::exception&) {
		std::cout << "Error of any function (std)" << std::endl;
	}
	catch (...)	{
		std::cout << "Error of any function (not std)" << std::endl;
	}
	return 0;
}