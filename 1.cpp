#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Общая функция, которую мы пытаемся решить
double function(double x) {
    return pow(x, 2) + log(x) - 6;
}

// Производная функции
double derivative(double x) {
    return 2 * x + 1 / x;
}

// Функция для вывода таблицы итераций для метода Ньютона и простой итерации
void PrintTable(int iteration, double xn, double xn_plus_1, double difference) {
    cout << iteration << "\t" <<setw(10) << xn << "\t"<< setw(12) << xn_plus_1 << "\t"<< setw(14) << difference << endl;
}

void PrintfTablHalfDivisionMethod(double LeftPoint, double RightPoint, int N)
{
    if (N == 1)
    {
        cout << "N";
        cout << "\t     a ";
        cout << "\t\t\t     b ";
        cout << "\t\t\t     b-a ";
        cout << endl;
        cout << "----------------------------------------------------------------------------------";
        cout << endl;
    }
    cout << N << " |";
    cout <<"\t" << setw(10) << LeftPoint;
    cout << "\t\t" << setw(10) << RightPoint;
    cout << "\t\t" << setw(12)<< RightPoint - LeftPoint;
    cout << endl;
}


// Функция для вывода таблицы итераций для метода простой итерации
void PrintTableSimpleIterationMethod(int iteration, double xn, double xn_plus_1, double difference) {
    cout << iteration << "\t" << setw(10) << xn << "\t" << setw(12) << xn_plus_1 << "\t" << setw(14) << difference << endl;
}

// Метод Ньютона
double NewtonMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1 = xn - function(xn) / derivative(xn);
    int iteration = 1;

    cout << "Iteration\txn\t\txn+1\t\tdifference" << endl;
    while (abs(xn_plus_1 - xn) > epsilon) {
        PrintTable(iteration, xn, xn_plus_1, abs(xn_plus_1 - xn));
        xn = xn_plus_1;
        xn_plus_1 = xn - function(xn) / derivative(xn);
        iteration++;
    }
    return xn_plus_1;
}

// Метод простой итерации
double SimpleIterationMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1 = xn - function(xn) / derivative(x0);
    int iteration = 1;

    cout << "Iteration\txn\t\txn+1\t\tdifference" << endl;
    while (abs(xn_plus_1 - xn) > epsilon) {
        PrintTableSimpleIterationMethod(iteration, xn, xn_plus_1, abs(xn_plus_1 - xn));
        xn = xn_plus_1;
        xn_plus_1 = xn - function(xn) / derivative(x0);
        iteration++;
    }
    return xn_plus_1;
}

double HalfDivisionMethod(double LeftPoint, double RightPoint,double epsilon)
{
    int iteration = 1;
    double midPoint = 0.0;
    if (function(LeftPoint) * function(RightPoint) < 0)// проверка на разность знаков функции на концах отрезка
    {
        while (abs(RightPoint - LeftPoint) > epsilon)// пока интервал больше погрешности
        {
            midPoint = (RightPoint + LeftPoint) / 2;
            PrintfTablHalfDivisionMethod(LeftPoint, RightPoint, iteration);
            if (function(LeftPoint) * function(midPoint) < 0)  RightPoint = midPoint;// если функция имеет разные знаки, то правая точка середина отрезка
            else LeftPoint = midPoint;
            iteration++;
        }
    } 
    else {
        cout << "The interval is not selected correctly. There is no solution in the segment" << endl;
    }
    return midPoint;
}

int main() {
    double a = 1; // Начало интервала
    double b = 5; // Конец интервала
    double epsilon = 0.0001; // Погрешность
    system("chcp 65001"); // Команда для поддержки русского языка в консоли

    cout << "Корни, найденные методом Ньютона:" << endl;
    double rootNewton = NewtonMethod((a + b) / 2, epsilon);
    cout << "Root: " << rootNewton << endl;

    cout << "\nКорни, найденные простым итерационным методом:" << endl;
    double rootSimpleIteration = SimpleIterationMethod((a + b) / 2, epsilon);
    cout << "Root: " << rootSimpleIteration << endl;

    cout << "\nКорни, найденные методом половинного деления:" << endl;
    double rootHalfDivision = HalfDivisionMethod(a, b, epsilon);
    cout << "Root: " << rootHalfDivision << endl;

    return 0;
}
