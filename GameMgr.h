#pragma once
class Dealer;
class GameMgr
{
private:
	Dealer* dealer;
public:
	void Initialization();
	void Updata();
	void Release();
};

