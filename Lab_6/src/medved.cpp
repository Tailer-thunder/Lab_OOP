#include "../include/medved.h"
#include "../include/ork.h"
#include "../include/belka.h"

Medved::Medved(int x, int y) : NPC(MedvedType, x, y) {}

Medved::Medved(std::istream& is) : NPC(MedvedType, is) {}

void Medved::print() {
    std::cout << *this;
}

bool Medved::is_medved() const {
    return true;
}

bool Medved::fight(std::shared_ptr<Ork> other) {
    fight_notify(other, false); 
    return false;
}

bool Medved::fight(std::shared_ptr<Belka> other) {
    fight_notify(other, true); 
    return true;
}

bool Medved::fight(std::shared_ptr<Medved> other) {
    fight_notify(other, false);
    return false;
}

void Medved::save(std::ostream& os) {
    os << MedvedType << std::endl;
    NPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Medved& medved) {
    os << "medved: " << *static_cast<NPC*>(&medved) << std::endl;
    return os;
}

bool Medved::accept(const std::shared_ptr<NPC>& attacker) {
    if (attacker->is_ork()) {
        return true;
    } else if (attacker->is_belka()) {
        return true;
    } else if (attacker->is_medved()) {
        return false;
    }
    return false;
}
