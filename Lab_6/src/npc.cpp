#include "npc.h"

// ����������� � ������������
NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}

// ����������� �� ������ �����
NPC::NPC(NpcType t, std::istream& is) : type(t) {
    is >> x >> y;
}

// �������� �����������
void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

// ����������� ������������ � ���������� ���
void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win) {
    for (auto& observer : observers) {
        observer->on_fight(shared_from_this(), defender, win);
    }
}

// �������� ���������� ����� NPC
bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const {
    return std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <= std::pow(distance, 2);
}

// ������ ��� �������� ���� (�� ��������� ���������� false)
bool NPC::is_ork() const { return false; }
bool NPC::is_belka() const { return false; }
bool NPC::is_medved() const { return false; }

// ���������� ������� ������ ������� � �����
void NPC::save(std::ostream& os) {
    os << x << " " << y << std::endl;
}

// ���������� ��������� ������
std::ostream& operator<<(std::ostream& os, NPC& npc) {
    os << "{ type: " << npc.type
       << ", x: " << npc.x
       << ", y: " << npc.y
       << " }";
    return os;
}
