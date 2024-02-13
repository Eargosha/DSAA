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
void print_array(const Array *arr, size_t size)
{
	for (unsigned i = 0; i < size; i++)			  // Цикл от 0 до конца массива
		cout << setprecision(3) << arr[i] << " "; // Происходит вывод с округлением в цикле
	cout << endl;								  // Переход на новую строку
}

/// Функция заполнения массива рандомными человеческими циферками
template <typename Array>
void rand_fill_array(Array *arr, size_t size, Array hign, Array low)
{
	int diap = hign - low;				// Диапозон рандома
	for (unsigned i = 0; i < size; i++) // Цикл для ввода заполнения
	{
		arr[i] = (float)rand() / RAND_MAX * diap + low; // Сама функция заполнения массива
														// RAND_MAX - константа записанная в бибилиотеке cstdlib.  Гарантируется, что это значение не менее 32767
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
	for (unsigned i = 0; i < size; i++) // Цикл для вывода массива в файл
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
	for (unsigned i = 0; i < size; i++) // Цикл для чтения массива из файла
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
void array_to_bin_file(const Array *arr, size_t size, const string &file_name)
{
	ofstream file(file_name, ios::binary);
	file.write(reinterpret_cast<const char *>(&size), sizeof(size));
	file.write(reinterpret_cast<const char *>(arr), sizeof(float) * size);
	file.close();
}

/// Выгоняет массив из бинарного файла
template <typename Array>
void array_from_bin_file(Array *&arr, size_t &size, const string &file_name)
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
size_t sequential_search(const Array arr[], size_t size, Array key)
{
	for (size_t i = 0; i < size; ++i)
		if (arr[i] == key)
			return i; // значение найдено, возвращаем индекс
	return -1;		  // значение не найдено, возращаем -1
}

/// Тест работы функции sequential_search
void sequential_search_assert()
{
	size_t sizeSmall = 3;

	int *a = new int[sizeSmall]{1, 2, 3};
	double *b = new double[sizeSmall]{1.01, 1.02, 1.03};
	string *c = new string[sizeSmall]{"Sponchbob", "Sandy", "Patric"};

	size_t temp2 = sequential_search(a, sizeSmall, 3);
	assert(temp2 == 2);

	size_t temp = sequential_search(b, sizeSmall, 1.01);
	assert(temp == 0);

	string Squid = "Squid";
	size_t temp3 = sequential_search(c, sizeSmall, Squid);
	assert(temp3 == -1);
	//dsda
	delete[] a;
	delete[] b;
	delete[] c;
}

/// Функция поиска ближайшего элемента к x в массиве
/// arr - массив, n - размер массива, x - то, что нужно найти, comparisions - кол-во сравнений
/// (n-1)*4+3 => Big-O(n), т.к. константы обрезаем
template <typename Array>
Array find_closest(Array arr[], size_t n, Array x, size_t &comparisions)
{
	comparisions = 1; //если пришел массив с 1 элементом, то возращаем это
	if (n == 1)		  //"самый ближайший" элемент
		return arr[0];

	Array closest = arr[0];		  //предполагаем, что первый элемент наиболее близок
	Array diff = abs(x - arr[0]); //находим разницу между x и первым элементом

	for (size_t i = 1; i < n; i++)
	{
		Array currentDiff = abs(x - arr[i]); //находим элемент в момент итерации
		if (currentDiff < diff)   //вот сравнение
		{
			comparisions++;	
			closest = arr[i];		//перемещаемся по масс		
			diff = currentDiff;		//заменяем конкретный элемент на элемент в момент итерации
		}
	}
	return closest;
}

#endif