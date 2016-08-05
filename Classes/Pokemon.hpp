//
//  Pokemon.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-02.
//
//

#ifndef Pokemon_hpp
#define Pokemon_hpp

#include <stdio.h>

#include "Move.hpp"
#include "Type.hpp"

#define POKEMONCOUNT 151

typedef enum {
    NONE,
    ASLEEP,
    POISONED,
    BURNED,
    FROZEN,
    PARALYZED
} Condition;

struct Stat {
    int hp;
    int atk;
    int def;
    int spd;
    int sp;
};

struct PokemonBase {
    int dex_id;
    Stat stat;
    std::string name_ko;
    Type type1;
    Type type2;
    float catch_rate;
    int base_exp;
    std::string sprite_front;
    std::string sprite_back;
    Move move1;
    Move move2;
    Move move3;
    Move move4;
    bool available_tm[56];
};

class Pokemon {
private:
    int pokemon_index;
    std::string nickname;
    int current_hp;
    int level;
    Condition status_condition;
    float catch_rate;
    int trainer_id;
    int exp;
    int ev_hp;
    Stat ev;
    Stat iv;
    Move move1;
    Move move2;
    Move move3;
    Move move4;
    int move1_pp;
    int move2_pp;
    int move3_pp;
    int move4_pp;
    Stat av;
    
public:
    
    Type type1;
    Type type2;
    
    Pokemon(int dex, Stat ev, Stat iv, Move m1, Move m2, Move m3, Move m4);
    Stat getStat() { return this->av; }
    void calculateStats();
    
};

class PokemonUtil {
public:
    static PokemonUtil *instance;
    
    static PokemonUtil *getInstance() {
        if(!instance) { instance = new PokemonUtil(); }
        return instance;
    }
    
    std::vector<PokemonBase> pokemons;
};


#endif /* Pokemon_hpp */
