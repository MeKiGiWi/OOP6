#pragma once
#include "npc.h"

struct Squirrel : public DungeonNPC {
    Squirrel(int x, int y, const std::string& name);
    Squirrel(std::istream& is);
    void print() override;
    void save(std::ostream& os) override;
    bool is_squirrel() const override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    virtual bool accept(std::shared_ptr<DungeonNPC> visitor) override;

    friend std::ostream& operator<<(std::ostream& os, Squirrel& squirrel);
};
