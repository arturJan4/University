#include <algorithm>
#include <cstdio>
#include <vector>

struct Segment
{
    std::pair<int, int> start;  // point on (x, y)
    std::pair<int, int> end;
    // own operator for sorting
    bool operator < (const Segment& other) const
    {
        return (start < other.start) || ((start == other.start) && (end < other.end));
    }
};

// TODO
constexpr Segment createSegment(const int &x1,const int &y1,const int &x2,const int &y2)
{
    return Segment{{x1, y1}, {x2, y2}};
}

struct Line
{
    int a;
    int b;
    bool vertical;  // can be opt
    const Segment * origin;
};

Line segmentToLine(const Segment &s)
{   
    // -2 means vertical
    Line newLine = {0, 0, false, &s};
    if(s.start.first == s.end.first) // matching x
    {
        newLine.a = -2;
        newLine.vertical = true;
    }    
    else if(s.start.second == s.end.second) // matching y
    {
        newLine.b = s.start.second;
    }
    else
    {
        newLine.a = (s.end.second - s.start.second) / (s.end.first - s.start.first); // (y2 - y1)/(x2 - x1)
        newLine.b = (s.end.second - (newLine.a * s.end.first)); // y - ax
    }

    return newLine;
}

// check if (x, y) can be on s1 or s2 by checking ranges
bool isInRange(const Segment &s1, const Segment &s2, float x)
{
    // you can only check x because y follows by this argument (TODO - check this)
    // first range
    std::pair<float, float> range1;
    if(s1.start.first < s1.end.first)
        range1 = {s1.start.first, s1.end.first};
    else
        range1 = {s1.end.first, s1.start.first};

    // second range
    std::pair<float, float> range2;
    if(s2.start.first < s2.end.first)
        range2 = {s2.start.first, s2.end.first};
    else
        range2 = {s2.end.first, s2.start.first};   
    
    // check if they even cross
    if((range1.second < range2.first) || (range1.first > range2.second))
        return false;

    // searched range
    float first = std::max(range1.first, range2.first);
    float second = std::min(range1.second, range2.second);

    if((x < first) || (x > second))
        return false;

    return true;
}

// only multiples of 45 degrees
std::pair<float, float> intersection(const Segment &s1, const Segment &s2)
{
    // check if ends meet -> yes -> return point of meet
    if(s1.start == s2.start)     // x1 = x2
        return s1.start;
    else if (s1.start == s2.end) // x1 = y2
        return s1.start;
    else if (s1.end == s2.start) // y1 = x1
        return s1.end;
    else if (s1.end == s2.end)   // y1 = x2
        return s1.end;

    Line l1 = segmentToLine(s1);
    Line l2 = segmentToLine(s2);
    
    // check if both are vertical
    if(l1.vertical && l2.vertical)
        return {-1, -1};

    // check if parallel -> no
    if(l1.a == l2.a)    // posible -1, 0, 1
        return {-1, -1};

    // one is vertical
    if(l1.vertical || l2.vertical)
    {
        if(l2.vertical)
        {
            std::swap(l1, l2);
        }
            
        // if perpendicular (y = x, x)
        // if vertical line x lies between x'ses of horizontal
        // if horizontal lne y lies between y'ses of vertical
        // point is (x - vertical, y - horizontal)
        if(l2.a == 0)
        {   
            float crossX = l1.origin->start.first;
            float crossY = l2.origin->start.second; 

            int x1 = std::min(l2.origin->end.first, l2.origin->start.first); 
            int x2 = std::max(l2.origin->end.first, l2.origin->start.first);
            int y1 = std::min(l1.origin->end.second, l1.origin->start.second);
            int y2 = std::max(l1.origin->end.second, l1.origin->start.second);
            bool crosses = (y1 <= crossY) && (crossY <= y2) && (x1 <= crossX) && (crossX <= x2);

            if(!crosses)
                return {-1, -1};

            return {l1.origin->start.first, l2.origin->start.second};
        }
    
        // vertical (x) and angle (y = ax + b)
        // x is set, y z prostej
        float crossX = l1.origin->start.first;
        float crossY = l2.a * crossX + l2.b; 

        if(isInRange(*l1.origin, *l2.origin, crossX))
        {
            if((crossY <= std::max(l1.origin->start.second, l1.origin->end.second))
              && (std::min(l1.origin->start.second, l1.origin->end.second) <= crossY))
                return {crossX, crossY};
        }

        return {-1, -1};
    }
    
    // horizontal (y = b) or angle and angle (y = ax + c)
    // x = (b2 - b1)/(a1 - a2)
    // y = a1x + b1
    // check if meets rules

    float crossX = float((l2.b - l1.b))/(l1.a - l2.a);
    float crossY = l1.a * crossX + l1.b;

    if(isInRange(s1,s2,crossX))
        return {crossX, crossY};
    
    return {-1,-1};
}

void bruteSolution()
{
    int n;
    std::vector<Segment> listSegments;
    listSegments.reserve(200000);
    std::vector<std::pair<float,float>> results;
    results.reserve(200000);
    
    scanf("%d", &n);

    for(int i = 0; i < n; ++i)
    {
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        Segment s = createSegment(x1,y1,x2,y2);
        listSegments.push_back(s);
    }
    
    auto error = std::make_pair<float, float>(-1, -1);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                std::pair<float,float> result = intersection(listSegments[i], listSegments[j]);

                if(result != error)
                    results.push_back(result);
            }
        }
    }

    std::sort(results.begin(), results.end());
    results.erase(std::unique(results.begin(), results.end()), results.end());


    if(results.size() == 0)
    {
        printf("BRAK");
    }
    
    else
    {
        for(size_t i = 0; i < results.size(); ++i)
        {
            printf("%.1f %.1f\n", results[i].first, results[i].second);
        }
    }
    
}

int main()
{
    //int n; // n <= 200 000
    //test1();
    //test2();
    //test3();
    bruteSolution();
    //sweepLineSolution();

    return 0;
}