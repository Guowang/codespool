#define __test__levelOrderBST__
#ifndef __test__levelOrderBST__


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x = 0) : val(x), left(NULL), right(NULL) {}
};

size_t getTreeHeight(TreeNode *root);
void getTreeHeight(TreeNode *node, size_t level, size_t& maxH);

vector<vector<int> > levelOrder(TreeNode *root);

void levelDFS(TreeNode *node, size_t index, vector<int>& v);

void buildTree(vector<string>&, vector<TreeNode>&);

int main() {
    string s[] = {"3","9","20","#","#","15","7"};
    vector<string> sv(s, s + sizeof(s) / sizeof(s[0]));
    vector<TreeNode> nv(sv.size());
    buildTree(sv, nv);
    TreeNode *root = &nv[0];
    levelOrder(root);
    return 0;
}

size_t getTreeHeight(TreeNode *root) {
    if (root == NULL) return 0;
    size_t maxH = 1;
    getTreeHeight(root, 1, maxH);
    return maxH;
}

void getTreeHeight(TreeNode *node, size_t level, size_t& maxH) {
    if (node == NULL) return;
    if (level > maxH)
        maxH = level;
    getTreeHeight(node->left, level + 1, maxH);
    getTreeHeight(node->right, level + 1, maxH);
}

vector<vector<int> > levelOrder(TreeNode *root) {
    size_t height = getTreeHeight(root);
    vector<vector<int> > results(height);
    for (size_t i = 1; i <= height; i++)
        levelDFS(root, i, results[i - 1]);
    
    return results;
}

void levelDFS(TreeNode *node, size_t index, vector<int> & v) {
    if (node == NULL) return;
    if (index == 1)
        v.push_back(node->val);
    levelDFS(node->left, index - 1, v);
    levelDFS(node->right, index - 1, v);
}

void buildTree(vector<string>& sv, vector<TreeNode>& nv) {
    size_t sz = sv.size();
    for (size_t i = 0; i < sz; i++) {
        if (sv[i] != "#") {
            nv[i].val = atoi(sv[i].c_str());
            size_t left = 2*i + 1, right = 2*i + 2;
            if (left < sz && sv[left] != "#")
                nv[i].left = &nv[left];
            if (right < sz && sv[right] != "#")
                nv[i].right = &nv[right];
        }
    }
}


#endif /* defined(__test__levelOrderBST__) */
