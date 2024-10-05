#include <iostream>
#include "../include/Thirteen.hpp"


int main() {

    Thirteen var1 = Thirteen();
    Thirteen var2 = Thirteen(3, 'C');
    Thirteen var3 = Thirteen{'1', 'A', 'C'};
    Thirteen var4 = Thirteen("1A7");


    std::cout << "��������� �������� ��������:" << std::endl;
    var1.print(std::cout) << std::endl;
    var2.print(std::cout) << std::endl;
    var3.print(std::cout) << std::endl;
    var4.print(std::cout) << std::endl;

    var2 += Thirteen("1");
    std::cout << "��������� � var2 1" << std::endl;
    var2.print(std::cout) << std::endl;

    try {
        var2 -= Thirteen("AAA");
        std::cout << "����� AAA �� var2" << std::endl;
        var2.print(std::cout) << std::endl;
    } catch (const std::logic_error& e) {
        std::cout << "������: " << e.what() << std::endl;
    }


    Thirteen var5 = var4;
    std::cout << "������ var5 ������������ var4:" << std::endl;
    var5.print(std::cout) << std::endl;


    var5 += Thirteen("12");
    std::cout << "��������� 12 � var5" << std::endl;
    var5.print(std::cout) << std::endl;


    Thirteen var6 = std::move(var3);
    std::cout << "������ var6 ������������ var3 (var3 ���������� ������):" << std::endl;
    var6.print(std::cout) << std::endl;
    std::cout << "��������� var3 ����� �����������:" << std::endl;
    var3.print(std::cout) << std::endl;

    return 0;
}