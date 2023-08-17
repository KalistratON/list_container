#include <iostream>

#include "List.h"


int main()
{	
	try {

		size_t N = 10;

		// validation of initialization:
		List<int> list1;
		List<int> list2(N);
		List<int> list3(list1);
		List<int> list4(std::move(list3));

		List<decltype('a')> list5 = {'a', 'b', 'h', 'c', 't'};
		List<decltype('a')> list6(list5.begin(), list5.end());

		list3 = std::move(list4);
		list2 = list1;

		// validation of list functional:
		List<int> list(1);
		List<int> listInit = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		if (!list.empty())
		{
			list.insert(list.begin(), listInit.begin(), listInit.end());
			list.insert(++(++(++list.begin())), *(++(++list.begin())));

			list.erase(++(++(++list.begin())));

			list.pushFront(-1);
			list.pushBack(-1);

			list.popFront();
			list.popBack();

			std::cout << "Current size of list : " << list.size() << std::endl;
		}

	}
	catch (const ListException& exc_) {
		std::cerr << exc_.what() << std::endl;
	}
	catch (const std::bad_alloc&) {


	}
	catch (const std::bad_cast&) {

	}
	catch (const std::exception&) {

	}
	catch (...)	{

	}
	return 0;
}