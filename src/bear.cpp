#include "bear.h"

#include "orc.h"
#include "squirrel.h"

Bear::Bear(int x, int y, const std::string& name)
    : DungeonNPC(BearType, x, y, name) {}
Bear::Bear(std::istream& is) : DungeonNPC(BearType, is) {}

void Bear::print() { std::cout << *this; }

void Bear::save(std::ostream& os) {
    os << BearType << std::endl;
    DungeonNPC::save(os);
}

bool Bear::is_bear() const { return true; }

bool Bear::fight(std::shared_ptr<Orc> other) {
    fight_notify(other, false);
    return false;
}

bool Bear::fight(std::shared_ptr<Squirrel> other) {
    fight_notify(other, true);
    return true;
}

bool Bear::fight(std::shared_ptr<Bear> other) {
    fight_notify(other, false);
    return false;
}

std::ostream& operator<<(std::ostream& os, Bear& bear) {
    os << "bear: " << *static_cast<DungeonNPC*>(&bear) << std::endl;
    return os;
}

bool Bear::accept(std::shared_ptr<DungeonNPC> visitor) {
    if (visitor->is_orc()) {
        return fight(std::dynamic_pointer_cast<Orc>(visitor));
    } else if (visitor->is_squirrel()) {
        return fight(std::dynamic_pointer_cast<Squirrel>(visitor));
    } else if (visitor->is_bear()) {
        return fight(std::dynamic_pointer_cast<Bear>(visitor));
    }
    return false;
}
