# list_container<br />
Реализация двусвязного списка<br />

Техническое задание<br />

Разработать шаблонный класс List, реализующий структуру данных «двусвязный список». Данный класс должен обеспечивать хранение данных любого типа (включая пользовательские) и реализовывать следующие методы:<br />

1.	Конструкторы:<br />
1.1.	Конструктор по умолчанию.<br />
1.2.	Конструктор, принимающий количество элементов (создает список с помощью конструкторов по умолчанию для элементов).<br />
1.3.	Конструктор, принимающий количество элементов и значение, инициализирующее элементы списка.<br />
1.4.	Конструктор, принимающий интервал [beg, end), заданный итераторами.<br />
1.5.	Конструктор, принимающий список инициализации std::initializer_list.<br />
1.6.	Копирующий конструктор.<br />
1.7.	Конструктор переноса.<br />

2.	Функции-операции:<br />
2.1.	Операция присваивания с копированием.<br />
2.2.	Операция присваивания с переносом.<br />
<br />
3.	Методы:<br />
3.1.	begin() – возвращает итератор на начало списка.<br />
3.2.	end() – возвращает итератор на элемент, следующий за последним.<br />
3.3.	pushBack(elem) – добавляет копию аргумента elem в конец списка. Предоставить обычную версию и версию с переносом.<br />
3.4.	popBack() – удаляет последний элемент.<br />
3.5.	pushFront(elem) – вставляет копию аргумента elem в начало списка. Предоставить обычную версию и версию с переносом.<br />
3.6.	popFront() – удаляет первый элемент.<br />
3.7.	insert(pos, elem) – вставляет копию элемента elem перед позицией итератора pos и возвращает позицию нового элемента. Предоставить обычную версию и версию с переносом.<br />
3.8.	insert(pos, beg, end) – вставляет копии всех элементов интервала [beg, end) перед позицией итератора pos и возвращает позицию первого нового элемента (или итератор pos, если новых элементов нет).<br />
3.9.	erase(pos) – удаляет элемент в позиции итератора pos и возвращает позицию следующего элемента.<br />
3.10.	resize(num) – изменяет количество элементов до num (если размер size() увеличивается, новые элементы создаются конструкторами по умолчанию для элементов).<br />
3.11.	empty() – возвращает результат проверки того, что контейнер пуст.<br />
3.12.	size() – возвращает размер списка.<br />
3.13.	clear() – удаляет все элементы списка.<br />
<br />
Основные требования для класса List<br />
1.	Предусмотреть генерацию и обработку возможных исключительных ситуаций.<br />
<br />
Разработать шаблонный класс итератора ListIterator, предназначенный для обхода элементов контейнера List. Данный класс является оберткой для обычного указателя. ListIterator должен иметь методы, перечисленные ниже:<br />
1.	Конструкторы:<br />
1.1.	Конструктор, принимающий ссылку на контейнер List.<br />
1.2.	Копирующий конструктор.<br />
2.	Деструктор.<br />
3.	Функции-операции:<br />
3.1.	++, -- (префиксные и постфиксные).<br />
3.2.	* (разыменование).<br />
3.3.	= (присваивание).<br />
3.4.	==, != (сравнение итераторов).<br />
3.5.	-> (оператор доступа).<br />
3.6.	Операция приведения типа.<br />

