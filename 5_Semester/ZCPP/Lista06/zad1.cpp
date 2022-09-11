#include <iostream>
#include <iomanip>
#include <random>
#include <utility>
#include <deque>

class person
{
public:
    std::string name;
    std::string surname;
    int age;
    double weight; // in kg
    double height; // in meters

    person(std::string name, std::string surname, int age, double weight, double height)
    : name(std::move(name)), surname(std::move(surname)), age(age), weight(weight), height(height)
    {}

    void print() const
    {
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << name << ", " << surname << + ", " << age << ", " << weight << " kg, " << height << "m.";
    }

    static void print_people(const std::deque<person>& people)
    {
        for (const auto& p : people)
        {
            p.print();
            std::cout << "\n";
        }
        std::cout << "========================\n";
    }

    static void print_people(const std::deque<person>::iterator& start, const std::deque<person>::iterator& end)
    {
        for (auto it = start; it != end; ++it)
        {
            (*it).print();
            std::cout << "\n";
        }
        std::cout << "========================\n";
    }
};


int main()
{
    std::deque<person> people = {
            person("Umer", "Reader", 20, 115, 1.80),
            person("Aron", "Lara", 5, 17.3, 1.00),
            person("Petra", "Norris", 45, 70.6, 1.90),
            person("Elesse", "Hinton", 22, 50.5, 1.60),
            person("Tatianna", "Alexander", 33, 66, 1.68),
            person("Leon", "Rees", 44, 75.3, 1.85),
            person("Sophia", "Torres", 37, 60.1, 1.67),
            person("Emelia", "Robin", 57, 70.7, 1.79),
            person("Nella", "Booker", 63, 80.7, 1.77),
            person("Elijah", "Ortiz", 67, 120.9, 1.95),
            person("Matilda", "Ramsey", 38, 74.0, 1.55),
    };

    person::print_people(people);
    // a - sort by BMI
    std::sort(people.begin(), people.end(), [](const person& a, const person& b) {
       return a.weight / (a.height * a.height) < b.weight / (b.height * b.height);
    });
    std::cout << "a - sort by BMI\n";
    person::print_people(people);

    // b - lose 10% weight
    std::for_each(people.begin(), people.end(), [](person &p) {p.weight = (p.weight*0.9);});
    std::cout << "b - lose 10% weight\n";

    person::print_people(people);

    // c
    auto it_split = std::partition(people.begin(), people.end(), [](person &p){return p.weight > 100;});
    std::cout << "c - partition\n";

    std::cout << "people with more than 100kgs: \n";
    person::print_people(people.begin(), it_split);

    std::cout << "people with less than 100kgs: \n";
    person::print_people(it_split, people.end());


    // d
    auto median_iter = people.begin() + people.size()/2;
    std::nth_element(people.begin(), median_iter, people.end(),
                     [](const person& a, const person& b){return a.height < b.height;});

    std::cout << "d - median\n";

    std::cout << "median height is: " << (*median_iter).height << "\n";
    person::print_people(people);


    // e
    std::random_device dev;
    //std::random_shuffle(people.begin(), people.end());
    std::mt19937 generator(dev());
    std::shuffle(people.begin(), people.begin() + 5, generator);
    std::shuffle(people.end() - 5, people.end(), generator);

    std::cout << "e - random shuffle\n";

    person::print_people(people);


    // f - oldest and youngest person
    auto [youngest, oldest] = minmax_element(people.cbegin(), people.cend(),
            [](const person& a, const person& b){return a.age < b.age;});

    std::cout << "youngest: \n";
    youngest->print();
    std::cout << "\n";

    std::cout << "oldest: \n";
    oldest->print();
    std::cout << "\n";
}