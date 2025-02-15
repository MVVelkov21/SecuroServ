#include "mainMenu.hpp"

bool mainMenu::isUserExists(const string& username, sqlite3* db) {
    const char* selectQuery = "SELECT * FROM LoginInfo WHERE username = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_ROW;
}

bool mainMenu::checkUser(sqlite3* db) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    char ch;
    do {
        ch = _getch();

        if (ch != '\r' && ch != '\n') {
            password.push_back(ch);
            std::cout << '*';
        }
    } while (ch != '\r' && ch != '\n');
    cout << endl;

    const char* selectQuery = "SELECT * FROM LoginInfo WHERE username = ? AND password = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement" << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
        dash.loggedInUsername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    }

    sqlite3_finalize(stmt);

    return result == SQLITE_ROW;
}

void mainMenu::saveLoginInfo(const string& username, const string& password, sqlite3* db) {
    if (isUserExists(username, db)) {
        cout << "User with the same username already exists. Please choose a different username." << endl;
        _getch();
        return;
    }

    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS LoginInfo ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "password TEXT NOT NULL);";

    if (sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr) != SQLITE_OK) {
        cout << "Error creating table: " << sqlite3_errmsg(db) << endl;
        return;
    }

    const char* insertQuery = "INSERT INTO LoginInfo (username, password) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error preparing statement" << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cout << "Error executing statement" << endl;
    }
    else {
        cout << "User information saved to the database." << endl;
        _getch();
    }

    sqlite3_finalize(stmt);
}

void mainMenu::menu() {
    cout << " __        ___ _ _ ____      _        _                     " << endl;
    cout << " \\ \\      / (_) | |  _ \\ ___| |_ _ __(_) _____   _____ _ __ " << endl;
    cout << "  \\ \\ /\\ / /| | | | |_) / _ \\ __| '__| |/ _ \\ \\ / / _ \\ '__|" << endl;
    cout << "   \\ V  V / | | | |  _ <  __/ |_| |  | |  __/\\ V /  __/ |   " << endl;
    cout << "    \\_/\\_/  |_|_|_|_| \\_\\___|\\__|_|  |_|\\___| \\_/ \\___|_|   " << endl;
    cout << "                       by SecuroServ                        " << endl;
    cout << "                                                            " << endl;

    if (sqlite3_open("database.db", &db) != SQLITE_OK) {
        cout << "Error opening database" << endl;
    }
    string choice;
    cout << "Do you want to sign up (1) or log in (2)? ";
    cin >> choice;

    if (choice == "1") {
        cout << "Enter a password atleast 6 characters long," << endl;
        cout << "including atleast 1 capital letter, number" << endl;
        cout << "and a special symbol." << endl << endl;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        char ch;
        while (true) {
            ch = _getch();

            if (ch == '\r' || ch == '\n') {
                if (password.length() >= 6 &&
                    std::any_of(password.begin(), password.end(), ::isdigit) &&
                    std::any_of(password.begin(), password.end(), ::isupper) &&
                    strpbrk(password.c_str(), "!@#$%^&*()-_+=<>?,./;:'\"[]{}\\|`~") != nullptr) {
                    break;
                }
                else {
                    std::cout << "\nInvalid password.";
                    _getch();
                    exit(0);
                }
            }
            else {
                password.push_back(ch);
                std::cout << '*';
            }
        }
        cout << endl;
        saveLoginInfo(username, password, db);
    }
    else if (choice == "2") {
        if (checkUser(db)) {
            cout << "Login successful! Press ENTER to continue." << endl;
            _getch();
            system("cls");
            dash.userDashboard();
        }
        else {
            cout << "Login failed. Invalid username or password." << endl;
            _getch();
        }
    }
    else {
        cout << "Invalid choice." << endl;
        _getch();
    }

    sqlite3_close(db);
}