#pragma once

#include "npc.h"

struct Bear : public NPC {
    Bear(int x, int y);
    Bear(std::istream &is);
    Bear(const Bear &other);  // Конструктор копирования

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<NPC> other) override;
    void print() override;
    void save(std::ostream &os) override;
};
