#include <iostream>
#include <vector>

using namespace std;

void printSwapPositions(int i, int j)
{
    cout << "Swapped positions: " << i << " and " << j << endl;
}

void permute(vector<int> &arr, int i, int j)
{
    if (i == j)
    {
        for (int k = 0; k < arr.size(); k++)
        {
            cout << arr[k] << " ";
        }
        cout << endl;
        return;
    }
    for (int k = i; k <= j; k++)
    {
        swap(arr[i], arr[k]);
        printSwapPositions(i, k);
        permute(arr, i + 1, j);
        swap(arr[i], arr[k]);
    }
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    int i = 2, j = 4;
    permute(arr, i, j);
    return 0;
}
