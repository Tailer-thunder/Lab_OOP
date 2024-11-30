#include "../include/belka.h"
#include "../include/medved.h"
#include "../include/ork.h"

Belka::Belka(int x, int y) : NPC(BelkaType, x, y) {}

Belka::Belka(std::istream& is) : NPC(BelkaType, is) {}

void Belka::print() {
    std::cout << *this;
}

bool Belka::is_belka() const {
    return true;
}

bool Belka::fight(std::shared_ptr<Medved> other) {
    fight_notify(other, false); 
    return false;
}

bool Belka::fight(std::shared_ptr<Ork> other) {
    fight_notify(other, false); 
    return false;
}

bool Belka::fight(std::shared_ptr<Belka> other) {
    fight_notify(other, false);
    return false;
}

void Belka::save(std::ostream& os) {
    os << BelkaType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Belka& belka) {
    os << "belka: " << *static_cast<NPC*>(&belka) << std::endl;
    return os;
}

bool Belka::accept(const std::shared_ptr<NPC>& attacker) {
    if (attacker->is_medved()) {
        return true;
    } else if (attacker->is_ork()) {
        return true;
    } else if (attacker->is_belka()) {
        return false;
    }
    return false;
}
