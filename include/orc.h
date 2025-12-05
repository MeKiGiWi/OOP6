#pragma once
#include "npc.h"

struct Orc : public DungeonNPC {
    Orc(int x, int y, const std::string& name);
    Orc(std::istream& is);

    void print() override;

    bool is_orc() const override;

    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Bear> other) override;

    void save(std::ostream& os) override;

    virtual bool accept(std::shared_ptr<DungeonNPC> visitor) override;

    friend std::ostream& operator<<(std::ostream& os, Orc& orc);
};
