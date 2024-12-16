#include "npc.h"

NPC::NPC(NpcType t, int _x, int _y, int move_dist, int kill_dist)
    : type(t), x(_x), y(_y), alive(true), move_distance(move_dist), kill_distance(kill_dist) {}

NPC::NPC(const NPC &other)  // Конструктор копирования
    : type(other.type), x(other.x), y(other.y), alive(other.alive), move_distance(other.move_distance), kill_distance(other.kill_distance) {}

NPC::NPC(NpcType t, std::istream &is)
    : type(t), alive(true) {
    is >> x >> y >> move_distance >> kill_distance;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    std::lock_guard<std::mutex> lck(mtx);
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    std::lock_guard<std::mutex> lck(mtx);
    for (auto &o : observers)
        o->on_fight(std::shared_ptr<NPC>(this, [](NPC *) {}), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other) {
    std::lock_guard<std::mutex> lck(mtx);
    const auto [other_x, other_y] = other->position();
    return (x - other_x) * (x - other_x) + (y - other_y) * (y - other_y) <= kill_distance * kill_distance;
}

std::pair<int, int> NPC::position() const {
    return {x, y};
}

NpcType NPC::get_type() const {
    return type;
}

int NPC::get_move_distance() const {
    return move_distance;
}

int NPC::get_kill_distance() const {
    return kill_distance;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y) {
    std::lock_guard<std::mutex> lck(mtx);
    x = std::max(0, std::min(max_x, x + shift_x));
    y = std::max(0, std::min(max_y, y + shift_y));
}

bool NPC::is_alive() const {
    return alive;
}

void NPC::must_die() {
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}
