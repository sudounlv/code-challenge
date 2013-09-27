// Solution to UNLV Sudo Moth Eradication problem
// Brian Kauke, September 2013

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

struct point
{
    point() : x(0.0), y(0.0) {}
    point(double x, double y) : x(x), y(y) {}
    bool operator==(const point& p)
    {
        return x == p.x && y == p.y;
    }
    friend std::ostream& operator<< (std::ostream&, const point&);
    double x, y;
};

std::ostream& operator<< (std::ostream& out, const point& p)
{
    out << std::fixed << std::setprecision(1);
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

double distance(const point& p0, const point& p1)
{
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;
    return std::sqrt(dx*dx + dy*dy);
}

typedef std::vector<point> point_vector;

bool clockwise_or_collinear(const point& a, const point& b, const point& c)
{
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) <= 0.0;
}

struct clockwise_comparator : public std::binary_function<point, point, bool>
{
    clockwise_comparator(point p) : a(p) { }
    
    // Returns false if c is clockwise from b with reference to a
    bool operator()(const point& b, const point& c)
    {
        return clockwise_or_collinear(a, b, c);
    }
    
    point a;
};

bool compare_y(const point& a, const point& b)
{
    return a.y < b.y;
}

int main(int argc, const char * argv[])
{
    int n_vertices = 0;
    std::string line;
    while(!std::cin.eof())
    {
        std::getline(std::cin, line);
        if (!(std::sscanf(line.c_str(), "%d", &n_vertices) == 1))
            exit(1);
        if (n_vertices == 0)
            break;
        
        point_vector points(n_vertices);
        std::vector<bool> on_hull(n_vertices, false);
        
        for (int i=0; i < n_vertices; ++i)
        {
            point p;
            std::getline(std::cin, line);
            if (!(std::sscanf(line.c_str(), "%lf %lf", &p.x, &p.y) == 2))
                exit(1);
            points[i] = p;
        }
        
        //std::cout << "Before sort:";
        //for (int i = 0; i < points.size(); ++i)
        //{
        //    std::cout << "(" << points[i].x << ", " << points[i].y << ") ";
        //}
        //std::cout << std::endl;
        
        // Swap the lowest point into the first position
        point_vector::iterator lowest_pos = std::min_element(points.begin(), points.end(), compare_y);
        std::swap(*lowest_pos, points.front());
        point lowest_point = points.front();
        
        std::sort(points.begin() + 1, points.end(), clockwise_comparator(lowest_point));
        
        //std::cout << "After sort: ";
        //for (int i = 0; i < points.size(); ++i)
        //{
        //    std::cout << "(" << points[i].x << ", " << points[i].y << ") ";
        //}
        //std::cout << std::endl;
        
        // The lowest point is always on the hull
        on_hull[0] = true;
        
        // TODO: n=0, n=1
        
        // Exclude last point from the loop. Must handle degenerate n=0, 1 cases or this will crash!
        for (point_vector::iterator it = points.begin() + 1; it < points.end() - 1; ++it)
        {
            point a = *(it - 1);
            point b = *it;
            point c = *(it + 1);
            //std::cout << "clockwise test: "
            //    << "(" << a.x << ", " << a.y << "), "
            //    << "(" << b.x << ", " << b.y << "), "
            //    << "(" << c.x << ", " << c.y << ")";
            if (clockwise_or_collinear(a, b, c))
            {
                //std::cout << " TRUE";
                on_hull[it - points.begin()] = true;
            }
            //std::cout << std::endl;
        }
        
        // Last one
        point_vector::iterator last = points.end() - 1;
        if (clockwise_or_collinear(*(last - 1), *last, points.front()))
        {
            on_hull[last - points.begin()] = true;
        }
        
        // Count the number of points on the hull
        int n_hull = std::accumulate(on_hull.begin(), on_hull.end(), 0);
        
        // Compact the original point vector to contain only points on the hull
        point_vector::iterator hp = points.begin();
        for (int i = 0; i < points.size(); ++i)
        {
            if (on_hull[i])
                *hp++ = points[i];
        }
        points.resize(n_hull);
        
        double perimeter = 0.0;
        for (point_vector::iterator it = points.begin(); it < points.end() - 1; ++it)
        {
            perimeter += distance(*it, *(it + 1));
        }
        // Handle the last point
        perimeter += distance(points.back(), points.front());
        
        for (point_vector::iterator it = points.begin(); it < points.end(); ++it)
        {
            std::cout << *it << "-";
        }
        std::cout << points.front();
        std::cout << std::endl;
        
        std::cout << std::setprecision(2) << "Perimeter length = " << perimeter << std::endl;
        
        std::cout << std::endl;
    }
    return 0;
}
