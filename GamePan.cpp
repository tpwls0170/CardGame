#include "GamePan.h"
#include "Player.h"
#include "Card.h"
#include "Account.h"

void GamePan::Init()
{
	account = new Account;
}

void GamePan::PlayerTurn(Player* (&player), Card* (&card),
	int myturn, int& peoplegamemoney, int& cardposx,
	int maxhumans, int userplayer)
{
	int SelectNum{ 0 };
	int battingMoney{ 0 };
	if (peoplegamemoney <= 0) {
		cout << "판돈이 없으므로 패스합니다." << endl;
		return;
	}
	else
	{
		cout << "1. 배팅 2.패 확인하기 3.다이 " << endl;
		cin >> SelectNum;
		if (SelectNum == 1) {
			while (1) {
				cout << "얼마를 배팅하시겠습니까? ";
				cin >> battingMoney;
				if (player[myturn].getMoney() < battingMoney) {
					cout << "배팅액 부족 ㅜ.ㅜ" << endl;
					cout << "현재보유 금액 : " << player[myturn].getMoney() << endl;
					continue;
				}
				else if (battingMoney > peoplegamemoney) {
					cout << "판돈보다 많은돈은 배팅 할 수없습니다." << endl;
					continue;
				}
				else {
					cout << battingMoney << "배팅하셨습니다." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					cout << "현재보유 금액 : " << player[myturn].getMoney() << endl;
					break;
				}
			}

			Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
			card[cardposx].setCardInfoNumber(0);
			++cardposx;
		}
		else if (SelectNum == 2) {
			if (player[myturn].getCardInfo1().Number > player[myturn].getCardInfo2().Number) {
				cout << player[myturn].getCardInfo2().Shape << " " << player[myturn].getCardInfo2().Number <<
					"\t" << player[myturn].getCardInfo1().Shape << " " << player[myturn].getCardInfo1().Number << endl;
			}
			else {
				cout << player[myturn].getCardInfo1().Shape << " " << player[myturn].getCardInfo1().Number <<
					"\t" << player[myturn].getCardInfo2().Shape << " " << player[myturn].getCardInfo2().Number << endl;
			}
			PlayerTurn(player, card, myturn, peoplegamemoney, cardposx,maxhumans,userplayer);
		}
		else if (SelectNum == 3) {
			cout << player[myturn].getName() << "다이를 선택했습니다." << endl;
			cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
			cout << "1. 돈 빌리기 2. 턴 넘기기" << endl;
			int mort{ 0 };
			cin >> mort;
			if (mort == 1) {
			cout << "1.돈 빌리기 2. 상환" << endl;
			int select{ 0 };
			cin >> select;
			if (select == 1) {
				account->Choice(player, maxhumans, userplayer, OutPut);
			}
			else if (select == 2) {
				int repay{ 0 };
				cout << "얼마를 상환할건가요?" << endl;
				cin >> repay;
				player[userplayer].setLandMoney(player[userplayer].getLandMoney() - repay);
				player[player[userplayer].getLandNum()].SetMoney(player[player[userplayer].getLandNum()].getMoney() + repay);
				cout << "player " << player[userplayer].getName() << " 님은 player" <<
					player[userplayer].getLandNum() + 1 << "님에게 " << repay << "를 상환" << endl <<
					"남은 금액 : " << player[userplayer].getLandMoney() << "입니다." << endl;
				OutPut.open("빚상환 장부.txt");
				OutPut << "player " << player[userplayer].getName() << " 님은 player" <<
					player[userplayer].getLandNum() + 1 << "님에게 " << repay << "를 상환" << endl <<
					"남은 금액 : " << player[userplayer].getLandMoney() << "입니다." << endl;
				OutPut.close();
				}
			}
		}
	}
}

void GamePan::AITurn(Player* (&player), Card* (&card), int myturn, 
	int& peoplegamemoney, int& cardposx, int carddecknum)
{
	int difference{ 0 };
	int battingMoney{ 0 };
	if (peoplegamemoney <= 0) {
		cout << "판돈이 없으므로 패스합니다." << endl;
		return;
	}
	else {
		if (player[myturn].getCardInfo1().Number < player[myturn].getCardInfo2().Number) {
			difference = player[myturn].getCardInfo2().Number - player[myturn].getCardInfo1().Number;
		}
		else {
			difference = player[myturn].getCardInfo1().Number - player[myturn].getCardInfo2().Number;
		}

		float battingprobability;	//배팅선택

		battingprobability = (float)difference / carddecknum;
		//카드가 줄어들수록 확률 증가
		if (battingprobability >= 22.f) {
			//allin 10 11
			if (player[myturn].getMoney() >= peoplegamemoney) {
				cout << "Player" << myturn + 1 << " 님이" << peoplegamemoney << "원을 배팅하셨습니다." << endl;
				battingMoney = peoplegamemoney;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				cout << "Player" << myturn + 1 << " 님이" << player[myturn].getMoney() << "원을 배팅하셨습니다." << endl;
				battingMoney = player[myturn].getMoney();
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
		}
		else if (battingprobability >= 18.f && battingprobability < 22.f) {
			//80pre 8 9
			if (player[myturn].getMoney() >= peoplegamemoney) {
				battingMoney = peoplegamemoney * 0.8f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.8f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
		}
		else if (battingprobability >= 13.f && battingprobability < 18.f) {
			//50pre 6 7
			if (player[myturn].getMoney() >= peoplegamemoney) {
				battingMoney = peoplegamemoney * 0.5f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.5f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
		}
		else if (battingprobability >= 11.f && battingprobability < 13.f) {
			//30pre 5
			if (player[myturn].getMoney() >= peoplegamemoney) {
				battingMoney = peoplegamemoney * 0.3f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.3f;
				cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
		}
		else if (battingprobability >= 6.f && battingprobability < 11.f) {
			//도박 4 3
			srand((unsigned int)time(NULL));
			if (rand() % 20 == 10) {
				if (player[myturn].getMoney() >= peoplegamemoney) {
					battingMoney = peoplegamemoney * 0.2f;
					cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
				else if (player[myturn].getMoney() < peoplegamemoney) {
					battingMoney = player[myturn].getMoney() * 0.2f;
					cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
			}
			else {
				cout << "Player" << myturn + 1 << "님이 다이를 선언했습니다." << endl;
				cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
				KeyDownEvent();
				system("cls");
			}
		}
		else if (battingprobability >= 0.f && battingprobability < 6.f) {
			//도박 1 2
			srand((unsigned int)time(NULL));
			if (rand() % 50 == 10) {
				if (player[myturn].getMoney() >= peoplegamemoney) {
					battingMoney = peoplegamemoney * 0.1f;
					cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;

					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
				else if (player[myturn].getMoney() < peoplegamemoney) {
					battingMoney = player[myturn].getMoney() * 0.1f;
					cout << "Player" << myturn + 1 << " 님이" << battingMoney << "원을 배팅하셨습니다." << endl;
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
			}
			else {
				cout << "Player" << myturn + 1 << "님이 다이를 선언했습니다." << endl;
				cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
				KeyDownEvent();
				system("cls");
			}
		}
	}
}

void GamePan::Comparison(Player* (&player), Card* (&card), int& peoplegamemoney, 
	int battingMoney, int myturn, int cardposx) 
{
	cout << "카드 한장을 건네 받습니다." << endl;
	cout << card[cardposx].getCardInfo().Shape << card[cardposx].getCardInfo().Number << endl;

	if (player[myturn].getCardInfo1().Number > player[myturn].getCardInfo2().Number) {
		cout << player[myturn].getCardInfo2().Shape << " " << player[myturn].getCardInfo2().Number <<
			"\t" << player[myturn].getCardInfo1().Shape << " " << player[myturn].getCardInfo1().Number << endl;
	}
	else {
		cout << player[myturn].getCardInfo1().Shape << " " << player[myturn].getCardInfo1().Number <<
			"\t" << player[myturn].getCardInfo2().Shape << " " << player[myturn].getCardInfo2().Number << endl;
	}
	if (player[myturn].getCardInfo1().Number != card[cardposx].getCardInfo().Number && player[myturn].getCardInfo2().Number != card[cardposx].getCardInfo().Number &&
		player[myturn].getCardInfo1().Number != 13 && player[myturn].getCardInfo2().Number != 13 &&
		player[myturn].getCardInfo1().Number < card[cardposx].getCardInfo().Number && player[myturn].getCardInfo2().Number > card[cardposx].getCardInfo().Number ||
		player[myturn].getCardInfo1().Number > card[cardposx].getCardInfo().Number && player[myturn].getCardInfo2().Number < card[cardposx].getCardInfo().Number) {
		cout << "배팅성공!!!!" << endl;
		if (peoplegamemoney > battingMoney && peoplegamemoney != 0) {
			peoplegamemoney -= battingMoney;
			player[myturn].SetMoney(player[myturn].getMoney() + (battingMoney * 2));
			cout << "획득한 금액 : " << battingMoney * 2 << endl;
			cout << "현재보유 금액 : " << player[myturn].getMoney() << endl;
			cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
			KeyDownEvent();
			system("cls");
		}
		else if (peoplegamemoney > battingMoney && peoplegamemoney <= 0) {
			player[myturn].SetMoney(player[myturn].getMoney() + peoplegamemoney);
			peoplegamemoney = 0;
			cout << "획득한 금액 : " << peoplegamemoney * 2 << endl;
			cout << "현재보유 금액 : " << player[myturn].getMoney() << endl;
			cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
			KeyDownEvent();
			system("cls");
		}
	}
	else if (player[myturn].getCardInfo1().Number == 13 || player[myturn].getCardInfo2().Number == 13) {
		cout << "본인 패에 13이 포함되어 자동으로 다이를 선택합니다." << endl;
		peoplegamemoney += battingMoney;
		KeyDownEvent();
		system("cls");
	}
	else {
		cout << "배팅 실패!! 배팅금액이 날아갔습니다" << endl;
		peoplegamemoney += battingMoney;
		cout << "잃은 금액 : " << battingMoney << endl;
		cout << "현재보유 금액 : " << player[myturn].getMoney() << endl;
		cout << "현재 남아있는 판돈 금액 : " << peoplegamemoney << endl;
		KeyDownEvent();
		system("cls");
	}
}

void GamePan::KeyDownEvent()
{
	cout << "아무키나 입력하세요(SKIP)" << endl;
	_getch();
}

void GamePan::Release()
{
	delete account;
}
