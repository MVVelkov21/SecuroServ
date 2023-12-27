#include "baseHeader.hpp"

class dashboard{
private:
	void willOptions();
	void willCreator();
	void willAccess();
	void dashboardTui();
	void createDatabaseAndTable(sqlite3*);
public:
	void userDashboard();
	string loggedInUsername;
};