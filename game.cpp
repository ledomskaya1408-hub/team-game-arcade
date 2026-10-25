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
void bossEncounter() {
    std::cout << "\n--- ВСТРЕЧА С БОССОМ: ИССУШИТЕЛЬ ---\n";
    std::cout << "Ты входишь в крепость Нижнего мира. Навстречу выходит Иссушитель!\n";

    int roll = rand() % 20 + 1;
    std::cout << "Ты бросаешь кубик... Выпало: " << roll << "\n";

    if (roll >= 16) {
        int win = 250;
        score += win;
        std::cout << "КРИТИЧЕСКИЙ УДАР! Ты побеждаешь Иссушителя и получаешь +" << win << " очков!\n";
        std::cout << "Из босса выпала звезда Нижнего мира.\n";
    } else if (roll <= 4) {
        int dmg = 40;
        hp -= dmg;
        if (hp < 0) {
            hp = 0;
        }
        std::cout << "ИССУШИТЕЛЬ ПРИЗВАЛ СКЕЛЕТОВ! Ты получаешь " << dmg << " урона.\n";
        std::cout << "Текущее HP: " << hp << "\n";
    } else {
        std::cout << "Ты отступаешь в портал. Бой не окончен, но ты цел.\n";
    }
}

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
// Рискованный рейд: примерно 50% успеха и 50% серьёзного урона.
void dangerousRaid() {
    const int outcome = rand() % 100;

    std::cout << "\n[РЕЙД] Вы отправляетесь в опасную зону...\n";

    if (outcome < 50) {
        const int points = 200 + rand() % 301;     // От 200 до 500.
        const int loot = 10 + rand() % 21;         // От 10 до 30 ресурсов.

        score += points;
        resources += loot;

        std::cout << "[УСПЕХ] Рейд завершён удачно!\n";
        std::cout << "Вы получили " << points << " очков и " << loot << " ресурсов.\n";
    } else {
        const int damage = 30 + rand() % 21;       // От 30 до 50 HP.

        hp -= damage;
        if (hp < 0) hp = 0;

        std::cout << "[ПРОВАЛ] В рейде вас атаковали!\n";
        std::cout << "Вы потеряли " << damage << " HP.\n";

        if (hp == 0) {
            std::cout << "Вы не пережили рейд.\n";
        }
    }
}
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
                dangerousRaid();
                break;
            case 2:
                restAtCamp();
                break;

            case 3:
                bossEncounter();
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
