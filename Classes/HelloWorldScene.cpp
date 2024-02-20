/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

std::vector<cocos2d::Sprite*>cardSprites;
std::vector<Card>cardInfos;
Player player;
Player dealer;
Deck deck;

char itemAdrBuf[BUF_LEN];
bool ready = false;


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

HelloWorld::HelloWorld() {
    this->isUserSelected = false;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    deck = Deck();
    player = Player();
    dealer = Player();
    
    auto button_odd = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::oddSelected, this));
    button_odd->setPosition(Vec2(80, 80));
    auto bt_odd = Menu::create(button_odd, NULL);
    bt_odd->setPosition(Vec2::ZERO);
    bt_odd->setTag(1);
    this->addChild(bt_odd, 1);

    auto button_even = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::evenSelected, this));
    button_even->setPosition(Vec2(400, 80));
    auto bt_even = Menu::create(button_even, NULL);
    bt_even->setPosition(Vec2::ZERO);
    bt_even->setTag(2);
    this->addChild(bt_even, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegin, this); // callback 2 - touch
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
    auto bg = Sprite::create("sprites/table.png");
    if (bg == nullptr) {
        exit(-1);
    }
    else {
        bg->setPosition(Vec2(240, 160));
    }
    this->addChild(bg);
    deck.shuffle();
    setHand();

    return true;
}

void HelloWorld::setUserTarget(bool tg) { // true = odd, false = even
    player.setTarget(tg);
    if (player.getTarget()) {
        dealer.setTarget(false);
    }
    else {
        dealer.setTarget(true);
    }
}

void HelloWorld::setHand() {
    int adder = 0;
    std::string temp = "sprites/back.png";
    for (int i = 0; i < 5; i++) {
        Card cd = deck.draw();
        cardInfos.push_back(cd);

        auto sprite = Sprite::create(temp);
        if (sprite == nullptr) {
            exit(-1);
        }
        else {
            sprite->setPosition(Vec2(80 + adder, 160));
            sprite->setTag(i);
        }
        this->addChild(sprite);
        adder += 80;
        cardSprites.push_back(sprite);
    }
}

void HelloWorld::removeC(int idx) {
    srand(static_cast<unsigned short>(time(NULL)));
    Vec2 tempLoc = Vec2(cardSprites[idx]->getPosition().x, cardSprites[idx]->getPosition().y);
    this->removeChild(cardSprites[idx], true);
    cocos2d::Sprite* temp = cardSprites[idx];
    cardSprites[idx] = cardSprites[cardSprites.size() - 1];
    cardSprites.pop_back();

    Card cdTemp = cardInfos[idx];
    cardInfos[idx] = cardInfos[cardInfos.size() - 1];
    cardInfos.pop_back();

    int adderX = 0;
    for (int i = idx; i < cardSprites.size(); i++) {
        cardSprites[i]->setPosition(tempLoc.x + adderX, tempLoc.y);
        adderX += 80;
    }
    player.cardChosen();
    // player
    
    int dealer_selected_idx = rand() % cardSprites.size();

    tempLoc = Vec2(cardSprites[dealer_selected_idx]->getPosition().x, cardSprites[dealer_selected_idx]->getPosition().y);
    this->removeChild(cardSprites[dealer_selected_idx], true);
    cocos2d::Sprite* _temp = cardSprites[dealer_selected_idx];
    cardSprites[dealer_selected_idx] = cardSprites[cardSprites.size() - 1];
    cardSprites.pop_back();

    cdTemp = cardInfos[dealer_selected_idx];
    cardInfos[dealer_selected_idx] = cardInfos[cardInfos.size() - 1];
    cardInfos.pop_back();

    adderX = 0;
    for (int i = dealer_selected_idx; i < cardSprites.size(); i++) {
        cardSprites[i]->setPosition(tempLoc.x + adderX, tempLoc.y);
        adderX += 80;
    }
    dealer.cardChosen();
    // dealer
    ready = true;
}

bool HelloWorld::onTouchBegin(Touch* touch, Event* event) {
    Point location = touch->getLocation();

    if (!player.isSelected()) {
        for (int i = 0; i < cardSprites.size(); i++) {
            if (cardSprites[i]->getBoundingBox().containsPoint(location)) {
                removeC(i);
                break;
            }
        }
    }
    else {
        CCLOG("Selected already");
    }
    return true;

}

void HelloWorld::showResult() {
    int sum = 0;
    bool rst;
    
    for (int i = 0; i < cardInfos.size(); i++) {
        setRevealingCardSprite(i);
        if (cardInfos[i].getRank() <= 10) {
            sum += cardInfos[i].getRank();
        }
    }
    rst = sum % 2 == 1 ? true : false;
    
    if (player.getTarget() == rst) {
        CCLOG("Player win!");
    }
    else {
        CCLOG("Dealer win!");
    }
}


// true stands odd, false stands even
void HelloWorld::oddSelected(cocos2d::Ref* pSender) { 
    if (ready) {
        this->setUserTarget(true);
        this->showResult();
        CCLOG("Worked");
    }
    else {
        CCLOG("Not worked");
    }
}

void HelloWorld::evenSelected(cocos2d::Ref* pSender) {
    if (ready) {
        this->setUserTarget(false);
        this->showResult();
        CCLOG("Worked");
    }
    else {
        CCLOG("Not worked");
    }
}

const char* HelloWorld::_getShape(const Card& cd) {
    char* temp = nullptr;
    switch (cd.getShape()) {
    case 's':
        temp = new char[sizeof(char) * strlen("spade") + 1];
        strcpy_s(temp, sizeof(char) * strlen("spade") + 1, "spade");
        temp[sizeof(char) * strlen("spade")] = '\0';
        break;
    case 'c':
        temp = new char[sizeof(char) * strlen("clover") + 1];
        strcpy_s(temp, sizeof(char) * strlen("clover") + 1, "clover");
        temp[sizeof(char) * strlen("clover")] = '\0';
        break;
    case 'h':
        temp = new char[sizeof(char) * strlen("heart") + 1];
        strcpy_s(temp, sizeof(char) * strlen("heart") + 1, "heart");
        temp[sizeof(char) * strlen("heart")] = '\0';
        break;
    case 'd':
        temp = new char[sizeof(char) * strlen("diamond") + 1];
        strcpy_s(temp, sizeof(char) * strlen("diamond") + 1, "diamond");
        temp[sizeof(char) * strlen("diamond")] = '\0';
        break;
    case 'j':
        temp = new char[sizeof(char) * strlen("joker") + 1];
        strcpy_s(temp, sizeof(char) * strlen("joker") + 1, "joker");
        temp[sizeof(char) * strlen("joker")] = '\0';
    }
    return temp;
}

const char* HelloWorld::_getRank(const Card& cd) {
    int size;
    char tempBuf[BUF_LEN];
    memset(tempBuf, 0, BUF_LEN);
    if (cd.getShape() != 'j') {
        strcpy_s(tempBuf, BUF_LEN, "_");
        switch (cd.getRank()) {
        case 1:
            strcat_s(tempBuf, BUF_LEN, "1");
            break;
        case 2:
            strcat_s(tempBuf, BUF_LEN, "2");
            break;
        case 3:
            strcat_s(tempBuf, BUF_LEN, "3");
            break;
        case 4:
            strcat_s(tempBuf, BUF_LEN, "4");
            break;
        case 5:
            strcat_s(tempBuf, BUF_LEN, "5");
            break;
        case 6:
            strcat_s(tempBuf, BUF_LEN, "6");
            break;
        case 7:
            strcat_s(tempBuf, BUF_LEN, "7");
            break;
        case 8:
            strcat_s(tempBuf, BUF_LEN, "8");
            break;
        case 9:
            strcat_s(tempBuf, BUF_LEN, "9");
            break;
        case 10:
            strcat_s(tempBuf, BUF_LEN, "10");
            break;
        case 11:
            strcat_s(tempBuf, BUF_LEN, "11");
            break;
        case 12:
            strcat_s(tempBuf, BUF_LEN, "12");
            break;
        case 13:
            strcat_s(tempBuf, BUF_LEN, "13");
            break;
        }
        strcat_s(tempBuf, BUF_LEN, ".png");
        tempBuf[strlen(tempBuf) + 1] = '\0';
        return tempBuf;
    }
    else {
        // joker
        CCLOG("joker selected");
        return nullptr;
    }
}

void HelloWorld::setRevealingCardSprite(int idx) {
    memset(itemAdrBuf, 0, BUF_LEN);
    strcpy_s(itemAdrBuf, BUF_LEN, "sprites/");
    if (cardInfos[idx].getShape() != 'j') {
        strcat_s(itemAdrBuf, BUF_LEN, _getShape(cardInfos[idx]));
        strcat_s(itemAdrBuf, BUF_LEN, "/");
        strcat_s(itemAdrBuf, BUF_LEN, _getShape(cardInfos[idx]));
        strcat_s(itemAdrBuf, BUF_LEN, _getRank(cardInfos[idx]));
        itemAdrBuf[strlen(itemAdrBuf) + 1] = '\0';
    }
    else {
        CCLOG("joker selected");
        // joker
    }
    cardSprites[idx]->setTexture(itemAdrBuf);
}