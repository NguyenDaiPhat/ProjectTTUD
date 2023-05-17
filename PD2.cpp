#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
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

int n;                                  // số lượng đơn hàng
double w;                               // trọng lượng đơn hàng tối đa mà shipper có thể mang
vector<double> weights;                 // vector chứa trọng lượng của n đơn hàng
vector<Point> points;                   // vector chứa 2*n các địa điểm, điểm nhận có chỉ số lẻ, điểm trả có chỉ số chẵn
vector<vector<double>> distances;       // vector lồng (ma trận) chứa khoảng cách của các điểm. Ví dụ distanceses[0][1] = distanceses[1][0] là khoảng cách điểm 0 tới điểm 1
vector<int> pointsOutput;               // vector chứa các chỉ mục địa điểm biểu diễn đường đi của shipper
vector<bool> visited(2 * n + 1, false); // vector đánh dấu các địa điểm đã được đi qua hay chưa
double totalWeight = 0;                 // tổng trọng lượng đơn hàng mà shipper đang mang đi

void input()
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
    string line, token;
    getline(inFile, line);
    istringstream iss(line);
    getline(iss, token, ',');
    n = stoi(token);
    getline(iss, token, ',');
    w = stod(token);
    Point pointStart;
    pointStart.setXY(0, 0);
    points.push_back(pointStart);
    pointsOutput.push_back(0);
    while (getline(inFile, line))
    {
        istringstream iss(line);
        double x1, y1, x2, y2, weight;
        getline(iss, token, ',');
        x1 = stod(token);
        getline(iss, token, ',');
        y1 = stod(token);
        getline(iss, token, ',');
        x2 = stod(token);
        getline(iss, token, ',');
        y2 = stod(token);
        getline(iss, token, ',');
        weight = stod(token);
        Point pointPickUp;
        pointPickUp.setXY(x1, y1);
        points.push_back(pointPickUp);
        Point pointDelivery;
        pointDelivery.setXY(x2, y2);
        points.push_back(pointDelivery);
        weights.push_back(weight);
    }
    for (int i = 0; i < 2 * n + 1; i++)
    {
        vector<double> pointJ;
        for (int j = 0; j < 2 * n + 1; j++)
        {
            pointJ.push_back(points[i].distance(points[j]));
        }
        distances.push_back(pointJ);
    }
    inFile.close();
}

void output()
// đẩy dữ diệu đầu ra là một vector chứa các địa điểm biểu diễn đường đi của shipper vô file output
{
    double totalDistance = 0; // tổng quãng đường di chuyển của shipper
    ofstream outFile;
    outFile.open("C:/Users/admin/Desktop/ProjectTTUD/output/output.csv");
    if (!outFile.is_open())
    {
        cout << "Fail to open file output !!!";
        exit(0);
    }
    // outFile << "Lo trinh: ";
    // for (int i = 0; i < pointsOutput.size(); i++)
    // {
    //     outFile << pointsOutput[i] << " ";
    //     if (i < pointsOutput.size() - 1)
    //        {
    //         totalDistance += distances[pointsOutput[i]][pointsOutput[i+1]];
    //         // cout << distances[pointsOutput[i]][pointsOutput[i + 1]] << endl;
    //        } 
    // }
    // outFile << endl <<"Tong quang duong: "<< totalDistance << endl;
    for (int i = 0; i < pointsOutput.size(); i++)
    {
        outFile << points[pointsOutput[i]].x << "," << points[pointsOutput[i]].y << endl;
    }
    outFile.close();
}

int findNearest(int curr)
{
    int nearest = -1;
    double minDistance = 1e9;
    for (int i = 0; i < 2 * n + 1; i++)
    {
        if (!visited[i] && distances[curr][i] < minDistance)
        {
            if ((i % 2 == 1 && totalWeight + weights[i / 2] <= w) || (i % 2 == 0 && visited[i - 1]))
            {
                nearest = i;
                minDistance = distances[curr][i];
            }
            // cout << nearest << " ";
        }
    }
    // cout << endl;
    return nearest;
}

void nearestNeighbor() // hàm này dùng thuật toán heuristic (Nearest Neighbor)
{
    visited[0] = true;
    int curr = 0;
    for (int i = 0; i < 2 * n + 1; i++)
    {
        int next = findNearest(curr);
        if (next == -1)
        {
            pointsOutput.push_back(0);
            break;
        }
        else if (next % 2 == 1)
            totalWeight += weights[next / 2];
        else
            totalWeight -= weights[(next - 1) / 2];
        visited[next] = true;
        pointsOutput.push_back(next);
        curr = next;
    }
}

void localsearch(int a, int b) // phương pháp localsearch 2-opt
{
    bool improved = true;
    while (improved)
    {
        improved = false;
        for (int i = a; i <= b; ++i)
        {
            for (int j = a + 1; j <= b; ++j)
            {
                int new1 = distances[pointsOutput[i - 1]][pointsOutput[j]] + distances[pointsOutput[i]][pointsOutput[j + 1]];
                int old1 = distances[pointsOutput[i - 1]][pointsOutput[i]] + distances[pointsOutput[j]][pointsOutput[j + 1]];
                int distDiff = new1 - old1;
                if (distDiff < 0)
                {
                    reverse(pointsOutput.begin() + i, pointsOutput.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }
}

void optimization()
{
    int i = 1;
    while (i < pointsOutput.size() - 2)
    {
        int j = i + 1;
        while ((j < pointsOutput.size() - 1) && (pointsOutput[i] % 2 == pointsOutput[j] % 2))
        {
            j++;
        }
        localsearch(i, j - 1);
        i = j - 1;
        i++;
    }
}

int main(int argc, char *agrv[])
{
    input();
    nearestNeighbor(); // tạo một lời giải ban đầu
    // output();
    optimization();    // tối ưu lời giải ban đầu
    // for (int i = 0; i < 2 * n + 1; i++)
    // {
    //     for (int j = 0; j < 2 * n + 1; j++)
    //     {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    output();
    return 0;
}