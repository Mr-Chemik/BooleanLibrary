# BooleanLibrary
A C++ library to help you work with Boolean algebra.

(EN) Instruction for use:

All unique (used at least once) variables must be in alphabetical order and in uppercase.

'()' - open and close brackets

Logical operations:

'!' - NOT

'*' - AND

'+' - OR

Logical operations without a certain order:

'|' - NAND

'^' - XOR

'#' - NOR

'>' - IMPLY

'=' - XNOR


List of method:

Boolean::simlplify(string str) - simplifying a boolean expression (return data - string)

Boolean::truth_table(string str) - building a truth table based on a given expression (return data - vector<vector < bool > >)

Boolean::result(string str)- returning only the result of the truth table (return data - vector< bool >)

Exsample of simplifying:
Input: A>B+(!A*C)+D

Output: !A+D+B


Библиотека для помощи в работе с булевой алгеброй.

(RU) Инструкция по применению:

Все уникальные (содержащиеся в едином экземпляре) переменные должны быть в алфавитном порядке и в верхнем регистре.

'()' - открывающая и закрывающая скобка

Логические операции:

'!' - Отрицание

'*' - Конъюнкция

'+' - Дизъюнкция

Логические переменные без четкого порядка:

'|' - Штрих Шеффера

'^' - Исключающее или

'#' - Стрелка Пирса

'>' - Импликация

'=' - Эквивалентность

Список Методов:

Boolean::simlplify(string str) - упрощение булевого выражения (возвращаемые данные - string)

Boolean::truth_table(string str) - построение таблицы истинности по заданному выражению (возвращаемые данные - vector<vector < bool > >)

Boolean::result(string str)- возврат только результата таблицы истинности (возвращаемые данные - vector< bool >)

Пример упрощения:
Вход: A>B+(!A*C)+D

Выход: !A+D+B
