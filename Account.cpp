#include "Account.h"
#include "Player.h"

void Account::Choice(Player* (&player), int MaxHumans, int userplayer, ofstream& output)
{
	int select{ 0 };
	cout << "� �÷��̾�� ���� �����ڽ��ϱ�?" << endl;
	for (int i = 0; i < MaxHumans; ++i) {
		if (i == userplayer) {
			continue;
		}
		else {
			cout << i + 1 << ". player " << i + 1 << "���� �����ݾ� : " << player[i].getMoney() << endl;
		}
	}
	cin >> select;
	player[userplayer].setLandNum(select);
	for (int i = 0; i < MaxHumans; ++i) {
		if (i == select) {
			int selectnum{ 0 };
			
			cout << "�󸶸� �����ðڽ��ϱ�?" << endl <<
				"1. 50% 2.30% 3. 10% "<< endl;
			cin >> selectnum;
			if (selectnum == 1) {
				MoneyLend(player, select, userplayer, 1,output);
			}
			else if (selectnum == 2) {
				MoneyLend(player, select, userplayer, 2,output);
			}
			else
			{
				MoneyLend(player, select, userplayer, 3, output);
			}
		}
		else {
			continue;
		}
	}
}

void Account::MoneyLend(Player* (&player), int select, int userplayer, int moneyselect, ofstream& output)
{
	int momeysize{ 0 };
	if (moneyselect == 1) {
		momeysize = player[select].getMoney() * 0.5f;
		player[userplayer].setLandMoney(momeysize);
		player[select].SetMoney(player[select].getMoney() - momeysize);
		output.open("�������.txt");
		output << "player " << player[userplayer].getName() << " ���� player " << select + 1 <<
			" �Կ��� " << momeysize << " ���� ������Ƚ��ϴ�." << endl;
		output.close();
	}
	else if (moneyselect == 2) {
		momeysize = player[select].getMoney() * 0.3f;
		player[userplayer].setLandMoney(momeysize);
		player[select].SetMoney(player[select].getMoney() - momeysize);
		output.open("�������.txt");
		output << "player " << player[userplayer].getName() << " ���� player " << select + 1 <<
			" �Կ��� " << momeysize << " ���� ������Ƚ��ϴ�." << endl;
		output.close();
	}
	else {
		momeysize = player[select].getMoney() * 0.1f;
		player[userplayer].setLandMoney(momeysize);
		player[select].SetMoney(player[select].getMoney() - momeysize);
		output.open("�������.txt");
		output << "player " << player[userplayer].getName() << " ���� player " << select + 1 <<
			" �Կ��� " << momeysize << " ���� ������Ƚ��ϴ�." << endl;
		output.close();
	}
	
}
