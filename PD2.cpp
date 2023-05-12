#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
struct Point // định nghĩa một điểm
{
    double x;
    double y;
    void setXY(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double distance(Point a)
    {
        return sqrt((this->x - a.x) * (this->x - a.x) + (this->y - a.y) * (this->y - a.y));
    }
};

struct Order // định nghĩa một đơn hàng
{
    Point pickup;
    Point delivery;
    double weight;
    void setOrder(double x1, double y1, double x2, double y2, double weight)
    {
        pickup.setXY(x1, y1);
        delivery.setXY(x2, y2);
        this->weight = weight;
    }
};

// void printOrders(vector<Order> orders){
//     for (int i = 0; i < orders.size(); i++)
//     {
//         cout << orders[i].pickup.x << " " << orders[i].pickup.y << " " << orders[i].delivery.x << " " << orders[i].delivery.y << " " << orders[i].weight;
//         cout << endl;
//     }
// }

int main(int argc, char *agrv[])
{
    ifstream inFile;
    inFile.open();
    int n, w;
    cin >> n >> w;
    vector<Order> orders;             // vector chứa tất cả các đơn hàng
    vector<vector<double>> distances; // vector lồng (ma trận) chứa khoảng cách của các điểm
    for (int i = 0; i < n; i++)
    {
        double x1, y1, x2, y2, weight;
        cin >> x1 >> y1 >> x2 >> y2 >> weight;
        Order order;
        order.setOrder(x1, y1, x2, y2, weight);
        orders.push_back(order);
    }
    // printOrders(orders); kiểm tra dãy các đơn hàng oke chưa bằng cách in ra

    return 0;
}