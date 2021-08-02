#include "blackcliff_pole.h"
#include "read_data.h"

BlackcliffPole::BlackcliffPole(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Blackcliff Pole")) {};