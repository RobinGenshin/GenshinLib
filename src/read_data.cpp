#include "read_data.h"
#include "enum_maps.h"

Data& Data::Get() {
    static Data instance;
    return instance;
};


float Data::pctstr_to_float(std::string pctstr) {
    if (pctstr == "") return 0;
    else {
        pctstr.pop_back();
        return (stof(pctstr) / 100);
    }
}

float Data::str_to_float(std::string pctstr) {
    if (pctstr == "") return 0;
    else return stof(pctstr);
}

int Data::str_to_int(std::string pctstr) {
    if (pctstr == "") return 0;
    else return stoi(pctstr);
}

std::vector<float> Data::str_to_vector_float(std::string liststr) {
    if (liststr == "") return {};
    else {
        std::vector<float> result;
        size_t start;
        size_t end = 0;
        while ((start = liststr.find_first_not_of(',', end)) != std::string::npos) {
            end = liststr.find(',', start);
            result.push_back(stof(liststr.substr(start, end - start)));
        }
        return result;
    }
}
std::vector<std::string> Data::str_to_vector_string(std::string liststr) {
    if (liststr == "") return {};
    else {
        std::vector<std::string> result;
        size_t start;
        size_t end = 0;
        while ((start = liststr.find_first_not_of(',', end)) != std::string::npos)
        {
            end = liststr.find(',', start);
            result.push_back(liststr.substr(start, end - start));
        }
        return result;
    }
}

std::pair<Stat, float> Data::str_to_pair_string_float(std::string pairstr) {
    if (pairstr == "") throw std::runtime_error("Incorrect pair string");
    else {
        std::vector<std::string> result;
        size_t start;
        size_t end = 0;
        while ((start = pairstr.find_first_not_of(':', end)) != std::string::npos)
        {
            end = pairstr.find(':', start);
            result.push_back(pairstr.substr(start, end - start));
        }
        //std::cout << pairstr << std::endl;
        return std::pair(EnumMap::get_stat_index(result.at(0)), Data::str_to_float(result.at(1)));
    }
};

std::map <std::string, GCharacter> Data::get_char_dict() {
    if (!character_data_read) read_character_data_from_local("data/Characters.csv", "data/Characters2.csv");
    return char_dict;
};

std::map <std::string, GWeapon> Data::get_weap_dict() {
    if (!weapon_data_read) read_weapon_data("data/Weapons.csv");
    return weap_dict;
};

std::map <std::string, FeatureData> Data::get_feature_dict() {
    if (!feature_data_read) read_feature_data("data/Features.csv");
    return feature_dict;
};

std::map <std::string, Monster> Data::get_monster_dict() {
    if (!monster_data_read) read_monster_data("data/Monsters.csv");
    return monster_dict;
};

std::map<int, float> Data::get_reaction_scaling_dict() {
    if (!reaction_scaling_data_read) read_reaction_scaling_data("data/ReactionScaling.csv");
    return reaction_scaling_dict;
};

void Data::read_character_data_from_string(std::string file1, std::string file2) {
    std::stringstream file1ss = std::stringstream(file1);
    //std::cout << file1ss.good() << std::endl;
    std::stringstream file2ss = std::stringstream(file2);

    rapidcsv::Document doc(file1ss, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    rapidcsv::Document doc2(file2ss, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));
    read_character_data(doc, doc2);
};

void Data::read_character_data_from_local(std::string file1, std::string file2) {
    rapidcsv::Document doc(file1, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    rapidcsv::Document doc2(file2, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));
    read_character_data(doc, doc2);
};


void Data::read_character_data(rapidcsv::Document doc, rapidcsv::Document doc2) {
    std::map<std::string, GCharacter> dict = {};
    std::vector<std::string> talents1 = { "normal", "charged" };
    std::vector<std::string> talents2 = { "skill", "burst" };
    std::vector<std::string> characters = { "Amber", "Albedo" };

    //std::cout << "Opened docs..\n";

    for (auto& c : characters) {
        dict.emplace(std::piecewise_construct,
            std::forward_as_tuple(c),
            std::forward_as_tuple());

        std::vector<std::string> columNames = doc2.GetColumnNames();
        //for (auto& i : columNames) std::cout << i << ", ";

        GCharacter& cha = dict.at(c);
        cha.character_name = c;
        cha.character_rarity = doc.GetCell<int>("character_rarity", c);
        cha.character_element = EnumMap::get_element_index(doc.GetCell<std::string>("element", c));
        cha.ascension_stat = EnumMap::get_stat_index(doc.GetCell<std::string>("ascension_stat", c));
        cha.weapon_type = EnumMap::get_weapon_index(doc.GetCell<std::string>("weapon_class", c));
        cha.region = EnumMap::get_region_index(doc.GetCell<std::string>("region", c));
        cha.character_stat_growths = CharacterStatGrowths(doc.GetCell<float>("base_atk", c), doc.GetCell<float>("base_def", c), doc.GetCell<float>("base_hp", c),
            doc.GetCell<float>("growth_atk", c), doc.GetCell<float>("growth_def", c), doc.GetCell<float>("growth_hp", c));

        for (size_t j = 0, jlen = talents1.size(); j < jlen; j++) {

            std::string talent = talents1.at(j);

            TalentData td;
            td.element = EnumMap::get_element_index(doc.GetCell<std::string>(std::string(talent + "_type"), c));
            td.talent_type = EnumMap::get_talent_index(talent);
            td.ticks = doc.GetCell<int>(std::string(talent + "_ticks"), c);
            td.times = str_to_vector_float(doc.GetCell<std::string>(talent + "_tick_times", c));
            td.a_tag = EnumMap::get_atag_index(doc.GetCell<std::string>(talent + "_a_tag", c));
            td.a_group = EnumMap::get_agroup_index(doc.GetCell<std::string>(talent +"_a_group", c));
            td.damage = {};
            std::vector<float> vd = str_to_vector_float(doc.GetCell<std::string>(talent + "_tick_damage", c));
            td.damage[DamageScalingStat::ATK] = vd;
            if (talent == "normal") td.at = doc.GetCell<float>("normal_at", c);
            if (talent == "normal" || talent == "charged") td.hitlag = str_to_vector_float(doc.GetCell<std::string>(talent + "_tick_hitlag", c));
            td.time_to_cancel = str_to_vector_float(doc.GetCell<std::string>(talent + "_cancel", c));
            td.time_to_swap = str_to_vector_float(doc.GetCell<std::string>(talent + "_swap", c));
            if (talent != "skill") td.time_to_skill = str_to_vector_float(doc.GetCell<std::string>(talent + "_skill", c));
            if (talent != "burst") td.time_to_burst = str_to_vector_float(doc.GetCell<std::string>(talent + "_burst", c));
            td.time_to_attack = str_to_vector_float(doc.GetCell<std::string>(talent + "_attack", c));
            if (talent == "skill" || talent == "burst") td.cd = doc.GetCell<float>(talent + "_cd", c);
            td.scaling = doc.GetCell<std::string>(talent + "_scaling", c);

            cha.talent_data.emplace(std::make_pair(EnumMap::get_talent_index(talent), std::make_shared<TalentData>(td)));
        };

        for (size_t j = 0, jlen = talents2.size(); j < jlen; j++) {
            std::string talent = talents2.at(j);

            TalentData td;
            td.element = EnumMap::get_element_index(doc.GetCell<std::string>("element", c));
            td.talent_type = EnumMap::get_talent_index(talent);
            td.ticks = doc2.GetCell<int>(std::string(talent + "_ticks"), c);
            td.times = str_to_vector_float(doc2.GetCell<std::string>(talent + "_tick_times", c));
            td.damage = {};
            std::vector<float> vd = str_to_vector_float(doc2.GetCell<std::string>(talent + "_tick_damage", c));
            td.damage[DamageScalingStat::ATK] = vd;
            if (talent == "normal" || talent == "charged") td.hitlag = str_to_vector_float(doc2.GetCell<std::string>(talent + "_tick_hitlag", c));
            td.time_to_cancel = str_to_vector_float(doc2.GetCell<std::string>(talent + "_cancel", c));
            td.time_to_swap = str_to_vector_float(doc2.GetCell<std::string>(talent + "_swap", c));
            if (talent != "skill") td.time_to_skill = str_to_vector_float(doc2.GetCell<std::string>(talent + "_skill", c));
            if (talent != "burst") td.time_to_burst = str_to_vector_float(doc2.GetCell<std::string>(talent + "_burst", c));
            td.time_to_attack = str_to_vector_float(doc2.GetCell<std::string>(talent + "_attack", c));
            if (talent == "skill" || talent == "burst") td.cd = doc2.GetCell<float>(talent + "_cd", c);
            if (talent == "skill") td.particles = str_to_vector_float(doc2.GetCell<std::string>("skill_particles", c));
            td.scaling = doc2.GetCell<std::string>(talent + "_scaling", c);

            cha.talent_data.emplace(std::make_pair(EnumMap::get_talent_index(talent), std::make_shared<TalentData>(td)));
        };
    };
    //std::cout << "Finished constructing character_data\n";
    char_dict = dict;
    character_data_read = true;
};

void Data::read_weapon_data(std::string file1) {

    std::cout << "READING WEAPON DATA: " << file1 << std::endl;
    //std::stringstream file1ss = std::stringstream(file1);

    rapidcsv::Document docc(file1, rapidcsv::LabelParams(0, -1),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    std::map<std::string, GWeapon> dict = {};

    //std::cout << docc.GetColumnNames().size() << std::endl;
    //std::cout << docc.GetRowNames().size() << std::endl;
    //for (auto& i : docc.GetColumnNames()) std::cout << i << ", ";


    //throw std::runtime_error("");

    std::vector<std::string> weapNames = docc.GetColumn<std::string>("weapon_name");

    rapidcsv::Document doc(file1, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));


    for (auto& c : weapNames) {
        dict.emplace(std::piecewise_construct,
            std::forward_as_tuple(c),
            std::forward_as_tuple());

        GWeapon& weap = dict.at(c);
        weap.weapon_name = c;
        weap.weapon_class = doc.GetCell<std::string>("weapon_class", c);
        weap.weapon_type = EnumMap::get_weapon_index(doc.GetCell<std::string>("weapon_type", c));
        weap.weapon_rarity = doc.GetCell<int>("weapon_rarity", c);
        std::string weapon_stat = doc.GetCell<std::string>("weapon_stat", c);
        weap.weapon_stat = EnumMap::get_stat_index(weapon_stat);
        weap.base_stat_value = Data::pctstr_to_float(doc.GetCell<std::string>(weapon_stat, c));
    };
    weap_dict = dict;
    weapon_data_read = true;
};

void Data::read_feature_data(std::string filePath) {
    rapidcsv::Document docc(filePath, rapidcsv::LabelParams(0, -1),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    std::map<std::string, FeatureData> dict = {};
    std::vector<std::string> featNames = docc.GetColumn<std::string>("feature_name");

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    //std::cout << featNames.size() << std::endl;

    for (auto& c : featNames) {
        dict.emplace(std::piecewise_construct,
            std::forward_as_tuple(c),
            std::forward_as_tuple());

        FeatureData& feat = dict.at(c);
        feat.name = c;
        if (doc.GetCell<std::string>("type", c) == "Dynamic") feat.dynamic = true; else feat.dynamic = false;
        feat.character = doc.GetCell<std::string>("character", c);
        feat.weapon = doc.GetCell<std::string>("weapon", c);
        feat.artifact = doc.GetCell<std::string>("artifact", c);
        feat.constellation = doc.GetCell<int>("constellation", c);
        feat.condition = str_to_vector_string(doc.GetCell<std::string>("condition", c));
        //std::cout << std::endl;
        //for (auto& i : feat.condition) std::cout << i << ", " << (i == "any");
        //std::cout << std::endl;
        feat.timing = doc.GetCell<std::string>("timing", c);
        feat.temporary = (doc.GetCell<std::string>("temporary", c) == "TRUE");
        feat.share = (doc.GetCell<std::string>("share", c) == "TRUE");
        feat.field = (doc.GetCell<std::string>("field", c) == "TRUE");

        std::vector<std::string> smvec = str_to_vector_string(doc.GetCell<std::string>("static_modifiers", c));
        if (smvec.size() > 0) for (auto& i : smvec) feat.stat_modifier_data.insert(str_to_pair_string_float(i));

        if (feat.character != "") feat.feature_category = "character";
    };
    feature_dict = dict;
    feature_data_read = true;
}

void Data::read_monster_data(std::string filePath) {
    rapidcsv::Document docc(filePath, rapidcsv::LabelParams(0, -1),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    std::map<std::string, Monster> dict = {};
    std::vector<std::string> featNames = docc.GetColumn<std::string>("monster");

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    //std::cout << featNames.size() << std::endl;

    for (auto& c : featNames) {
        dict.emplace(std::piecewise_construct,
            std::forward_as_tuple(c),
            std::forward_as_tuple());
        Monster& monster = dict.at(c);
        monster.monster_name = c;
        std::vector<Element> vec = {Element::ANEMO, Element::CRYO, Element::ELECTRO, Element::GEO, Element::HYDRO, Element::PHYSICAL, Element::PYRO};
        for (auto& i : vec) monster.res_dict.emplace(i, Data::pctstr_to_float(doc.GetCell<std::string>(EnumMap::get_string_element(i) + "_res", c)));
    };
    monster_dict = dict;
    monster_data_read = true;
};

void Data::read_reaction_scaling_data(std::string filePath) {
    rapidcsv::Document docc(filePath, rapidcsv::LabelParams(0, -1),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));
    std::map<int, float> dict = {};

    std::vector<int> levels = docc.GetColumn<int>("level");

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(0, 0),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true));

    for (auto& c : levels) {
        dict.emplace(c, doc.GetCell<float>("multiplier", c));
    };

    reaction_scaling_dict = dict;
    reaction_scaling_data_read = true;

};

Data::Data() : char_dict({}), weap_dict({}), feature_dict(), reaction_scaling_dict() { read_feature_data("data/Features.csv"); };
