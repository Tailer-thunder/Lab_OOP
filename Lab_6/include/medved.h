#pragma once
#include "npc.h"

struct Medved : public NPC {
    Medved(int x, int y);
    Medved(std::istream& is);

    void print() override;

    bool is_medved() const override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;

    bool fight(std::shared_ptr<Ork> other) override;
    bool fight(std::shared_ptr<Belka> other) override;
    bool fight(std::shared_ptr<Medved> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Medved& medved);
};
