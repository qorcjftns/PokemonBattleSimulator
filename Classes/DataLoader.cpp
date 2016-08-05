//
//  DataLoader.cpp
//  PokemonBattleSimulator
//
//  Created by CheulSoon Baek on 2016-08-04.
//
//

#include "cocos2d.h"
#include "sqlite3.h"

#include "DataLoader.hpp"
#include "Pokemon.hpp"
#include "Move.hpp"
#include "Type.hpp"
#include "Item.hpp"

DataLoader *DataLoader::instance = NULL;

static int callback_item(void *data, int argc, char **argv, char **azColName){
    Item i = Item();
    i.item_id = atoi(argv[0]);
    i.name_en = argv[1]?argv[1]:"";
    i.name_ko = argv[2]?argv[2]:"";
    i.name_jp = argv[3]?argv[3]:"";
    
    ItemUtil::getInstance()->items.push_back(i);
}

static int callback_move(void *data, int argc, char **argv, char **azColName){
    
    Move m = Move(
                  atoi(argv[0]), // id
                  argv[1]?argv[1]:"",
                  argv[2]?argv[2]:"",
                  argv[3]?argv[3]:"", // names
                  argv[6]?atoi(argv[6]):-1, // pp
                  argv[7]?atoi(argv[7]):-1, // power
                  argv[8]?atoi(argv[8]):-1, // accuracy
                  MoveCategory(atoi(argv[5])), // category
                  Type(atoi(argv[4]))); // type
    
    MoveUtil::getInstance()->movelist.push_back(m);
    
    return 0;
}

static int callback_movelearn_lvl1(void *data, int argc, char **argv, char **azColName){
    Move m = MoveUtil::getInstance()->movelist[atoi(argv[1]) - 1];
    ((std::vector<Move> *) data)->push_back(m);
    return 0;
}

static int callback_movelearn(void *data, int argc, char **argv, char **azColName){
    
    MoveLearn ml = MoveLearn();
    ml.dex_id = atoi(argv[0]);
    ml.move_id = atoi(argv[1]);
    ml.level = atoi(argv[2]);
    ml.machine = atoi(argv[3]);
    
    MoveUtil::getInstance()->movelearn_list.push_back(ml);
    
    return 0;
}

static int callback_basestat(void *data, int argc, char **argv, char **azColName){
    char * errMsg = NULL;
    sqlite3 *db = (sqlite3 *)data;
    
    int dex_id = atoi(argv[0]);
    
    std::string name = argv[2];
    
    Type type1 = Type(atoi(argv[7]) - 1);
    Type type2 = argv[8] ? Type(atoi(argv[8]) - 1) : type1;
    
    Stat stat;
    stat.hp = atoi(argv[9]);
    stat.atk = atoi(argv[10]);
    stat.def = atoi(argv[11]);
    stat.sp = atoi(argv[12]);
    stat.spd = atoi(argv[13]);
    
    PokemonBase p;
    
    p.dex_id = dex_id;
    p.name_ko = name;
    p.stat = stat;
    p.type1 = type1;
    p.type2 = type2;
    
    // Get Move Learnable Data
    std::stringstream ss;
    ss << "SELECT * FROM MoveLearnGen1 WHERE pokemon_id = " << p.dex_id;
    std::string sql = ss.str();
    sqlite3_exec(db, sql.c_str(), callback_movelearn, NULL, &errMsg);
    
    // Handle Level 1 Move
    std::vector<Move> lvl1Moves = std::vector<Move>();
    ss << " AND level = 1";
    sql = ss.str();
    sqlite3_exec(db, sql.c_str(), callback_movelearn_lvl1, &lvl1Moves, &errMsg);
    
    p.move1 = lvl1Moves.size() >= 1 ? lvl1Moves[0] : Move();
    p.move2 = lvl1Moves.size() >= 2 ? lvl1Moves[1] : Move();
    p.move3 = lvl1Moves.size() >= 3 ? lvl1Moves[2] : Move();
    p.move4 = lvl1Moves.size() >= 4 ? lvl1Moves[3] : Move();
    
    // Front Sprite Image
    ss = std::stringstream();
    ss << "res/FRLG/" << dex_id << ".png";
    p.sprite_front = ss.str();
    
    // Back Sprite Image
    ss = std::stringstream();
    ss << "res/FRLG/back/" << dex_id << ".png";
    p.sprite_back = ss.str();
    
    PokemonUtil::getInstance()->pokemons.push_back(p);
    
    return 0;
}

void DataLoader::loadPokemonDataFromDB() {
    char * errMsg = NULL;
    // Get Pokemon Stat
    sqlite3_exec(db, "SELECT * FROM PokemonDataGen1", callback_basestat, db, &errMsg);
}
void DataLoader::loadMoveDataFromDB() {
    char * errMsg = NULL;
    // Get Move Data
    sqlite3_exec(db, "SELECT * FROM MoveGen1", callback_move, NULL, &errMsg);
}
void DataLoader::loadItemDataFromDB() {
    char * errMsg = NULL;
    // Get Move Data
    sqlite3_exec(db, "SELECT * FROM ItemGen1", callback_item, NULL, &errMsg);
}


void DataLoader::loadFromDB() {
    char * errMsg = NULL;
    int result;
    
    std::string dbPath = cocos2d::FileUtils::getInstance()->getWritablePath();
    
    printf("%s\n", dbPath.c_str());
    
    dbPath.append("pokemon.sqlite");
    
    
//    if(!cocos2d::FileUtils::getInstance()->isFileExist(dbPath)) {
        cocos2d::Data d = cocos2d::FileUtils::getInstance()->getDataFromFile("res/pokemon.sqlite");
        cocos2d::FileUtils::getInstance()->writeDataToFile(d, dbPath);
//    }
    
    result = sqlite3_open_v2(dbPath.c_str(), &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    
    if( result != SQLITE_OK )
        CCLOG( "failed，status_code:%d ，error_msg:%s\n" , result, errMsg );

    loadMoveDataFromDB();
    loadPokemonDataFromDB();
    loadItemDataFromDB();
}



