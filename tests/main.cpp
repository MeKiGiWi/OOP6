#include <gtest/gtest.h>

#include "../include/bear.h"
#include "../include/npc.h"
#include "../include/orc.h"
#include "../include/squirrel.h"

// Test to verify the basic functionality of the dungeon editor
TEST(DungeonEditorTest, CreateAndPlaceNPCs) {
    // Create different types of NPCs
    auto orc = std::make_shared<Orc>(100, 200, "Gronk");
    auto squirrel = std::make_shared<Squirrel>(300, 400, "Chippy");
    auto bear = std::make_shared<Bear>(50, 75, "Bruno");

    // Verify coordinates
    EXPECT_EQ(orc->x, 100);
    EXPECT_EQ(orc->y, 200);
    EXPECT_EQ(squirrel->x, 300);
    EXPECT_EQ(squirrel->y, 400);
    EXPECT_EQ(bear->x, 50);
    EXPECT_EQ(bear->y, 75);

    // Verify names
    EXPECT_EQ(orc->name, "Gronk");
    EXPECT_EQ(squirrel->name, "Chippy");
    EXPECT_EQ(bear->name, "Bruno");

    // Verify types
    EXPECT_TRUE(orc->is_orc());
    EXPECT_TRUE(squirrel->is_squirrel());
    EXPECT_TRUE(bear->is_bear());

    // Verify distance calculation
    EXPECT_TRUE(orc->is_close(
        squirrel, 300));  // Should be close enough (distance ~282.84)
    EXPECT_FALSE(orc->is_close(squirrel, 200));  // Should be too far
}

// Test battle functionality
TEST(DungeonEditorTest, BattleRules) {
    auto orc = std::make_shared<Orc>(100, 100, "Orc1");
    auto squirrel = std::make_shared<Squirrel>(10, 10, "Squirrel1");
    auto bear = std::make_shared<Bear>(10, 100, "Bear1");

    // Orc vs Squirrel: Squirrel should win (squirrels kill orcs)
    EXPECT_FALSE(orc->fight(squirrel));  // Orc loses to squirrel

    // Reset for next test
    auto orc2 = std::make_shared<Orc>(100, 100, "Orc2");
    // Squirrel vs Orc: Squirrel should win (squirrels kill orcs)
    EXPECT_TRUE(squirrel->fight(orc2));

    // Bear vs Squirrel: Bear should win (bears kill squirrels)
    auto squirrel2 = std::make_shared<Squirrel>(10, 10, "Squirrel2");
    EXPECT_TRUE(bear->fight(squirrel2));

    // Orc vs Bear: Orc should win (orcs kill bears)
    auto bear2 = std::make_shared<Bear>(10, 100, "Bear2");
    EXPECT_TRUE(orc->fight(bear2));

    // Squirrels don't want to fight (both survive)
    auto squirrel3 = std::make_shared<Squirrel>(100, 100, "Squirrel3");
    auto squirrel4 = std::make_shared<Squirrel>(10, 100, "Squirrel4");
    EXPECT_FALSE(squirrel3->fight(squirrel4));  // Both squirrels should survive

    // Both bears die in fight
    auto bear3 = std::make_shared<Bear>(10, 100, "Bear3");
    auto bear4 = std::make_shared<Bear>(100, 100, "Bear4");
    EXPECT_FALSE(bear3->fight(bear4));  // Both bears should die
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
