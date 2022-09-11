#include "weighted_graph.hpp"

bool Weighted_graph::has_edge(const std::list<edge> &edges, int dest_idx)
{
    for (const edge& e : edges)
    {
        if (e.destination_idx == dest_idx)
            return true;
    }
    return false;
}

bool Weighted_graph::exists_edge(int idx_s, int idx_d)
{
    if (!idx_set.contains(idx_s) || !idx_set.contains(idx_d))
        throw std::invalid_argument("Invalid indexes of an edge");

    return has_edge(adj_list[idx_s], idx_d) && has_edge(adj_list[idx_d], idx_s);
}

bool Weighted_graph::find_path(int idx_src, int idx_dst)
{
    std::stack<int> nodes_stack;
    std::vector<bool> visited(max_id);

    nodes_stack.push(idx_src);
    visited[idx_src] = true;

    while(!nodes_stack.empty())
    {
        int cur = nodes_stack.top();
        visited[cur] = true;
        nodes_stack.pop();

        if (cur == idx_dst)
            return true;

        for (auto& edge : adj_list[cur])
        {
            int dest = edge.destination_idx;
            if (!visited[dest])
            {
                nodes_stack.push(dest);
            }
        }
    }

    return false;
}


Weighted_graph::Weighted_graph(std::initializer_list<std::string> nodes,
               std::initializer_list<std::tuple<std::string, std::string, double>> edges)
{
    for (auto& node : nodes)
    {
        add_node(node);
    }

    for (auto& [src, dest, weight] : edges)
    {
        add_edge(src, dest, weight);
    }
}

void Weighted_graph::add_node(const std::string& name)
{
    if (keyset.contains(name))
    {
        std::cerr << "key of name " << name << " already exists!";
        return;
    }

    int new_idx = this->max_id + 1;
    name_to_idx[name] = new_idx;
    idx_to_name[new_idx] = name;
    adj_list[new_idx] = {};

    keyset.insert(name);
    idx_set.insert(new_idx);

    this->max_id = new_idx;
}

void Weighted_graph::add_edge(const std::string& node_src, const std::string& node_dest, double weight)
{
    if(!keyset.contains(node_src) || !keyset.contains(node_dest))
        throw std::invalid_argument("nodes of those names aren't present in the graph");

    int idx_s = name_to_idx[node_src];
    int idx_d = name_to_idx[node_dest];

    if (exists_edge(idx_s, idx_d) || exists_edge(idx_d, idx_s))
    {
        std::cerr << "edge from " << node_src << " to " << node_dest << " already exists!";
        return;
    }


    adj_list[idx_s].push_back({idx_d, weight});
    adj_list[idx_d].push_back({idx_s, weight});
}

bool Weighted_graph::delete_node(const std::string& name)
{
    if (!keyset.contains(name))
    {
        std::cerr << "key of name " << name << " doesn't exist!";
        return false;
    }

    int idx = name_to_idx[name];

    // delete edges
    for (auto& node : adj_list)
    {
        auto& edges = node.second;
        edges.erase(std::remove_if(edges.begin(),
                                   edges.end(),
                                   [&](edge cur) {return idx == cur.destination_idx;}) ,
                    edges.end());
    }


    // internal cleaning
    name_to_idx.erase(name);
    idx_to_name.erase(idx);
    adj_list.erase(idx);
    keyset.erase(name);
    idx_set.erase(idx);

    return true;
}

void Weighted_graph::delete_edge(const std::string& node_src, const std::string& node_dest)
{
    if(!keyset.contains(node_src) || !keyset.contains(node_dest))
        throw std::invalid_argument("nodes of those names aren't present in the graph");

    int idx_s = name_to_idx[node_src];
    int idx_d = name_to_idx[node_dest];

    if (!exists_edge(idx_s, idx_d) || !exists_edge(idx_d, idx_s))
    {
        std::cerr << "edge from " << node_src << " to " << node_dest << " doesn't exist!";
        return;
    }

    adj_list[idx_s].remove_if([&](edge cur) {return idx_d == cur.destination_idx;});
    adj_list[idx_d].remove_if([&](edge cur) {return idx_s == cur.destination_idx;});
}

void Weighted_graph::change_weight(const std::string& node_src, const std::string& node_dest, double weight)
{
    this->delete_edge(node_src, node_dest);
    add_edge(node_src, node_dest, weight);
}

void Weighted_graph::print_path(const std::string& node_src, const std::string& node_dest)
{
    if(!keyset.contains(node_src) || !keyset.contains(node_dest))
        throw std::invalid_argument("nodes of those names aren't present in the graph");

    int idx_s = name_to_idx[node_src];
    int idx_d = name_to_idx[node_dest];

    if(find_path(idx_s, idx_d))
        std::cout << "Path between " << node_src << " and " << node_dest << " does exist!\n";
    else
        std::cout << "Path between " << node_src << " and " << node_dest << " doesn't exist!\n";
}

void Weighted_graph::print()
{
    for (auto& [idx, edges] : adj_list)
    {
        std::cout << "[" << idx_to_name[idx] << "]: ";

        for (auto& [dest_idx, weight] : edges)
        {
            std::cout << "(" << idx_to_name[dest_idx] << ", w=" << weight << "), ";
        }
        std::cout << "\n";
    }
}
