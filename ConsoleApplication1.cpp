// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;


class MatrixFunctions
{
private:
	static int** matrix;
	static int rowC, colC;

public:
	MatrixFunctions(int** m, int rowCount, int colCount);
	~MatrixFunctions();
	static int** MinMaxReplace();
	static int** RowsChange();
};

int** MatrixFunctions::matrix = {};
int MatrixFunctions::colC = 0;
int MatrixFunctions::rowC = 0;

MatrixFunctions::MatrixFunctions(int** m = {}, int rowCount = 0, int colCount = 0) // конструкт по умолчани.
{
	matrix = m;
	rowC = rowCount;
	colC = colCount;
}

MatrixFunctions::~MatrixFunctions() // деконструкт
{
	delete[] matrix;
}

int** MatrixFunctions::MinMaxReplace()
{
	if (rowC <= 0 || colC <= 0)
		return nullptr;

	int min = matrix[0][0];
	int minR = 0, minC = 0;

	int max = matrix[0][0];
	int maxR = 0, maxC = 0;

	for (int r = 0; r < rowC; r++)
	{
		for (int c = 0; c < colC; c++)
		{
			if (matrix[r][c] < min)
			{
				min = matrix[r][c];
				minR = r;
				minC = c;
			}

			if (matrix[r][c] > max)
			{
				max = matrix[r][c];
				maxR = r;
				maxC = c;
			}
		}
	}

	int buf = matrix[minR][minC];
	matrix[minR][minC] = matrix[maxR][maxC];
	matrix[maxR][maxC] = buf;

	return matrix;
}

int** MatrixFunctions::RowsChange()
{
	if (rowC <= 0 || colC <= 0)
		return nullptr;

	for (int i = 1; i < rowC; i += 2)
	{
		int* buf = matrix[i];
		matrix[i] = matrix[i - 1];
		matrix[i - 1] = buf;
	}

	return matrix;
}


//Процедура вывода матрицы на экран
void PrintMatr(int** matr, int* rowCount, int* colCount)
{
	std::cout << std::endl << "Массив:" << std::endl;
	for (int r = 0; r < *rowCount; r++)
	{
		for (int c = 0; c < *colCount; c++)
		{
			auto temp = matr[r][c];
			std::cout << temp << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	//Установить русскую кодировку консоли
	setlocale(LC_ALL, "Russian");

	//Выделение памяти под указатели
	int* colCount = new int(0);
	int* rowCount = new int(0);

	//Ввод размеров массива
	std::cout << "Введите кол-во столбцов массива:" << std::endl;
	std::cin >> *colCount;
	std::cout << "Введите кол-во строк массива:" << std::endl;
	std::cin >> *rowCount;

	//Выделение памяти на указатель на массив указателей
	int** arr = new int* [*rowCount];
	//Выделение памяти под каждый указатель на массив в массиве указателей
	for (int i = 0; i < *rowCount; i++)
	{
		arr[i] = new int[*colCount];
	}

	//Цикл ввода массива через консоль
	for (int r = 0; r < *rowCount; r++)
	{
		std::cout << "Строка " << r + 1 << ":" << std::endl;
		for (int c = 0; c < *colCount; c++)
		{
			std::cin >> arr[r][c];
		}
	}

	//Вывод исходного массива
	PrintMatr(arr, rowCount, colCount);

	//Для конструктора надо сделать объект
	MatrixFunctions* obj = new MatrixFunctions(arr, *rowCount, *colCount);

	//Получаем массив после перемены мест макс и мин элементов (берутся первые в случае дублирования)
	int** res = MatrixFunctions::MinMaxReplace();
	PrintMatr(res, rowCount, colCount);

	//Получаем массив смены местами строк
	res = MatrixFunctions::RowsChange();
	PrintMatr(res, rowCount, colCount);

	//Удаление указателей
	delete colCount;
	delete rowCount;
	delete obj;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
