// GenshinSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "sim.h"
#include "enum_maps.h"
#include "weapon_dict.h"

int main()
{
    std::cout << "Constructing team..\n";
    Team t;
    std::cout << "Constructed team..\n";
    t.EquipComponentToPlayer(0, Player::ComponentsInd::CHARACTER, "Albedo");
    t.players.at(0).get()->set_mainstat(Player::ArtifactPiece::FLOWER, Stat::FLAT_HP);
    t.players.at(0).get()->set_mainstat(Player::ArtifactPiece::GOBLET, Stat::GEO_DMG);
    t.players.at(0).get()->set_substat_amount(Stat::PCT_DEF, 0);

    Enemy e;
    e.EquipMonster("Cryowhopper");
    std::cout << "Constructing sim instance..\n";
    Sim sim(&t, &e);
    std::cout << "Constructed sim instance.\n";
    std::cout << sim.players.size() << std::endl;
    std::cout << "Turning on sim..\n";

    for (auto& i : WeaponDict::Get().map) {
        t.EquipComponentToPlayer(0, Player::ComponentsInd::WEAPON, i.first);
        sim.ResetTeam();
        sim.TurnOnSim();
    };

    std::cout << "DPS: " << (sim.damage / sim.current_time) << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
