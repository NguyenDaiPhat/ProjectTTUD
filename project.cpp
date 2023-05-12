#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
struct Point
{
    double x;
    double y;
    void setXY(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

double Distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    int n;
    cin >> n;
    vector<Point> M;
    vector<vector<Point>> Dis;
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        Point point;
        point.setXY(x, y);
        M.push_back(point);
    }
    // for (auto i : M)
    // {
    //     cout << i.x << " " << i.y;
    //     cout << endl;
    // }
    return 0;
}