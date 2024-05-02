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


// Вспомогательная функция для метода простых итераций
// Функция g(x) для метода простых итераций
double g(double x) {
    return exp((6 - sqrt(x * x)) / 2);
}

double simpleIterationMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1;
    int iteration = 0;

    cout << "Iteration\txn\t\txn+1\t\tdifference" << endl;

    do {
        xn_plus_1 = g(xn);
        cout << iteration << "\t" << setprecision(10) << xn << "\t" << setprecision(10) << xn_plus_1 << "\t" << fixed << setprecision(6) << abs(xn_plus_1 - xn) << endl;

        if (abs(xn_plus_1 - xn) < epsilon) {
            return xn_plus_1; // Возвращаем найденный корень
        }

        xn = xn_plus_1;
        iteration++;
    } while (iteration < 50);
    return xn_plus_1; // Возвращаем найденный корень

}

// Метод отделения корней
pair<double, double> separate_roots(double a, double b, double epsilon) {
    if (function(a) * function(b) >= 0) {
        cout << "На концах отрезка [a, b] функция имеет одинаковые знаки, метод отделения корней не может быть применен." << endl;
        return make_pair(NAN, NAN);
    }

    double c = a;
    while ((b - a) >= epsilon) {
        c = (a + b) / 2;
        if (function(c) == 0.0) {
            break;
        } else if (function(c) * function(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    return make_pair(a, b);
}

// Метод половинного деления для поиска корня
double HalfDivisionMethod(double a, double b, double epsilon) {
    int iteration = 1;
    double midPoint;

    cout << "N\ta\t\tb\t\tb-a" << std::endl;
    cout << "---------------------------------" << std::endl;

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

int main() {
    double a = 0.0; // Начало интервала
    double b = 5; // Конец интервала
    double epsilon = 0.0001; // Погрешность
    double X0 =  0.5; 
    system("chcp 65001"); // Команда для поддержки русского языка в консоли

    cout << "\nКорни, найденные простым итерационным методом:" << endl;
    double rootSimpleIteration = simpleIterationMethod(X0, epsilon);
    if (!isnan(rootSimpleIteration)) {
        cout << "Root: " << setprecision(6) << rootSimpleIteration << endl;
    }
    
    cout << "Интервалы, содержащие корни, найденные методом отделения корней:" << endl;
    pair<double, double> rootInterval = separate_roots(a, b, epsilon);
    if (!isnan(rootInterval.first) && !isnan(rootInterval.second)) {
        cout << "Интервал: [" << rootInterval.first << ", " << rootInterval.second << "]" << endl;
    };

    cout << "\nКорни, найденные методом половинного деления:" << endl;
    double rootHalfDivision = HalfDivisionMethod(a, b, epsilon);
    cout << "Root: " << rootHalfDivision << endl;

    return 0;
}
