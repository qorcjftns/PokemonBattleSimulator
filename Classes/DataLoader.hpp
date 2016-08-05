//
//  DataLoader.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#ifndef DataLoader_hpp
#define DataLoader_hpp

#include <stdio.h>

#include "Pokemon.hpp"

class DataLoader {
public:
    static DataLoader *instance;
    
    static DataLoader *getInstance() {
        if(!instance) { instance = new DataLoader(); }
        return instance;
    }
    
    void loadPokemonDataFromDB();
};



#endif /* DataLoader_hpp */
