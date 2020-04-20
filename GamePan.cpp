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
		cout << "�ǵ��� �����Ƿ� �н��մϴ�." << endl;
		return;
	}
	else
	{
		cout << "1. ���� 2.�� Ȯ���ϱ� 3.���� " << endl;
		cin >> SelectNum;
		if (SelectNum == 1) {
			while (1) {
				cout << "�󸶸� �����Ͻðڽ��ϱ�? ";
				cin >> battingMoney;
				if (player[myturn].getMoney() < battingMoney) {
					cout << "���þ� ���� ��.��" << endl;
					cout << "���纸�� �ݾ� : " << player[myturn].getMoney() << endl;
					continue;
				}
				else if (battingMoney > peoplegamemoney) {
					cout << "�ǵ����� �������� ���� �� �������ϴ�." << endl;
					continue;
				}
				else {
					cout << battingMoney << "�����ϼ̽��ϴ�." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					cout << "���纸�� �ݾ� : " << player[myturn].getMoney() << endl;
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
			cout << player[myturn].getName() << "���̸� �����߽��ϴ�." << endl;
			cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
			cout << "1. �� ������ 2. �� �ѱ��" << endl;
			int mort{ 0 };
			cin >> mort;
			if (mort == 1) {
			cout << "1.�� ������ 2. ��ȯ" << endl;
			int select{ 0 };
			cin >> select;
			if (select == 1) {
				account->Choice(player, maxhumans, userplayer, OutPut);
			}
			else if (select == 2) {
				int repay{ 0 };
				cout << "�󸶸� ��ȯ�Ұǰ���?" << endl;
				cin >> repay;
				player[userplayer].setLandMoney(player[userplayer].getLandMoney() - repay);
				player[player[userplayer].getLandNum()].SetMoney(player[player[userplayer].getLandNum()].getMoney() + repay);
				cout << "player " << player[userplayer].getName() << " ���� player" <<
					player[userplayer].getLandNum() + 1 << "�Կ��� " << repay << "�� ��ȯ" << endl <<
					"���� �ݾ� : " << player[userplayer].getLandMoney() << "�Դϴ�." << endl;
				OutPut.open("����ȯ ���.txt");
				OutPut << "player " << player[userplayer].getName() << " ���� player" <<
					player[userplayer].getLandNum() + 1 << "�Կ��� " << repay << "�� ��ȯ" << endl <<
					"���� �ݾ� : " << player[userplayer].getLandMoney() << "�Դϴ�." << endl;
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
		cout << "�ǵ��� �����Ƿ� �н��մϴ�." << endl;
		return;
	}
	else {
		if (player[myturn].getCardInfo1().Number < player[myturn].getCardInfo2().Number) {
			difference = player[myturn].getCardInfo2().Number - player[myturn].getCardInfo1().Number;
		}
		else {
			difference = player[myturn].getCardInfo1().Number - player[myturn].getCardInfo2().Number;
		}

		float battingprobability;	//���ü���

		battingprobability = (float)difference / carddecknum;
		//ī�尡 �پ����� Ȯ�� ����
		if (battingprobability >= 22.f) {
			//allin 10 11
			if (player[myturn].getMoney() >= peoplegamemoney) {
				cout << "Player" << myturn + 1 << " ����" << peoplegamemoney << "���� �����ϼ̽��ϴ�." << endl;
				battingMoney = peoplegamemoney;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				cout << "Player" << myturn + 1 << " ����" << player[myturn].getMoney() << "���� �����ϼ̽��ϴ�." << endl;
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
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.8f;
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
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
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.5f;
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
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
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
			else if (player[myturn].getMoney() < peoplegamemoney) {
				battingMoney = player[myturn].getMoney() * 0.3f;
				cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
				player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
				Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
				card[cardposx].setCardInfoNumber(0);
				++cardposx;
			}
		}
		else if (battingprobability >= 6.f && battingprobability < 11.f) {
			//���� 4 3
			srand((unsigned int)time(NULL));
			if (rand() % 20 == 10) {
				if (player[myturn].getMoney() >= peoplegamemoney) {
					battingMoney = peoplegamemoney * 0.2f;
					cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
				else if (player[myturn].getMoney() < peoplegamemoney) {
					battingMoney = player[myturn].getMoney() * 0.2f;
					cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
					player[myturn].SetMoney(player[myturn].getMoney() - battingMoney);
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
			}
			else {
				cout << "Player" << myturn + 1 << "���� ���̸� �����߽��ϴ�." << endl;
				cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
				KeyDownEvent();
				system("cls");
			}
		}
		else if (battingprobability >= 0.f && battingprobability < 6.f) {
			//���� 1 2
			srand((unsigned int)time(NULL));
			if (rand() % 50 == 10) {
				if (player[myturn].getMoney() >= peoplegamemoney) {
					battingMoney = peoplegamemoney * 0.1f;
					cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;

					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
				else if (player[myturn].getMoney() < peoplegamemoney) {
					battingMoney = player[myturn].getMoney() * 0.1f;
					cout << "Player" << myturn + 1 << " ����" << battingMoney << "���� �����ϼ̽��ϴ�." << endl;
					Comparison(player, card, peoplegamemoney, battingMoney, myturn, cardposx);
					card[cardposx].setCardInfoNumber(0);
					++cardposx;
				}
			}
			else {
				cout << "Player" << myturn + 1 << "���� ���̸� �����߽��ϴ�." << endl;
				cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
				KeyDownEvent();
				system("cls");
			}
		}
	}
}

void GamePan::Comparison(Player* (&player), Card* (&card), int& peoplegamemoney, 
	int battingMoney, int myturn, int cardposx) 
{
	cout << "ī�� ������ �ǳ� �޽��ϴ�." << endl;
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
		cout << "���ü���!!!!" << endl;
		if (peoplegamemoney > battingMoney && peoplegamemoney != 0) {
			peoplegamemoney -= battingMoney;
			player[myturn].SetMoney(player[myturn].getMoney() + (battingMoney * 2));
			cout << "ȹ���� �ݾ� : " << battingMoney * 2 << endl;
			cout << "���纸�� �ݾ� : " << player[myturn].getMoney() << endl;
			cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
			KeyDownEvent();
			system("cls");
		}
		else if (peoplegamemoney > battingMoney && peoplegamemoney <= 0) {
			player[myturn].SetMoney(player[myturn].getMoney() + peoplegamemoney);
			peoplegamemoney = 0;
			cout << "ȹ���� �ݾ� : " << peoplegamemoney * 2 << endl;
			cout << "���纸�� �ݾ� : " << player[myturn].getMoney() << endl;
			cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
			KeyDownEvent();
			system("cls");
		}
	}
	else if (player[myturn].getCardInfo1().Number == 13 || player[myturn].getCardInfo2().Number == 13) {
		cout << "���� �п� 13�� ���ԵǾ� �ڵ����� ���̸� �����մϴ�." << endl;
		peoplegamemoney += battingMoney;
		KeyDownEvent();
		system("cls");
	}
	else {
		cout << "���� ����!! ���ñݾ��� ���ư����ϴ�" << endl;
		peoplegamemoney += battingMoney;
		cout << "���� �ݾ� : " << battingMoney << endl;
		cout << "���纸�� �ݾ� : " << player[myturn].getMoney() << endl;
		cout << "���� �����ִ� �ǵ� �ݾ� : " << peoplegamemoney << endl;
		KeyDownEvent();
		system("cls");
	}
}

void GamePan::KeyDownEvent()
{
	cout << "�ƹ�Ű�� �Է��ϼ���(SKIP)" << endl;
	_getch();
}

void GamePan::Release()
{
	delete account;
}
