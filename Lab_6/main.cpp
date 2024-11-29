#include "include/npc.h"
#include "include/ork.h"
#include "include/belka.h"
#include "include/medved.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <set>
#include <cstdlib>
#include <ctime>

using set_t = std::set<std::shared_ptr<NPC>>;

class TextObserver : public IFightObserver {
private:
    TextObserver() = default;

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << "\nMurder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

std::shared_ptr<NPC> factory(std::istream& is) {
    int type = 0;
    if (is >> type) {
        switch (static_cast<NpcType>(type)) {
            case OrkType: return std::make_shared<Ork>(is);
            case BelkaType: return std::make_shared<Belka>(is);
            case MedvedType: return std::make_shared<Medved>(is);
            default: std::cerr << "Unexpected NPC type: " << type << std::endl; break;
        }
    }
    return nullptr;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    switch (type) {
        case OrkType: return std::make_shared<Ork>(x, y);
        case BelkaType: return std::make_shared<Belka>(x, y);
        case MedvedType: return std::make_shared<Medved>(x, y);
        default: return nullptr;
    }
}

void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
        return;
    }
    fs << array.size() << std::endl;
    for (const auto& npc : array)
        npc->save(fs);
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Failed to open file for loading: " << filename << std::endl;
        return result;
    }

    size_t count = 0;
    fs >> count;
    for (size_t i = 0; i < count; ++i) {
        if (auto npc = factory(fs)) {
            result.insert(npc);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (const auto& npc : array)
        npc->print();
    return os;
}

set_t fight(const set_t& array, size_t distance) {
    set_t dead_list;

    for (const auto& attacker : array) {
        for (const auto& defender : array) {
            if (attacker != defender && attacker->is_close(defender, distance)) {
                bool success = defender->accept(attacker);
                if (success)
                    dead_list.insert(defender);
            }
        }
    }

    return dead_list;
}

int main() {
    std::srand(std::time(nullptr)); // ������������� ���������� ��������� �����
    set_t array;

    // ��������� ��������� NPC
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        auto npc = factory(static_cast<NpcType>(std::rand() % 3 + 1), std::rand() % 100, std::rand() % 100);
        if (npc) array.insert(npc);
    }

    // ����������
    std::cout << "Saving ..." << std::endl;
    save(array, "npc.txt");

    // ��������
    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    // �����
    std::cout << "Fighting ..." << std::endl << array;
    for (size_t distance = 20; distance <= 100 && !array.empty(); distance += 10) {
        auto dead_list = fight(array, distance);
        for (const auto& dead : dead_list)
            array.erase(dead);

        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl;
    }

    // ���������� � �����
    std::cout << "Survivors:" << std::endl << array;

    return 0;
}
