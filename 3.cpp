#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <numeric>

using namespace std;

// Функция для расчета критерия Хи-квадрат
double calculateChiSquare(const vector<int>& data, int size) {
    double mean = accumulate(data.begin(), data.end(), 0.0) / size;
    double chiSquare = 0.0;

    for (int num : data) {
        chiSquare += pow(num - mean, 2) / mean;
    }

    return chiSquare;
}


int main() {
    // Создаем генератор случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    // Создаем 3 массива размером 50, 100 и 1000
    vector<int> array50(50), array100(100), array1000(1000);

    // Заполняем массивы случайными числами от 1 до 100
    for (int& num : array50) {
        num = dis(gen);
    }
    for (int& num : array100) {
        num = dis(gen);
    }
    for (int& num : array1000) {
        num = dis(gen);
    }

    // Рассчитываем значение критерия Хи-квадрат для каждого массива
    double chiSquare50 = calculateChiSquare(array50, 50);
    double chiSquare100 = calculateChiSquare(array100, 100);
    double chiSquare1000 = calculateChiSquare(array1000, 1000);

    // Выводим результаты
    cout << "Массив размером 50:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare50 << endl;
    if (chiSquare50 < 67.5) {
        cout << "Гипотеза о нормальном распределении принимается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << accumulate(array50.begin(), array50.end(), 0.0) / 50 << endl;
    cout << endl;


    cout << "Массив размером 100:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare100 << endl;
    if (chiSquare100 < 124.3) {
        cout << "Гипотеза о нормальном распределении принимается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << accumulate(array100.begin(), array100.end(), 0.0) / 100 << endl;
    cout << endl;


    cout << "Массив размером 1000:" << endl;
    cout << "Критерий Хи-квадрат: " << chiSquare1000 << endl;
    if (chiSquare1000 < 1124.0) {
        cout << "Гипотеза о нормальном распределении принимается" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается" << endl;
    }
    cout << "Ожидаемое математическое ожидание: 50.5" << endl;
    cout << "Реальное математическое ожидание: " << accumulate(array1000.begin(), array1000.end(), 0.0) / 1000 << endl;

    return 0;
}
