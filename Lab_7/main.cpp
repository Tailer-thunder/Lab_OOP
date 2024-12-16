#include "..\include\npc.h"
#include "..\include\squirrel.h"
#include "..\include\bear.h"
#include "..\include\orc.h"
#include <sstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>
#include <set>
#include <fstream>

using namespace std::chrono_literals;
std::mutex print_mutex;
bool game_running = true;

// Text Observer
class TextObserver : public IFightObserver {
private:
    TextObserver() {}

public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::lock_guard<std::mutex> lck(print_mutex);
            std::cout << std::endl << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};

// Фабрики -----------------------------------
std::shared_ptr<NPC> factory(std::istream& is) {
    std::shared_ptr<NPC> result;
    int type{ 0 };
    if (is >> type) {
        switch (type) {
        case SquirrelType:
            result = std::make_shared<Squirrel>(is);
            break;
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        case OrcType:
            result = std::make_shared<Orc>(is);
            break;
        }
    }
    else {
        std::cerr << "unexpected NPC type:" << type << std::endl;
    }

    if (result) {
        result->subscribe(TextObserver::get());
    }

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y) {
    std::shared_ptr<NPC> result;
    switch (type) {
    case SquirrelType:
        result = std::make_shared<Squirrel>(x, y);
        break;
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    case OrcType:
        result = std::make_shared<Orc>(x, y);
        break;
    default:
        break;
    }
    if (result) {
        result->subscribe(TextObserver::get());
    }

    return result;
}

// save array to file
void save(const std::set<std::shared_ptr<NPC>>& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& n : array) {
        n->save(fs);
    }
    fs.flush();
    fs.close();
}

std::set<std::shared_ptr<NPC>> load(const std::string& filename) {
    std::set<std::shared_ptr<NPC>> result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) {
            result.insert(factory(is));
        }
        is.close();
    }
    else {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }
    return result;
}

// print to screen
std::ostream& operator<<(std::ostream& os, const std::set<std::shared_ptr<NPC>>& array) {
    for (auto& n : array) {
        n->print();
    }
    return os;
}

std::set<std::shared_ptr<NPC>> fight(const std::set<std::shared_ptr<NPC>>& array, size_t distance) {
    std::set<std::shared_ptr<NPC>> dead_list;

    for (const auto& attacker : array) {
        for (const auto& defender : array) {
            if ((attacker != defender) && attacker->is_close(defender) && defender->accept(attacker)) {
                dead_list.insert(defender);
            }
        }
    }

    return dead_list;
}

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    std::mutex mtx;
    FightManager() {}

public:
    static FightManager& get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent&& event) {
        std::lock_guard<std::mutex> lck(mtx);
        events.push(event);
    }

    void operator()() {
        while (game_running) {
            std::optional<FightEvent> event;
            if (!events.empty()) {
                std::lock_guard<std::mutex> lck(mtx);
                event = events.front();
                events.pop();
            }

            if (event) {
                if (event->attacker->is_alive() && event->defender->is_alive()) {
                    if (event->defender->accept(event->attacker)) {
                        event->defender->must_die();
                    }
                }
            }

            std::this_thread::sleep_for(100ms);
        }
    }
};

int main() {
    std::set<std::shared_ptr<NPC>> array; // монстры
    const int MAX_X{ 100 };
    const int MAX_Y{ 100 };
    const int DISTANCE{ 50 };

    // Генерируем начальное распределение монстров
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i) {
        array.insert(factory(NpcType(std::rand() % 3), std::rand() % MAX_X, std::rand() % MAX_Y));
    }

    std::cout << "Starting list:" << std::endl << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE]() {
        while (game_running) {
            for (const std::shared_ptr<NPC>& npc : array) {
                if (npc->is_alive()) {
                    npc->move(std::rand() % (npc->get_move_distance() * 2 + 1) - npc->get_move_distance(),
                              std::rand() % (npc->get_move_distance() * 2 + 1) - npc->get_move_distance(), MAX_X, MAX_Y);
                }
            }

            for (const std::shared_ptr<NPC>& npc : array) {
                for (const std::shared_ptr<NPC>& other : array) {
                    if ((other != npc) && (npc->is_alive()) && (other->is_alive()) && (npc->is_close(other))) {
                        FightManager::get().add_event({ npc, other });
                    }
                }
            }
            std::this_thread::sleep_for(10ms);
        }
    });

    const int grid{ 20 };
    const int step_x{ MAX_X / grid };
    const int step_y{ MAX_Y / grid };
    std::array<char, grid * grid> fields{ 0 };
    for (int i = 0; i < 30; i++) {
        fields.fill(0);
        for (const std::shared_ptr<NPC>& npc : array) {
            const auto [x, y] = npc->position();
            int i = x / step_x;
            int j = y / step_y;

            // Проверка границ массива
            if (i >= 0 && i < grid && j >= 0 && j < grid) {
                if (npc->is_alive()) {
                    switch (npc->get_type()) {
                    case SquirrelType:
                        fields[i + grid * j] = 'S';
                        break;
                    case BearType:
                        fields[i + grid * j] = 'B';
                        break;
                    case OrcType:
                        fields[i + grid * j] = 'O';
                        break;
                    default:
                        break;
                    }
                }
                else {
                    fields[i + grid * j] = '.';
                }
            }
        }

        {
            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0) {
                        std::cout << "[" << c << "]";
                    }
                    else {
                        std::cout << "[ ]";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        std::this_thread::sleep_for(1s);
    }

    game_running = false;
    move_thread.join();
    fight_thread.join();

    std::cout << "Game Over!" << std::endl;
    return 0;
}
