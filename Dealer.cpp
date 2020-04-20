#include "Dealer.h"
#include "Card.h"
#include "Player.h"
#include "GamePan.h"
#include "Library.h"
#include <Windows.h>
HDC hdc = GetWindowDC(GetForegroundWindow());

void Dealer::Init()
{
	card = new Card[52];
	gamepan = new GamePan;
	gamepan->Init();
	int StartMoney{ 0 };
	string PlayerName{ NULL };
	cout << "월남뽕을 시작합니다 인원수를 선택해주세요" << endl;
	cin >> MaxHumans;
	cout << "시작 게임머니를 설정해주세요" << endl;
	cin >> StartMoney;
	player = new Player[MaxHumans];
	for (int i = 0; i < MaxHumans; ++i) {
		player[i].SetMoney(StartMoney);
	}
	cout << "사용자의 월남뽕 선수를 선택해주세요 (1 ~ " << MaxHumans << " 까지)" << endl;
	cin >> UserPlayer;
	cout << "이름 설정 : ";
	cin >> PlayerName;
	UserPlayer -= 1;
	player[UserPlayer].setName(PlayerName);
}

void Dealer::Shuffle()
{
	int AddressNumber{ 0 };
	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j <= 13; ++j) {
			if (i == 0) {
				card[AddressNumber].setCardInfoShape("♠");
			}
			else if (i == 1) {
				card[AddressNumber].setCardInfoShape("◆");
			}
			else if (i == 2) {
				card[AddressNumber].setCardInfoShape("♣");
			}
			else { card[AddressNumber].setCardInfoShape("♥"); }
			card[AddressNumber].setCardInfoNumber(j);
			++AddressNumber;
		}
	}

	string tempshape{ NULL };
	int tempnumber{ 0 };
	int temp{ 0 }, temp1{ 0 };
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; ++i) {
		temp = rand() % 51;
		tempnumber = card[temp].getCardInfo().Number;
		tempshape = card[temp].getCardInfo().Shape;
		temp1 = rand() % 51;
		card[temp].setCardInfoNumber(card[temp1].getCardInfo().Number);
		card[temp].setCardInfoShape(card[temp1].getCardInfo().Shape);
	}
}

void Dealer::FirstTurn()
{
	system("cls");
	int RandomDice[6] = { 1,2,3,4,5,6 };
	int pos{ 0 }, end{ 0 };
	srand((unsigned int)time(NULL));
	cout << "선턴잡기 게임(주사위)을 시작합니다" << endl;
	for (int i = 0; i < 6; ++i) {
		pos = rand() % 5;
		if (RandomDice[pos] != 0 && player[i].getDice() == 0) {
			player[i].SetDice(RandomDice[pos]);
			RandomDice[pos] = 0;
		}
	}

	for (int i = 0; i < MaxHumans; ++i) {
		for (int j = 0; j < 6; ++j) {
			if (player[i].getDice() == 0 && RandomDice[j] != 0)
			{
				player[i].SetDice(RandomDice[j]);
				RandomDice[j] = 0;
			}
		}
	}

	for (int i = 0; i < MaxHumans; ++i) {
		if (i == UserPlayer) {
			cout << "player " << player[i].getName() << " 님의 주사위 수는 " <<
				player[i].getDice() << "입니다." << endl;
			continue;
		}
		cout << "player " << i + 1 << " 님의 주사위 수는 " <<
			player[i].getDice() << "입니다." << endl;
	}
	int FirstTurn{ 0 };
	for (int i = 0; i < MaxHumans; ++i) {
		if (FirstTurn < player[i].getDice()) {
			FirstTurn = player[i].getDice();
		}
	}
	int firstnumber{ 0 };
	for (int i = 0; i < MaxHumans; ++i) {
		if (i == UserPlayer && FirstTurn == player[i].getDice()) {
			cout << "========================================================" << endl;
			cout << "Player " << player[i].getName() << "님의 주사위 숫자가 가장크므로 선턴입니다." << endl;
			player[i].setMyturn(1);
			firstnumber = i;
			break;
		}
		if (FirstTurn == player[i].getDice()) {
			cout << "========================================================" << endl;
			cout << "Player " << i + 1 << "님의 주사위 숫자가 가장크므로 선턴입니다." << endl;
			player[i].setMyturn(1);
			firstnumber = i;
			break;
		}
	}
	int sequence{ 2 };
	for (int i = 0; i < MaxHumans; ++i) {
		if (i == firstnumber) { continue; }
		else {
			player[i].setMyturn(sequence);
			++sequence;
		}
	}
	Sleep(5000);
}

void Dealer::GiveCard()
{
	for (int i= 0; i < MaxHumans; ++i) {
		for (int j = 0; j < 2; ++j) {
			player[i].setCardInfoShape(card[PosX].getCardInfo().Shape, j);
			player[i].setCardInfoNumber(card[PosX].getCardInfo().Number, j);
			card[PosX].setCardInfoNumber(0);
			++PosX;
		}
	}
	//출력 테스트
/*	int tese{ 0 };
	for (int i = 0; i < MaxHumans; ++i) {
		cout << player[i].getCardInfo1().Shape << " " <<
				player[i].getCardInfo1().Number << "\t";
		cout << player[i].getCardInfo2().Shape << " " <<
				player[i].getCardInfo2().Number;
		++tese;
		if (tese == 2) {
			cout << endl;
			tese = 0;
		}
 	}
	cout << endl << "------------------------------------" << endl;
	tese = 0;
	for (int i = 0; i < 52; ++i) {
		cout << card[i].getCardInfo().Shape << " " <<
			card[i].getCardInfo().Number << "\t";
		++tese;
		if (tese == 13) {
			cout << endl;
			tese = 0;
		}
	}*/
}

void Dealer::GameStadium()
{
	int battingMoney{ 0 };
	int firstbattingMoney{ 0 };
	bool FirstPlayer{ false };
	for (int i = 0; i < MaxHumans; ++i) {
		if (player[i].getMoney() < 0)
		{
			GameFinsh = true;
		}
	}
	if (GameFinsh == true) {
		cout << "보유금액을 모두 소진하였습니다." << endl;
		return;
	}
	else
	{
		CardDeckNumber();
		cout << "현재 남아있는 카드 수 : " << CardDeckNum << endl;
		cout << "게임 참가 금액설정 " << endl;
		cin >> firstbattingMoney;

		for (int i = 0; i < MaxHumans; ++i) {
			PeopleGameMoney += firstbattingMoney;
			player[i].SetMoney(player[i].getMoney() - firstbattingMoney);
		}
		for (int i = 0; i < MaxHumans; ++i) {
			if (UserPlayer == i) {
				cout << "Player " << player[i].getName() << "님의 현재 배팅금액 : " <<
					player[i].getMoney() << "입니다." << endl;
				continue;
			}
			cout << "Player " << i + 1 << "님의 현재 배팅금액 : " <<
				player[i].getMoney() << "입니다." << endl;
		}

		//선턴 플레이
		for (int i = 0; i < MaxHumans; ++i) {
			if (FirstPlayer == false && player[i].getMyturn() == 1 &&
				i == UserPlayer)
			{
				cout << "Player " << player[i].getName() << "님의 차례입니다." << endl;
				gamepan->PlayerTurn(player, card, i, PeopleGameMoney, PosX,MaxHumans,UserPlayer);
				FirstPlayer = true;
			}
			else if (FirstPlayer == false && player[i].getMyturn() == 1)
			{
				cout << "Player " << i + 1 << "님의 차례입니다." << endl;
				gamepan->AITurn(player, card, i, PeopleGameMoney, PosX, CardDeckNum);
				FirstPlayer = true;
			}
		}

		for (int i = 0; i < MaxHumans; ++i) {
			if (FirstPlayer == true && player[i].getMyturn() != 1 &&
				i == UserPlayer)
			{
				cout << "Player " << player[i].getName() << "님의 차례입니다." << endl;
				gamepan->PlayerTurn(player, card, i, PeopleGameMoney, PosX, MaxHumans, UserPlayer);
			}
			else if (FirstPlayer == true && player[i].getMyturn() != 1)
			{
				cout << "Player " << i + 1 << "님의 차례입니다." << endl;
				gamepan->AITurn(player, card, i, PeopleGameMoney, PosX, CardDeckNum);
			}
		}
	}
}

void Dealer::CardDeckNumber()
{
	CardDeckNum = 0;
	for (int i = 0; i < 52; ++i) {
		if (card[i].getCardInfo().Number != 0){
			++CardDeckNum;
		}
	}
}

void Dealer::ShuffleDraw()
{
	system("cls");
	RectangleShape rectangle[15];
	for (int i = 0; i < 15; ++i) {
		rectangle[i].left = 400; rectangle[i].top = 150; rectangle[i].right = 510; rectangle[i].bottom = 350;
		DrawData(rectangle[i],1);
		Rectangle(hdc, rectangle[i].left, rectangle[i].top, rectangle[i].right, rectangle[i].bottom);
		Sleep(800);
	}
}

void Dealer::GiveCardDraw()
{
	RectangleShape rectangle[4] = {
		{200,150,310,350},
		{350,150,460,350},
		{500,150,610,350},
		{650,150,760,350}, };

	for (int i = 0; i < 5; ++i) {
		cout << endl << endl << endl;
		cout << "\t" << "\t" << "\t패돌리는중...." << endl;
		DrawData(rectangle[0],2);
		Rectangle(hdc, rectangle[0].left, rectangle[0].top, rectangle[0].right, rectangle[0].bottom);
		Rectangle(hdc, rectangle[1].left, rectangle[1].top, rectangle[1].right, rectangle[1].bottom);
		Rectangle(hdc, rectangle[2].left, rectangle[2].top, rectangle[2].right, rectangle[2].bottom);
		Rectangle(hdc, rectangle[3].left, rectangle[3].top, rectangle[3].right, rectangle[3].bottom);
		Sleep(300);
		system("cls");
	}

	for (int i = 0; i < 5; ++i) {
		cout << endl << endl << endl;
		cout << "\t" << "\t" << "\t패돌리는중...." << endl;
		DrawData(rectangle[1], 2);
		Rectangle(hdc, rectangle[1].left, rectangle[1].top, rectangle[1].right, rectangle[1].bottom);
		Rectangle(hdc, rectangle[2].left, rectangle[2].top, rectangle[2].right, rectangle[2].bottom);
		Rectangle(hdc, rectangle[3].left, rectangle[3].top, rectangle[3].right, rectangle[3].bottom);
		Sleep(300);
		system("cls");
	}
	for (int i = 0; i < 5; ++i) {
		cout << endl << endl << endl;
		cout << "\t" << "\t" << "\t패돌리는중...." << endl;
		DrawData(rectangle[2], 2);
		Rectangle(hdc, rectangle[2].left, rectangle[2].top, rectangle[2].right, rectangle[2].bottom);
		Rectangle(hdc, rectangle[3].left, rectangle[3].top, rectangle[3].right, rectangle[3].bottom);
		Sleep(300);
		system("cls");
	}
	for (int i = 0; i < 5; ++i) {
		cout << endl << endl << endl;
		cout << "\t" << "\t" << "\t패돌리는중...." << endl;
		DrawData(rectangle[3], 2);
		Rectangle(hdc, rectangle[3].left, rectangle[3].top, rectangle[3].right, rectangle[3].bottom);
		Sleep(300);
		system("cls");
	}
}

void Dealer::DrawData(RectangleShape& rectangle, int select)
{
	if(select == 1) {
		srand((unsigned int)time(NULL));
		int randompos = rand() % 7;
		if (randompos == 0) {
			rectangle.top += Shufflepos2;
			rectangle.bottom += Shufflepos2;
		}
		else if (randompos == 1) {
			rectangle.top -= Shufflepos1;
			rectangle.bottom -= Shufflepos1;
		}
		else if (randompos == 2) {
			rectangle.left -= Shufflepos2;
			rectangle.right -= Shufflepos2;
		}
		else if (randompos == 3) {
			rectangle.left += Shufflepos1;
			rectangle.right += Shufflepos1;
		}
		else if (randompos == 4) {
			rectangle.top -= Shufflepos1;
			rectangle.bottom -= Shufflepos1;
			rectangle.left -= Shufflepos2;
			rectangle.right -= Shufflepos2;
		}
		else if (randompos == 5) {
			rectangle.top += Shufflepos2;
			rectangle.bottom += Shufflepos2;
			rectangle.left += Shufflepos1;
			rectangle.right += Shufflepos1;
		}
		else if (randompos == 6) {
			rectangle.top -= Shufflepos1;
			rectangle.bottom -= Shufflepos1;
			rectangle.left += Shufflepos2;
			rectangle.right += Shufflepos2;
		}
		else if (randompos == 7) {
			rectangle.top += Shufflepos2;
			rectangle.bottom += Shufflepos2;
			rectangle.left -= Shufflepos2;
			rectangle.right -= Shufflepos2;

		}
	}
	else if (select == 2) {
		rectangle.top += GiveCardpos;
		rectangle.bottom += GiveCardpos;
	}
}

bool Dealer::getGameFinsh()
{
	return GameFinsh;
}

void Dealer::Release()
{
	delete[] card;
	delete[] player;

	gamepan->Release();
	delete	 gamepan;
}