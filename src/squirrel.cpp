#include "squirrel.h"

#include "bear.h"
#include "orc.h"

Squirrel::Squirrel(int x, int y, const std::string& name)
    : DungeonNPC(SquirrelType, x, y, name) {}
Squirrel::Squirrel(std::istream& is) : DungeonNPC(SquirrelType, is) {}

void Squirrel::print() { std::cout << *this; }

void Squirrel::save(std::ostream& os) {
    os << SquirrelType << std::endl;
    DungeonNPC::save(os);
}

bool Squirrel::is_squirrel() const { return true; }

bool Squirrel::fight(std::shared_ptr<Orc> other) {
    fight_notify(other, true);
    return true;
}

bool Squirrel::fight(std::shared_ptr<Squirrel> other) {
    fight_notify(other, false);
    return false;
}

bool Squirrel::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, true);
    return true;
}

std::ostream& operator<<(std::ostream& os, Squirrel& squirrel) {
    os << "squirrel: " << *static_cast<DungeonNPC*>(&squirrel) << std::endl;
    return os;
}

bool Squirrel::accept(std::shared_ptr<DungeonNPC> visitor) {
    if (visitor->is_orc()) {
        return fight(std::dynamic_pointer_cast<Orc>(visitor));
    } else if (visitor->is_squirrel()) {
        return fight(std::dynamic_pointer_cast<Squirrel>(visitor));
    } else if (visitor->is_bear()) {
        return fight(std::dynamic_pointer_cast<Bear>(visitor));
    }
    return false;
}
