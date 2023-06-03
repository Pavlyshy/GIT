#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Car
{
public:
    std::string name;
    int year;
    float engineVolume;
    float price;

    Car(const std::string& n, int y, float ev, float p)
        : name(n), year(y), engineVolume(ev), price(p)
    {
    }
};

class CarShowroom
{
private:
    std::vector<Car> cars;

public:
    void addCar(const Car& car)
    {
        cars.push_back(car);
    }

    void removeCar(const std::string& name)
    {
        cars.erase(std::remove_if(cars.begin(), cars.end(),
            [&](const Car& car) { return car.name == name; }), cars.end());
    }

    void displayCars()
    {
        for (const Car& car : cars)
        {
            std::cout << "Name: " << car.name << ", Year: " << car.year
                << ", Engine Volume: " << car.engineVolume
                << ", Price: " << car.price << std::endl;
        }
    }

    void sortCarsByYear()
    {
        std::sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.year < b.year; });
    }

    void sortCarsByPrice()
    {
        std::sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.price < b.price; });
    }

    std::vector<Car> searchCarsByYear(int targetYear)
    {
        std::vector<Car> result;
        std::copy_if(cars.begin(), cars.end(), std::back_inserter(result),
            [&](const Car& car) { return car.year == targetYear; });
        return result;
    }

    std::vector<Car> searchCarsByEngineVolume(float targetVolume)
    {
        std::vector<Car> result;
        std::copy_if(cars.begin(), cars.end(), std::back_inserter(result),
            [&](const Car& car) { return car.engineVolume == targetVolume; });
        return result;
    }

    void saveToFile(const std::string& filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (const Car& car : cars)
            {
                file << car.name << "," << car.year << ","
                    << car.engineVolume << "," << car.price << "\n";
            }
            file.close();
            std::cout << "Data saved to file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            cars.clear();
            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                std::string name;
                int year;
                float engineVolume;
                float price;

                if (std::getline(iss, name, ',') &&
                    std::getline(iss, line, ',') && std::stringstream(line) >> year &&
                    std::getline(iss, line, ',') && std::stringstream(line) >> engineVolume &&
                    std::getline(iss, line) && std::stringstream(line) >> price)
                {
                    cars.emplace_back(name, year, engineVolume, price);
                }
            }
            file.close();
            std::cout << "Data loaded from file: " << filename << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
};

int main()
{
    CarShowroom showroom;

    // Зчитування даних з файлу (якщо існує)
    showroom.loadFromFile("car_data.txt");

    int choice = 0;
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
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string name;
            int year;
            float engineVolume;
            float price;

            std::cout << "Enter car name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter year of manufacture: ";
            std::cin >> year;

            std::cout << "Enter engine volume: ";
            std::cin >> engineVolume;

            std::cout << "Enter price: ";
            std::cin >> price;

            showroom.addCar(Car(name, year, engineVolume, price));
            break;
        }
        case 2:
        {
            std::string name;
            std::cout << "Enter car name to remove: ";
            std::cin.ignore();
            std::getline(std::cin, name);

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
            std::cout << "Cars sorted by year." << std::endl;
            break;
        }
        case 5:
        {
            showroom.sortCarsByPrice();
            std::cout << "Cars sorted by price." << std::endl;
            break;
        }
        case 6:
        {
            int year;
            std::cout << "Enter year to search: ";
            std::cin >> year;

            std::vector<Car> cars = showroom.searchCarsByYear(year);
            std::cout << "Cars found:" << std::endl;
            for (const Car& car : cars)
            {
                std::cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << std::endl;
            }
            break;
        }
        case 7:
        {
            float volume;
            std::cout << "Enter engine volume to search: ";
            std::cin >> volume;

            std::vector<Car> cars = showroom.searchCarsByEngineVolume(volume);
            std::cout << "Cars found:" << std::endl;
            for (const Car& car : cars)
            {
                std::cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << std::endl;
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
            std::cout << "Exiting program." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }
    }

    return 0;
}
