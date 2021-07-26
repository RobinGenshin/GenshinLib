#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include "rapidcsv.h"
#include "character.h"
#include "weapon.h"
#include "talent_data.h"
#include "damage_data.h"
#include "static_feature.h"
#include "monster.h"

class Data {

public:

    static Data& Get();
    Data(const Data&) = delete;

    static float pctstr_to_float(std::string pctstr);

    static float str_to_float(std::string pctstr);
    static int str_to_int(std::string pctstr);

    static std::vector<float> str_to_vector_float(std::string liststr);
    static std::vector<std::string> str_to_vector_string(std::string liststr);

    static std::pair<Stat, float> str_to_pair_string_float(std::string pairstr);

    std::map <std::string, GCharacter> get_char_dict();
    std::map <std::string, GWeapon> get_weap_dict();
    std::map <std::string, FeatureData> get_feature_dict();
    std::map <std::string, Monster> get_monster_dict();
    std::map <int, float> get_reaction_scaling_dict();

    void read_character_data_from_string(std::string file1, std::string file2);
    void read_character_data_from_local(std::string file1, std::string file2);

    void read_character_data(rapidcsv::Document doc, rapidcsv::Document doc2);

    void read_weapon_data(std::string file1);
    void read_feature_data(std::string filePath);
    void read_monster_data(std::string filePath);
    void read_reaction_scaling_data(std::string filePath);

private:
    Data();
    bool character_data_read = false;
    bool weapon_data_read = false;
    bool feature_data_read = false;
    bool monster_data_read = false;
    bool reaction_scaling_data_read = false;

    std::map <std::string, GCharacter> char_dict;
    std::map <std::string, GWeapon> weap_dict;
    std::map <std::string, FeatureData> feature_dict;
    std::map <std::string, Monster> monster_dict;
    std::map <int, float> reaction_scaling_dict;
};
