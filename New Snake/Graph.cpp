#include "Graph.h"
#include "SFML/Graphics.hpp"
#include <algorithm>
#include <iostream>

void Graph::SetGraph(Snake &snake, Fruit &fruit) {

	
	// Initialization
	sf::Vector2i head_location(snake.GetHeadLocation().x / TILE_SIZE, snake.GetHeadLocation().y / TILE_SIZE);

	body_locations.clear();

	for (int i = 0; i < snake.GetSize() - 1; i++) {
		sf::Vector2i body_location(snake.GetBodyLocation(i).x / TILE_SIZE, snake.GetBodyLocation(i).y / TILE_SIZE);
		body_locations.push_back(body_location);
	}

	sf::Vector2i fruit_location(fruit.GetLocation().x / TILE_SIZE, fruit.GetLocation().y / TILE_SIZE);

	Node* start_location = new Node{  0, 0, head_location.x, head_location.y, nullptr };

	Node* end_location = new Node{ 0, 0, fruit_location.x, fruit_location.y, nullptr };
	start_location->h_cost = CalculateH(start_location, end_location);
	open.push_back(start_location);

	std::cout << "Start Node: (" << start_location->x << ", " << start_location->y << ')' << std::endl;
	std::cout << "Target Node: (" << end_location->x << ", " << end_location->y << ')' << std::endl;

	// AStar algorithm
	// Pseudocode by Sebastian Lague
	while (!open.empty()) {
		// Sort the Open vector by comparing f cost (g + h)
		std::sort(open.begin(), open.end(), CompareNodes);
		Node* current_node = open.front();
		std::cout << "Current Node: (" << current_node->x << ", " << current_node->y << ')' << std::endl;
		closed.push_back(current_node);
		// remove front of Open
		open.erase(open.begin());

		// Check if current node is the goal
		if (current_node->x == end_location->x && current_node->y == end_location->y) {
			return; // Stop algorithm
		}

		// Add neighbors
		AddNeighbors(current_node);

		// Calculate costs
		for (int i = 0; i < open.size(); i++) {
			Node* neighbor = open[i];

			if (InClosed(neighbor)) {
				delete neighbor;
				continue;
			}


			if (current_node->g_cost + 1 < neighbor->g_cost || !InOpen(neighbor)) {
				neighbor->h_cost = CalculateH(neighbor, end_location);
				neighbor->g_cost = current_node->g_cost + 1; // Cost increases by 1
				neighbor->previous = current_node;
				if (!InOpen(neighbor)) {
					open.push_back(neighbor);
				}
			}
		}
	}
}

// Using Manhattan Distance
// 1) It is computationally the fastest
// 2) Diagonal moves in the traditional sense are not possible
int Graph::CalculateH(Node* start, Node* end) {
	return abs(start->x - end->x) + abs(start->y - end->y);
}

// Add a neighbor by shifting the x / y accordingly
void Graph::AddNeighbors(Node* current_node) {
	if (current_node->x > 0) {
		Node* shift_left = new Node;
		shift_left->x = current_node->x - 1;
		shift_left->y = current_node->y;

		if (!InClosed(shift_left) && !InOpen(shift_left)) {
			open.push_back(shift_left);
			shift_left->previous = current_node;
		}
		else {
			delete shift_left;
		}
	}
	if (current_node->x < BOARD_SIZE - 1) {
		Node* shift_right = new Node;
		shift_right->x = current_node->x + 1;
		shift_right->y = current_node->y;

		if (!InClosed(shift_right) && !InOpen(shift_right)) {
			open.push_back(shift_right);
			shift_right->previous = current_node;

		}
		else {
			delete shift_right;
		}
	}
	if (current_node->y > 1) {
		Node* shift_up = new Node;
		shift_up->x = current_node->x;
		shift_up->y = current_node->y - 1;

		if (!InClosed(shift_up) && !InOpen(shift_up)) {
			open.push_back(shift_up);
			shift_up->previous = current_node;
		}
		else {
			delete shift_up;
		}
	}
	if (current_node->y < BOARD_SIZE) {
		Node* shift_down = new Node;
		shift_down->x = current_node->x;
		shift_down->y = current_node->y + 1;

		if (!InClosed(shift_down) && !InOpen(shift_down)) {
			open.push_back(shift_down);
			shift_down->previous = current_node;
		}
		else {
			delete shift_down;
		}
	}
}

bool Graph::CompareNodes(Node* a, Node* b) {
	return (a->g_cost + a->h_cost) > (b->g_cost + b->h_cost);
}

bool Graph::InClosed(Node* current_node) {
	for (int i = 0; i < closed.size(); i++) {
		if (closed[i]->x == current_node->x && closed[i]->y == current_node->y) {
			return true;
		}
	}
	return false;
}

bool Graph::InOpen(Node* current_node) {
	for (int i = 0; i < open.size(); i++) {
		if (open[i]->x == current_node->x && open[i]->y == current_node->y) {
			return true;
		}
	}
	return false;
}

std::queue<int> Graph::GetShortestPath() {

	Node* current_node = closed.back();
	Node* previous_node = current_node->previous;

	while (previous_node != nullptr) {
		if (previous_node->y > current_node->y) {
			shortest_path.push(1); // Up
			std::cout << "Up\n";
		}
		else if (previous_node->y < current_node->y) {
			shortest_path.push(2); // Down
			std::cout << "Down\n";

		}
		else if (previous_node->x > current_node->x) {
			shortest_path.push(3); // Left
			std::cout << "Left\n";

		}
		else if (previous_node->x < current_node->x) {
			shortest_path.push(4); // Right
			std::cout << "Right\n";

		}
		current_node = previous_node;
		previous_node = current_node->previous;
	}
	return shortest_path;
}

void Graph::ClearNodes() {
	// Free memory in open vector
	for (Node* node : open) {
		delete node;
	}
	open.clear();

	// Free memory in closed vector
	for (Node* node : closed) {
		delete node;
	}
	closed.clear();

	while (!shortest_path.empty()) {
		shortest_path.pop();
	}

	body_locations.clear();
}

// Destructor to clear dynamically allocated memory
Graph::~Graph() {
	ClearNodes();
}