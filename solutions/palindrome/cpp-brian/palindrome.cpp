#include <iostream>
#include <string>

using std::string;

int main(int argc, char **argv)
{
    string line;
    line.reserve(1024);
    
    while (!std::cin.eof())
    {
        // Read a line of input
        std::getline(std::cin, line);
        
        // Skip blank lines
        if (line.length() == 0)
            continue;
        
        // Remove non-alpha chars and convert to lowercase
        string::iterator p0 = line.begin();
        for (string::const_iterator p1 = line.begin(); p1 < line.end(); ++p1)
        {
            const char c = tolower(*p1);
            if ('a' <= c && c <= 'z')
                *(p0++) = c;
        }        
        line.resize(p0 - line.begin());
        
        const int n = line.length();

        // Check palindrome-ness
        bool palindrome = true;
        for (int i=0; i < n / 2; i++)
        {
            if (line[i] != line[n - i - 1])
            {
                palindrome = false;
                break;
            } 
        }

        // Print result
        std::cout << (palindrome ? "Yes" : "No") << std::endl;
    }
    
    return 0;
}
