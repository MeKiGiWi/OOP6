#include "orc.h"

#include "bear.h"
#include "squirrel.h"

Orc::Orc(int x, int y, const std::string& name)
    : DungeonNPC(OrcType, x, y, name) {}
Orc::Orc(std::istream& is) : DungeonNPC(OrcType, is) {}

void Orc::print() { std::cout << *this; }

bool Orc::is_orc() const { return true; }

bool Orc::fight(std::shared_ptr<Orc> other) {
    // Orcs kill orcs
    fight_notify(other, true);
    return true;
}

bool Orc::fight(std::shared_ptr<Squirrel> other) {
    fight_notify(other, false);
    return false;
}

bool Orc::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, true);
    return true;
}

void Orc::save(std::ostream& os) {
    os << OrcType << std::endl;
    DungeonNPC::save(os);
}

std::ostream& operator<<(std::ostream& os, Orc& orc) {
    os << "orc: " << *static_cast<DungeonNPC*>(&orc) << std::endl;
    return os;
}

bool Orc::accept(std::shared_ptr<DungeonNPC> visitor) {
    if (visitor->is_orc()) {
        return fight(std::dynamic_pointer_cast<Orc>(visitor));
    } else if (visitor->is_squirrel()) {
        return fight(std::dynamic_pointer_cast<Squirrel>(visitor));
    } else if (visitor->is_bear()) {
        return fight(std::dynamic_pointer_cast<Bear>(visitor));
    }
    return false;
}
