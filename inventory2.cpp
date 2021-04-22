#include <iostream>
#include <vector>
using namespace std;

/*
	 ***last update 2021-04-22***
	 인벤토리 위주로 구현 , 목표
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
	// 소모성 아이템인가?
	bool isUsed;
	// 아이템 종류
	string type;
public:
	Item(string _name, int _id, string _description,bool _isUsed,string _type)
		:name(_name), id(_id), description(_description), isUsed(_isUsed),type(_type) {}

	string getName() { return name; }
	int getId() { return id; }


	void printDescription() {
		// 40글자씩 엔터
		cout << name << endl;
		cout << description << endl;
		cout << endl;
	}
	string getItemType() { return type; }

};

class ItemHandler {
private:
	vector<Item> list;
public:
	// 아이템 한개를 추가한다.
	void createItem(string _name, int id, string _desc,bool _isUsed,string _type) {
		Item tmp(_name, id, _desc,_isUsed,_type);
		list.push_back(tmp);
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

	Item findItem(int id) {
		for (int i = 0; i < list.size(); ++i) {
			if (id == list[i].getId()) {
				return list[i];
			}
		}
		cout << "유효하지 않은 아이디 값입니다." << endl;
		return Item("NULL", -1, "NULL",false,"NULL");
	}

	// 존재하는 모든 아이템을 출력한다.
	void print() {
		for (int i = 0; i < list.size(); ++i) {
			cout << list[i].getName() << endl;
		}
	}
};


class Inventory {
protected:
	// 아이템 종류 , 갯수
	vector<pair<Item,int> > list;
public:
	// 가지고 있는 모든 아이템을 출력한다.
	void printAllInventory() {
		cout << endl;
		for (int i = 0; i < list.size(); ++i) {
			cout << i + 1 << ", " << list[i].first.getName() << " ";
		}
		cout << "아이템 설명을 원한다면 d를 입력하세요.  종료를 원하면 아무거나 누르세요. " << endl;
		char key;
		cin >> key;
		if (key == 'd') {
			printItemInfo();
		}
		else {
			return;
		}
		cout << endl;
	}
	// 아이템 설명을 출력한다.
	
	void printItemInfo() {
		int idx;
		cout << endl; cout << "아이템 출력 창 왼쪽 숫자를 입력하면 원하는 설명이 나옵니다." << endl;
		cin >> idx;
		if (0 <= idx && idx <= list.size()) {
			list[idx - 1].first.printDescription();
		}

		else
			cout << "잘못된 값을 입력했습니다." << endl;
	}

	// 아이템을 얻는다.
	void getItem(Item _item,int value) {
		if (_item.getId() == -1) return;
		list.push_back({ _item,value });
	}
};

class Player : public Inventory {
private:
	// 변수 : 가지고 있는 아이템(인벤토리), 체력, 
	int hp;

public:
	void useItem(Item _item, int value) {
		int id = _item.getId();
		if (id == -1) return;
		if (_item.getItemType() == "potion") {
			for (int i = 0; i < list.size(); ++i) {
				if (list[i].first.getId() == id) {
					if (list[i].second > 1) {
						list[i].second--;
						if (id == 1) hp += 50;
					}
					else if (list[i].second == 1) {
						//q 벡터를 제거
					}
				}
			}
		}
		else {
			cout << "사용할 수 없는 아이템 종류입니다." << endl;
		}
	}
};

class Monster {
protected:
	int hp;
	vector<pair<int,Item> > DropItems;
public:
	Monster(int _hp, vector<pair<int,Item> > _dropitem) : hp(_hp) {
		for (int i = 0; i < _dropitem.size(); ++i)
			DropItems.push_back(_dropitem[i]);
	}

	void printDropItems() {
		for (int i = 0; i < DropItems.size(); ++i) {
			cout << " 아이템 이름 : " << DropItems[i].second.getName()
				<< ", " << " 드롭확률 : " << DropItems[i].first << "%" << endl;
		}
	}
};

class Zombie : public Monster {
private:
public:
	Zombie(int _hp, vector<pair<int, Item> > _dropitem) :Monster(_hp, _dropitem) {}
	void printDropItems() {
		cout << "<<--Zombie 드롭 아이템, 드롭률 -->> " << endl;
		Monster::printDropItems();
		cout << endl;
	}
};

int main(void) {
	string type[3] = { "potion","normal","equipment" };


	vector<pair<int,Item> > zombie_drop_items;
	// 아이템 생성
	ItemHandler IH;
	int item_cnt = 0;
	IH.createItem("하급 포션", ++item_cnt, "이 포션을 마시면 50의 hp를 회복할 수 있다.",true,type[0]);
	Player player;
	player.getItem(IH.findItem(1),10);
	player.printAllInventory();
	player.printItemInfo();

	zombie_drop_items.push_back({ 33,IH.findItem(1) });

	Zombie zom(20,zombie_drop_items);
	zom.printDropItems();
	
	return 0;
}
