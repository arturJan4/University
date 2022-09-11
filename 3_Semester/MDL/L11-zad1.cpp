#include <iostream>
#include <vector>
#include <string>

class Graph
{
    private:
        int numOfVertices;
        std::vector<std::vector<int>> edges;
    public:
    Graph(int numOfVertices)
    {
        this->numOfVertices = numOfVertices;

		this->edges.resize(numOfVertices, std::vector<int>(numOfVertices, 0));
    }

    void add_edge(int from, int to)
    {
        this->edges[from][to] += 1;
    }

    void remove_edge(int from, int to)
    {
        this->edges[from][to] -= 1;
    }

    std::string toString()
    {
        std::string s =  "";
        for(int i = 0; i < numOfVertices; ++i)
        {
            for(int j = 0; j < numOfVertices; ++j)
            {
                s += std::to_string(edges[i][j]);    
            }
            s += '\n';
        }
        return s;
    }

    int findSource()
    {
        int candidate = 0;
        for(int i = 2; i < numOfVertices; ++i)
        {
            if(edges[candidate][i] == 0)
            {
                candidate = i;
            }
        }

        for(int i = 2; i < candidate; ++i)
        {
            if(edges[candidate][i] == 0)
                return -1;
        }

        for(int i = 0; i < numOfVertices; ++i)
        {
            if(edges[i][candidate] != 0)
                return -1;
        }
        return candidate;
    }
};

int main(int argc, char const *argv[])
{
    Graph g = Graph(5);

    g.add_edge(0,1);
    g.add_edge(0,3);
    g.add_edge(0,4);
    
    g.add_edge(1,3);

    g.add_edge(2,0);
    g.add_edge(2,1);
    g.add_edge(2,3);
    g.add_edge(2,4);

    g.add_edge(3,4);

    g.add_edge(4,1);
     
    // sprawdzanie nie dziala - [i][i]
    std::cout << g.toString();
    std::cout << g.findSource();
    return 0;
}
