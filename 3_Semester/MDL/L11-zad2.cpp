#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>

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

    void topologicalSortDFS(int v, bool visited[], std::stack<int> &Stack)
    {
        visited[v] = true;
    
        for(int i = 0; i < this->numOfVertices; ++i)
        {   
            if(edges[v][i] == 0)
                continue;
            if(!visited[i])
                topologicalSortDFS(i, visited, Stack);
        }
    
        Stack.push(v);
    }
    
    void topologicalSort()
    {
        std::stack<int> Stack;
    
        bool *visited = new bool[this->numOfVertices];
        for (int i = 0; i < this->numOfVertices; i++)
            visited[i] = false;
    
        for (int i = 0; i < this->numOfVertices; i++)
            if (visited[i] == false)
                topologicalSortDFS(i, visited, Stack);
    
        while (Stack.empty() == false)
        {
            std::cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

int main(int argc, char const *argv[])
{
    Graph g = Graph(8);
    
    g.add_edge(0,2);

    g.add_edge(1,0);

    g.add_edge(2,4);
    g.add_edge(2,3);
    g.add_edge(2,7);

    g.add_edge(4,5);
    g.add_edge(4,6);

    g.add_edge(7,6);

    std::cout << g.toString();
    g.topologicalSort();
    return 0;
}
