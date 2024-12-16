#include "..\include\squirrel.h"

Squirrel::Squirrel(int x, int y) : NPC(SquirrelType, x, y, 5, 5) {}

Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

Squirrel::Squirrel(const Squirrel &other) : NPC(other) {}

bool Squirrel::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Squirrel>(this, [](Squirrel*) {}));
}

bool Squirrel::fight(std::shared_ptr<NPC> other) {
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;
    bool win = attack > defense;
    fight_notify(other, win);
    return win;
}

void Squirrel::print() {
    std::cout << "Squirrel at (" << x << ", " << y << ")\n";
}

void Squirrel::save(std::ostream &os) {
    os << SquirrelType << " " << x << " " << y << " " << move_distance << " " << kill_distance << "\n";
}
