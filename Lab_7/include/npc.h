#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <random>
#include <set>

enum NpcType {
    SquirrelType,
    BearType,
    OrcType,
    UnknownType
};

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<class NPC> attacker, const std::shared_ptr<class NPC> defender, bool win) = 0;
};

class NPC {
protected:
    std::mutex mtx;
    NpcType type;
    int x, y;
    bool alive;
    int move_distance;
    int kill_distance;
    std::vector<std::shared_ptr<IFightObserver>> observers;

public:
    NPC(NpcType t, int _x, int _y, int move_dist, int kill_dist);
    NPC(const NPC &other);  // Конструктор копирования
    NPC(NpcType t, std::istream &is);
    virtual ~NPC() = default;

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other);
    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    virtual bool fight(std::shared_ptr<NPC> other) = 0;
    virtual void print() = 0;
    virtual void save(std::ostream &os) = 0;

    std::pair<int, int> position() const;
    NpcType get_type() const;
    int get_move_distance() const;
    int get_kill_distance() const;
    void move(int shift_x, int shift_y, int max_x, int max_y);
    bool is_alive() const;
    void must_die();
};
