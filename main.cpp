#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

int probabilityOfAddingEdgeToGraph(double p) // Function for get a random probability for adding or not to the graph's edge
{
	double r = ((double)rand() / (RAND_MAX)); // Get random number
	return p > r;
}

void addEdge(int a, int b, vector<vector<int>> &edge) // Function for adding edge to the graph
{
	edge[a].push_back(b);
	edge[b].push_back(a);
}

vector<vector<int>> graph_random_build(int n, double p) // Function for building a random graph
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

 /* Function that check if graph is connectivity by running one time BFS and check the vector distance */
int connectivity(vector<vector<int>> edge) 
{
	int n = edge.size();
	vector<int> dist = BFS(0, edge);
	for (int i = 1; i < n; i++) if (dist[i] < 1) return 0; 
	/* We will get dist[i]<1 this means that there is no path from the start vertex to the same vertex -> not connectivity*/
	return 1;
}

 /* Function that check if every vertex in the garph is isolated */
int Isolated_Is(vector<vector<int>> edge)
{
	int n = edge.size();
	for (int i = 0; i < n; i++) if (!edge[i].size()) return 1; // If the vector's size is 0 this means that the vertex is isolated
	return 0;
}

/* */
int diameter(vector<vector<int>> edge)
{
	int n = edge.size();
	vector<int> dist;
	int diam = 0, temp;
	if (!connectivity(edge)) return -1; // If the graph is not connectivity return -1
	for (int i = 0; i < n; i++) { // for each vertex run BFS and save the max distance
		dist = BFS(0, edge); 
		temp = int(*max_element(dist.begin(), dist.end()));
		diam = max(temp, diam);
	}
	return diam;
}

void checkConnectivity(double arr[], int n, double threshold1and3)
{
    fstream fout;
    fout.open("reportRandomGraphAttributes.csv", ios::out | ios::app);
	vector<vector<int>> edge;
	int success, fails;
	for (int i = 0; i < 10; i++) {
    	success = 0, fails = 0;
		for (int j = 0; j < 500; j++) {
			edge = graph_random_build(n, arr[i]);
			if (arr[i] < threshold1and3) {
				if (connectivity(edge)) {
					fails++;
				} else {
					success++;
				}
			}
			else {
				if (!connectivity(edge)) {
					fails++;
				} else {
					success++;
				}
			}
		}
        fout << "Work=" << success << ", fails=" << fails << "\t";
	}
	fout << "\n";
    fout.close();
}

void checkIsolated_Is(double arr[], int n, double threshold1and3)
{
	fstream fout;
    fout.open("reportRandomGraphAttributes.csv", ios::out | ios::app);
	vector<vector<int>> edge;
	int work, fails;
	for (int i = 0; i < 10; i++) {
		work = 0, fails = 0;
		for (int j = 0; j < 500; j++) {
			edge = graph_random_build(n, arr[i]);
			if (arr[i] < threshold1and3) {
				if (!Isolated_Is(edge)) {
					fails++;
				} else {
					work++;
				}
			}
			else {
				if (Isolated_Is(edge)) {
					fails++;
				} else {
					work++;
				}
			}
		}
        fout << "Work=" << work << ", fails=" << fails << "\t";
	}
	fout << "\n";
    fout.close();
}

void checkDiameter(double arr[], int n, double threshold2)
{
	fstream fout;
    fout.open("reportRandomGraphAttributes.csv", ios::out | ios::app);
	vector<vector<int>> edge;
	int work, fails;
	for (int i = 0; i < 10; i++) {
		work = 0, fails = 0;
		for (int j = 0; j < 500; j++) {
			edge = graph_random_build(n, arr[i]);
			if (arr[i] > threshold2) {
				if (diameter(edge) != 2) {
					fails++;
				} else {
					work++;
				}
			}
			else {
				if (diameter(edge) <= 2) {
					fails++;
				} else {
					work++;
				}
			}
		}
        fout << "Work=" << work << ", fails=" << fails << "\t";
	}
	fout.close();
}

int main()
{
    /* Variable Settings */
	int n = 1000;
	double arr[10] = { 0.06, 0.062, 0.064, 0.066, 0.068, 0.072, 0.074, 0.076, 0.078, 0.08 };
	double arr2[10] = { 0.09, 0.095, 0.1, 0.105, 0.11, 0.115, 0.12, 0.125, 0.13, 0.35 };
	double threshold1and3 = log(n) / n;
	double threshold2 = sqrt(2 * log(n) / n);

	/* Random number settings */
	srand(time(NULL));

    /* Build connectivity and Isolated_Is table in csv file */
    fstream fout;
    fout.open("reportRandomGraphAttributes.csv", ios::out | ios::app);
    for (int i = 0; i < 10; i++) {
        fout << arr[i] << "\t\t\t\t";
    }
    fout << "\n\n\n";
    fout.close();

	/* Functions for random graph attributes testing on connectivity and isolated */
	checkConnectivity(arr, n, threshold1and3);
	checkIsolated_Is(arr, n, threshold1and3);

    /* Build diameter table in csv file */
	fout;
    fout.open("reportRandomGraphAttributes.csv", ios::out | ios::app);
    for (int i = 0; i < 10; i++) {
        fout << arr2[i] << "\t\t\t\t";
    }
    fout << "\n";
    fout.close();

	/* Functions for random graph attributes testing on diameter*/
	checkDiameter(arr2, n, threshold2);
    return 0;
}
