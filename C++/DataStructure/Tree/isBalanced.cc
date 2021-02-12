#include <iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
    bool isBalanced(TreeNode *root)
    {
        return height(root) != -1;
    }
    int height(TreeNode *root)
    {
        if (!root)
            return 0;
        else
        {
            int lh, rh;
            if ((lh = height(root->left)) == -1 || (rh = height(root->right)) == -1)
                return -1;
            else if (abs(lh - rh) > 1)
            {
                return -1;
            }
            else
            {
                return max(lh, rh)+1;
            }
        }
    }
};