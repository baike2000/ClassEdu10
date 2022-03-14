#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>

using namespace std;

class Account {
public:
	virtual void start() = 0;
	virtual void allow() = 0;
	virtual void end() = 0;
	virtual int maxLimit() = 0;
	// Template Method
	void withdraw(int amount) {
		cout << amount << endl;
		start();
		if (amount < maxLimit())
			allow();
		else
			cout << "Not allowed"
			<< endl;
		end();
	}
};

class AccountNormal : public Account {
public:
	void start() {
		cout << "Start ..." << endl;
	}
	void allow() {
		cout << "Allow ..." << endl;
	}
	void end() {
		cout << "End ..." << endl;
	}
	int maxLimit() { return 1000; }
};
class AccountPower : public Account {
public:
	void start() {
		cout << "Start ..." << endl;
	}
	void allow() {
		cout << "Allow ..." << endl;
	}
	void end() {
		cout << "End ..." << endl;
	}
	int maxLimit() { return 5000; }
};

int main() {
	AccountPower power;
	power.withdraw(1500);
	AccountNormal normal;
	normal.withdraw(1500);
	return 0;
}

