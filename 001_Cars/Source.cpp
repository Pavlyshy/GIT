#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Car
{
public:
    string name;
    int year;
    float engineVolume;
    float price;

    Car(const string& n, int y, float ev, float p)
        : name(n), year(y), engineVolume(ev), price(p)
    {
    }
};

class CarShowroom
{
private:
    vector<Car> cars;

public:
    void addCar(const Car& car)
    {
        cars.push_back(car);
    }

    void removeCar(const string& name)
    {
        cars.erase(remove_if(cars.begin(), cars.end(),
            [&](const Car& car) { return car.name == name; }), cars.end());
    }

    void displayCars()
    {
        for (const Car& car : cars)
        {
            cout << "Name: " << car.name << endl;
            cout<<"Year: " << car.year << endl;
            cout << "Engine Volume : " << car.engineVolume << endl;
            cout<<"Price: " << car.price << endl;
        }
    }

    void sortCarsByYear()
    {
        sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.year < b.year; });
    }

    void sortCarsByPrice()
    {
        sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.price < b.price; });
    }

    vector<Car> searchCarsByYear(int targetYear)
    {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result),
            [&](const Car& car) { return car.year == targetYear; });
        return result;
    }

    vector<Car> searchCarsByEngineVolume(float targetVolume)
    {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result),
            [&](const Car& car) { return car.engineVolume == targetVolume; });
        return result;
    }

    void saveToFile(const string& filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const Car& car : cars)
            {
                file << car.name << "," << car.year << ","
                    << car.engineVolume << "," << car.price << "\n";
            }
            file.close();
            cout << "Data saved to file: " << filename << endl;
        }
        else
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            cars.clear();
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string name;
                string yearStr;
                string engineVolumeStr;
                string priceStr;

                if (getline(iss, name, ',') &&
                    getline(iss, yearStr, ',') &&
                    getline(iss, engineVolumeStr, ',') &&
                    getline(iss, priceStr))
                {
                    int year = stoi(yearStr);
                    float engineVolume = stof(engineVolumeStr);
                    float price = stof(priceStr);

                    cars.emplace_back(name, year, engineVolume, price);
                }
            }
            file.close();
            cout << "Data loaded from file: " << filename << endl;
        }
        else
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};

int main()
{
    CarShowroom showroom;

    showroom.loadFromFile("car_data.txt");

    int choice;
    while (choice != 9)
    {
        std::cout << "Menu:\n"
            << "1. Add Car\n"
            << "2. Remove Car\n"
            << "3. Display Cars\n"
            << "4. Sort Cars by Year\n"
            << "5. Sort Cars by Price\n"
            << "6. Search Cars by Year\n"
            << "7. Search Cars by Engine Volume\n"
            << "8. Save Cars to File\n"
            << "9. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name;
            int year;
            float engineVolume;
            float price;

            cout << "Enter car name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter year of manufacture: ";
            cin >> year;

            cout << "Enter engine volume: ";
            cin >> engineVolume;

            cout << "Enter price: ";
            cin >> price;

            showroom.addCar(Car(name, year, engineVolume, price));
            break;
        }
        case 2:
        {
            string name;
            cout << "Enter car name to remove: ";
            cin.ignore();
            getline(std::cin, name);

            showroom.removeCar(name);
            break;
        }
        case 3:
        {
            showroom.displayCars();
            break;
        }
        case 4:
        {
            showroom.sortCarsByYear();
            cout << "Cars sorted by year." << std::endl;
            break;
        }
        case 5:
        {
            showroom.sortCarsByPrice();
            cout << "Cars sorted by price." << endl;
            break;
        }
        case 6:
        {
            int year;
            cout << "Enter year to search: ";
            cin >> year;

            vector<Car> cars = showroom.searchCarsByYear(year);
            cout << "Cars found:" << endl;
            for (const Car& car : cars)
            {
                cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << std::endl;
            }
            break;
        }
        case 7:
        {
            float volume;
            cout << "Enter engine volume to search: ";
            cin >> volume;

            vector<Car> cars = showroom.searchCarsByEngineVolume(volume);
            cout << "Cars found:" << endl;
            for (const Car& car : cars)
            {
                cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << endl;
            }
            break;
        }
        case 8:
        {
            showroom.saveToFile("car_data.txt");
            break;
        }
        case 9:
        {
            cout << "Exiting program." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
