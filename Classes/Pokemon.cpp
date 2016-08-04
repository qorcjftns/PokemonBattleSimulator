//
//  Pokemon.cpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-02.
//
//

#include "cocos2d.h"
#include "Pokemon.hpp"
#include "sqlite3.h"

DataLoader *DataLoader::instance = NULL;

static int callback(void *data, int argc, char **argv, char **azColName){
    
    int dex_id = atoi(argv[0]);
    
    std::string name = argv[1];
    
    Poketype type1 = Poketype(atoi(argv[7]));
    Poketype type2 = argv[8] ? Poketype(atoi(argv[8])) : type1;
    
    Stat stat;
    stat.hp = atoi(argv[9]);
    stat.atk = atoi(argv[10]);
    stat.def = atoi(argv[11]);
    stat.spd = atoi(argv[14]);
    stat.sp = atoi(argv[12]);
    
    PokemonBase p;

    p.dex_id = dex_id;
    p.name_ko = name;
    p.stat = stat;
    p.type1 = type1;
    p.type2 = type2;
    
    DataLoader::getInstance()->pokemons.push_back(p);
    
    return 0;
}

void DataLoader::loadPokemonDataFromDB() {
    sqlite3 *db;
    char * errMsg = NULL;
    int result;
    
    std::string dbPath = cocos2d::FileUtils::getInstance()->getWritablePath();
    
    dbPath.append("pokemon.sqlite");
    
    
    if(!cocos2d::FileUtils::getInstance()->isFileExist(dbPath)) {
        cocos2d::Data d = cocos2d::FileUtils::getInstance()->getDataFromFile("res/pokemon.sqlite");
        cocos2d::FileUtils::getInstance()->writeDataToFile(d, dbPath);
    }
    
    result = sqlite3_open_v2(dbPath.c_str(), &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    
    if( result != SQLITE_OK )
        CCLOG( "failed，status_code:%d ，error_msg:%s\n" , result, errMsg );
    
    sqlite3_exec(db, "SELECT * FROM PokemonData", callback, NULL, &errMsg);
}