#include <iostream>
#include <memory>
#include <vector>
#include "include/Array.h"
#include "include/Rectangle.h"
#include "include/Trapezoid.h"
#include "include/Rhomb.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;

    while (true) {
        std::cout << "�������� ������ (1 - �������������, 2 - ��������, 3 - ����): ";
        int choice;
        std::cin >> choice;

        std::shared_ptr<Figure<double>> figure;

        try {
            if (choice == 1) {
                figure = std::make_shared<Rectangle<double>>();
                std::cout << "������� ���������� ����� (x1 y1 x2 y2): ";
                std::cin >> dynamic_cast<Rectangle<double>*>(figure.get());
            } else if (choice == 2) {
                figure = std::make_shared<Trapezoid<double>>();
                std::cout << "������� ���������� ����� (x1 y1 x2 y2 x3 y3 x4 y4): ";
                std::cin >> dynamic_cast<Trapezoid<double>*>(figure.get());
            } else if (choice == 3) {
                figure = std::make_shared<Rhomb<double>>();
                std::cout << "������� ���������� ����� (x1 y1 x2 y2 x3 y3 x4 y4): ";
                std::cin >> dynamic_cast<Rhomb<double>*>(figure.get());
            } else {
                std::cout << "�������� �����! ����������, ���������� �����." << std::endl;
                continue;
            }

            figures.add(figure);
        } catch (const std::invalid_argument& e) {
            std::cerr << "������ �����: " << e.what() << std::endl;
            continue;
        }
    }

    double totalArea = 0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        std::cout << figures[i].get() << std::endl;
        totalArea += figures[i]->area();
    }

    std::cout << "����� ������� �����: " << totalArea << std::endl;

    return 0;
}
