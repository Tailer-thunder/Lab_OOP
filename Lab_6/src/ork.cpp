#include "../include/ork.h"
#include "../include/medved.h"
#include "../include/belka.h"

Ork::Ork(int x, int y) : NPC(OrkType, x, y) {}

Ork::Ork(std::istream& is) : NPC(OrkType, is) {}

void Ork::print() {
    std::cout << *this;
}

bool Ork::is_ork() const {
    return true;
}

bool Ork::fight(std::shared_ptr<Medved> other) {
    fight_notify(other, true); 
    return true;
}

bool Ork::fight(std::shared_ptr<Belka> other) {
    fight_notify(other, true); 
    return true;
}

bool Ork::fight(std::shared_ptr<Ork> other) {
    fight_notify(other, false);
    return false;
}

void Ork::save(std::ostream& os) {
    os << OrkType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Ork& ork) {
    os << "ork: " << *static_cast<NPC*>(&ork) << std::endl;
    return os;
}

bool Ork::accept(const std::shared_ptr<NPC>& attacker) {
    if (attacker->is_medved()) {
        return true;
    } else if (attacker->is_belka()) {
        return true;
    } else if (attacker->is_ork()) {
        return false;
    }
    return false;
}
