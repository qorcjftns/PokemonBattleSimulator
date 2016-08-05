//
//  Move.cpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#include "Move.hpp"


MoveUtil *MoveUtil::instance = NULL;

Move::Move() {
    
}

Move::Move(int move_id, std::string name_en, std::string name_ko, std::string name_jp, int pp, int power, int accuracy, MoveCategory category, Type type) {
    
    this->move_id = move_id;
    
    this->name_en = name_en;
    this->name_ko = name_ko;
    this->name_jp = name_jp;
    
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    
    this->move_category = category;
    this->move_type = type;
    
}

std::string Move::getName() {
    return name_ko;
}

std::vector<Move> MoveUtil::getMoveLearnByPokemon(int dex_id) {
    int size = movelearn_list.size();
    std::vector<Move> ret;
    for(int i = 0 ; i < size ; i++) {
        if(movelearn_list[i].dex_id == dex_id) {
            ret.push_back(movelist[movelearn_list[i].move_id - 1]);
        }
    }
    return ret;
}

std::vector<Move> MoveUtil::getMoveLearnByPokemonlvl1(int dex_id) {
    int size = movelearn_list.size();
    std::vector<Move> ret;
    for(int i = 0 ; i < size ; i++) {
        if(movelearn_list[i].dex_id == dex_id && movelearn_list[i].level == 1) {
            ret.push_back(movelist[movelearn_list[i].move_id - 1]);
        }
    }
    return ret;
}
