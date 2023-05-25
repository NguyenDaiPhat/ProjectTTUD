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

struct Input{
    int n;
    double w;
    vector<double> weights;
    vector<Point> points;
    vector<vector<double>> distances;
    vector<int> pointsOutput;
    vector<bool> visited;
    vector<double> w_points; 
    double totalWeight;
    double totalDistance;

    void input()
    {
        ifstream inFile;
        inFile.open("filetest.csv");
        if (!inFile.is_open())
        {
            cout << "Failed to open the input file!" << endl;
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

        while (getline(inFile, line)){
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

        visited.resize(2 * n + 1, false);
        totalWeight = 0;

        calculateDistances();
        inFile.close();
    }

    void calculateDistances()
    {
        for (int i = 0; i < 2 * n + 1; i++)
        {
            vector<double> pointDistances;
            for (int j = 0; j < 2 * n + 1; j++)
            {
                pointDistances.push_back(points[i].distance(points[j]));
            }
            distances.push_back(pointDistances);
        }
    }
};

struct Output{
    vector<int> pointsOutput;
    vector<vector<double>> distances;
    vector<Point> points;
    double totalDistance;
    void output(string file){
        ofstream outFile(file);
        if (!outFile.is_open()){
            cout << "Failed to open the output file!" << endl;
            exit(0);
        }
        for (int i = 0; i < pointsOutput.size(); i++) {
            int index = pointsOutput[i];
            Point point = points[index];
            outFile << point.x << "," << point.y << endl;
        }
        
        outFile.close();
    }

    void showOutput(){
        cout << "Lo trinh: ";
        for (int i = 1; i < pointsOutput.size()-1; i++){
            if(pointsOutput[i]%2 == 0){
                cout << "D" << pointsOutput[i]/2 << " ";
            }else{
                cout << "P" << (pointsOutput[i]+1)/2 << " ";
            }
        }
        cout << endl
             << "Tong quang duong: " << totalDistance << endl
             << endl;
        
    }
};

struct Solution{
    int findNearest(Input &input, int curr)
    {
        int nearest = -1;
        double minDistance = 1e9;
        for (int i = 0; i < 2 * input.n + 1; i++){
            if (!input.visited[i] && input.distances[curr][i] < minDistance){
                if ((i % 2 == 1 && input.totalWeight + input.weights[i / 2] <= input.w) || (i % 2 == 0 && input.visited[i - 1])){
                    nearest = i;
                    minDistance = input.distances[curr][i];
                }
            }
        }
        return nearest;
    }

    void nearestNeighbor(Input &input){
        input.visited[0] = true;
        int curr = 0;
        input.w_points.resize(2 * input.n + 1);
        for (int i = 0; i < 2 * input.n + 1; i++)
        {
            int next = findNearest(input, curr);
            if (next == -1)
            {
                input.pointsOutput.push_back(0);
                cout << input.totalWeight << "\n";
                break;
            }
            else if (next % 2 == 1){
                input.totalWeight += input.weights[next / 2];
                input.w_points[i] = input.totalWeight;
            }else{
                input.totalWeight -= input.weights[(next - 1) / 2];
                input.w_points[i] = input.totalWeight * -1;
            }
            input.visited[next] = true;
            input.pointsOutput.push_back(next);
            curr = next;
        }
    }
// 0 1 2 3 4 5 6 7
// 0 1 3 2 5 4 6 0
// 0 1 2 1 2 1 0 0

    void totalDistance(Input &input){
        input.totalDistance = 0;
        for (int i = 0; i < input.pointsOutput.size()-1; i++){
            input.totalDistance += input.distances[input.pointsOutput[i]][input.pointsOutput[i + 1]];
        }
    }
// a=2 b=5
    bool checkSwap(Input &input, vector<int> &clone, int a, int b){
        vector<double> w_pointsClone;
        
        //check nhặt trc trả sau
        bool check = true;
        if(clone[a]%2==0){           
            check = false; 
            for(int i=0; i<a; i++){
                if(clone[i] == clone[a]-1)
                    check = true;
            }
            if(check == false)
                return false;
        }
        if(clone[b]%2==0){           
            check = false; 
            for(int i=0; i<b; i++){
                if(clone[i] == clone[b]-1)
                    check = true;
            }
            if(check == false)
                return false;
        }
        if(clone[a]%2!=0){           
            check = false; 
            for(int i=0; i<a; i++){
                if(clone[i] != clone[a]+1)
                    check = true;
            }
            if(check == false)
                return false;
        }
        if(clone[b]%2!=0){           
            check = false; 
            for(int i=0; i<b; i++){
                if(clone[i] != clone[b]+1)
                    check = true;
            }
            if(check == false)
                return false;
        }

        //check w
        double total = 0;
        w_pointsClone.push_back(0);
        for(int i=1; i<2*input.n+1; i++){
            if(clone[i] %2 ==0){
                total -= input.weights[clone[(i-1)/2]]; 
            }else{
                total += input.weights[clone[i/2]]; 
            }
            w_pointsClone.push_back(total);
        }

        for(int i=a; i < w_pointsClone.size(); i++){
            if(w_pointsClone[i] > input.w)
                return false;
        }
        return true;
    }

    void Swap(Input &input){
        bool improved = true;
        while(improved){
            improved = false;
            int best_swap1=-1, best_swap2=-1;
            double best_dis=999999999, Dis;
            for(int i = 1; i<2*input.n+1; i++){
                for(int j = 1+i; j< 2*input.n+1; j++){
                    if(i !=j){
                        vector<int> clone(input.pointsOutput.begin(), input.pointsOutput.end());
                        swap(clone[i], clone[j]);
                        // tinh khoang cach cu
                        double oldDis=input.distances[input.pointsOutput[i - 1]][input.pointsOutput[i]] 
                                    + input.distances[input.pointsOutput[i]][input.pointsOutput[i + 1]] 
                                    + input.distances[input.pointsOutput[j - 1]][input.pointsOutput[j]] 
                                    + input.distances[input.pointsOutput[j]][input.pointsOutput[j + 1]];

                        double newDis= input.distances[clone[i - 1]][clone[i]] 
                                     + input.distances[clone[i]][clone[i + 1]]
                                     + input.distances[clone[j - 1]][clone[j]] 
                                     + input.distances[clone[j]][clone[j + 1]];
                        
                        // if ban sao dung 
                        if(checkSwap(input, clone, i, j)){
                            if(newDis - oldDis<0){
                                improved = true;
                                Dis=input.totalDistance-oldDis+newDis;
                                if (Dis<best_dis){
                                    best_dis = Dis;
                                    best_swap1 = i;
                                    best_swap2 = j; 
                                }
                            }
                        }  
                    }
                }
            }
            if(improved){
                swap(input.pointsOutput[best_swap1], input.pointsOutput[best_swap2]);
                input.totalDistance = best_dis;
            }
        }
    }

    bool checkRel(Input &input, vector<int>&clone, int a, int b, int category ){
        vector<double> w_pointsClone;
        double newDis;
        //check vi tri
        if(category ==0 && clone[b]%2==1){
            for(int i=b; i>a; i--){
                if(clone[i]== clone[b]+1)
                    return false;
            }
        }
        if(category ==1 && clone[a]%2 == 0){
            for(int i=a; i<b; i++){
                if(clone[i] == clone[a]-1){
                    return false;
                }
            }
        }
        //check w
        double total = 0;
        w_pointsClone.push_back(0);
        for(int i=1; i<2*input.n+1; i++){
            if(clone[i] %2 ==0){
                total -= input.weights[clone[(i-1)/2]]; 
            }else{
                total += input.weights[clone[i/2]]; 
            }
            w_pointsClone.push_back(total);
        }

        for(int i=0; i < w_pointsClone.size(); i++){
            if(w_pointsClone[i] > input.w)
                return false;
        }
        return true;
    }

    void Relocate(Input &input){
        bool improved = true;
        while(improved){
            improved = false;
            vector<int> best_clone;
            double best_dis=999999999, Dis;
            int a, b, c,category;//category == 1 : relocate về phía trước, category ==0 relocate về phía sau
            for (int i = 1; i < 2 * input.n + 1; i++) {
                for (int j = 1; j < 2 * input.n + 1; j++) {
                    if (i != j && i + 1 != j && i - 1 != j ) {
                        vector<int> clone(input.pointsOutput.begin(), input.pointsOutput.end());
                        if(i<j){
                            a=i;
                            b=j;
                            category = 0;// relocate từ trước ra sau
                            for(int k=a; k<b; k++){
                                clone[k]= clone[k+1];
                            }
                            clone[j] = input.pointsOutput[i];
                        }else{
                            a=j;
                            b=i;
                            category = 1;
                            for(int k=b; k>a; k--){
                                clone[k]= clone[k-1];
                            }
                            clone[j] = input.pointsOutput[i];                        
                        }
                        double oldDis, newDis;
                        if(category==1){
                            oldDis = input.distances[input.pointsOutput[a - 1]][input.pointsOutput[a]] 
                            + input.distances[input.pointsOutput[b]][input.pointsOutput[b + 1]]
                            + input.distances[input.pointsOutput[b - 1]][input.pointsOutput[b]] ;

                            newDis = input.distances[clone[a - 1]][clone[a]] 
                                        + input.distances[clone[a]][clone[a + 1]]
                                        + input.distances[clone[b]][clone[b+1]] ;
                        }
                        else{
                            oldDis = input.distances[input.pointsOutput[a - 1]][input.pointsOutput[a]] 
                                        + input.distances[input.pointsOutput[a]][input.pointsOutput[a + 1]]
                                        + input.distances[input.pointsOutput[b]][input.pointsOutput[b+1]] ;
                            newDis = input.distances[clone[a - 1]][clone[a]] 
                                        + input.distances[clone[b]][clone[b + 1]]
                                        + input.distances[clone[b - 1]][clone[b]] ;
                        }
                        
                        
                        if(checkRel(input, clone, a, b, category)){
                            if(newDis < oldDis){
                                improved = true;
                                Dis=input.totalDistance-oldDis+newDis;
                                if (Dis<best_dis){
                                    best_dis = Dis;
                                    best_clone = clone;
                                }
                            }
                        }
                    }
                }
            }
            if(improved){
                input.pointsOutput = best_clone;
                input.totalDistance = best_dis;
            }
        }
    }
};

int main(int argc, char *agrv[]){
    Input input;
    input.input();

    Output output;
    output.distances = input.distances;
    output.points = input.points;
    Solution solution;
    solution.nearestNeighbor(input);
    solution.totalDistance(input);
    output.totalDistance = input.totalDistance;
    output.pointsOutput = input.pointsOutput;
    output.showOutput();
    output.output("outputGen.csv");


    solution.Swap(input);
    output.pointsOutput = input.pointsOutput;
    output.totalDistance = input.totalDistance;
    output.showOutput();

    solution.Relocate(input);
    output.pointsOutput = input.pointsOutput;
    output.totalDistance = input.totalDistance;
    output.showOutput();

    output.output("outputOp.csv");

    return 0;
}