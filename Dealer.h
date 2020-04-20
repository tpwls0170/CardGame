#pragma once
class Card;
class Player;
class GamePan;

#define Shufflepos1 80
#define Shufflepos2 20
#define GiveCardpos 60

struct RectangleShape {
	int left;
	int top;
	int right;
	int bottom;
};

class Dealer
{
private:
	Card* card;
	Player* player;
	GamePan* gamepan;

	int MaxHumans;
	int UserPlayer;
	int PosX{ 0 };
	int CardDeckNum{ 0 };
	int PeopleGameMoney{ 0 };

	bool GameFinsh{ false };
public:
	void Init();
	void Shuffle();
	void FirstTurn();
	void GiveCard();
	void CardDeckNumber();
	void GameStadium();

	void ShuffleDraw();
	void GiveCardDraw();
	void DrawData(RectangleShape& rectangle, int select);

	bool getGameFinsh();
	void Release();
};

