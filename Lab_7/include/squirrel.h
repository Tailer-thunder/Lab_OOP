#pragma once

#include "npc.h"

struct Squirrel : public NPC {
    Squirrel(int x, int y);
    Squirrel(std::istream &is);
    Squirrel(const Squirrel &other);  // Конструктор копирования

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    void print() override;
    void save(std::ostream &os) override;
};
