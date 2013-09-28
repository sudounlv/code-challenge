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
    
    // Returns true if c is clockwise from b with reference to a
    bool operator()(const point& b, const point& c)
    {
        return clockwise_or_collinear(a, b, c);
    }
    
    point a;
};

bool compare_y(const point& a, const point& b)
{
    if (a.y == b.y)
        return a.x < b.x;
    else
        return a.y < b.y;
}

void reduce_to_convex_hull(point_vector& points)
{
    size_t n = points.size();
    
    // With 3 or fewer points, all must be on the hull, so nothing to do
    if (n < 4)
        return;
    
    // Swap the lowest point into the first position
    point_vector::iterator lowest_pos = std::min_element(points.begin(), points.end(), compare_y);
    std::swap(*lowest_pos, points.front());
    point lowest_point = points.front();
    
    // Sort points (except first) by angle from lowest point
    std::sort(points.begin() + 1, points.end(), clockwise_comparator(lowest_point));
    
    // Initialize stack with lowest point, largest angle point
    point_vector::iterator hull_back = points.begin() + 1;
    
    // Perform scan to determine whether points are on the hull
    for (point_vector::iterator it = points.begin() + 2; it < points.end(); ++it)
    {
        while (!clockwise_or_collinear(*(hull_back - 1), *hull_back, *it))
        {
            if (hull_back > points.begin())
                --hull_back; // Pop stack
        }
        
        // Add point to hull stack
        std::swap(*(++hull_back), *it);
    }
    
    // Compact the original point vector to contain only points on the hull
    size_t n_hull = hull_back - points.begin() + 1;
    points.resize(n_hull);
}

int main(int argc, const char * argv[])
{
    int n_vertices = 0, region_number = 0;
    std::string line;
    while(!std::cin.eof())
    {
        // Read the number of points in the region
        std::getline(std::cin, line);
        if (!(std::sscanf(line.c_str(), "%d", &n_vertices) == 1))
            exit(1);
        if (n_vertices == 0)
            break;
        
        // Increment region number (first region is 1)
        ++region_number;
        
        // Print separator line
        if (region_number != 1)
            std::cout << std::endl;
        
        // Allocate storage for points
        point_vector points(n_vertices);
        
        // Read points
        for (int i=0; i < n_vertices; ++i)
        {
            point p;
            std::getline(std::cin, line);
            if (!(std::sscanf(line.c_str(), "%lf %lf", &p.x, &p.y) == 2))
                exit(1);
            points[i] = p;
        }
        
        // Run convex hull algorithm
        reduce_to_convex_hull(points);
        
        // Compute perimeter
        double perimeter = 0.0;
        for (point_vector::iterator it = points.begin(); it < points.end() - 1; ++it)
        {
            perimeter += distance(*it, *(it + 1));
        }
        perimeter += distance(points.back(), points.front());
        
        // Print region header
        std::cout << "Region #" << region_number << ":" << std::endl;
        
        // Print region perimeter
        for (point_vector::iterator it = points.begin(); it < points.end(); ++it)
        {
            std::cout << *it << "-";
        }
        std::cout << points.front() << std::endl;
        
        // Print the perimeter length
        std::cout << std::setprecision(2) << "Perimeter length = " << perimeter << std::endl;
    }
    return 0;
}
