#include "blackcliff_longsword.h"
#include "read_data.h"

BlackcliffLongsword::BlackcliffLongsword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Blackcliff Longsword")) {};