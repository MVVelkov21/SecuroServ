#include "baseHeader.hpp"

class dashboard{
private:	
	void willOptions();
	void willCreator();
	void willAccess();
	void dashboardTui();
	void createDatabaseAndTable(sqlite3*);
	bool checkUser(const string&, sqlite3*);
	void printTextForUsername(const std::string&);
public:
	void userDashboard();
	string loggedInUsername;
};