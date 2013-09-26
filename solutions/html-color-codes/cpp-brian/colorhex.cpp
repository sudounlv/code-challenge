// Solution to the UNLV Sudo HTML Color Codes problem
// Brian Kauke <kaukeb@gmail.com>, September 2013

#include <iostream>
#include <cstdio>
#include <cassert>
#include <map>
#include <stdexcept>

#include "htmlcolors.h"

int line_number = 0;

void err_bad_input(std::string reason)
{
    std::cout << "Bad input on line number " << line_number;
    if (reason.length() > 0)
        std::cout << " (" << reason << ")";
    std::cout << "." << std::endl;
    exit(1);
}

void err_bad_input()
{
    err_bad_input("");
}

bool is_lowercase_letter(char c) { return 97 <= c && c <= 122; }

bool is_uppercase_letter(char c) { return 65 <= c && c <= 90; }

bool is_digit(char c) { return 48 <= c && c <= 57; }

int main(int argc, char **argv)
{
    std::string input_line;
    int r, g, b;
    // Array to iterate through components
    int * const comp[3] = { &r, &g, &b };
    // Map for HTML color name lookup
    typedef const unsigned char * rgb_triplet;
    std::map<std::string, rgb_triplet> html_colors;
    
    // Initialize color name map
    for (int i=0; i < n_colors; i++)
    {
        html_colors[std::string(color_names[i])] = color_values[i];
    }
    
    while (std::getline(std::cin, input_line))
    {
        ++line_number;
        
        // Skip blank lines
        if (input_line.length() == 0)
            continue;
        
        // Determine whether this is a name or a numeric specification
        // by inspecting the first character on the line.
        if (is_lowercase_letter(input_line[0]) || is_uppercase_letter(input_line[0]))
        {
            std::string color_name(input_line);
            
            // First convert name to lower-case
            for (int i=0; i < color_name.length(); i++)
                color_name[i] = tolower(color_name[i]);
            
            // Look up color by name
            rgb_triplet color;
            try
            {
                color = html_colors.at(color_name);
            }
            catch (std::out_of_range)
            {
                err_bad_input("unknown color name");
            }
            
            // Set RGB values
            for (int i=0; i < 3; i++)
                *comp[i] = color[i];
        }
        else if (is_digit(input_line[0]))
        {
            // Parse numbers
            if (std::sscanf(input_line.c_str(), "%d %d %d", &r, &g, &b) != 3)
                err_bad_input();
            
            // Make sure numbers are between 0 and 255 inclusive
            for (int i=0; i < 3; i++)
                if (!(0 <= *comp[i] && *comp[i] <= 255))
                    err_bad_input("number out of range");
        }
        else
        {
            err_bad_input();
        }
        
        // Output hex code
        std::printf("#%02X%02X%02X\n", r, g, b);
    }
    
    return 0;
}
