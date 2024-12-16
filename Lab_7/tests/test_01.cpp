#include <gtest/gtest.h>
#include "..\include\npc.h"
#include "..\include\squirrel.h"
#include "..\include\bear.h"
#include "..\include\orc.h"

// Тесты для класса NPC через производные классы
TEST(NPC, Constructor) {
    Squirrel squirrel(10, 20);
    EXPECT_EQ(squirrel.get_type(), SquirrelType);
    EXPECT_EQ(squirrel.position().first, 10);
    EXPECT_EQ(squirrel.position().second, 20);
    EXPECT_EQ(squirrel.get_move_distance(), 5);
    EXPECT_EQ(squirrel.get_kill_distance(), 5);
}

TEST(NPC, Move) {
    Squirrel squirrel(10, 20);
    squirrel.move(1, 1, 100, 100);
    EXPECT_EQ(squirrel.position().first, 11);
    EXPECT_EQ(squirrel.position().second, 21);
}

TEST(NPC, IsClose) {
    Squirrel squirrel1(10, 20);
    Squirrel squirrel2(12, 22);
    EXPECT_TRUE(squirrel1.is_close(std::make_shared<Squirrel>(squirrel2)));
}

// Тесты для класса Squirrel
TEST(Squirrel, Constructor) {
    Squirrel squirrel(10, 20);
    EXPECT_EQ(squirrel.get_type(), SquirrelType);
    EXPECT_EQ(squirrel.position().first, 10);
    EXPECT_EQ(squirrel.position().second, 20);
    EXPECT_EQ(squirrel.get_move_distance(), 5);
    EXPECT_EQ(squirrel.get_kill_distance(), 5);
}

TEST(Squirrel, Fight) {
    Squirrel squirrel1(10, 20);
    Squirrel squirrel2(12, 22);
    EXPECT_TRUE(squirrel1.fight(std::make_shared<Squirrel>(squirrel2)));
}

// Тесты для класса Bear
TEST(Bear, Constructor) {
    Bear bear(10, 20);
    EXPECT_EQ(bear.get_type(), BearType);
    EXPECT_EQ(bear.position().first, 10);
    EXPECT_EQ(bear.position().second, 20);
    EXPECT_EQ(bear.get_move_distance(), 5);
    EXPECT_EQ(bear.get_kill_distance(), 10);
}

TEST(Bear, Fight) {
    Bear bear1(10, 20);
    Bear bear2(12, 22);
    EXPECT_TRUE(bear1.fight(std::make_shared<Bear>(bear2)));
}

// Тесты для класса Orc
TEST(Orc, Constructor) {
    Orc orc(10, 20);
    EXPECT_EQ(orc.get_type(), OrcType);
    EXPECT_EQ(orc.position().first, 10);
    EXPECT_EQ(orc.position().second, 20);
    EXPECT_EQ(orc.get_move_distance(), 20);
    EXPECT_EQ(orc.get_kill_distance(), 10);
}

TEST(Orc, Fight) {
    Orc orc1(10, 20);
    Orc orc2(12, 22);
    EXPECT_TRUE(orc1.fight(std::make_shared<Orc>(orc2)));
}
