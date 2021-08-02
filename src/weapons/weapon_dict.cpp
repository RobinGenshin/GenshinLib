#include "weapon_dict.h"
#include "alley_flash.h"
#include "amenoma_kageuchi.h"
#include "aquila_favonia.h"
#include "favonius_sword.h"
#include "festering_desire.h"
#include "fillet_blade.h"
#include "freedom_sworn.h"
#include "harbinger_of_dawn.h"
#include "iron_sting.h"
#include "mistsplitter.h"
#include "primordial_jade_cutter.h"
#include "royal_longsword.h"
#include "sacrificial_sword.h"
#include "skyward_blade.h"
#include "summit_shaper.h"
#include "the_black_sword.h"
#include "the_flute.h"

WeaponDict& WeaponDict::Get() {
    static WeaponDict instance;
    return instance;
};

WeaponDict::WeaponDict() {
    map["The Alley Flash"] = &createInstance<AlleyFlash>;
    map["Amenoma Kageuchi"] = &createInstance<AmenomaKageuchi>;
    map["Aquila Favonia"] = &createInstance<AquilaFavonia>;
    map["Favonius Sword"] = &createInstance<FavoniusSword>;
    map["Festering Desire"] = &createInstance<FesteringDesire>;
    map["Fillet Blade"] = &createInstance<FilletBlade>;
    map["Freedom Sworn"] = &createInstance<FreedomSworn>;
    map["Harbinger of Dawn"] = &createInstance<HarbingerOfDawn>;
    map["Iron Sting"] = &createInstance<IronSting>;
    map["Mistsplitter Reforged"] = &createInstance<Mistsplitter>;
    map["Primordial Jade Cutter"] = &createInstance<PrimordialJadeCutter>;
    map["Royal Longsword"] = &createInstance<RoyalLongsword>;
    map["Sacrificial Sword"] = &createInstance<SacrificialSword>;
    map["Skyward Blade"] = &createInstance<SkywardBlade>;
    map["Summit Shaper"] = &createInstance<SummitShaper>;
    map["The Black Sword"] = &createInstance<TheBlackSword>;
    map["The Flute"] = &createInstance<TheFlute>;
};