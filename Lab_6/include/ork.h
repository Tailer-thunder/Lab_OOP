#pragma once
#include "npc.h"

struct Ork : public NPC {
    Ork(int x, int y);
    Ork(std::istream& is);

    void print() override;

    bool is_ork() const override;

    bool accept(const std::shared_ptr<NPC>& attacker) override;

    bool fight(std::shared_ptr<Ork> other) override;
    bool fight(std::shared_ptr<Belka> other) override;
    bool fight(std::shared_ptr<Medved> other) override;

    void save(std::ostream& os) override;

    friend std::ostream& operator<<(std::ostream& os, Ork& ork);
};
