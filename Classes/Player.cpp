#include "Player.h"

Player::Player() : target(NULL), balance(0), isTargetSelected(false), isCardSelected(false){}

Player::Player(const __int64 balance) {
	this->balance = balance;
	this->target = NULL;
	this->isTargetSelected = false;
	this->isCardSelected = false;
}

void Player::setTarget(const char target) {
	this->target = target;
	this->isTargetSelected = true;
}

void Player::setBalance(const __int64 balancec) {
	this->balance = balance;
}

void Player::addBalance(const __int64 balance) {
	this->balance += balance;
}

void Player::withBalance(const __int64 balance) {
	this->balance -= balance;
}

const char Player::getTarget() {
	if (this->isTargetSelected) {
		return this->target;
	}
}

const __int64 Player::getBalance() {
	return this->balance;
}


void Player::cardChosen() {
	this->isCardSelected = true;
}
 
const bool Player::isSelected() {
	return this->isCardSelected;
}