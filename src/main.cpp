#include <format>
#include <ios>
#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

bool checkTree(TreeNode* root) {
    auto sumOfChilds = root->left->val + root->right->val;
    return sumOfChilds == root->val;
}

int main() {
    auto left = new TreeNode(4);
    auto right = new TreeNode(6);
    auto root = new TreeNode(10, left, right);

    cout << std::boolalpha << checkTree(root) << "\n";
}
