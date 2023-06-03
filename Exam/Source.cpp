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

    
    return 0;
}
