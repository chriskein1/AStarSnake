#ifndef GRAPH_H
#define GRAPH_H

#include "Global.h"
#include "Snake.h"
#include "Fruit.h"
#include <vector>
#include <queue>
#include "SFML/Graphics.hpp"

class Snake;
class Fruit;

struct Node {
	int g_cost;
	int h_cost;
	int x;
	int y;
	Node* previous;
};

class Graph {
private:
	std::vector<sf::Vector2i> body_locations;
	std::vector<Node*> open;
	std::vector<Node*> closed;
	std::queue<int> shortest_path;
	int CalculateH(Node *start, Node *end);
	static bool CompareNodes(Node* a, Node* b);
	void AddNeighbors(Node* current_node);
	bool InClosed(Node* current_node);
	bool InOpen(Node* current_node);

public:
	void SetGraph(Snake& snake, Fruit& fruit);
	std::queue<int> GetShortestPath();
	void ClearNodes();
	~Graph();
};

#endif