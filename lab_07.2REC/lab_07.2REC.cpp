#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// Рекурсивне створення матриці
void Create(int** a, int rows, int cols, int low, int high,
    int i = 0, int j = 0)
{
    if (i >= rows)
        return;

    a[i][j] = low + rand() % (high - low + 1);

    if (j < cols - 1)
        Create(a, rows, cols, low, high, i, j + 1);
    else
        Create(a, rows, cols, low, high, i + 1, 0);
}

// Рекурсивне виведення матриці
void Print(int** a, int rows, int cols, int i = 0, int j = 0)
{
    if (i >= rows)
    {
        cout << endl;
        return;
    }

    cout << setw(5) << a[i][j];

    if (j < cols - 1)
        Print(a, rows, cols, i, j + 1);
    else
    {
        cout << endl;
        Print(a, rows, cols, i + 1, 0);
    }
}

// Рекурсивний пошук мінімального елемента рядка
int MinInRow(int** a, int row, int cols, int j = 0)
{
    if (j == cols - 1)
        return a[row][j];

    int minimum = MinInRow(a, row, cols, j + 1);

    if (a[row][j] < minimum)
        return a[row][j];

    return minimum;
}

// Рекурсивне обчислення суми мінімумів усіх рядків
int SumRowMins(int** a, int rows, int cols, int i = 0)
{
    if (i >= rows)
        return 0;

    return MinInRow(a, i, cols)
        + SumRowMins(a, rows, cols, i + 1);
}

int main()
{
    srand((unsigned)time(0));

    // rows — кількість рядків, cols — кількість стовпців
    const int rows = 7;
    const int cols = 6;

    // Межі значень елементів матриці
    const int low = -20;
    const int high = 30;

    int** a = new int* [rows];

    for (int i = 0; i < rows; i++)
        a[i] = new int[cols];

    Create(a, rows, cols, low, high);

    cout << "Matrix:" << endl;
    Print(a, rows, cols);

    int sum = SumRowMins(a, rows, cols);

    cout << "Sum of row minimums = " << sum << endl;

    for (int i = 0; i < rows; i++)
        delete[] a[i];

    delete[] a;

    return 0;
}