#include <iostream>
#include <iomanip>
#include <tuple>
#include <list>
#include <utility>

class point
{
public:
    double x;
    double y;
    std::tuple<int, int, int> rgb;
    std::string name;

    point(double x, double y, std::tuple<int, int, int> rgb, std::string name)
    : x(x), y(y), rgb(std::move(rgb)), name(std::move(name))
    {}

    double calc_brightness () const
    {
        return 0.3 * std::get<0>(this->rgb)  +
               0.59 * std::get<1>(this->rgb) +
               0.11 * std::get<2>(this->rgb);
    }

    void print() const
    {
        std::cout << std::setprecision(1) << std::fixed;
        std::cout << "(x,y)=(" << x << + ", " << y << "), "
        << "R:" << std::get<0>(this->rgb)
        << ",G:" <<  std::get<1>(this->rgb)
        << ",B:" <<  std::get<2>(this->rgb)
        << ", name:" << name;
    }

    static void print_points(const std::list<point>& points)
    {
        for (const auto& p : points)
        {
            p.print();
            std::cout << "\n";
        }
        std::cout << "========================\n";
    }
};

int main()
{
    std::list<point> points = {
        point(2.0, -3.0, {100, 30, 70}, "test"),
        point(4.0, 15, {200, 100, 0}, "name"),
        point(-2.0, 20, {150, 150, 15}, "tettt"),
        point(5.2, -4.2, {5, 20, 105}, "ttttttttt"),
        point(6.0, -3.0, {10, 30, 200}, "xaaddddddd"),
        point(3.3, 5.0, {15, 70, 111}, "ttetetettet"),
        point(-2.0, -3.0, {10, 100, 212}, "te"),
        point(6.0, 3.6, {30, 5, 42}, "t"),
        point(43.0, 7.0, {120, 14, 35}, "tes"),
        point(1.2, -3.0, {210, 54, 0}, "tedd"),
        point(2.5, 8.0, {205, 12, 3}, "terrr"),
        point(2.7, -3.1, {215, 7, 4}, "tetttwt"),
        point(-5.6, 32.0, {123, 35, 42}, "test1"),
        point(-2.0, 42.0, {105, 23, 50}, "tedt"),
        point(-4.0, 33.0, {143, 95, 60}, "txxt"),
        point(-92.0, -3.0, {123, 204, 20}, "taat"),
        point(12.0, 23.0, {115, 124, 42}, "tzzzzzt"),
    };
    point::print_points(points);

    // a - remove if name is longer than 5 letters
    points.erase(std::remove_if(points.begin(), points.end(), [](const point &p) {return p.name.size() > 5;}),
                 points.end());
    std::cout << "a - remove if name is longer than 5 letters\n";
    point::print_points(points);

    // b - count in each quadrant
    auto predI   = [](const point& p) {return p.x > 0 && p.y > 0;};
    auto predII  = [](const point& p) {return p.x < 0 && p.y > 0;};
    auto predIII = [](const point& p) {return p.x < 0 && p.y < 0;};
    auto predIV  = [](const point& p) {return p.x > 0 && p.y < 0;};

    std::cout << "quadrant I count:"   << count_if(points.cbegin(), points.cend(), predI) << "\n";
    std::cout << "quadrant II count:"  << count_if(points.cbegin(), points.cend(), predII) << "\n";
    std::cout << "quadrant III count:" << count_if(points.cbegin(), points.cend(), predIII) << "\n";
    std::cout << "quadrant IV count:"  << count_if(points.cbegin(), points.cend(), predIV) << "\n";

    // c - sort by luminance
    points.sort([](const point& p1, const point& p2) {return p1.calc_brightness() < p2.calc_brightness();});
    std::cout << "c - sort by luminance\n";
    point::print_points(points);

    // d - how many dark points (luminance < 64)
    std::list<point> dark_points;
    std::copy_if(points.cbegin(), points.cend(), std::back_inserter(dark_points),
                 [&](const auto& point){return point.calc_brightness() < 64;});

    std::cout << "d - count dark points\n";
    point::print_points(dark_points);
}