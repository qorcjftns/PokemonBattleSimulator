//
//  Move.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#ifndef Move_hpp
#define Move_hpp

#include <stdio.h>

#include "Type.hpp"

#define MOVECOUNT 165

typedef enum {
    PHYSICAL, SPECIAL, STATUS
} MoveCategory;

class Move {
private:
    int move_id;
    std::string name_en;
    std::string name_ko;
    std::string name_jp;
    
    int pp;
    int power;
    int accuracy;
    
    MoveCategory move_category;
    
    Type move_type;
    
public:
    Move();
    Move(int move_id, std::string name_en, std::string name_ko, std::string name_jp, int pp, int power, int accuracy, MoveCategory category, Type type);
    
    std::string getName();
    
};

struct MoveLearn {
    int dex_id;
    int move_id;
    int level;
    int machine;
};

class MoveUtil {
public:
    static MoveUtil *instance;
    
    static MoveUtil *getInstance() {
        if(!instance) { instance = new MoveUtil(); }
        return instance;
    }
    std::vector<Move> getMoveLearnByPokemon(int dex_id);
    std::vector<Move> getMoveLearnByPokemonlvl1(int dex_id);
    std::vector<MoveLearn> movelearn_list;
    std::vector<Move> movelist;
};


#endif /* Move_hpp */
