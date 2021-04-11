#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

int connectivity(vector<vector<int>> edge)
{
	int n = edge.size();
	vector<int> dist = BFS(0, edge);
	for (int i = 1; i < n; i++) if (dist[i] < 1) return 0;
	return 1;
}

int Isolated_Is(vector<vector<int>> edge)
{
	int n = edge.size();
	for (int i = 0; i < n; i++) if (!edge[i].size()) return 1;
	return 0;
}

int diameter(vector<vector<int>> edge)
{
	int n = edge.size();
	vector<int> dist;
	int diam = 0, temp;
	if (!connectivity(edge)) return -1;
	for (int i = 0; i < n; i++) {
		dist = BFS(0, edge);
		temp = int(*max_element(dist.begin(), dist.end()));
		diam = max(temp, diam);
	}
	return diam;
}

int main()
{
    cout << "Hello" << endl;
    return 0;
}