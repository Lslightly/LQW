#include <queue>
#include <iostream>
#include <vector>

using namespace std;

class KthLargest
{
private:
    priority_queue<int, vector<int>, greater<int>> q_prior;
    int k;
public:
    KthLargest(int k, vector<int>& nums)
    {
        this->k = k;
        int len = nums.size();
        for (int i = 0; i < len; i++)
            q_prior.push(nums[i]);
        for (int i = 0; i < len-k; i++)
            q_prior.pop();
    }

    int add(int val)
    {
        if (q_prior.size() < k)
        {
            q_prior.push(val);
            return q_prior.top();
        }
        if (val <= this->q_prior.top()) return this->q_prior.top();
        else
        {
            this->q_prior.push(val);
            this->q_prior.pop();
            return this->q_prior.top();
        }
        
    }
};

int main(void)
{
    vector<int> example = {4, 5, 8, 2};
    KthLargest K(3, example);
    cout << K.add(3);
    cout << K.add(5);
    cout << K.add(10);
    cout << K.add(9);
    cout << K.add(4);
}