#pragma once
#include "npc.h"

struct Bear : public DungeonNPC {
    Bear(int x, int y, const std::string& name);
    Bear(std::istream& is);

    void print() override;
    void save(std::ostream& os) override;
    bool is_bear() const override;

    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    virtual bool accept(std::shared_ptr<DungeonNPC> visitor) override;

    friend std::ostream& operator<<(std::ostream& os, Bear& bear);
};
