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

// Метод отделения корней
void separate_roots(double& a, double& b, double epsilon) {
    if (function(a) * function(b) >= 0) {
        cout << "На концах отрезка [a, b] функция имеет одинаковые знаки, метод отделения корней не может быть применен." << endl;
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
}

// Комбинированный метод секущих-хорд
double CombinedMethod(double x0, double x1, double epsilon) {
    double x_prev = x0;
    double x_curr = x1;
    int iteration = 1;

    cout << "N\tx" << endl;
    cout << "---------------------" << endl;

    while (abs(x_curr - x_prev) > epsilon) {
        double f_prev = function(x_prev);
        double f_curr = function(x_curr);
        double delta_x = x_curr - x_prev;
        double delta_f = f_curr - f_prev;

        double x_next = x_curr - (x_curr - x_prev) * f_curr / delta_f;

        cout << iteration++ << "\t" << x_next << endl;

        x_prev = x_curr;
        x_curr = x_next;
    }

    return x_curr;
}

//метод Хорд: a, b - пределы хорды
double chordMethod(double a, double b, double epsilon) {
    int iterator = 1;

    cout << "N\ta\t\tb\t\tb-a" << endl;
    cout << "---------------------------------" << endl;

    while(abs(b - a) >= epsilon) {
        cout << iterator << setw(10) << a << setw(14) << b << setw(14) << b - a << endl;

        a = a - (b - a) * function(a) / (function(b) - function(a));
        b = b - (a - b) * function(b) / (function(a) - function(b));
        iterator++;
    }
    return b;
}


// Метод половинного деления для поиска корня
double HalfDivisionMethod(double a, double b, double epsilon) {
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

int main() {
    double a = 0.0; // Начало интервала
    double b = 5.0; // Конец интервала
    double epsilon = 0.0001; // Погрешность

    system("chcp 65001"); // Команда для поддержки русского языка в консоли

   
    cout << "\nКорни, найденные методом половинного деления:" << endl;
    double rootHalfDivision = HalfDivisionMethod(a, b, epsilon);
    cout << "Root: " << rootHalfDivision << endl;

    separate_roots(a, b, epsilon);

    cout << "\nКорни, найденные комбинированным методом секущих – хорд :" << endl;
    double rootIteration =CombinedMethod(a, b, epsilon);
    cout << "Root: " << rootIteration << endl;

    cout << "Корни, найденные методом секущих:" << endl;
    double rootSecant = chordMethod(a, b, epsilon);
    cout << "Root: " << rootSecant << endl;


    return 0;
}
