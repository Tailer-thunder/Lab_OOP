#pragma once

#include "npc.h"

struct Orc : public NPC {
    Orc(int x, int y);
    Orc(std::istream &is);
    Orc(const Orc &other);  // Конструктор копирования

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    void print() override;
    void save(std::ostream &os) override;
};
