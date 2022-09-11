#ifndef LISTA5_WEIGHTED_GRAPH_HPP
#define LISTA5_WEIGHTED_GRAPH_HPP
#include <list>
#include <iostream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <stack>

class Weighted_graph
{
private:
    struct edge
    {
        int destination_idx;
        double weight;
    };

    // max idx given to a node (never decreasing)
    int max_id = 0;

    // we want to sync those 2 to have bi-directional map
    std::unordered_map<std::string, int> name_to_idx;
    std::unordered_map<int, std::string> idx_to_name;

    std::set<std::string> keyset; // node names already in use
    std::set<int> idx_set;        // idx's for those names that are in use (after deletion we may have less than max_id)

    std::unordered_map<int, std::list<edge>> adj_list; // graph representation

    // check whether edges has an edge with idx=dest_idx
    bool has_edge(const std::list<edge> &edges, int dest_idx);
    // check where there exists and edge between idx_s, idx_d
    bool exists_edge(int idx_s, int idx_d);
    // check if there exists any path between idx_src and idx_dest
    bool find_path(int idx_src, int idx_dst);

public:
    Weighted_graph() = default;

    Weighted_graph(std::initializer_list<std::string> nodes,
                   std::initializer_list<std::tuple<std::string, std::string, double>> edges);

    void add_node(const std::string& name);
    void add_edge(const std::string& node_src, const std::string& node_dest, double weight);

    bool delete_node(const std::string& name); // delete node and associated edges (from and to given node)
    void delete_edge(const std::string& node_src, const std::string& node_dest);

    void change_weight(const std::string& node_src, const std::string& node_dest, double weight);

    void print_path(const std::string& node_src, const std::string& node_dest);
    void print();

    ~Weighted_graph() = default;
};


#endif //LISTA5_WEIGHTED_GRAPH_HPP
