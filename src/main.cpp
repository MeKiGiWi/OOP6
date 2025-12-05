#include <fstream>

#include "bear.h"
#include "npc.h"
#include "orc.h"
#include "squirrel.h"

class ConsoleObserver : public IFightObserver {
   private:
    ConsoleObserver() {};

   public:
    static std::shared_ptr<IFightObserver> get() {
        static ConsoleObserver instance;
        return std::shared_ptr<IFightObserver>(&instance,
                                               [](IFightObserver*) {});
    }

    void on_fight(const std::shared_ptr<DungeonNPC> attacker,
                  const std::shared_ptr<DungeonNPC> defender,
                  bool win) override {
        if (win) {
            std::cout << std::endl << "Combat Result --------" << std::endl;
            std::cout << "Attacker: ";
            attacker->print();
            std::cout << "Defender: ";
            defender->print();
        }
    }
};

class FileObserver : public IFightObserver {
   private:
    std::ofstream log_file;

   public:
    FileObserver() { log_file.open("log.txt", std::ios::app); }

    ~FileObserver() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    void on_fight(const std::shared_ptr<DungeonNPC> attacker,
                  const std::shared_ptr<DungeonNPC> defender,
                  bool win) override {
        if (win) {
            log_file << "Combat Result --------" << std::endl;
            log_file << "Attacker: ";
            attacker->print();
            log_file << "Defender: ";
            defender->print();
            log_file << std::endl;
            log_file.flush();
        }
    }
};

std::shared_ptr<DungeonNPC> factory(std::istream& is) {
    std::shared_ptr<DungeonNPC> result;
    int type{0};
    if (is >> type) {
        switch (type) {
            case OrcType:
                result = std::make_shared<Orc>(is);
                break;
            case SquirrelType:
                result = std::make_shared<Squirrel>(is);
                break;
            case BearType:
                result = std::make_shared<Bear>(is);
                break;
        }
    } else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result) {
        result->subscribe(ConsoleObserver::get());
        result->subscribe(std::make_shared<FileObserver>());
    }

    return result;
}

std::shared_ptr<DungeonNPC> factory(NpcType type, int x, int y,
                                    const std::string& name) {
    std::cout << "Type:" << (int)type << std::endl;
    std::shared_ptr<DungeonNPC> result;
    switch (type) {
        case OrcType:
            result = std::make_shared<Orc>(x, y, name);
            break;
        case SquirrelType:
            result = std::make_shared<Squirrel>(x, y, name);
            break;
        case BearType:
            result = std::make_shared<Bear>(x, y, name);
            break;
        default:
            break;
    }
    if (result) {
        result->subscribe(ConsoleObserver::get());
        result->subscribe(std::make_shared<FileObserver>());
    }

    return result;
}

void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& n : array) n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) result.insert(factory(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream& operator<<(std::ostream& os, const set_t& array) {
    for (auto& n : array) n->print();
    return os;
}
set_t fight(const set_t& array, size_t distance) {
    set_t dead_list;

    for (const auto& attacker : array)
        for (const auto& defender : array)
            if ((attacker != defender) &&
                (attacker->is_close(defender, distance))) {
                // Using Visitor pattern: attacker accepts defender as visitor
                bool success = defender->accept(attacker);
                if (success) dead_list.insert(defender);
            }

    return dead_list;
}
int main() {
    set_t array;

    std::cout << "Generating dungeon NPCs ..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        int x = std::rand() % 501;
        int y = std::rand() % 501;
        std::string name = "NPC_" + std::to_string(i);
        array.insert(factory(NpcType(std::rand() % 3 + 1), x, y, name));
    }
    std::cout << "Saving dungeon ..." << std::endl;

    save(array, "dungeon.txt");

    std::cout << "Loading dungeon ..." << std::endl;
    array = load("dungeon.txt");

    std::cout << "Dungeon NPCs list:" << std::endl;
    std::cout << array << std::endl;

    std::cout << "Starting battle mode ..." << std::endl;

    for (size_t distance = 20; (distance <= 100) && !array.empty();
         distance += 10) {
        auto dead_list = fight(array, distance);
        for (auto& d : dead_list) array.erase(d);
        std::cout << "Battle stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl
                  << std::endl;
    }

    std::cout << "Survivors:" << std::endl << array;

    return 0;
}
