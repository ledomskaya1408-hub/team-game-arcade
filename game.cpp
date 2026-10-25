#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

int hp = 100;
int resources = 50;
int score = 0;
int turn = 1;

void printHUD() {
    std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score << "] ================\n";
    std::cout << "❤️  Здоровье: " << hp << "/100  |   Ресурсы: " << resources << "\n";
    std::cout << "-------------------------------------------------------\n";
}
// ------------------------------------------------------------
void restAtCamp() {
    std::cout << "\n--- ТОРГОВЕЦ ---\n";
    int cost = 20;
    if (resources < cost) {
        std::cout << "У тебя недостаточно изумрудов! Нужно " << cost << ", а есть " << resources << ".\n";
        return;
    }

    resources -= cost;
    int healAmount = 30;
    hp += healAmount;


    if (hp > 100) {
        hp = 100;
    }

    std::cout << "Ты съел золотое яблоко и отдохнул в деревне.\n";
    std::cout << "HP: " << hp << "/100. Осталось изумрудов: " << resources << ".\n";
}
// ------------------------------------------------------------
int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
#else
    setlocale(LC_ALL, "");
#endif
    srand(time(NULL));
    int choice = 0;

    std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";

    while (hp > 0) {
        printHUD();
        std::cout << "1. Рискованная операция (Высокая награда / Высокий риск)\n";
        std::cout << "2. База / Лагерь (Лечение и обмен ресурсов)\n";
        std::cout << "3. Особое событие / Рулетка удачи\n";
        std::cout << "0. Сдаться и зафиксировать счет\n";
        std::cout << "Выберите действие > ";

        if (!(std::cin >> choice)) break;

        switch (choice) {
            case 1:
            // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
                std::cout << "\n[!] Модуль риска еще в разработке (Issue #1).\n";
                break;
            case 2:
                restAtCamp();
                break;

            case 3:
            // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/БОССА (ISSUE #3)]
                std::cout << "\n[!] Модуль событий еще в разработке (Issue #3).\n";
                break;
            case 0:
                hp = 0;  // Выход из цикла
                break;
            default:
                std::cout << "\nНеизвестная команда!\n";
                break;
        }
        // Каждый успешный ход дает очки выживания
        if (hp > 0) {
            turn++;
            score += 10;
        }
    }


    std::cout << "\n ИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";

    return 0;
}