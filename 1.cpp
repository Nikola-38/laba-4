#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Общая функция, которую мы пытаемся решить
double function(double x) {
    return pow(x - 6, 2) + log(x);
}

// Производная функции
double derivative(double x) {
    return 2 * (x - 6) + 1 / x;
}



// Метод половинного деления для поиска корня
double HalfDivisionMethod(double& a, double& b, double epsilon) {
    int iteration = 1;
    double midPoint;

    cout << "N\ta\t\tb\t\tb-a" << endl;
    cout << "---------------------------------" << endl;

    if (function(a) * function(b) > 0) {
        cout << "Интервал выбран неправильно. В данном сегменте нет решения." << endl;
        return NAN;
    }

    while (abs(b - a) > epsilon) {
        midPoint = (b + a) / 2.0;
        cout << iteration << setw(10) << a << setw(14) << b << setw(14) << b - a << endl;
        if (function(a) * function(midPoint) < 0) {
            b = midPoint;
        } else {
            a = midPoint;
        }
        iteration++;
    }
    return midPoint;
}

// Комбинированный метод секущих-хорд
double CombinedMethod(double x0, double x1, double epsilon) {
    double x_minus1 = x0;
    double x = x1;
    int iteration = 1;

     cout << "N\ta\t\tb\t\tb-a" << endl;
    cout << "---------------------------------" << endl;

    while (abs(x - x_minus1) > epsilon) {

        cout << iteration << setw(10) << x_minus1 << setw(14) << x << setw(14) << x - x_minus1 << endl;

        double f_min1 = function(x_minus1);
        double f_x = function(x);
        double delta_x = x - x_minus1;
        double delta_f = f_x - f_min1;

        double x_plus1 = x - (x - x_minus1) * f_x / delta_f;

        cout << iteration++ << "\t" << x_plus1 << endl;

        x_minus1 = x;
        x = x_plus1;
    }

    return x;
}

//метод Хорд: a, b - пределы хорды
double chordMethod(double a0, double b0, double epsilon) {
    double x0 = (a0 + b0) / 2; // Начальное приближение
    int k = 0; // Счетчик итераций

    double M = max(abs(derivative(a0)), abs(derivative(b0))); // Верхняя граница
    double m = min(abs(derivative(a0)), abs(derivative(b0))); // Нижняя граница

    cout << "Итерация\tx\t\tf(x)" << endl;
    cout << "-----------------------------------" << endl;

    while (true) {
        double xk = x0 - function(x0) * (b0 - a0) / (function(b0) - function(a0)); // Вычисление xk+1
        cout << k << "\t" << xk << "\t" << function(xk) << endl;

        if (abs(xk - x0) <= epsilon) { // Проверка условия остановки
            return xk;
        }

        // Определение неподвижного конца отрезка
        if (derivative(a0) * derivative(xk) < 0) {
            b0 = xk;
        } else {
            a0 = xk;
        }

        x0 = xk;
        k++;
    }
}

int main() {
    double a = 0.0; // Начало интервала
    double b = 8.0; // Конец интервала
    double epsilon = 0.0001; // Погрешность

    system("chcp 65001"); 

    cout << "\nКорни, найденные методом половинного деления:" << endl;
    double rootHalfDivision = HalfDivisionMethod(a, b, epsilon);
    cout << "Root: " << rootHalfDivision << endl;

    cout << "\nКорни, найденные комбинированным методом секущих – хорд :" << endl;
    double rootIteration =CombinedMethod(a, b, epsilon);
    cout << "Root: " << rootIteration << endl;

    cout << "Корни, найденные методом хорд:" << endl;
    double rootSecant = chordMethod(a, b, epsilon);
    cout << "Root: " << rootSecant << endl;

    return 0;
}
