// Autor: Иванов Егор

#ifndef MODULE_FOR_7_H
#define MODULE_FOR_7_H

// необходимые подключения
#include <string>
#include <iomanip>
#include <cassert>

using namespace std; // Пространоство имен

/// Функция вывода массива arr размера size на экран
template <typename Array>
void print_array(const Array *arr, long long size)
{
	for (long long i = 0; i < size; i++)		  // Цикл от 0 до конца массива
		cout << setprecision(3) << arr[i] << " "; // Происходит вывод с округлением в цикле
	cout << endl;								  // Переход на новую строку
}

/// Функция заполнения массива рандомными человеческими циферками
template <typename Array>
void rand_fill_array(Array *arr, size_t size, Array hign, Array low)
{
	int diap = hign - low;			  // Диапозон рандома
	for (size_t i = 0; i < size; i++) // Цикл для ввода заполнения
	{
		arr[i] = (float)rand() / RAND_MAX * diap + low; // Сама функция заполнения массива
	}
}

/// Функция вывода массива в текстовый файл
template <typename Array>
void array_to_file(const Array *arr, size_t size, const string &file_name)
{
	ofstream file(file_name); // Открытие файла Out file stream
	if (!file.is_open())	  // Если не открыт файл
	{
		throw runtime_error("File not found"); // Если что, то в ошибку
											   // return;
	}
	for (size_t i = 0; i < size; i++) // Цикл для вывода массива в файл
	{
		file << arr[i] << endl; // Выводим элемент, затем новую строку
	}
}

/// Функция загрузки массива из файла
template <typename Array>
void array_from_file(Array *arr, size_t size, const string &file_name)
{
	ifstream file(file_name); // Открытие файла In file stream
	if (!file.is_open())	  // Если не открыт файл
	{
		throw runtime_error("File not found"); // Если что, то в ошибку
											   // cout << "File not found:" << endl;          // Если что, то в ошибку
	}
	for (size_t i = 0; i < size; i++) // Цикл для чтения массива из файла
	{
		file >> arr[i]; // Построчно числа в массив
	}
}

/// Функция поиска кол-ва элементов массива в файле
size_t array_size_form_file(const string &file_name)
{
	size_t res = 0;			  // Переменная для счета кол-ва строк
	string line;			  // Строка, с помощью которой ищем кол-во строк
	ifstream file(file_name); // Открытие файла In file stream
	if (!file.is_open())	  // Если не открыт файл
	{
		throw runtime_error("File not found"); // Если что, то в ошибку
											   // return 0;
	}
	// while (getline(file, line)) // Цикл счёта кол-ва строк -> кол-ва элементов массива
	// {
	//     res++; // Цикл будет жить, пока getline делает переходы
	// }
	while (!file.eof())
	{
		char ch;
		file >> ch;
		res++;
	}

	file.close(); // Закрыть файл
	if (res == 0) // Ошибка, если файл пуст
		throw runtime_error("Array not found in file - file is empty");
	return res;
}

/// Загоняет массив в бинарный файл
template <typename Array>
void array_to_bin_file(const Array *arr, long long size, const string &file_name)
{
	ofstream file(file_name, ios::binary);
	file.write(reinterpret_cast<const char *>(&size), sizeof(size));
	file.write(reinterpret_cast<const char *>(arr), sizeof(float) * size);
	file.close();
}

/// Выгоняет массив из бинарного файла
template <typename Array>
void array_from_bin_file(Array *&arr, long long &size, const string &file_name)
{
	ifstream file(file_name, ios::binary);
	file.read(reinterpret_cast<char *>(&size), sizeof(size));
	arr = new Array[size];
	file.read(reinterpret_cast<char *>(arr), sizeof(Array) * size);
	file.close();
}

/// Функция проверяющая отсортирован ли динамический массив arr размера size (элементы должны быть сравнимыми)
/// Есть 2 сортировки: по возростанию(по умолчанию) и убыванию(задается третьим параметром rule: 'l' по убыванию)
template <typename Array>
bool arr_is_sort(const Array *arr, size_t size, const char rule = '2')
{
	if (size == 0 || size == 1) // Если 1 или 0 элементов возращаем true
		return true;

	if (rule == 'l')
		for (size_t i = 0; i < size - 1; i++)
		{
			if (arr[i] <= arr[i + 1])
				return false;
		}
	else
		for (size_t i = 0; i < size - 1; i++)
		{
			if (arr[i] >= arr[i + 1])
				return false;
		}
	return true;
}

/// Тест работы функции is_assert
void arr_is_sorted_assert()
{
	unsigned *sorted_int = new unsigned[3]{1, 2, 3};
	unsigned *unsorted_int = new unsigned[3]{4, 2, 3};
	assert(arr_is_sort(sorted_int, 3));
	assert(arr_is_sort(unsorted_int, 3) == false);

	double *sorted_double = new double[3]{1.01, 1.02, 1.03};
	double *unsorted_double = new double[3]{1.01, 1.002, 1.03};
	assert(arr_is_sort(sorted_double, 3));
	assert(arr_is_sort(unsorted_double, 3) == false);

	unsigned *reverse_sorted_unsigned = new unsigned[3]{3, 2, 1};
	assert(arr_is_sort(reverse_sorted_unsigned, 3, 'l'));

	string *sorted_string = new string[3]{"aaa", "aab", "aac"};
	string *unsorted_string = new string[3]{"aad", "aab", "aac"};
	assert(arr_is_sort(sorted_string, 3));
	assert(arr_is_sort(unsorted_string, 3) == false);

	delete[] sorted_int;
	delete[] unsorted_int;
	delete[] sorted_double;
	delete[] unsorted_double;
	delete[] reverse_sorted_unsigned;
	delete[] sorted_string;
	delete[] unsorted_string;
}

/// Последовательный поиск по массиву, если key будет найден, то вернется его индекс, если же нет, то вернется число -1
template <typename Array>
long long sequential_search(const Array arr[], long long size, Array key)
{
	arr_is_sort(arr, size);
	for (long long i = 0; i < size; ++i)
		if (arr[i] == key)
			return i; // значение найдено, возвращаем индекс
	return -1;		  // значение не найдено, возращаем -1
}

/// Тест работы функции sequential_search
void sequential_search_assert()
{
	long long sizeSmall = 3;

	int *a = new int[sizeSmall]{1, 2, 3};
	double *b = new double[sizeSmall]{1.01, 1.02, 1.03};
	string *c = new string[sizeSmall]{"Sponchbob", "Sandy", "Patric"};

	long long temp2 = sequential_search(a, sizeSmall, 3);
	assert(temp2 == 2);

	long long temp = sequential_search(b, sizeSmall, 1.01);
	assert(temp == 0);

	string Squid = "Squid";
	long long temp3 = sequential_search(c, sizeSmall, Squid);
	assert(temp3 == -1);
	// dsda
	delete[] a;
	delete[] b;
	delete[] c;
}

/// Функция поиска ближайшего элемента к x в массиве
/// arr - массив, n - размер массива, x - то, что нужно найти, comparisions - кол-во сравнений
/// (n-1)*4+3 => Big-O(n), т.к. константы обрезаем
template <typename Array>
Array find_closest(Array arr[], size_t n, Array x, int &comparisions)
{
	comparisions = 1; // если пришел массив с 1 элементом, то возращаем это
	if (n == 1)		  //"самый ближайший" элемент
		return arr[0];

	Array closest = arr[0];		  // предполагаем, что первый элемент наиболее близок
	Array diff = abs(x - arr[0]); // находим разницу между x и первым элементом

	for (size_t i = 1; i < n; i++)
	{
		Array currentDiff = abs(x - arr[i]); // находим элемент в момент итерации
		if (currentDiff < diff)				 // вот сравнение
		{
			comparisions++;
			closest = arr[i];	// перемещаемся по масс
			diff = currentDiff; // заменяем конкретный элемент на элемент в момент итерации
		}
	}
	return closest;
}

/// Тестирование функции find_closest
void find_closest_assert()
{
	int sizeSmall = 6;
	int voidest;
	int *a = new int[sizeSmall]{1, 2, 3, 4, 5, 6};
	double *b = new double[sizeSmall]{1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int *c = new int[sizeSmall]{5, 3, 2, 67, 34, 1};

	int temp = find_closest(a, sizeSmall, 8, voidest);
	assert(temp == 6);

	double temp2 = find_closest(b, sizeSmall, 1.032, voidest);
	assert(temp2 == 1.03);

	int temp3 = find_closest(c, sizeSmall, 31, voidest);
	assert(temp3 == 34);

	delete[] a;
	delete[] b;
	delete[] c;
}

/// Функция сортировки массива пузырьком по порядку - от меньшего к большему
/// arr - массив типа Array, size - размер массива
/// Т.к. цикл вложенный, то его BigO(n^2)
template <typename Array>
void sort_buble(Array *arr, size_t size)
{
	Array temp;							  // Временное хранение
	for (size_t i = 0; i < size - 1; i++) // Один цикл
	{
		for (size_t j = 0; j < size - i - 1; j++) // Второй цикл
		{
			if (arr[j] > arr[j + 1]) // Если по с пом циклов нашли элементы, где пред > след
			{
				temp = arr[j]; // то поменять элементы местами
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/// Функция бинарного поиска элемента key в массиве arr размера size
/// Возращает индекс элемента либо -1, если элемент не найден, либо -2, если массив не отсортирован
/// Массив должен быть обязательно отсортирован!
template <typename Array>
long long binary_search(Array *arr, size_t size, Array key)
{

	if (arr_is_sort(arr, size) == false)
	{
		return -2;
	}

	int l = 0;	  // Пол = 0
	int r = size; // Потолочек, переназначение для того, чтобы изменять r
	int mid;	  // Серединка

	while (l <= r)
	{
		mid = (l + r) / 2; // Находим срединный индекс отрезка [l,r]

		if (arr[mid] == key) // Ну а вдруг смередина и есть искомый элемент
			return mid;
		if (arr[mid] > key) // Проверяем, какую часть нужно отбросить
			r = mid - 1;	// то верх
		else
			l = mid + 1; // то низ
	}

	return -1; // Если не нашли
}

/// Тест работы функции binary_search
void binary_search_assert()
{
	long long sizeSmall = 6;

	int *a = new int[sizeSmall]{1, 2, 3, 4, 5, 6};
	double *b = new double[sizeSmall]{1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	// один не отсортированный
	int *c = new int[sizeSmall]{5, 3, 2, 5, 3, 2};

	// поиск последней позиции
	long long temp2 = binary_search(a, sizeSmall, 6);
	assert(temp2 == 5);

	// посик средней позиции
	long long temp3 = binary_search(a, sizeSmall, 3);
	assert(temp3 == 2);

	// ну не нашел
	long long temp4 = binary_search(a, sizeSmall, 54);
	assert(temp4 == -1);

	// в начальной позиции
	long long temp = binary_search(b, sizeSmall, 1.01);
	assert(temp == 0);

	// и если массивчик не отсортирован :(
	long long temp5 = binary_search(c, sizeSmall, 2);
	assert(temp5 == -2);

	delete[] a;
	delete[] b;
	delete[] c;
}

/// Функция бинарного поиска элемента key в массиве arr размера size
/// Возращает индекс элемента либо -1, если элемент не найден, либо -2, если массив не отсортирован
/// Массив должен быть обязательно отсортирован!
template <typename Array>
long long interpolation_search(Array arr[], size_t size, Array key)
{
	size_t low = 0;			// Верхняя граница
	size_t high = size - 1; // Нижняя граница

	if (arr_is_sort(arr, size) == false)
	{ // Проверка на сортировку массива
		return -2;
	}

	while (low <= high && key >= arr[low] && key <= arr[high]) // Пока не найдем индекц нашего key
	{
		if (low == high) // если в массиве 1 элемент
		{
			if (arr[low] == key) // и этот элемент есть key
				return low;		 // возращаем его индекс
			return -1;			 // если нет то -1, что значит key не найден
		}

		// Формула интерполяции для определения предполагаемого положения искомого элемента
		size_t pos = low + ((key - arr[low]) * (high - low) / (arr[high] - arr[low]));

		if (arr[pos] == key) // если вдруг по угадайке нагадали позицию элементаааа, то возращаем ее
			return pos;
		if (arr[pos] < key) // если угадайка меньше
			low = pos + 1;	// увеличиваем нижнюю границу на это кол-во
		else
			high = pos - 1; // или - верхнюю
	}

	return -1; // если не нашли вообще возращаем -1
}

/// Тест работы функции interpolation_search
void interpolation_search_assert()
{
	long long sizeSmall = 6;

	int *a = new int[sizeSmall]{1, 2, 3, 4, 5, 6};
	double *b = new double[sizeSmall]{1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	// один не отсортированный
	int *c = new int[sizeSmall]{5, 3, 2, 5, 3, 2};

	// поиск последней позиции
	long long temp2 = interpolation_search(a, sizeSmall, 6);
	assert(temp2 == 5);

	// посик средней позиции
	long long temp3 = interpolation_search(a, sizeSmall, 3);
	assert(temp3 == 2);

	// ну не нашел
	long long temp4 = interpolation_search(a, sizeSmall, 54);
	assert(temp4 == -1);

	// в начальной позиции
	long long temp = interpolation_search(b, sizeSmall, 1.01);
	assert(temp == 0);

	// и если массивчик не отсортирован :(
	long long temp5 = interpolation_search(c, sizeSmall, 2);
	assert(temp5 == -2);

	delete[] a;
	delete[] b;
	delete[] c;
}

/// Процедура сортировки массива методом простого выбора
/// Принимает массив типа Array, размер массива
template <typename Array>
void selectionSortRecursive(Array arr[], size_t n, int index = 0)
{
	if (index == n - 1)
	{ // выходим из ок... функции, если размер = 1
		return;
	}

	int min_index = index; // находим индекс минимального элемента
	for (int j = index + 1; j < n; j++)
	{
		if (arr[j] < arr[min_index])
		{				   // сравниваем элементы
			min_index = j; // заменяем индекс, если сравнение прошло
		}
	}

	swap(arr[index], arr[min_index]);		   // меняем элемент местами
	selectionSortRecursive(arr, n, index + 1); // рекурсируем
}

/// Тест работы функции selectionSortRecursive
void selectionSortRecursive_assert()
{
	long long sizeSmall = 6;

	int *a = new int[sizeSmall]{6, 2, 3, 4, 5, 1};
	double *b = new double[sizeSmall]{1.04, 1.05, 1.03, 1.01, 1.02, 1.06};
	int *c = new int[sizeSmall]{5, 3, 2, 5, 3, 2};

	int *a_ = new int[sizeSmall]{1, 2, 3, 4, 5, 6};
	double *b_ = new double[sizeSmall]{1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int *c_ = new int[sizeSmall]{2, 2, 3, 3, 5, 5};

	// поиск последней позиции
	selectionSortRecursive(a, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(a[i] == a_[i]);
	}

	// посик средней позиции
	selectionSortRecursive(b, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(b[i] == b_[i]);
	}

	// ну не нашел
	selectionSortRecursive(c, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(c[i] == c_[i]);
	}

	delete[] a, b, c;
	delete[] a_, b_, c_;
}

/// Процедура сортировки массива методом простого выбора
/// Принимает массив типа Array, размер массива  int *a = new int[6]{3, 4, 90, 14, 23, 12};
template <typename Array>
void selectionSortIterative(Array arr[], size_t n)
{
	for (int i = 0; i < n - 1; i++)
	{ // тут определяем итерацию одного элемента
		int min_index = i;
		for (int j = i + 1; j < n; j++)
		{ // тут определяем итерацию элемента с чем сравнимаем
			if (arr[j] < arr[min_index])
			{
				min_index = j; // ну и если проходит сравнение меняем индексы
			}
		}
		swap(arr[i], arr[min_index]); // и меняем значения в массиве
	}
}

/// Тест работы функции selectionSortIterative
void selectionSortIterative_assert()
{
	long long sizeSmall = 6;

	int *a = new int[sizeSmall]{6, 2, 3, 4, 5, 1};
	double *b = new double[sizeSmall]{1.04, 1.05, 1.03, 1.01, 1.02, 1.06};
	int *c = new int[sizeSmall]{5, 3, 2, 5, 3, 2};

	int *a_ = new int[sizeSmall]{1, 2, 3, 4, 5, 6};
	double *b_ = new double[sizeSmall]{1.01, 1.02, 1.03, 1.04, 1.05, 1.06};
	int *c_ = new int[sizeSmall]{2, 2, 3, 3, 5, 5};

	// поиск последней позиции
	selectionSortIterative(a, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(a[i] == a_[i]);
	}

	// посик средней позиции
	selectionSortIterative(b, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(b[i] == b_[i]);
	}

	// ну не нашел
	selectionSortIterative(c, sizeSmall);
	for (int i = 0; i > sizeSmall; i++)
	{
		assert(c[i] == c_[i]);
	}

	delete[] a, b, c;
	delete[] a_, b_, c_;
}

#endif