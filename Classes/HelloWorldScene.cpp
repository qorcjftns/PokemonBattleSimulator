#include "cocos2d.h"
#include "CocosGUI.h"

#include "HelloWorldScene.h"
#include "DataLoader.hpp"
#include "Pokemon.hpp"
#include "Battle.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    /////////////////////////////
//    // 2. add a menu item with "X" image, which is clicked to quit the program
//    //    you may modify it.
//
//    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//    
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    DataLoader::getInstance()->loadFromDB();
    
    Player p;
    p.pokemons.push_back(Pokemon(1));
    p.pokemons.push_back(Pokemon(4));
    p.pokemons.push_back(Pokemon(7));
    
    auto pokemonListView = cocos2d::ui::ListView::create();
    pokemonListView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    pokemonListView->setTouchEnabled(true);
    pokemonListView->setBounceEnabled(true);
    
    auto uiLayer = Layer::create();
    this->addChild(uiLayer);
    
    Size spriteSize;
    
    for(int i = 0 ; i < POKEMONCOUNT ; i++) {
        PokemonBase pkmn = PokemonUtil::getInstance()->pokemons[i];
        
        // Sprite
        auto spr = Sprite::create(pkmn.sprite_front);
        spr->setAnchorPoint(Vec2(0, 0.5));
        spr->setScale(5);
        
        // Name
        auto nameLabel = Label::createWithSystemFont(pkmn.name_ko, "Arial", 24);
        nameLabel->setPositionX(spr->getContentSize().width*5 + nameLabel->getContentSize().width/2);
        
        // Create Widget
        auto wid = cocos2d::ui::Widget::create();
        
        // Widget Setting
        Size widSize = spr->getContentSize() * 5;
        widSize.width += nameLabel->getContentSize().width + 10;
        wid->setContentSize(widSize);
        
        
        wid->addChild(spr);
        wid->addChild(nameLabel);
        
        if(spriteSize.width < wid->getContentSize().width)
            spriteSize = wid->getContentSize();
        
        pokemonListView->pushBackCustomItem(wid);
    }
    
    pokemonListView->setContentSize(Size(spriteSize.width, visibleSize.height));
    pokemonListView->setInnerContainerSize(Size(spriteSize.width, spriteSize.height * POKEMONCOUNT));
    
    pokemonListView->setPosition(Vec2(origin.x + (visibleSize.width / 2) - (spriteSize.width / 2),
                                      origin.y));
    
    uiLayer->addChild(pokemonListView);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
