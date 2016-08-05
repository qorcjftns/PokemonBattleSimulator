//
//  Battle.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-05.
//
//

#ifndef Battle_hpp
#define Battle_hpp

#include <stdio.h>
#include "Pokemon.hpp"
#include "Item.hpp"

class Player {
public:
    std::vector<Pokemon> pokemons;
    std::vector<Item> items;
    std::string nickname;
};

class Battle {
public:
    Player player1;
    Player player2;
};

#endif /* Battle_hpp */
