#include "GameMgr.h"
#include "Dealer.h"

void GameMgr::Initialization()
{
	dealer = new Dealer;
	dealer->Init();
}

void GameMgr::Updata()
{
	while (1) {
		dealer->Shuffle();
		dealer->ShuffleDraw();
		dealer->FirstTurn();
		dealer->GiveCard();
		dealer->GiveCardDraw();
		dealer->GameStadium();
		if (dealer->getGameFinsh() == true) {
			break;
		}
	}
}

void GameMgr::Release()
{
	dealer->Release();
}
