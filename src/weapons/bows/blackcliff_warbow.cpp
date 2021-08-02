#include "blackcliff_warbow.h"
#include "read_data.h"

BlackcliffWarbow::BlackcliffWarbow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Blackcliff Warbow")) {};