#include "..\include\orc.h"

Orc::Orc(int x, int y) : NPC(OrcType, x, y, 20, 10) {}

Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

Orc::Orc(const Orc &other) : NPC(other) {}

bool Orc::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Orc>(this, [](Orc*) {}));
}

bool Orc::fight(std::shared_ptr<NPC> other) {
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;
    bool win = attack > defense;
    fight_notify(other, win);
    return win;
}

void Orc::print() {
    std::cout << "Orc at (" << x << ", " << y << ")\n";
}

void Orc::save(std::ostream &os) {
    os << OrcType << " " << x << " " << y << " " << move_distance << " " << kill_distance << "\n";
}
