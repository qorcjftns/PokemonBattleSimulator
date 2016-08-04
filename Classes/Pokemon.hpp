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

#define POKEMONCOUNT 151

typedef enum {
    NORMAL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
} Poketype;
static const char * PoketypeStrings[] = {
    "NORMAL", "FIRE", "WATER", "GRASS", "ELECTRIC", "ICE", "FIGHTING",
    "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON"
};

typedef enum {
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
    Poketype type1;
    Poketype type2;
    float catch_rate;
    int base_exp;
    std::string sprite_front;
    std::string sprite_back;
    int move1;
    int move2;
    int move3;
    int move4;
    bool available_tm[56];
    
};

class Pokemon {
private:
    int pokemon_index;
    std::string nickname;
    int current_hp;
    int level;
    Condition status_condition;
    Poketype type1;
    Poketype type2;
    float catch_rate;
    int move1;
    int move2;
    int move3;
    int move4;
    int trainer_id;
    int exp;
    int ev_hp;
    Stat ev;
    Stat iv;
    int move1_pp;
    int move2_pp;
    int move3_pp;
    int move4_pp;
    Stat av;
    
public:
    
};

class DataLoader {
public:
    static DataLoader *instance;
    
    static DataLoader *getInstance() {
        if(!instance) { instance = new DataLoader(); }
        return instance;
    }
    static const char *getPoketypeString(Poketype t) {
        return PoketypeStrings[t - 1];
    }
    
    void loadPokemonDataFromDB();
    std::vector<PokemonBase> pokemons;
};

#endif /* Pokemon_hpp */
