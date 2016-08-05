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

Pokemon::Pokemon(int dex, Stat ev, Stat iv, Move m1, Move m2, Move m3, Move m4) {
    this->pokemon_index = dex;
    this->ev = ev;
    this->iv = iv;
    this->move1 = m1;
    this->move2 = m2;
    this->move3 = m3;
    this->move4 = m4;
    this->status_condition = NONE;
    
    PokemonBase base = PokemonUtil::getInstance()->pokemons[dex-1];
    
    this->type1 = base.type1;
    this->type2 = base.type2;
    
    this->level = 50; // Default level is 50
    
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

