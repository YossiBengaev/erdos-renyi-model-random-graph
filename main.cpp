#include <iostream>
#include <vector>
#include <queue>
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

vector<int> BFS(int v, vector<vector<int>> edge)
{
	int u, i, n = edge.size();
	vector<int> dist(n, 0);
	vector<bool> visited(n, false);
	queue<int> q;
	visited[v] = 1;
	q.push(v);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (i = 0; i < edge[u].size(); i++) {
			if (visited[edge[u][i]] == 0) {
				visited[edge[u][i]] = 1;
				dist[edge[u][i]] += dist[u] + 1;
				q.push(edge[u][i]);
			}
		}
	}
	return dist;
}

int main()
{
    cout << "Hello" << endl;
    return 0;
}