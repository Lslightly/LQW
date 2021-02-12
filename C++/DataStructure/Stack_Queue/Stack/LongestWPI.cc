#include <stack>
#include <vector>
using namespace std;
class Solution
{
public:
    int longestWPI(vector<int>& hours)
    {
        int maxlen = 0;
        int len = hours.size();
        int pre_len = len+1;
        vector<int> prefixSum(pre_len);
        int preSum = 0;
        for (int i = 0; i < len; i++)
        {
            prefixSum[i] = preSum;
            preSum += (hours[i] > 8)?1:-1;
        }
        prefixSum[len] = preSum;
        stack<int> ST;
        ST.push(0);
        for (int i = 1; i < pre_len; i++)
        {
            if (prefixSum[i] < prefixSum[ST.top()])
            {
                ST.push(i);
            }
        }
        for (int j = pre_len-1; j >= 0; j--)
        {
            while (!ST.empty() && prefixSum[j] - prefixSum[ST.top()] > 0)
            {
                maxlen = max(maxlen, j - ST.top());
                ST.pop();
            }
        }
        return maxlen;
    }
};

int main(void)
{
    vector<int> hours = {9,9,6,0,6,6,9};
    Solution S;
    S.longestWPI(hours);
    return 0;
}