#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class User {
private:
    string username;
    string password;
    string fullName;
    string address;
    string phone;
    map<string, int> testResults; // Ключ - назва тесту, значення - результат

public:
    User(const string& username, const string& password, const string& fullName, const string& address, const string& phone) {
        this->username = username;
        this->password = password;
        this->fullName = fullName;
        this->address = address;
        this->phone = phone;
    }

    string getUsername() const {
        return username;
    }
    string getFullName() const {
        return fullName;
    }
    string getPassword()const {
        return password;
    }
    string getAddress() const {
        return address;
    }
    string getPhone() const {
        return phone;
    }

    void addTestResult(const string& testName, int result) {
        testResults.emplace(testName, result);
    }

    int getTestResult(const string& testName) const {
        if (testResults.find(testName) != testResults.end()) {
            return testResults.at(testName);
        }
        return -1;
    }
};

class Test {
private:
    string name;
    vector<string> questions;
    vector<bool> correctAnswers;

public:
    Test(const string& name) {
        this->name = name;
    }

    void addQuestion(const string& question, bool correctAnswer) {
        questions.push_back(question);
        correctAnswers.push_back(correctAnswer);
    }

    const string& getName() const {
        return name;
    }

    const vector<string>& getQuestions() const {
        return questions;
    }

    const vector<bool>& getAnswers() const {
        return correctAnswers;
    }

    int getTotalQuestions() const {
        return questions.size();
    }

    int getCorrectAnswers(const vector<bool>& userAnswers) const {
        if (userAnswers.size() != correctAnswers.size()) {
            cout << "Invalid number of answers." << endl;
            return -1;
        }

        int count = 0;
        for (int i = 0; i < correctAnswers.size(); i++) {
            if (userAnswers[i] == correctAnswers[i]) {
                count++;
            }
        }

        return count;
    }

    /*double calculatePercentage(int correctAnswers) const {
        return static_cast<double>(correctAnswers) / correctAnswers.size() * 100;
    }*/

    int gradeTest(const vector<bool>& answers) const {
        int totalQuestions = questions.size();
        if (answers.size() != totalQuestions) {
            return -1;
        }

        int correctCount = 0;
        for (int i = 0; i < totalQuestions; i++) {
            if (answers[i] == correctAnswers[i]) {
                correctCount++;
            }
        }

        int score = 12 * correctCount / totalQuestions;
        return score;
    }
};

class Category {
private:
    string name;
    map<string, Test> tests;

public:
    Category(const string& name) {
        this->name = name;
    }

    string getName()const {
        return name;
    }

    void addTest(const string& testName, const Test& test) {
        tests.emplace(testName, test);
    }

    const map<string, Test>& getTests() const {
        return tests;
    }

    const Test* getTest(const string& testName) const {
        if (tests.find(testName) != tests.end()) {
            return &(tests.at(testName));
        }
        return nullptr;
    }
};

class TestingSystem {
private:
    string adminUsername;
    string adminPassword;
    User admin;
    map<string, User> users;
    vector<Category> categories;

public:
    TestingSystem(const string& adminUsername, const string& adminPassword) : admin(adminUsername, adminPassword, "", "", "") {
        this->adminUsername = adminUsername;
        this->adminPassword = adminPassword;
    }

    void registerUser(const string& username, const string& password, const string& fullName, const string& address, const string& phone) {
        if (users.find(username) != users.end()) {
            cout << "This username is already taken. Please choose a different username." << endl;
            return;
        }

        users.emplace(username, User(username, password, fullName, address, phone));
        cout << "User registered successfully." << endl;
    }

    bool login(const string& username, const string& password) {
        if (username == adminUsername && password == adminPassword) {
            return true;
        }

        auto it = users.find(username);
        if (it != users.end() && it->second.getPassword() == password) {
            return true;
        }

        return false;
    }

    void removeUser(const string& username) {
        if (username == admin.getUsername()) {
            cout << "Cannot remove the admin user." << endl;
            return;
        }

        auto it = users.find(username);
        if (it != users.end()) {
            users.erase(it);
            cout << "User '" << username << "' has been removed." << endl;
        }
        else {
            cout << "User '" << username << "' not found." << endl;
        }
    }

    User* getUser(const string& username) {
        if (username == admin.getUsername()) {
            return &admin;
        }

        auto it = users.find(username);
        if (it != users.end()) {
            return &(it->second);
        }

        return nullptr;
    }

    void addCategory(const Category& category) {
        categories.push_back(category);
    }

    const vector<Category>& getCategories() const {
        return categories;
    }

    User& getAdmin() {
        return admin;
    }

    const User& getAdmin() const {
        return admin;
    }

    const map<string, User>& getUsers() const {
        return users;
    }
};

int main() {
    TestingSystem system("admin", "adminpassword");

    Category mathCategory("Mathematics");
    Category scienceCategory("Science");

    Test mathTest("Math Test");
    mathTest.addQuestion("2 + 2 = ?", true);
    mathTest.addQuestion("3 * 5 = ?", false);
    mathCategory.addTest("Basic Math", mathTest);

    Test scienceTest("Science Test");
    scienceTest.addQuestion("Water boils at 100 degrees Celsius. True or false?", true);
    scienceTest.addQuestion("The Earth is flat. True or false?", false);
    scienceCategory.addTest("General Science", scienceTest);

    system.addCategory(mathCategory);
    system.addCategory(scienceCategory);

    system.registerUser("john", "password", "John Doe", "123 Main St", "555-1234");
    system.registerUser("jane", "password", "Jane Smith", "456 Elm St", "555-5678");

    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool loggedIn = system.login(username, password);
    if (loggedIn) {
        if (username == "admin") {
            cout << "Welcome, Administrator!" << endl;
            cout << "Select an option:" << endl;
            cout << "1. Manage users" << endl;
            cout << "2. Conduct test" << endl;
            cout << "3. View statistics" << endl;
            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "Select an option:" << endl;
                cout << "1. Add a new user" << endl;
                cout << "2. Remove a user" << endl;

                int userOption;
                cin >> userOption;

                switch (userOption) {
                case 1:
                    cout << "Enter the username: ";
                    string newUsername;
                    cin >> newUsername;

                    cout << "Enter the password: ";
                    string newPassword;
                    cin >> newPassword;

                    cout << "Enter the full name: ";
                    string newFullName;
                    cin.ignore();
                    getline(cin, newFullName);

                    cout << "Enter the address: ";
                    string newAddress;
                    cin.ignore();
                    getline(cin, newAddress);

                    cout << "Enter the phone number: ";
                    string newPhone;
                    cin >> newPhone;

                    system.registerUser(newUsername, newPassword, newFullName, newAddress, newPhone);
                    break;

                case 2:
                    cout << "Enter the username of the user to remove: ";
                    string removeUsername;
                    cin >> removeUsername;

                    system.removeUser(removeUsername);
                    break;

                default:
                    cout << "Invalid choice. Exiting..." << endl;
                    break;
                }

                break;
            case 2:
                cout << "Select a category:" << endl;
                const vector<Category>& categories = system.getCategories();
                for (int i = 0; i < categories.size(); i++) {
                    cout << i + 1 << ". " << categories[i].getName() << endl;
                }
                int categoryChoice;
                cin >> categoryChoice;

                if (categoryChoice >= 1 && categoryChoice <= categories.size()) {
                    const Category& selectedCategory = categories[categoryChoice - 1];
                    const vector<Test>& tests = selectedCategory.getTests();

                    cout << "Select a test:" << endl;
                    for (int i = 0; i < tests.size(); i++) {
                        cout << i + 1 << ". " << tests[i].getName() << endl;
                    }
                    int testChoice;
                    cin >> testChoice;

                    if (testChoice >= 1 && testChoice <= tests.size()) {
                        const Test& selectedTest = tests[testChoice - 1];

                        // Виконання тесту
                        // ...

                        break;
                    }
                }
                cout << "Invalid choice. Exiting..." << endl;
                break;
            case 3:
                // Перегляд статистики
                // ...
                break;
            default:
                cout << "Invalid choice. Exiting..." << endl;
                break;
            }
        }
        else {
            // Дії користувача
            cout << "Welcome, " << system.getUser(username)->getFullName() << "!" << endl;
            // Виконання операцій користувача (реєстрація, тестування, перегляд результатів)
            // ...
        }
    }
    else {
        cout << "Invalid username or password. Please try again." << endl;
    }

    return 0;
}

