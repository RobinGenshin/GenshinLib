#include "blackcliff_agate.h"
#include "read_data.h"

BlackcliffAgate::BlackcliffAgate(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Blackcliff Agate")) {};