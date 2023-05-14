#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX = 1005;
int n;
double dist[MAX][MAX];
vector<int> path;

// Tìm người láng giềng gần nhất chưa được thăm
int find_nearest(int curr, vector<bool> &visited)
{
    int nearest = -1;
    double min_dist = 1e9;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i] && dist[curr][i] < min_dist)
        {
            nearest = i;
            min_dist = dist[curr][i];
        }
    }
    return nearest;
}

// Tìm đường đi tốt nhất bằng giải thuật nearest neighbor
void find_path(int start)
{
    path.push_back(start);
    vector<bool> visited(n + 1, false);
    visited[start] = true;
    int curr = start;
    for (int i = 1; i < n; i++)
    {
        int next = find_nearest(curr, visited);
        visited[next] = true;
        path.push_back(next);
        curr = next;
    }
}

// Tính độ dài đường đi
double compute_distance()
{
    double distance = 0;
    for (int i = 1; i < n; i++)
    {
        distance += dist[path[i - 1]][path[i]];
    }
    distance += dist[path[n - 1]][path[0]];
    return distance;
}

int main()
{
    // Nhập vào số đỉnh và ma trận khoảng cách
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> dist[i][j];
        }
    }
    // Tìm đường đi tốt nhất
    find_path(1);
    // Tính độ dài đường đi và in kết quả
    double distance = compute_distance();
    cout << "Path: ";
    for (int i = 0; i < n; i++)
    {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Distance: " << distance << endl;
    return 0;
}
