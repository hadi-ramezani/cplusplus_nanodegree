#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    this->start_node =  &m_Model.FindClosestNode(start_x, start_y);
    this->end_node =  &m_Model.FindClosestNode(end_x, end_y);

}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*this->end_node);
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    current_node->visited = true;
    for (auto node: current_node->neighbors){
        if (node->visited == false) {
            node->parent = current_node;
            node->g_value = current_node->g_value + node->distance(*current_node);
            node->h_value = this->CalculateHValue(node);
            this->open_list.push_back(node);
            node->visited = true;
        }
    }
}


RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(this->open_list.begin(), this->open_list.end(), RouteModel::Node::Compare);
    auto n = this->open_list.back();
    this->open_list.pop_back();
    return n;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    path_found.push_back(*current_node);

    // TODO: Implement your solution here.
    while (current_node->distance(*this->start_node) > 0)
    {
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
        path_found.push_back(*current_node);
    }
    std::reverse(path_found.begin(), path_found.end());
    
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.
    current_node = this->start_node;
    while (current_node->distance(*this->end_node) > 0)
    {
        this->AddNeighbors(current_node);
        current_node = NextNode();
    }
    this->m_Model.path = this->ConstructFinalPath(current_node);
}