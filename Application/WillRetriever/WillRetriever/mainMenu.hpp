#include "userDashboard.hpp"

class mainMenu {
private:
	sqlite3* db;
	bool isUserExists(const string& username, sqlite3* db);
	bool checkUser(sqlite3* db);
	void saveLoginInfo(const string& username, const string& password, sqlite3* db);
public:
	void menu();
};