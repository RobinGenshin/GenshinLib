#include "blackcliff_slasher.h"
#include "read_data.h"

BlackcliffSlasher::BlackcliffSlasher(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Blackcliff Slasher")) {};