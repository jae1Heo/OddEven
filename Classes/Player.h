#pragma once
#include <iostream>
class Player {
private:
	char target;
	__int64 balance;
	bool isTargetSelected;
	bool isCardSelected;
public:
	Player();
	Player(const __int64);

	void setTarget(const char);
	void setBalance(const __int64);
	void addBalance(const __int64);
	void withBalance(const __int64);
	void cardChosen();

	const char getTarget();
	const __int64 getBalance();
	const bool isSelected();

};