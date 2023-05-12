#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
struct Point // định nghĩa một địa điểm gồm tọa độ x và y
{
    double x;
    double y;
    void setXY(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double distance(Point a) // hàm tính khoảng cách giữa 2 địa điểm bất kì
    {
        return sqrt((this->x - a.x) * (this->x - a.x) + (this->y - a.y) * (this->y - a.y));
    }
};

struct Order // định nghĩa một đơn hàng gồm điểm nhận, điểm trả và cân nặng
{
    Point pointPickUp;
    Point pointDelivery;
    double weight;
    void setOrder(Point pointPickUp, Point pointDelivery, double weight)
    {
        this->pointDelivery.setXY(pointPickUp.x, pointPickUp.y);
        this->pointDelivery.setXY(pointDelivery.x, pointDelivery.y);
        this->weight = weight;
    }
};

void input(int &n, double &w, vector<Point> &points, vector<Order> &orders) // lấy dữ liệu đầu vào gồm số lượng, cân nặng và đơn hàng từ file input
{
    ifstream inFile;
    inFile.open("C:/Users/admin/Desktop/ProjectTTUD/input/input1.csv");
    if (!inFile.is_open())
    {
        cout << "Fail to open file input !!!";
        exit(0);
    }
    string line, s;
    getline(inFile, line);
    istringstream iss(line);
    getline(iss, s, ',');
    n = stoi(s);
    getline(iss, s, ',');
    w = stod(s);
    while (getline(inFile, line))
    {
        istringstream iss(line);
        double x1, y1, x2, y2, weight;
        getline(iss, s, ',');
        x1 = stod(s);
        getline(iss, s, ',');
        y1 = stod(s);
        getline(iss, s, ',');
        x2 = stod(s);
        getline(iss, s, ',');
        y2 = stod(s);
        getline(iss, s, ',');
        weight = stod(s);
        Point pointPickUp;
        pointPickUp.setXY(x1,y1);
        points.push_back(pointPickUp);
        Point pointDelivery;
        pointDelivery.setXY(x2, y2);
        points.push_back(pointDelivery);
        Order order;
        order.setOrder(pointPickUp, pointDelivery, weight);
        orders.push_back(order);
    }
    inFile.close();
}

void output(vector<Point> points) // đẩy dữ diệu đầu ra là một vector chứa các địa điểm biểu diễn đường đi của shipper vô file output
{
    ofstream outFile;
    outFile.open("C:/Users/admin/Desktop/ProjectTTUD/output/output.csv");
    if (!outFile.is_open())
    {
        cout << "Fail to open file output !!!";
        exit(0);
    }
    for (int i = 0; i < points.size(); i++)
    {
        outFile << points[i].x << "," << points[i].y << endl;
    }
    outFile.close();
}

int main(int argc, char *agrv[])
{

    int n;                            // số lượng đơn hàng
    double w;                         // trọng lượng đơn hàng
    vector<Order> orders;             // vector chứa tất cả các đơn hàng
    vector<Point> points;
    vector<vector<double>> distances; // vector lồng (ma trận) chứa khoảng cách của các điểm
    vector<Point> pointsOutput;             // vector chứa các địa điểm biểu diễn đường đi của shipper
    input(n, w, points, orders);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

        }
    }
    for (int i = 0; i < 2*n; i++) // test output
    {
        pointsOutput.push_back(points[i]);
    }
    output(pointsOutput);
    return 0;
}