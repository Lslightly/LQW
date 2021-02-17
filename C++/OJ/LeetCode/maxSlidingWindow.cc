#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        if (k == 1) return nums;
        vector<int> max_in_window;
        if (nums.empty()) return {};
        int maxi, max_num;
        max_num = max_in_k(nums, k-1, 0, maxi);
        for (int i = k-1; i < nums.size(); i++)
        {
            max_num = max(max_num, nums[i]);
            max_in_window.push_back(max_num);
            if (nums[i] == max_num) maxi = i;
            else if (maxi == i-k+1)
            {
                max_num = max_in_k(nums, k-1, i-k+2, maxi);
            }
        }
        return max_in_window;
    }
    int max_in_k(vector<int> &nums, int k, int start, int &maxi)
    {
        int max_num = nums[start];
        maxi = start;
        for (int i = start+1; i < start+k; i++)
        {
            max_num = max(max_num, nums[i]);
            if (max_num == nums[i])
                maxi = i;
        }
        return max_num;
    }
};

int main()
{
    vector<int> nums;
    Solution S;
    nums = S.maxSlidingWindow(nums, 3);
    while (!nums.empty())
    {
        cout << nums[nums.size() - 1];
        nums.pop_back();
    }
}