//
//  Type.cpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#include "Type.hpp"

std::string TypeUtil::typeToString(Type t) {
    return TypeStrings[t];
}

Type TypeUtil::stringToType(std::string s) {
    for(int i = 0 ; i < 15 ; i++) {
        if(TypeStrings[i] == s) {
            return Type(i);
        }
    }
    return Type::NORMAL;
}