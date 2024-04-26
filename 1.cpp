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

// Функция g(x) для метода простых итераций
double g(double x) {
    return exp((6 - sqrt(x * x)) / 2);
}

// Метод Ньютона для поиска корня
double newtonMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1;
    int iteration = 1; // Инициализируем счетчик итераций с 1

    cout << "Iteration\txn\t\txn+1\t\tdifference" << std::endl;

    do {
        xn_plus_1 = xn - function(xn) / derivative(xn);
        cout << iteration << setw(20) << xn << setw(20) << xn_plus_1 << setw(20) << abs(xn_plus_1 - xn) << endl;
        xn = xn_plus_1;
        iteration++; // Инкрементируем счетчик итераций
    } while (abs(function(xn)) > epsilon);

    return xn;
}

// Метод простых итераций для поиска корня
double simpleIterationMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1;
    int iteration = 0;
    bool repeated = false;
    vector<double> roots; // Вектор для хранения предыдущих корней

    cout << "Iteration\txn\t\txn+1\t\tdifference" << std::endl;

    do {
        xn_plus_1 = g(xn);
        cout << iteration << setw(15) << xn << setw(15) << xn_plus_1 << setw(15) << abs(xn_plus_1 - xn) << endl;

        // Проверяем, не повторяется ли ответ
        for (double root : roots) {
            if (abs(xn_plus_1 - root) < epsilon) {
                repeated = true;
                break;
            }
        }

        if (!repeated) {
            roots.push_back(xn_plus_1); // Добавляем корень в вектор
        } 
        xn = xn_plus_1;
        iteration++;
    } while (abs(g(xn)) > epsilon && iteration < 100 && !repeated);

    return xn;
}

// Метод половинного деления для поиска корня
double HalfDivisionMethod(double a, double b, double epsilon) {
    int iteration = 1;
    double midPoint;

    cout << "N\ta\t\tb\t\tb-a" << std::endl;
    cout << "---------------------------------" << std::endl;

    if (function(a) * function(b) < 0) { // проверка на разность знаков функции на концах отрезка
        while (abs(b - a) > epsilon) { // пока интервал больше погрешности
            midPoint = (b + a) / 2.0;
            cout << iteration << setw(10) << a << setw(14) << b << setw(14) << b - a << endl;
            if (function(a) * function(midPoint) < 0) {
                b = midPoint; // если функция имеет разные знаки, то правая точка становится серединой отрезка
            } else {
                a = midPoint; // иначе левая точка становится серединой отрезка
            }
            iteration++;
        }
        return midPoint; // возвращаем найденный корень
    } else {
        cout << "Интервал выбран неправильно. В данном сегменте нет решения" << endl;
        return NAN;
    }
}

int main() {
    double a = 0.0; // Начало интервала
    double b = 5.0; // Конец интервала
    double epsilon = 0.0001; // Погрешность
    system("chcp 65001"); // Команда для поддержки русского языка в консоли

    cout << "Корни, найденные методом Ньютона:" << endl;
    double rootNewton = newtonMethod((a + b) / 2, epsilon);
    cout << "Root: " << rootNewton << endl;

    cout << "\nКорни, найденные простым итерационным методом:" << endl;
    double rootSimpleIteration = simpleIterationMethod((a + b) / 2, epsilon);
    cout << "Root: " << rootSimpleIteration << endl;

    cout << "\nКорни, найденные методом половинного деления:" << endl;
    double rootHalfDivision = HalfDivisionMethod(a, b, epsilon);
    cout << "Root: " << rootHalfDivision << endl;

    return 0;
}
