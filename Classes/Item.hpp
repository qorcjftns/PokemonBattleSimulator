//
//  Item.hpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-05.
//
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>

class Item {
public:
    int item_id;
    std::string name_en;
    std::string name_ko;
    std::string name_jp;
};

class ItemUtil {
public:
    static ItemUtil *instance;
    
    static ItemUtil *getInstance() {
        if(!instance) { instance = new ItemUtil(); }
        return instance;
    }
    
    std::vector<Item> items;
};

#endif /* Item_hpp */
