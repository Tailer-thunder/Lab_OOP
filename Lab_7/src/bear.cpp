#include "..\include\bear.h"

Bear::Bear(int x, int y) : NPC(BearType, x, y, 5, 10) {}

Bear::Bear(std::istream &is) : NPC(BearType, is) {}

Bear::Bear(const Bear &other) : NPC(other) {}

bool Bear::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Bear>(this, [](Bear*) {}));
}

bool Bear::fight(std::shared_ptr<NPC> other) {
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;
    bool win = attack > defense;
    fight_notify(other, win);
    return win;
}

void Bear::print() {
    std::cout << "Bear at (" << x << ", " << y << ")\n";
}

void Bear::save(std::ostream &os) {
    os << BearType << " " << x << " " << y << " " << move_distance << " " << kill_distance << "\n";
}
