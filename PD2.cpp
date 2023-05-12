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

void Input(int &n, double &w, vector<Point> &points, vector<double> &weights, vector<vector<double>> &distances)
// lấy dữ liệu đầu vào gồm số lượng, cân nặng và đơn hàng từ file input
// thêm dữ liệu vào n, w, vector point, weight
// tính khoảng cách giữa các điểm và thêm vào ma trận distances
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
        pointPickUp.setXY(x1, y1);
        points.push_back(pointPickUp);
        Point pointDelivery;
        pointDelivery.setXY(x2, y2);
        points.push_back(pointDelivery);
        weights.push_back(weight);
    }
    for (int i = 0; i < 2 * n; i++)
    {
        vector<double> pointJ;
        for (int j = 0; j < 2 * n; j++)
        {
            pointJ.push_back(points[i].distance(points[j]));
        }
        distances.push_back(pointJ);
    }
    inFile.close();
}

void Output(vector<Point> pointsOutput) // đẩy dữ diệu đầu ra là một vector chứa các địa điểm biểu diễn đường đi của shipper vô file output
{
    ofstream outFile;
    outFile.open("C:/Users/admin/Desktop/ProjectTTUD/output/output.csv");
    if (!outFile.is_open())
    {
        cout << "Fail to open file output !!!";
        exit(0);
    }
    for (int i = 0; i < pointsOutput.size(); i++)
    {
        outFile << pointsOutput[i].x << "," << pointsOutput[i].y << endl;
    }
    outFile.close();
}

int main(int argc, char *agrv[])
{

    int n;                            // số lượng đơn hàng
    double w;                         // trọng lượng đơn hàng
    vector<double> weights;           // vector chứa trọng lượng của n đơn hàng
    vector<Point> points;             // vector chứa tất cả các địa điểm, điểm nhận có chỉ số chẵn, điểm trả có chỉ số lẻ
    vector<vector<double>> distances; // vector lồng (ma trận) chứa khoảng cách của các điểm. Ví dụ distanceses[0][1] là khoảng cách điểm 0 tới điểm 1
    vector<Point> pointsOutput;       // vector chứa các địa điểm biểu diễn đường đi của shipper
    Input(n, w, points, weights, distances);

    // for (int i = 0; i < 2 * n; i++) // test output
    // {
    //     pointsOutput.push_back(points[i]);
    // }
    // Output(pointsOutput);
    return 0;
}