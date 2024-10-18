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
        std::cout << "�������� ������ (1 - �������������, 2 - ��������, 3 - ����, 0 - �����): ";
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
                std::cout << "�������� �����. ���������� ��� ���." << std::endl;
                continue;  
        }

        std::cout << "������� 4 ���������� (x1 y1, x2 y2, x3 y3, x4 y4): ";
        std::cin >> fig.get(); 
        figures[figure_count++] = std::move(fig);  
    }

    while (true) {
        std::cout << "\n�������: 1 - �������� ������ �����; 2 - ������� ������; 3 - ������� ����� �������; 0 - �����" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;  
        }

        switch (choice) {
            case 1:  
                for (int i = 0; i < figure_count; i++) {
                    std::cout << i + 1 << ": " << figures[i] << ", ������� = " << static_cast<double>(*figures[i]) << std::endl;
                }
                break;

            case 2: 
                int index;
                std::cout << "������� ����� ������ ��� ��������: ";
                std::cin >> index;
                index--;  
                if (index >= 0 && index < figure_count) {
                    figures[index].reset();  
                    std::cout << "������ ��� ������� " << (index + 1) << " �������." << std::endl;
                    for (int i = index; i < figure_count - 1; i++) {
                        figures[i] = std::move(figures[i + 1]);
                    }
                    figure_count--;  
                } else {
                    std::cout << "������������ ����� ������." << std::endl;
                }
                break;

            case 3:  
                double total_area = 0;
                for (int i = 0; i < figure_count; i++) {
                    total_area += static_cast<double>(*figures[i]);
                }
                std::cout << "����� ������� ����� = " << total_area << std::endl;
                break;

            default:
                std::cout << "������������ �����. ���������� �����." << std::endl;
                break;
        }
    }

    return 0;
}
