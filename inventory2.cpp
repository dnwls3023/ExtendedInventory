#include <iostream>
#include <vector>
using namespace std;

/*
	 ***last update 2021-04-20***
	 인벤토리 위주로 구현
	 기능 1 : 인벤토리를 구현한다.
	 기능 2 : 인벤토리를 종류별로 나눈다.
	 기능 3 : 몬스터를 구현한 뒤, 이 몬스터를 잡았을 때 아이템을 드롭시키고 
	 아이템을 플레이어가 가져 인벤토리에 저장할 수 있도록 한다.
	 기능 4 : 아이템을 소모성으로 제작하여 소모할 수 있게 만든다. (ex 하급 포션 : 50의 hp를 회복한다.)

 */


class Item {
private:
	// 아이템 이름
	string name;
	// 아이템 id
	int id;
	// 아이템 설명
	string description;
public:
	Item(string _name, int _id, string _description)
		:name(_name), id(_id), description(_description) {}

	string getName() { return name; }
	int getId() { return id; }


	void printDescription() {
		// 40글자씩 엔터
		cout << name << endl;
		cout << description << endl;
		cout << endl;
	}


};

class ItemHandler {
private:
	vector<Item> list;
public:
	// 아이템 한개를 추가한다.
	void createItem(Item _item) {
		if (check(_item))
			list.push_back(_item);
		else {
			cout << "중복되는 아이템이 존재합니다." << endl;
			cout << "아이템 이름 : " << _item.getName() << endl;
		}

	}
	// 아이템 다수를 추가한다.
	void createItemM(Item _item[], int size) {
		for (int i = 0; i < size; ++i) {
			if (check(_item[i]))
				list.push_back(_item[i]);
		}
	}

	// 중복되는 아이템이 존재하는지 확인한다.
	// 아이템 아이디가 두 개 이상 있으면 중복된다. 이름은 상관 x
	bool check(Item _item) {
		bool flag = true;
		for (int i = 0; i < list.size(); ++i) {
			if (list[i].getId() == _item.getId())
				flag = false;
		}
		return flag;
	}

	// 존재하는 모든 아이템을 출력한다.
	void print() {
		for (int i = 0; i < list.size(); ++i) {
			cout << list[i].getName() << endl;
		}
	}
};


class Inventory{
private:
	vector<Item> list;
public:
	// 가지고 있는 모든 아이템을 출력한다.
	void printAllInventory() {
		for (int i = 0; i < list.size(); ++i) {
			cout <<i+1<<". "<< list[i].getName() << " ";
		}
		cout << endl;
	}
	// 아이템 설명을 출력한다.
	void printItemInfo() {
		int idx;
		cin >> idx;
		if (0 <= idx && idx <= list.size()) {
			list[idx - 1].printDescription();
		}
			
		else
			cout << "잘못된 값을 입력했습니다." << endl;
	}

	// 아이템을 얻는다.
	void getItem(Item _item) {
		list.push_back(_item);
	}
};

class Player : public Inventory{
private:
	// 변수 : 가지고 있는 아이템(인벤토리), 체력, 
	int hp;

public:
};

int main(void) {
	// 아이템 생성
	Item potion1("하급 포션", 1, "이 포션을 마시면 50의 hp를 회복할 수 있다.");
	ItemHandler IH;
	IH.createItem(potion1);
	Player player;
	player.getItem(potion1);
	player.printAllInventory();
	player.printItemInfo();
	return 0;
}
