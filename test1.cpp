#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int n, a[N][N], path[N];

// Nearest Neighbor heuristic
void generateInitialSolution()
{
    path[1] = 1;
    vector<int> unused(n - 1);
    for (int i = 2; i <= n; ++i)
        unused[i - 2] = i;
    for (int i = 2; i <= n; ++i)
    {
        int minDist = INT_MAX, nearest;
        for (int j = 0; j < unused.size(); ++j)
        {
            int dist = a[path[i - 1]][unused[j]];
            if (dist < minDist)
            {
                minDist = dist;
                nearest = unused[j];
            }
        }
        path[i] = nearest;
        unused.erase(find(unused.begin(), unused.end(), nearest));
    }
}

// Calculate the total distance of a path
int calculatePathLength(int *path)
{
    int len = 0;
    for (int i = 1; i < n; ++i)
        len += a[path[i]][path[i + 1]];
    len += a[path[n]][path[1]];
    return len;
}

// 2-opt local search algorithm
void localSearch(int *path)
{
    bool improved = true;
    while (improved)
    {
        improved = false;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                int new1 = a[path[i - 1]][path[j]] + a[path[i]][path[j + 1]];
                int old1 = a[path[i - 1]][path[i]] + a[path[j]][path[j + 1]];
                int distDiff = new1 - old1; // new
                                            // old
                if (distDiff < 0)
                {
                    reverse(path + i, path + j + 1);
                    improved = true;
                }
            }
        }
    }
}

// Main function
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];

    // Generate initial solution using Nearest Neighbor heuristic
    generateInitialSolution();

    // Local search to optimize the solution
    localSearch(path);

    // Print the optimized solution
    cout << calculatePathLength(path) << endl;
    for (int i = 1; i <= n; ++i)
        cout << path[i] << " ";
    cout << endl;
    cout << path[0];
    return 0;
}
