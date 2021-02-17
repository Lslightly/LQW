#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c)
    {
        int r_ori = nums.size(), c_ori = nums[0].size();
        if (r_ori * c_ori != r * c) return nums;
        
        vector<int> row;
        vector<vector<int>> matrix_new;
        int ci = 0;
        for (int i = 0; i < r_ori; i++)
        {
            for (int j = 0; j < c_ori; j++)
            {
                row.push_back(nums[i][j]);
                ci++;
                if (ci == c)
                {
                    ci = 0;
                    matrix_new.push_back(row);
                    row.clear();
                }
            }
        }
        return matrix_new;
    }
};