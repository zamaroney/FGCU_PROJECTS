// Zachary Maroney

#include <iostream>
#include <string>

using namespace std;

#define MAX_STR_LEN 10

const char TAB_CHAR = 9;

enum Menu {
	None,
	New,
	Original,
	Reversed,
	Quit
};

Menu getMenuItem();
int getInputString(string &buff);
string getReversed(char *buff, int len);

int main() {

	Menu choice;

	int strLen;
	bool isGood = false;
	string strBuff;

	do {
		
		choice = getMenuItem();

		switch(choice) {
		case New:
			strLen = getInputString(strBuff);
			isGood = strLen > 1;
			if (!isGood) {
				cout << endl << "String too short!" << endl;
			}

			break;
		case Original:
			if (!isGood) {
				cout << endl << "Enter a new string first!" << endl;
			}
			else {
				cout << endl << "You entered: " << strBuff << endl;
			}

			break;
		case Reversed:
			if (!isGood) {
				cout << endl << "Enter a new string first!" << endl;
			}
			else {
				cout << endl << "Your String reversed: " << getReversed(&strBuff[0], strLen) << endl;
			}

			break;
		case Quit:
			cout << endl << "Good Bye!" << endl;
			break;
		default:
			cout << endl << "Invalid Choice!" << endl;
		};

	} while (choice != Quit);

	return 0;
}

Menu getMenuItem() {
	Menu item = None;

	cout << endl << "String Processor Menu" << endl;
	cout << TAB_CHAR << "1) New String" << endl;
	cout << TAB_CHAR << "2) Show Original String" << endl;
	cout << TAB_CHAR << "3) Show Reversed String" << endl;
	cout << TAB_CHAR << "4) Quit" << endl;

	char item_in;
	cout << "Enter choice: ";
	cin >> item_in;

	if (item_in >= '1' && item_in <= '4') {
		item = Menu(item_in - '0');
	}
	cin.ignore();

	return item;
}

int getInputString(string &buff) {
	cout << endl << "Inpute a String of text: ";
	getline(cin, buff);
	return buff.length();
}

string getReversed(char *buff, int len) {
	string reversed(MAX_STR_LEN, ' ');

	buff += len - 1;
	for (int i = 0; i < len; i++) {
		reversed[i] = *buff;
		buff--;
	}

	return reversed;
}
