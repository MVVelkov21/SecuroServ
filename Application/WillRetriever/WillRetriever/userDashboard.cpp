#include "mainMenu.hpp"

void dashboard::userDashboard(){
	system("cls");
	cout << "  ____            _     _                         _ " << endl;
	cout << " |  _ \\  __ _ ___| |__ | |__   ___   __ _ _ __ __| |" << endl;
	cout << " | | | |/ _` / __| '_ \\| '_ \\ / _ \\ / _` | '__/ _` |" << endl;
	cout << " | |_| | (_| \\__ \\ | | | |_) | (_) | (_| | | | (_| |" << endl;
	cout << " |____/ \\__,_|___/_| |_|_.__/ \\___/ \\__,_|_|  \\__,_|" << endl;
	cout << "  User: " << loggedInUsername << endl;
	willOptions();
}

void dashboard::willOptions() {
	int flag;
	cout << "1.Create a will        2.Access a will        3.Exit" << endl;
	cin >> flag;
	if (flag == 1) {
		willCreator();
	}
	if (flag == 2) {
		willAccess();
	}
	if (flag == 3) {
		exit(0);
	}
}

void dashboard::willCreator() {

}

void dashboard::willAccess(){

}
