//
//  Type.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#ifndef Type_hpp
#define Type_hpp

#include <stdio.h>

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
} Type;
static const char * TypeStrings[] = {
    "NORMAL", "FIRE", "WATER", "GRASS", "ELECTRIC", "ICE", "FIGHTING",
    "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON"
};

class TypeUtil {
public:
    static std::string typeToString(Type t);
    static Type stringToType(std::string s);
};

#endif /* Type_hpp */
