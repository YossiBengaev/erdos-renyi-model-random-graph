#include <iostream>
#include <vector>
using namespace std;

int probabilityOfAddingEdgeToGraph(double p)
{
	double r = ((double)rand() / (RAND_MAX)); // Get random number
	return p > r;
}

void addEdge(int a, int b, vector<vector<int>> &edge)
{
	edge[a].push_back(b);
	edge[b].push_back(a);
}

vector<vector<int>> graph_random_build(int n, double p)
{
	int i, j, maxEdges = p * (n * (n - 1) / 2), countEdges = 0;
	vector<vector<int>> edge(n, vector<int>());
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			if (countEdges == maxEdges)
				return edge;
			if (probabilityOfAddingEdgeToGraph(p)) {
				addEdge(i, j, edge);
				countEdges++;
			}
		}
	}
	return edge;
}

int main()
{
    vector<vector<int>> edge = graph_random_build(5, 0.3);
    return 0;
}