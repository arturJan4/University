#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <limits>

using edge = std::pair<int, int>;        // pair <node, weight>
using edgesList = std::vector<edge>;    // adjacency list

int main()
{    
    int n, m;           // vertices & edges
    scanf("%d %d", &n, &m);

    // std::cout << sizeof(std::vector<edgesList>) + (sizeof(edgesList) * adjacency_list.size());
    std::vector<edgesList> adjacency_list(n);
    
    for(int i = 0; i < m; ++i)
    {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        --from; --to;
        adjacency_list[from].push_back(std::make_pair(to, weight));
        adjacency_list[to].push_back(std::make_pair(from, weight));
    }
    
    int answer = std::numeric_limits<int>::max();
    auto comparator = [](edge a, edge b) { return a.second < b.second; };
    std::priority_queue<edge, edgesList, decltype(comparator)> queue(comparator);
    queue.push(std::make_pair<int, int>(0, 0));     // start vertex
    bool* visited = new bool[n] {};                 // zero (false) initalized
    
    while(!queue.empty())
    {
        edge top = queue.top();
        queue.pop();
        int weight = top.second;
        
        int currentNode = top.first;
        if(visited[currentNode] == false)
        {
            visited[currentNode] = true;
            //std::cout << currentNode+1 << "-----\n";

            if(weight != 0)
                answer = std::min(weight, answer);      // minimum edge in MST is the answer

            for(edge e : adjacency_list[currentNode])
            {   
                //std::cout << e.first+1 << ", " << e.second <<  "\n";
                if(!visited[e.first])
                    queue.push(e);
            }
        }        
    }
    printf("%d", answer);

    return 0;
}