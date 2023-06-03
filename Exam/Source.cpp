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
    vector<string> questions; // Список питань
    vector<bool> correctAnswers; // Список правильних відповідей

public:
    Test(const string& name) {
        this->name = name;
    }

    void addQuestion(const string& question, bool correctAnswer) {
        questions.push_back(question);
        correctAnswers.push_back(correctAnswer);
    }

    // Додаткові методи для доступу до полів тесту

    int getTotalQuestions() const {
        return questions.size();
    }

    int gradeTest(const vector<bool>& answers) const {
        int totalQuestions = questions.size();
        if (answers.size() != totalQuestions) {
            return -1; // Помилка: неправильна кількість відповідей
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
    map<string, Test> tests; // Ключ - назва тесту, значення - об'єкт тесту

public:
    Category(const string& name) {
        this->name = name;
    }

    void addTest(const string& testName, const Test& test) {
        tests.emplace(testName, test);
    }

    // Додаткові методи для доступу до полів категорії та тестів

    const Test* getTest(const string& testName) const {
        if (tests.find(testName) != tests.end()) {
            return &(tests.at(testName));
        }
        return nullptr; // Тест не знайдено
    }
};

class TestingSystem {
private:
    string adminUsername;
    string adminPassword;
    User admin;
    map<string, User> users; // Ключ - логін користувача, значення - об'єкт користувача
    vector<Category> categories; // Список категорій

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
            return true; // Вхід адміністратора
        }

        auto it = users.find(username);
        if (it != users.end() && it->second.getPassword() == password) {
            return true; // Вхід користувача
        }

        return false; // Помилка входу
    }

    User* getUser(const string& username) {
        if (username == admin.getUsername()) {
            return &admin;
        }

        auto it = users.find(username);
        if (it != users.end()) {
            return &(it->second);
        }

        return nullptr; // Користувача не знайдено
    }

    void addCategory(const Category& category) {
        categories.push_back(category);
    }

    // Додаткові методи для доступу до користувачів, категорій та адміністратора

    // Додаткові методи для виконання операцій адміністратора (управління користувачами, тестуванням, статистикою)

    // Додаткові методи для виконання операцій гостя (реєстрація, тестування, перегляд результатів)

};

int main() {
    TestingSystem system("admin", "adminpassword");

    // Додавання категорій, тестів, запитань до системи

    // Реєстрація користувачів

    // Вхід в систему, виконання дій користувача

    return 0;
}
