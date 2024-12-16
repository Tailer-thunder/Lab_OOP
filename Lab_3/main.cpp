#include <iostream>
#include <memory>
#include "../include/Rectangle.h"
#include "../include/Rhomb.h"
#include "../include/Trapezoid.h"

int main() {
    const int MAX_FIGURES = 100;  
    std::unique_ptr<Figure> figures[MAX_FIGURES];  
    int figure_count = 0;

    while (true) {
        std::cout << "Выберите фигуру (1 - Прямоугольник, 2 - Трапеция, 3 - Ромб, 0 - Выход): ";
        int choice;
        std::cin >> choice;

        if (choice == 0 || figure_count >= MAX_FIGURES) {
            break;
        }

        std::unique_ptr<Figure> fig;  
        switch (choice) {
            case 1:
                fig = std::make_unique<Rectangle>(); 
                break;
            case 2:
                fig = std::make_unique<Trapezoid>();  
                break;
            case 3:
                fig = std::make_unique<Rhomb>();  
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
                continue;  
        }

        std::cout << "Введите 4 координаты (x1 y1, x2 y2, x3 y3, x4 y4): ";
        std::cin >> fig.get(); 
        figures[figure_count++] = std::move(fig);  
    }

    while (true) {
        std::cout << "\nКоманды: 1 - Показать список фигур; 2 - Удалить фигуру; 3 - Вывести общую площадь; 0 - Выход" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;  
        }

        switch (choice) {
            case 1:  
                for (int i = 0; i < figure_count; i++) {
                    std::cout << i + 1 << ": " << figures[i] << ", Площадь = " << static_cast<double>(*figures[i]) << std::endl;
                }
                break;

            case 2: 
                int index;
                std::cout << "Введите номер фигуры для удаления: ";
                std::cin >> index;
                index--;  
                if (index >= 0 && index < figure_count) {
                    figures[index].reset();  
                    std::cout << "Фигура под номером " << (index + 1) << " удалена." << std::endl;
                    for (int i = index; i < figure_count - 1; i++) {
                        figures[i] = std::move(figures[i + 1]);
                    }
                    figure_count--;  
                } else {
                    std::cout << "Некорректный номер фигуры." << std::endl;
                }
                break;

            case 3:  
                double total_area = 0;
                for (int i = 0; i < figure_count; i++) {
                    total_area += static_cast<double>(*figures[i]);
                }
                std::cout << "Общая площадь фигур = " << total_area << std::endl;
                break;

            default:
                std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
                break;
        }
    }

    return 0;
}
