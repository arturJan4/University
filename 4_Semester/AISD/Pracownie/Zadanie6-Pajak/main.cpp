#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

using edge = std::pair<int, int>;        // pair <node, weight>
using edgesList = std::vector<edge>;    // adjacency list

void addEdge(std::vector<edgesList> &adj_list, int from, int to, int weight)
{
    --from; --to;
    adj_list[from].push_back(std::make_pair(to, weight));
    adj_list[to].push_back(std::make_pair(from, weight));
}

int solution(const std::vector<edgesList> &adj_list, int n)
{
    
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

            for(edge e : adj_list[currentNode])
            {   
                //std::cout << e.first+1 << ", " << e.second <<  "\n";
                if(!visited[e.first])
                    queue.push(e);
            }
        }        
    }
    return answer;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    size_t n, m;           // vertices & edges
    std::cin >> n >> m;

    std::vector<edgesList> adjacency_list(n);
    // std::cout << sizeof(std::vector<edgesList>) + (sizeof(edgesList) * adjacency_list.size());

    for(size_t i = 0; i < m; ++i)
    {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        addEdge(adjacency_list, from, to, weight);
    }

    std::cout << solution(adjacency_list, n);
    
    return 0;
}