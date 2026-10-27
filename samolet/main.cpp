
#define NOMINMAX
#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    double mainTank[2]{ 300, 1000 };
    double extraTank[2]{ 0, 100 };

    double maxWeight[2][3]{
        { 750, 1500, 2000 },
        { 1000, 2000, 3000 }
    };

    double fuelRate[2][3]{
        { 1, 4, 7 },
        { 2, 4, 6 }
    };

    double distance[2]{};

    int choice = 0;
    double weight = 0;
    double consumption = 0;


    std::cout << "Самолет 1\n";
    std::cout << "Самолет 2\n";
    std::cout << "Выберите самолет: ";
    if (!(std::cin >> choice) || choice < 1 || choice > 2)
    {
        std::cout << "Неверный номер самолета!\n";
        return 0;
    }

    int plane = choice - 1;

    std::cout << "\nВведите расстояние от А до В (км): ";
    if (!(std::cin >> distance[0]) || distance[0] < 0)
    {
        std::cout << "Некорректное расстояние!\n";
        return 0;
    }

    std::cout << "Введите расстояние от В до С (км): ";
    if (!(std::cin >> distance[1]) || distance[1] < 0)
    {
        std::cout << "Некорректное расстояние!\n";
        return 0;
    }

    std::cout << "Введите вес груза (кг): ";
    if (!(std::cin >> weight) || weight < 0)
    {
        std::cout << "Некорректный вес груза!\n";
        return 0;
    }

    if (weight > maxWeight[plane][2])
    {
        std::cout << "\nСамолет не может поднять такой груз!\n";
        std::cout << "Полет невозможен!\n";
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        if (weight <= maxWeight[plane][i])
        {
            consumption = fuelRate[plane][i];
            break;
        }
    }

    double fuelAB = distance[0] * consumption;
    double fuelBC = distance[1] * consumption;

    std::cout << "Расчет полета \n";

    std::cout << "Самолет " << choice << "\n";
    std::cout << "Расход топлива: " << consumption << " л/км\n";
    std::cout << "Топливо на А-В: " << fuelAB << " л\n";
    std::cout << "Топливо на В-С: " << fuelBC << " л\n";

    double totalFuel = mainTank[plane] + extraTank[plane];

    if (fuelAB > totalFuel)
    {
        std::cout << "\nНедостаточно топлива для полета от А до В!\n";
        std::cout << "Полет по маршруту невозможен!\n";
        return 0;
    }

    double extraLeft = extraTank[plane] - fuelAB;

    if (extraLeft < 0)
    {
        extraLeft = 0;
    }

    double mainUsed = fuelAB - extraTank[plane];

    if (mainUsed < 0)
    {
        mainUsed = 0;
    }

    double mainLeft = mainTank[plane] - mainUsed;

    double mainNeeded = fuelBC - extraLeft;

    if (mainNeeded < 0)
    {
        mainNeeded = 0;
    }

    if (mainNeeded > mainTank[plane])
    {
        std::cout << "\nНедостаточно емкости бака для полета от В до С!\n";
        std::cout << "Полет по маршруту невозможен!\n";
        return 0;
    }

    double refuel = mainNeeded - mainLeft;

    if (refuel < 0)
    {
        refuel = 0;
    }

    std::cout << "\nСамолет успешно долетит до точки В!\n";
    std::cout << "Остаток основного бака: " << mainLeft << " л\n";

    if (choice == 2)
    {
        std::cout << "Остаток временного бака: " << extraLeft << " л\n";
    }

    std::cout << "\nМинимальная дозаправка в точке В: "
        << refuel << " л\n";

    std::cout << "\nПолет по маршруту А-В-С возможен!\n";

    return 0;
}
