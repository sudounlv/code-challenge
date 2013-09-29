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

typedef std::vector<point> point_vector;

std::ostream& operator<< (std::ostream& out, const point& p)
{
    out << std::fixed << std::setprecision(1);
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

double distance(const point& p0, const point& p1)
{
    const double dx = p1.x - p0.x;
    const double dy = p1.y - p0.y;
    return std::sqrt(dx*dx + dy*dy);
}

double cross_direction(const point& a, const point& b, const point& c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

point centroid(const point& a, const point& b, const point& c)
{
    const double x = (a.x + b.x + c.x) / 3;
    const double y = (a.y + b.y + c.y) / 3;
    return point(x, y);
}

// Returns which quadrant b lies in relative to a.
// Choice of quadrant numbering is arbitrary - here upper left quadrant is zero.
int quadrant(const point& a, const point& b)
{
    const double dx = b.x - a.x;
    const double dy = b.y - a.y;
    if (dx < 0) // Left
    {
        if (dy < 0) // Bottom left
            return 3;
        else // Top left
            return 0;
    }
    else
    {
        if (dy < 0) // Bottom right
            return 2;
        else // Top right
            return 1;
    }
}

struct clockwise_comparator : public std::binary_function<point, point, bool>
{
    clockwise_comparator(point p) : a(p) { }
    
    // Returns true if c is clockwise from b with reference to a
    bool operator()(const point& b, const point& c)
    {
        int q_b = quadrant(a, b);
        int q_c = quadrant(a, c);
        
        if (q_b != q_c)
            return q_b < q_c;
        else
            // If we're in the same quadrant, check the cross product
            return cross_direction(a, b, c) < 0.0;
    }
    
    const point a;
};

bool compare_y(const point& a, const point& b)
{
    // Fall through to x comparison if y coords are equal
    if (a.y == b.y)
        return a.x < b.x;
    else
        return a.y < b.y;
}

// Reduce vector of points to its convex hull using Graham Scan
// Leave the interior points in the vector, after the hull points
size_t find_convex_hull(point_vector& points)
{
    size_t n = points.size();
    
    // With 3 or fewer points, all must be on the hull, so nothing to do
    if (n < 4)
        return n;
    
    // Swap the lowest point into the first position
    const point_vector::iterator lowest_pos = std::min_element(points.begin(), points.end(), compare_y);
    std::swap(*lowest_pos, points.front());
    const point lowest_point = points.front();
    
    // Sort points (except first) by angle from lowest point
    std::sort(points.begin() + 1, points.end(), clockwise_comparator(lowest_point));
    
    // Initialize stack with lowest point, largest angle point
    point_vector::iterator hull_back = points.begin() + 1;
    
    // Perform scan to determine whether points are on the hull
    for (point_vector::iterator it = points.begin() + 2; it <= points.end(); ++it)
    {
        point p;
        
        // In the last iteration, wrap around to the first point
        if (it == points.end())
            p = points.front();
        else
            p = *it;
        
        // If this point would produce a concavity with the current hull points, we need to
        // backtrack by discarding hull points until that is not the case. These discarded
        // points will be interior to the new hull which includes the current point.
        while (cross_direction(*(hull_back - 1), *hull_back, p) >= 0)
        {
            
            --hull_back; // Pop stack
            
            // The first point always remains on the hull
            if (hull_back == points.begin())
                break;
        }
        
        // Swap point into the hull stack, unless we've wrapped around
        if (it != points.end())
            std::swap(*(++hull_back), *it);
    }
    
    // Return number of points comprising the hull (now at front of vector).
    return hull_back - points.begin() + 1;
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
        
        // Run Graham Scan algorithm
        const size_t n_hull = find_convex_hull(points);
        
        const point_vector::iterator hull_end = points.begin() + n_hull;
        
        // Compute perimeter length from the convex hull
        double perimeter_length = 0.0;
        for (point_vector::const_iterator it = points.begin(); it < hull_end - 1; ++it)
        {
            perimeter_length += distance(*it, *(it + 1));
        }
        // Connect the last point to to the first
        perimeter_length += distance(points[n_hull - 1], points[0]);
        
        // Now handle points that are not on the convex hull, but are on the perimeter.
        if (n_hull < points.size())
        {
            // 1. Create a point p_center the hull by taking the centroid of any three hull points
            const point p_center = centroid(points[0], points[n_hull / 2], points[n_hull - 1]);
            
            // 2. Sort hull points and interior points, clockwise around p_center
            std::sort(points.begin(), hull_end, clockwise_comparator(p_center));
            std::sort(hull_end, points.end(), clockwise_comparator(p_center));
            
            // 3. Read the first two hull points. Scan through interior points until they are outside the
            //    triangle <p_center, h0, h1>. If any fall on the line h0h1, swap them to the front of the
            //    interior points list, Repeat until finished.
            
            // Start with last point on hull, which will be the last one in Q3
            point h0 = points[n_hull - 1];
            point h1;
            
            point_vector::iterator ip = hull_end; // Iterates through interior points
            point_vector::iterator perimeter_back = hull_end; // Back of perimeter points stack
            
            for (point_vector::const_iterator hp = points.begin(); hp <= hull_end; ++hp)
            {
                // Wrap h1 around to first point for last line
                if (hp == hull_end)
                    h1 = points.front();
                else
                    h1 = *hp;
                
                // Work on line h0->h1
                while (ip < points.end())
                {
                    point p = *ip;
                    // If p is in this slice, p should be right of p_center->h0 and left of p_center->h1
                    if (cross_direction(p_center, h0, p) <= 0.0 && cross_direction(p_center, h1, p) >= 0.0)
                    {
                        // Now check to see whether this is on the line h0->h1 or not
                        if (cross_direction(h0, h1, p) == 0.0)
                        {
                            // Add this point to the perimeter points stack
                            std::swap(*ip, *perimeter_back++);
                        }
                        ++ip;
                    }
                    else
                    {
                        // No more interior points in this slice; move to the next one
                        break;
                    }
                }
                
                // Shift h1 before advancing to next slice
                h0 = h1;
            }
            
            // Number of points on perimeter includes all hull points and non-hull perimeter points
            const size_t n_perim = perimeter_back - points.begin();
            
            // 4. Sort all the perimeter points clockwise around p_center
            std::sort(points.begin(), perimeter_back, clockwise_comparator(p_center));
            
            // 5. Shrink vector to contain only the perimeter
            points.resize(n_perim);
        }
        
        // Print region header
        std::cout << "Region #" << region_number << ":" << std::endl;
        
        // Print region perimeter
        for (point_vector::const_iterator it = points.begin(); it < points.end(); ++it)
        {
            std::cout << *it << "-";
        }
        std::cout << points.front() << std::endl;
        
        // Print the perimeter length
        std::cout << std::setprecision(2) << "Perimeter length = " << perimeter_length << std::endl;
    }
    return 0;
}
