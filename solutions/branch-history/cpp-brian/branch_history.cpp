#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <set>

struct commit
{
    commit() {}
    commit(int index, std::string& message, int p1, int p2)
        : index(index), message(message)
    {
        parents[0] = p1;
        parents[1] = p2;
    }
    int index;
    int parents[2];
    std::string message;
};

int main (int argc, char *argv[])
{
    if (argc != 2)
        exit(1);
    
    std::string target_ref(argv[1]);
    std::string line;
    
    int n_commits, n_refs;
    
    std::getline(std::cin, line);
    std::istringstream(line) >> n_commits;
    
    std::vector<commit> commits(n_commits);
    
    for (int i=0; i < n_commits; i++)
    {
        int p1, p2;
        std::getline(std::cin, line);
        if (std::sscanf(line.c_str(), "%d %d", &p1, &p2) != 2)
            exit(1);
        std::getline(std::cin, line);
        commits[i] = commit(i, line, p1, p2);
        std::getline(std::cin, line);
        if (line.length() != 0)
            exit(1);
    }
    
    std::getline(std::cin, line);
    std::istringstream(line) >> n_refs;
    
    std::map<std::string, int> refs;
    
    for (int i=0; i < n_refs; i++)
    {
        int index;
        char name_buf[line.length()];
        std::getline(std::cin, line);
        if (std::sscanf(line.c_str(), "%s %d", name_buf, &index) != 2)
            exit(1);
        refs[std::string(name_buf)] = index;
    }
    
    int start_index = refs[target_ref];
    
    // Note: std::set is internally ordered and so can be used as a priority
    // queue with unique elements. This is all that's needed for DAG traversal.
    //
    // However, here I'm using both a pqueue and a set to track all the discovered
    // nodes. This "textbook" breadth-first traversal can handle general digraphs
    // (with cycles), not only DAGs.
    
    std::priority_queue<int> open_nodes;
    std::set<int> discovered_nodes;
    
    open_nodes.push(start_index);
    
    while (!open_nodes.empty())
    {
        commit &c = commits[open_nodes.top()];
        open_nodes.pop();
        std::cout << c.message << std::endl;
        for (int i=0; i < 2; i++)
        {
            int p = c.parents[i];
            if (p != -1 && discovered_nodes.find(p) == discovered_nodes.end())
            {
                open_nodes.push(p);
                discovered_nodes.insert(p);
            }
        }
    }
    
    return 0;
}