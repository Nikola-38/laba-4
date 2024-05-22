#include <iostream>
#include <vector>
#include <random>
using namespace std;

// Функция для генерации случайного числа в диапазоне от min до max
int randomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// Алгоритм "всегда сотрудничать"
bool alwaysCooperate(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    return true;
}

// Стратегия уступки: сотрудничать, если противник сотрудничал в предыдущем раунде, иначе предавать
bool titForTat(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    if (round_number == 0) {
        return true;
    }
    return enemy_choices[round_number - 1];
}

// Алгоритм со случайными выборами
bool randomChoice(int round_number, vector<bool> self_choices, vector<bool> enemy_choices) {
    return randomNumber(0, 1) == 1;
}

// Функция для сравнения алгоритмов
void compareAlgorithms() {
    int num_rounds = randomNumber(100, 200);
    vector<bool> algorithm1_choices, algorithm2_choices, algorithm3_choices;
    int algorithm1_score = 0, algorithm2_score = 0, algorithm3_score = 0;

    for (int round = 0; round < num_rounds; round++) {
        bool algorithm1_choice = randomChoice(round, algorithm1_choices, algorithm2_choices);
        bool algorithm2_choice = titForTat(round, algorithm2_choices, algorithm1_choices);
        bool algorithm3_choice = alwaysCooperate(round, algorithm3_choices, algorithm2_choices);

        algorithm1_choices.push_back(algorithm1_choice);
        algorithm2_choices.push_back(algorithm2_choice);
        algorithm3_choices.push_back(algorithm3_choice);

        // Сравниваем все три алгоритма
        if (algorithm1_choice && algorithm2_choice) {
            algorithm1_score += 4;
            algorithm2_score += 4;
        } else if (algorithm1_choice && !algorithm2_choice) {
            algorithm1_score += 0;
            algorithm2_score += 20;
        } else if (!algorithm1_choice && algorithm2_choice) {
            algorithm1_score += 20;
            algorithm2_score += 0;
        } else {
            algorithm1_score += 24;
            algorithm2_score += 24;
        }

        if (algorithm1_choice && algorithm3_choice) {
            algorithm1_score += 4;
            algorithm3_score += 4;
        } else if (algorithm1_choice && !algorithm3_choice) {
            algorithm1_score += 0;
            algorithm3_score += 20;
        } else if (!algorithm1_choice && algorithm3_choice) {
            algorithm1_score += 20;
            algorithm3_score += 0;
        } else {
            algorithm1_score += 24;
            algorithm3_score += 24;
        }

        if (algorithm3_choice && algorithm2_choice) {
            algorithm3_score += 24;
            algorithm2_score += 24;
        } else if (algorithm3_choice && !algorithm2_choice) {
            algorithm3_score += 0;
            algorithm2_score += 20;
        } else if (!algorithm3_choice && algorithm2_choice) {
            algorithm3_score += 20;
            algorithm2_score += 0;
        } else {
            algorithm3_score += 4;
            algorithm2_score += 4;
        }
    }

    cout << "randomChoice: " << algorithm1_score << endl;
    cout << "adaptiveRandomChoice: " << algorithm2_score << endl;
    cout << "alwaysCooperate: " << algorithm3_score << endl;
}

int main() {
    compareAlgorithms();
    return 0;
}
