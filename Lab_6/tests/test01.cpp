#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/ork.h"
#include "../include/belka.h"
#include "../include/medved.h"
#include <memory>

TEST(FightTest, OrkKillsMedved) {
    auto ork = std::make_shared<Ork>(0, 0);
    auto medved = std::make_shared<Medved>(1, 1);

    EXPECT_TRUE(ork->accept(medved));
    EXPECT_FALSE(medved->accept(ork));
}

TEST(FightTest, MedvedKillsBelka) {
    auto medved = std::make_shared<Medved>(0, 0);
    auto belka = std::make_shared<Belka>(1, 1);

    EXPECT_TRUE(medved->accept(belka));
    EXPECT_FALSE(belka->accept(medved));
}

TEST(FightTest, OrkKillsBelka) {
    auto ork = std::make_shared<Ork>(0, 0);
    auto belka = std::make_shared<Belka>(1, 1);

    EXPECT_TRUE(ork->accept(belka));
    EXPECT_FALSE(belka->accept(ork));
}

TEST(FightTest, SameTypeFightDraw) {
    auto ork1 = std::make_shared<Ork>(0, 0);
    auto ork2 = std::make_shared<Ork>(1, 1);

    EXPECT_FALSE(ork1->accept(ork2));
    EXPECT_FALSE(ork2->accept(ork1));

    auto belka1 = std::make_shared<Belka>(0, 0);
    auto belka2 = std::make_shared<Belka>(1, 1);

    EXPECT_FALSE(belka1->accept(belka2));
    EXPECT_FALSE(belka2->accept(belka1));

    auto medved1 = std::make_shared<Medved>(0, 0);
    auto medved2 = std::make_shared<Medved>(1, 1);

    EXPECT_FALSE(medved1->accept(medved2));
    EXPECT_FALSE(medved2->accept(medved1));
}

TEST(FightTest, DistanceTest) {
    auto ork = std::make_shared<Ork>(0, 0);
    auto medved = std::make_shared<Medved>(5, 5);

    EXPECT_FALSE(ork->is_close(medved, 4));
    EXPECT_TRUE(ork->is_close(medved, 10));
}
