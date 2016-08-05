//
//  Pokemon.cpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-02.
//
//

#include <cmath>

#include "cocos2d.h"
#include "sqlite3.h"

#include "Pokemon.hpp"
#include "DataLoader.hpp"

PokemonUtil *PokemonUtil::instance = NULL;

Pokemon::Pokemon(int dex) {
    this->pokemon_index = dex;
    this->ev = ev;
    this->iv = iv;
    this->status_condition = NONE;
    
    PokemonBase base = PokemonUtil::getInstance()->pokemons[dex-1];
    
    this->move1 = base.move1;
    this->move2 = base.move2;
    this->move3 = base.move3;
    this->move4 = base.move4;
    
    // Set Individual Value (IV)
    std::srand(std::time(0));
    this->iv = Stat();
    iv.hp = rand() % IV_MAX_GEN1;
    iv.atk = rand() % IV_MAX_GEN1;
    iv.def = rand() % IV_MAX_GEN1;
    iv.spd = rand() % IV_MAX_GEN1;
    iv.sp = rand() % IV_MAX_GEN1;
    
    // Set Effort Value (EV)
    std::srand(std::time(0));
    this->ev = Stat();
    iv.hp = 0;
    iv.atk = 0;
    iv.def = 0;
    iv.spd = 0;
    iv.sp = 0;
    
    this->type1 = base.type1;
    this->type2 = base.type2;
    
    this->level = 1;
    
    calculateStats();
}

void Pokemon::calculateStats() {
    Stat av;
    PokemonBase base = PokemonUtil::getInstance()->pokemons[this->pokemon_index-1];
    av.hp = std::floor((((base.stat.hp + iv.hp) * 2) + std::floor(std::sqrt(ev.hp))) * level / 100) + level + 10;
    av.atk = std::floor((((base.stat.atk + iv.atk) * 2) + std::floor(std::sqrt(ev.atk))) * level / 100) + 5;
    av.def = std::floor((((base.stat.def + iv.def) * 2) + std::floor(std::sqrt(ev.def))) * level / 100) + 5;
    av.spd = std::floor((((base.stat.spd + iv.spd) * 2) + std::floor(std::sqrt(ev.spd))) * level / 100) + 5;
    av.sp = std::floor((((base.stat.sp + iv.sp) * 2) + std::floor(std::sqrt(ev.sp))) * level / 100) + 5;
    
    this->av = av;
}

