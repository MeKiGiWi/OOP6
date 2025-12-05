#include "npc.h"

DungeonNPC::DungeonNPC(NpcType t, int _x, int _y, const std::string& _name)
    : type(t), x(_x), y(_y), name(_name) {}
DungeonNPC::DungeonNPC(NpcType t, std::istream& is) : type(t) {
    is >> x;
    is >> y;
    std::getline(is, name);  // Read the name from the remaining line
    if (name.empty() || name[0] == ' ') {
        std::getline(is, name);  // Get the name from the next line if needed
    }
    if (!name.empty() && name[0] == ' ') {
        name = name.substr(1);
    }
}
void DungeonNPC::subscribe(std::shared_ptr<IFightObserver> observer) {
    observers.push_back(observer);
}

void DungeonNPC::fight_notify(const std::shared_ptr<DungeonNPC> defender,
                              bool win) {
    for (auto& o : observers) o->on_fight(shared_from_this(), defender, win);
}

bool DungeonNPC::is_close(const std::shared_ptr<DungeonNPC>& other,
                          size_t distance) const {
    if (std::pow(x - other->x, 2) + std::pow(y - other->y, 2) <=
        std::pow(distance, 2))
        return true;
    else
        return false;
}

bool DungeonNPC::is_orc() const { return false; }
bool DungeonNPC::is_squirrel() const { return false; }
bool DungeonNPC::is_bear() const { return false; }

void DungeonNPC::save(std::ostream& os) {
    os << x << std::endl;
    os << y << std::endl;
    os << name << std::endl;
}

std::ostream& operator<<(std::ostream& os, DungeonNPC& npc) {
    os << "{ name: " << npc.name << ", x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}
