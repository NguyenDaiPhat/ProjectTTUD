#include <iostream>
#include <vector>
using namespace std;
// cách hoán vị, chọn 1 số đầu xong hoán vị phần còn lại, tiếp tục chọn các số khác rồi hoán vị phần còn lại
// quá trình hoán vị phần còn lại cũng tương tự bước đầu
// đến khi dãy hoán vị chỉ còn 1 số thì dừng và in ra
void permute(vector<int> &nums, int i, int j, vector<vector<int>> &res)
{
    if (i == j)
    {
        res.push_back(nums);
        return;
    }
    for (int k = i; k <= j; k++) // chọn đối tượng đầu tiên cần giữ, lần lượt là 3 4 5
    {
        swap(nums[i], nums[k]); // chọn đổi lên đầu để cố định, sau đó thì hoán vị phần còn lại của dãy
        cout << "Swapped " << i << " and " << k << endl;
        permute(nums, i + 1, j, res);
        swap(nums[i], nums[k]);
    }
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    int i = 2, j = 4;
    vector<vector<int>> res;
    permute(nums, i, j, res);
    for (auto v : res)
    {
        for (auto x : v)
        {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
