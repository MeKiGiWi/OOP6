#pragma once

#include <math.h>

#include <cstring>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

// type for dungeon NPCs
struct DungeonNPC;
struct Orc;
struct Squirrel;
struct Bear;
using set_t = std::set<std::shared_ptr<DungeonNPC>>;

enum NpcType { Unknown = 0, OrcType = 1, SquirrelType = 2, BearType = 3 };

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<DungeonNPC> attacker,
                          const std::shared_ptr<DungeonNPC> defender,
                          bool win) = 0;
};

struct DungeonNPC : public std::enable_shared_from_this<DungeonNPC> {
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    std::vector<std::shared_ptr<IFightObserver>> observers;

    DungeonNPC(NpcType t, int _x, int _y, const std::string& _name);
    DungeonNPC(NpcType t, std::istream& is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<DungeonNPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<DungeonNPC>& other,
                          size_t distance) const;

    virtual bool is_orc() const;
    virtual bool is_squirrel() const;
    virtual bool is_bear() const;

    virtual bool fight(std::shared_ptr<Orc> other) = 0;
    virtual bool fight(std::shared_ptr<Squirrel> other) = 0;
    virtual bool fight(std::shared_ptr<Bear> other) = 0;
    virtual void print() = 0;

    virtual void save(std::ostream& os);

    // Visitor pattern method
    virtual bool accept(std::shared_ptr<DungeonNPC> visitor) = 0;

    friend std::ostream& operator<<(std::ostream& os, DungeonNPC& npc);
};
