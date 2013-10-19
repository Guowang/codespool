#define __test__leetcode__
#ifndef __test__leetcode__


#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <string>
#include <tr1/unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
};
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
};
//Divide Two Integers
int divide(int dividend, int divisor) {
    size_t p = abs(dividend), q = abs(divisor);
    if (p < q) return 0;
    size_t result = 0;
    while (p > q) {
        size_t r = 1, i = q;
        for (; i < p; i <<= 1, r <<= 1)
            ;
        r >>= 1;
        i >>= 1;
        result += r;
        p -= i;
    }
    if (p == q) result += 1;
    if((dividend > 0 && divisor < 0) ||(dividend < 0 && divisor > 0))
        return -result;
    return result;
}
//Pow(x,n)
double pow(double x, int n) {
    size_t p = abs(n);
    double r = 1.0;
    for (double base = x; p != 0; base *= base, p >>= 1)
        if (p & 1)
            r *= base;
    if (n < 0) return 1.0 / r;
    return r;
}
/*
bool isSymmetric(TreeNode *l, TreeNode *r) {
    if (l == NULL) return r == NULL;
    if (r == NULL) return l == NULL;
    if (r->val != l->val) return false;
    return isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left);
}
bool isSymmetric(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return true;
    return isSymmetric(root->left, root->right);
}
*/
//Symmetric Tree
bool isSymmetric(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return true;
    queue<TreeNode*> ql, qr;
    TreeNode *nl, *nr;
    ql.push(root->left);
    qr.push(root->right);
    
    while (!ql.empty() && !qr.empty()) {
        nl = ql.front();
        ql.pop();
        nr = qr.front();
        qr.pop();
        if (nl == NULL && nr == NULL) continue;
        if (nl == NULL && nr != NULL) return false;
        if (nl != NULL && nr == NULL) return false;
        if (nl->val != nr->val) return false;
        ql.push(nl->left);
        ql.push(nl->right);
        qr.push(nr->right);
        qr.push(nr->left);
    }
    return ql.size() == qr.size();
}
//Text Justification
vector<string> fullJustify(vector<string> &words, int L) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<string> ret;
    if (L == 0) {
        ret.push_back("");
        return ret;
    }
    string line;
    size_t i = 0, index = 0, sz = words.size(), wordcount = 0, letters = 0, len = 0;
    size_t unit = 0, gapcount = 0, blanks = 0;
    
    while (i < sz) {
        index = i;
        line = "";
        wordcount = 1;
        len = words[i].length();
        letters = len;
        ++i;
        while (i < sz) {
            if (len + 1 + words[i].length() <= L) {
                letters += words[i].length();
                len += 1 + words[i].length();
                ++wordcount;
                ++i;
            }
            else
                break;
        }
        if (wordcount == 1) {
            line = words[index];
            if (len < L)
                line += string(L - len, ' ');
            ret.push_back(line);
            continue;
        }
        blanks = L - letters;
        unit = blanks / (wordcount - 1);
        gapcount = blanks - unit * (wordcount - 1);
        if (index + wordcount == sz) {
            for (size_t start = 0; start < wordcount - 1; ++start)
                line += words[index + start] + " ";
            line += words[index + wordcount - 1];
            if (L > letters + wordcount - 1)
                line += string(L - letters - wordcount + 1, ' ');
            ret.push_back(line);
            break;
        }
        for (size_t start = 0; start < wordcount - 1; ++start) {
            line += words[index + start] + string(unit, ' ');
            if (start < gapcount)
                line += " ";
        }
        line += words[index + wordcount - 1];
        ret.push_back(line);
    }
    return ret;
}
//Minimum Window Substring
string minWindow(string S, string T) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    string ret = "";
    size_t n = S.size(), m = T.size(), count = 0, s = 0, e = 0;
    tr1::unordered_map<char, size_t> cur, tar;
    tr1::unordered_map<char, size_t>::iterator it;
    
    for (size_t i = 0; i < m; ++i) {
        it = tar.find(T[i]);
        if (it == tar.end())
            tar.insert(pair<char, size_t>(T[i], 1));
        else
            it->second += 1;
        cur.insert(pair<char, size_t>(T[i], 0));
    }
    
    for (e = 0; e < n; ++e) {
        it = cur.find(S[e]);
        if (it == cur.end())
            continue;
        if (it->second < tar.find(S[e])->second)
            ++count;
        it->second += 1;
        while (s <= e && (cur.find(S[s]) == cur.end() || cur.find(S[s])->second > tar.find(S[s])->second)) {
            if (cur.find(S[s]) != cur.end())
                cur.find(S[s])->second -= 1;
            ++s;
        }
        if (count == m) {
            if (ret == "" || ret.size() > e - s + 1)
                ret = S.substr(s, e - s + 1);
        }
    }
    
    return ret;
}
//Binary Tree Maximum Path Sum
int maxPathSum(TreeNode *node, int &g) {
    if (node == NULL) {
        g = 0;
        return INT_MIN;
    }
    int g_left = 0;
    int g_right = 0;
    int f_left = maxPathSum(node->left, g_left);
    int f_right = maxPathSum(node->right, g_right);
    int f = g_left + node->val + g_right;
    g = max(0, node->val + max(g_left, g_right));
    f = max(f, f_left);
    f = max(f, f_right);
    return f;
}
int maxPathSum(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return 0;
    int g = root->val;
    return maxPathSum(root, g);
}
//Best Time to Buy and Sell Stock
int maxProfitIII(vector<int> &prices) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t SZ = prices.size();
    if (SZ < 2) return 0;
    if (SZ == 2) return max(0, prices[1] - prices[0]);
    vector<int> minval(SZ, INT_MIN), maxval(SZ, INT_MIN);
    
    int p = prices[0], maxpro = prices[1] - prices[0];
    for (size_t i = 1; i < SZ; ++i) {
        maxpro = max(maxpro, prices[i] - p);
        minval[i] = maxpro;
        p = min(p, prices[i]);
    }
    
    p = prices[SZ - 1], maxpro = prices[SZ - 1] - prices[SZ - 2];
    for (int i = SZ - 2; i >= 0; --i) {
        maxpro = max(maxpro, p - prices[i]);
        maxval[i] = maxpro;
        p = max(p, prices[i]);
    }
    
    int ret = maxval[0];
    for (size_t i = 1; i < SZ - 2; ++i) {
        ret = max(ret, minval[i]);
        ret = max(ret, maxval[i + 1]);
        ret = max(ret, minval[i] + maxval[i + 1]);
    }
    return max(0, ret);
}
int maxProfitII(vector<int> &prices) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t SZ = prices.size();
    if (SZ < 2) return 0;
    
    int maxpro = 0;
    size_t s = 0, i = 0;
    
    for (i = 0; i < SZ - 1; ++i) {
        if (prices[i + 1] >= prices[i])
            continue;
        maxpro += prices[i] - prices[s];
        s = i + 1;
    }
    if (prices[i] >= prices[i - 1])
        maxpro += prices[i] - prices[s];
    
    return maxpro;
}
//Triangle
int minimumTotal(vector<vector<int> > &triangle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t n = triangle.size();
    if (n == 0) return 0;
    if (n == 1) return triangle[0][0];
    
    vector<int> cur(n, 0), next(n, 0);
    cur[0] = triangle[0][0] + triangle[1][0];
    cur[1] = triangle[0][0] + triangle[1][1];
    
    for (size_t i = 2; i < n; ++i) {
        next[0] = cur[0] + triangle[i][0];
        next[i] = cur[i - 1] + triangle[i][i];
        for (size_t j = 1; j < i; ++j) {
            next[j] = triangle[i][j] + min(cur[j - 1], cur[j]);
        }
        cur.swap(next);
    }
    int ret = cur[0];
    for (size_t i = 1; i < n; ++i) {
        ret = min(ret, cur[i]);
    }
    return ret;
}
//Populating Next Right Pointers in Each Node
void connect(TreeLinkNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if(root == NULL) return;
    
    root->next = NULL;
    TreeLinkNode *cur = root, *nxt, *p = cur, *l = NULL, *r = NULL;
    
    while (cur != NULL) {
        nxt = NULL;
        p = cur;
        l = NULL;
        r = NULL;
        while (p != NULL) {
            if (l == NULL && p->left != NULL)
                l = p->left;
            if (l == NULL && p->right != NULL)
                l = p->right;
            if (l != NULL && nxt == NULL)
                nxt = l;
            if (r == NULL && p->left != NULL && p->left != l)
                r = p->left;
            if (r == NULL && p->right != NULL && p->right != l)
                r = p->right;
            if (l != NULL && r != NULL) {
                l->next = r;
                l = r;
                r = NULL;
                if (l == p->left)
                    continue;
            }
            p = p->next;
        }
        cur = nxt;
    }
}
//Maximal Rectangle
int maximalRectangle(vector<vector<char> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t n = matrix.size();
    if (n == 0) return 0;
    size_t m = matrix[0].size();
    vector<int> height(m, 0), left(m, -1), right(m, m);
    int l = -1, r = m, area = 0;
    
    for (int i = 0; i < n; ++i) {
        l = -1;
        r = m;
        //fill in height[] and left[]
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == '0') {
                height[j] = 0;
                left[j] = -1;
                l = j;
            }
            else {
                height[j] += 1;
                left[j] = max(left[j], l);
            }
        }
        //fill in right[] and calc area
        for (int j = m - 1; j >= 0; --j) {
            if (matrix[i][j] == '0') {
                right[j] = m;
                r = j;
            }
            else
                right[j] = min(right[j], r);
            area = max(area, (right[j] - left[j] - 1)*height[j]);
        }
    }
    return area;
}
//Largest Rectangle in Histogram
int largestRectangleArea(vector<int> &height) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int n = height.size();
    vector<int> left(n, -1);
    stack<int> l, r;
    int area = 0;
    
    //fill in left[]
    for (int  i = 0; i < n; ++i) {
        while (!l.empty() && height[l.top()] >= height[i])
            l.pop();
        if (l.empty())
            left[i] = -1;
        else
            left[i] = l.top();
        l.push(i);
    }
    //calc right[] and area
    for (int i = n - 1; i >= 0; --i) {
        while (!r.empty() && height[r.top()] >= height[i])
            r.pop();
        if (r.empty())
            area = max(area, (n - left[i] - 1)*height[i]);
        else
            area = max(area, (r.top() - left[i] - 1)*height[i]);
        r.push(i);
    }
    return area;
}
//Distinct Subsequences
int numDistinct(string S, string T) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t n = S.size(), m = T.size(), ret = 0;
    if (m == 0 || n == 0) return 0;
    vector<size_t> cur(n, 0), next(n, 0);
    for (size_t i = 0; i < n; ++i)
        if (S[i] == T[0])
            cur[i] = 1;
    
    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            next[j] = 0;
            if (i <= j && S[j] == T[i]) {
                for (size_t k = i - 1; k < j; ++k)
                    next[j] += cur[k];
            }
        }
        next.swap(cur);
    }
    
    for (size_t i = m - 1; i < n; ++i)
        ret += cur[i];
    
    return ret;
}
//Flatten Binary Tree to Linked List
void flatten(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return;
    if (root->left != NULL) {
        TreeNode *p = root->left;
        while (p->right != NULL)
            p = p->right;
        p->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
    flatten(root->right);
}
//Path Sum II
void findLeaves(TreeNode *node, vector<int> v, vector<vector<int> > &ret, int s, int &sum) {
    v.push_back(node->val);
    vector<int> vl(v.begin(), v.end()), vr(v.begin(), v.end());
    s += node->val;
    if (node->left != NULL)
        findLeaves(node->left, vl, ret, s, sum);
    if (node->right != NULL)
        findLeaves(node->right, vr, ret, s, sum);
    if (node->left == NULL && node->right == NULL && s == sum)
        ret.push_back(v);
}

vector<vector<int> > pathSum(TreeNode *root, int sum) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret;
    vector<int> v;
    if (root == NULL) return ret;
    findLeaves(root, v, ret, 0, sum);
    return ret;
}
//Path Sum I
bool hasPathSum(TreeNode *node, int s, int sum) {
    if (node == NULL) return false;
    s += node->val;
    if (node->left == NULL && node->right == NULL && s == sum)
        return true;
    return hasPathSum(node->left, s, sum) || hasPathSum(node->right, s, sum);
}
bool hasPathSum(TreeNode *root, int sum) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return hasPathSum(root, 0, sum);
}
//Minimum Depth of Binary Tree
int minDepth(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return 0;
    int l = minDepth(root->left) + 1, r = minDepth(root->right) + 1;
    if (l == 1 || r == 1)
        return max(l, r);
    return min(l, r);
}
int minDepth(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return 0;
    
    queue<pair<TreeNode*, int> > q;
    TreeNode *p;
    int l = 0;
    q.push(pair<TreeNode*, int>(root, 1));
    
    while (!q.empty()) {
        p = q.front().first;
        l = q.front().second;
        q.pop();
        if (p->left == NULL && p->right == NULL)
            break;
        if (p->left != NULL)
            q.push(pair<TreeNode*, int>(p->left, l + 1));
        if (p->right != NULL)
            q.push(pair<TreeNode*, int>(p->right, l + 1));
    }
    
    return l;
}
//Balanced Binary Tree
int height(TreeNode *node) {
    if (node == NULL)
        return 0;
    int l = height(node->left), r = height(node->right);
    return 1 + max(l, r);
}
bool isBalanced(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL)
        return true;
    int l = height(root->left), r = height(root->right);
    if (abs(l - r) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}
//Convert Sorted List to Binary Search Tree
TreeNode *sortedListToBST(ListNode *head) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (head == NULL)
        return NULL;
    TreeNode *root = new TreeNode(head->val);
    if (head->next == NULL)
        return root;
    if (head->next->next == NULL) {
        TreeNode *l = new TreeNode(head->val);
        root->val = head->next->val;
        root->left = l;
        return root;
    }
    ListNode *prev = head, *s = head->next, *q = head->next->next;
    
    while (q != NULL && q->next != NULL) {
        prev = s;
        s = s->next;
        q = q->next->next;
    }
    
    prev->next = NULL;
    TreeNode *l = sortedListToBST(head);
    TreeNode *r = sortedListToBST(s->next);
    root->val = s->val;
    root->left = l;
    root->right = r;
    return root;
}
//Convert Sorted Array to Binary Search Tree
TreeNode *sortedArrayToBST(vector<int>&num, size_t s, size_t SZ) {
    if (SZ == 0)
        return NULL;
    if (SZ == 1) {
        TreeNode *n = new TreeNode(num[s]);
        return n;
    }
    size_t mid = s + SZ/2;
    TreeNode *n = new TreeNode(num[mid]);
    TreeNode *l = sortedArrayToBST(num, s, SZ/2);
    TreeNode *r = sortedArrayToBST(num, mid + 1, SZ - SZ/2 - 1);
    n->left = l;
    n->right = r;
    return n;
}
TreeNode *sortedArrayToBST(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return sortedArrayToBST(num, 0, num.size());
}
//Binary Tree Level Order Traversal II
vector<vector<int> > levelOrderBottom(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > v;
    if (root == NULL) return v;
    deque<TreeNode*> cur, next;
    TreeNode *p;
    cur.push_back(root);
    
    while (!cur.empty()) {
        vector<int> level;
        next.clear();
        while (!cur.empty()) {
            p = cur.front();
            cur.pop_front();
            level.push_back(p->val);
            if (p->left != NULL)
                next.push_back(p->left);
            if (p->right != NULL)
                next.push_back(p->right);
        }
        cur.swap(next);
        v.insert(v.begin(), level);
    }
    return v;
}
//Construct Binary Tree from Inorder and Postorder Traversal
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, size_t is, vector<int> &postorder, size_t ps, size_t n, tr1::unordered_map<int, size_t> &map) {
        if (n == 0)
            return NULL;
        TreeNode *root = new TreeNode(postorder[ps + n - 1]);
        if (n == 1)
            return root;
        /*
        //for BST
        int low = is, high = is + n - 1, pos = is, val = root->val;
        while (low <= high) {
            pos = low + (high - low)/2;
            if (inorder[pos] < val)
                low = pos + 1;
            else if (inorder[pos] > val)
                high = pos - 1;
            else
                break;
        }
        */
        size_t pos = map.find(root->val)->second;
        TreeNode *left = buildTree(inorder, is, postorder, ps, pos - is, map);
        TreeNode *right = buildTree(inorder, pos + 1, postorder, ps + pos - is, n - pos + is - 1, map);
        
        root->left = left;
        root->right = right;
        
        return root;
        
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        tr1::unordered_map<int, size_t> map;
        for (size_t i = 0; i < inorder.size(); ++i)
            map.insert(pair<int, size_t>(inorder[i],i));
        return buildTree(inorder, 0, postorder, 0, inorder.size(), map);
    }
};
//Construct Binary Tree from Preorder and Inorder Traversal
TreeNode *buildTree(vector<int> &inorder, size_t is, vector<int> &preorder, size_t ps, size_t n, tr1::unordered_map<int, size_t> &map) {
    if (n == 0)
        return NULL;
    TreeNode *root = new TreeNode(preorder[ps]);
    if (n == 1)
        return root;
    size_t pos = map.find(root->val)->second;
    TreeNode *left = buildTree(inorder, is, preorder, ps + 1, pos - is, map);
    TreeNode *right = buildTree(inorder, pos + 1, preorder, ps + pos - is + 1, n - pos + is - 1, map);
    
    root->left = left;
    root->right = right;
    
    return root;
    
}
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    tr1::unordered_map<int, size_t> map;
    for (size_t i = 0; i < inorder.size(); ++i)
        map.insert(pair<int, size_t>(inorder[i],i));
    return buildTree(inorder, 0, preorder, 0, inorder.size(), map);
}
//Maximum Depth of Binary Tree
int maxDepth(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return 0;
    
    queue<pair<TreeNode*, int> > q;
    TreeNode *p;
    int l = 0, d = 0;
    q.push(pair<TreeNode*, int>(root, 1));
    
    while (!q.empty()) {
        p = q.front().first;
        l = q.front().second;
        d = max(d, l);
        q.pop();
        if (p->left != NULL)
            q.push(pair<TreeNode*, int>(p->left, l + 1));
        if (p->right != NULL)
            q.push(pair<TreeNode*, int>(p->right, l + 1));
    }
    
    return d;
}
//Binary Tree Zigzag Level Order Traversal
vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret;
    if (root == NULL)
        return ret;
    //is current level number even?
    TreeNode *p;
    deque<TreeNode*> cur, next;
    bool isEven = true;
    cur.push_back(root);
    
    while (!cur.empty()) {
        vector<int> v;
        while (!cur.empty()) {
            p = cur.front();
            v.push_back(p->val);
            if (isEven) {
                if (p->left != NULL)
                    next.push_front(p->left);
                if (p->right != NULL)
                    next.push_front(p->right);
            }
            else {
                if (p->right != NULL)
                    next.push_front(p->right);
                if (p->left != NULL)
                    next.push_front(p->left);
            }
            cur.pop_front();
        }
        isEven = !isEven;
        cur.swap(next);
        next.clear();
        ret.push_back(v);
    }
    return ret;
}
//Recover Binary Search Tree
void recoverTree(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (root == NULL) return;
    TreeNode nl(INT_MIN), nr(INT_MAX);
    TreeNode *pl = &nl, *pr = &nr, *cur = root, *prev = &nl;
    
    while (cur != NULL) {
        if (cur->left == NULL) {
            if (prev->val > cur->val && cur->val < pr->val)
                pr = cur;
            if (prev->val > cur->val && prev->val > pl->val)
                pl = prev;
            prev = cur;
            cur = cur->right;
        }
        else {
            TreeNode *p = cur->left;
            while (p->right != NULL && p->right != cur)
                p = p->right;
            if (p->right == NULL) {
                p->right = cur;
                cur = cur->left;
            }
            else {
                p->right = NULL;
                if (prev->val > cur->val && cur->val < pr->val)
                    pr = cur;
                if (prev->val > cur->val && prev->val > pl->val)
                    pl = prev;
                prev = cur;
                cur = cur->right;
            }
        }
    }
    
    int tmp = pl->val;
    pl->val = pr->val;
    pr->val = tmp;
}
//using prev
void inOrder(TreeNode *cur, vector<TreeNode*> &v) {
    if (cur == NULL)
        return;
    inOrder(cur->left, v);
    if (v[2] != NULL && v[2]->val > cur->val) {
        v[1] = cur;
        if (v[0] == NULL)
            v[0] = v[2];
    }
    v[2] = cur;
    inOrder(cur->right, v);
}
void recoverTree(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<TreeNode*> v(3);
    inOrder(root, v);
    if (v[0] != NULL) {
        swap(v[0]->val, v[1]->val);
    }
}
//Validate Binary Search Tree
bool isBST(TreeNode *n, int vmin, int vmax) {
    if (n == NULL) return true;
    if (n->val <= vmin || n->val >= vmax) return false;
    return isBST(n->left, vmin, n->val) && isBST(n->right, n->val, vmax);
}
bool isValidBST(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return isBST(root, INT_MIN, INT_MAX);
}
//Interleaving String
bool isInterleave(string s1, string s2, string s3) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (s3.length() != s1.length() + s2.length()) return false;
    
    size_t m = s1.length(), n = s2.length();
    vector<vector<bool> > T(m + 1, vector<bool>(n + 1, false));
    
    for (size_t i = 1; i <= m; ++i) {
        if (s1[i - 1] == s3[i - 1])
            T[i][0] = true;
        else
            break;
    }
    
    for (size_t j = 1; j <= n; ++j) {
        if (s2[j - 1] == s3[j - 1])
            T[0][j] = true;
        else
            break;
    }
    
    T[0][0] = true;
    
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j)
            if ((s1[i - 1] == s3[i + j - 1] && T[i - 1][j]) || (s2[j - 1] == s3[i + j - 1] && T[i][j - 1]))
                T[i][j] = true;
    }
    
    return T[m][n];
}
vector<TreeNode *> getTrees(int start, int end) {
    vector<TreeNode *> ret;
    if (start > end)  {
        ret.push_back(NULL);
        return ret;
    }
    if (start == end) {
        TreeNode *node = new TreeNode(start);
        ret.push_back(node);
        return ret;
    }
    
    for (int i = start; i <= end; ++i) {
        vector<TreeNode *> nl = getTrees(start, i - 1), nr = getTrees(i + 1, end);
        for (int l = 0; l < nl.size(); ++l) {
            for (int r = 0; r < nr.size(); ++r) {
                TreeNode *node = new TreeNode(i);
                node->left = nl[l];
                node->right = nr[r];
                ret.push_back(node);
            }
        }
    }
    
    return ret;
}

vector<TreeNode *> generateTrees(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<TreeNode *> ret;
    if (n == 0) {
        ret.push_back(NULL);
        return ret;
    }
    if (n == 1) {
        TreeNode *node = new TreeNode(1);
        ret.push_back(node);
        return ret;
    }
    
    ret = getTrees(1, n);
    
    return ret;
}
int getTrees(int start, int end) {
    if (start >= end) return 1;
    
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        int l = getTrees(start, i - 1), r = getTrees(i + 1, end);
        sum += l*r;
    }
    return sum;
}
int numTrees(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n <= 1) return n;
    return getTrees(1, n);
}
string intToRoman(int num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    char v[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int base = 10, start = 0;
    string ret = "";
    
    while (num > 0) {
        int digit = num % 10;
        num /= 10;
        string s = "";
        switch(digit) {
            case 1:
                s = s + v[start];
                break;
            case 2:
                s = s + v[start] + v[start];
                break;
            case 3:
                s = s + v[start] + v[start] + v[start];
                break;
            case 4:
                s = s + v[start] + v[start + 1];
                break;
            case 5:
                s = s + v[start + 1];
                break;
            case 6:
                s = s + v[start + 1] + v[start];
                break;
            case 7:
                s = s + v[start + 1] + v[start] + v[start];
                break;
            case 8:
                s = s + v[start + 1] + v[start] + v[start] + v[start];
                break;
            case 9:
                s = s + v[start] + v[start + 2];
                break;
            default:
                break;
        }
        ret = s + ret;
        start += 2;
    }
    return ret;
}
int romanToInt(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int ret = 0;
    vector<int> v(s.size(), 0);
    
    for (int i = 0; i < v.size(); ++i) {
        switch(s[i]) {
            case 'I':
                v[i] = 1;
                break;
            case 'V':
                v[i] = 5;
                break;
            case 'X':
                v[i] = 10;
                break;
            case 'L':
                v[i] = 50;
                break;
            case 'C':
                v[i] = 100;
                break;
            case 'D':
                v[i] = 500;
                break;
            case 'M':
                v[i] = 1000;
                break;
            default:
                break;
        }
    }
    
    int i = v.size() - 1;
    while (i >= 0) {
        if (i >= 1 && v[i - 1] < v[i]) {
            ret += v[i] - v[i - 1];
            i -= 2;
        }
        else
            ret += v[i--];
    }
    
    return ret;
}
void parseIP(string IP, string s, int count, unordered_set<string>& set) {
    if (count == 0) {
        if (s.length() == 0) return;
        if (s[0] == '0' && s.length() > 1) return;
        int i = atoi(s.c_str());
        if (i >= 0 && i <= 255)
            set.insert(IP + s);
        return;
    }
    
    for (int i = 1; i <= min(3, (int)s.length() - count); ++i) {
        string subs = s.substr(0, i);
        int val = atoi(subs.c_str());
        if (val >= 0 && val <= 255)
            parseIP(IP + subs + '.', s.substr(i), count - 1, set);
        if (s[0] == '0')
            break;
    }
}

vector<string> restoreIpAddresses(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<string> v;
    unordered_set<string> set;
    parseIP("", s, 3, set);
    for (unordered_set<string>::iterator it = set.begin(); it != set.end(); ++it)
        v.push_back(*it);
    return v;
}
ListNode *reverseBetween(ListNode *head, int m, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (m == n) return head;
    
    ListNode *start = NULL, *end = NULL, *prev = NULL, *cur = head, *next = NULL;
    int count = 1;
    bool flag = false;
    
    while (cur != NULL) {
        next = cur->next;
        if (count == m - 1)
            start = cur;
        if (count == m) {
            end = cur;
            flag = true;
        }
        if (flag)
            cur->next = prev;
        if (count == n) {
            if (start != NULL)
                start->next = cur;
            else
                head = cur;
            end->next = next;
            break;
        }
        prev = cur;
        cur = next;
        ++count;
    }
    
    return head;
}
vector<vector<int> > subsetsWithDup(vector<int> &S) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret(1, vector<int>());
    int start = 0, SZ = S.size();
    
    sort(S.begin(), S.end());
    
    while (start < SZ) {
        int count = 0;
        int c = start;
        while (c < SZ && S[c++] == S[start])
            ++count;
        int size = ret.size();
        for (int i = 0; i < size; ++i) {
            for (int j = 1; j <= count; ++j) {
                int k = j;
                vector<int> v(ret[i].begin(), ret[i].end());
                while (k-- > 0)
                    v.push_back(S[start]);
                ret.push_back(v);
            }
        }
        start += count;
    }
    
    return ret;
}
class fillRowSolution {
private:
    int size, count;
    vector<int> cols, left_to_right_diag, right_to_left_diag;
public:
    void fillRow(int row_index) {
        if (row_index == size) {
            ++count;
            return;
        }
        
        for (int j = 0; j < size; ++j) {
            int ldiag = size - 1 - (row_index - j), rdiag = row_index + j;
            /*
             int ri = size - 1 - row_index;
             if (j == row_index)
             ldiag = 0;
             else
             ldiag = (row_index > j) ? 2*abs(row_index - j) - 1 : 2*abs(row_index - j);
             if (j == ri)
             rdiag = 0;
             else
             rdiag = (j < ri) ? 2*abs(ri - j) - 1 : 2*abs(ri - j);
             */
            if (!cols[j] || !left_to_right_diag[ldiag] || !right_to_left_diag[rdiag])
                continue;
            cols[j] = false;
            left_to_right_diag[ldiag] = false;
            right_to_left_diag[rdiag] = false;
            fillRow(row_index + 1);
            cols[j] = true;
            left_to_right_diag[ldiag] = true;
            right_to_left_diag[rdiag] = true;
        }
    }
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n < 1) return 0;
        size = n;
        count = 0;
        cols.resize(n, true);
        left_to_right_diag.resize(2*n - 1, true);
        right_to_left_diag.resize(2*n - 1, true);
        fillRow(0);
        return count;
    }
};
//N Queen II
class NQueenIISolution {
private:
    int size, count;
    vector<int> cols, left_to_right_diag, right_to_left_diag;
public:
    void init(){
        cols.clear();
        left_to_right_diag.clear();
        right_to_left_diag.clear();
        cols.resize(size, 0);
        left_to_right_diag.resize(2*size - 1, 0);
        right_to_left_diag.resize(2*size - 1, 0);
    }
    void fillRow(int row_index) {
        if (row_index == size) {
            ++count;
            return;
        }
        
        for (int j = 0; j < ((row_index == 0) ? size/2 : size); ++j) {
            int ldiag = size - 1 - (row_index - j), rdiag = row_index + j;
            if (cols[j] || left_to_right_diag[ldiag] || right_to_left_diag[rdiag])
                continue;
            cols[j] = 1;
            left_to_right_diag[ldiag] = 1;
            right_to_left_diag[rdiag] = 1;
            fillRow(row_index + 1);
            cols[j] = 0;
            left_to_right_diag[ldiag] = 0;
            right_to_left_diag[rdiag] = 0;
        }
    }
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n < 1) return 0;
        if (n == 1) return 1;
        size = n;
        count = 0;
        init();
        fillRow(0);
        count <<= 1;
        if (n % 2 != 0) {
            int mid = n/2;
            init();
            cols[mid] = 1;
            left_to_right_diag[size - 1 + mid] = 1;
            right_to_left_diag[mid] = 1;
            fillRow(1);
        }
        return count;
    }
};
//Subset II
void addOneToCounter(vector<int> &counter, vector<int> &count, bool &flag) {
    int i = 0;
    while (i != counter.size()) {
        if (counter[i] < count[i]) {
            counter[i] += 1;
            break;
        }
        else {
            counter[i] = 0;
            ++i;
        }
    }
    if (i == counter.size())
        flag = false;
}

vector<vector<int> > subsetsWithDup(vector<int> &S) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    tr1::unordered_map<int,int> entry_map;
    tr1::unordered_map<int, int>::iterator it;
    vector<vector<int> > ret;
    sort(S.begin(), S.end());
    for (int i = 0; i < S.size(); ++i) {
        it = entry_map.find(S[i]);
        if (it == entry_map.end())
            entry_map.insert(pair<int, int>(S[i], 1));
        else
            it->second += 1;
    }
    
    vector<int> entry(entry_map.size()), count(entry_map.size());
    for (int i = 0, index = 0; i < S.size();) {
        it = entry_map.find(S[i]);
        entry[index] = it->first;
        count[index] = it->second;
        i += count[index];
        ++index;
    }
    
    bool flag = true;
    int SZ = entry.size();
    vector<int> counter(SZ, 0);
    while (flag) {
        vector<int> v;
        for (int i = 0; i < SZ; ++i) {
            int k = counter[i];
            while (k--)
                v.push_back(entry[i]);
        }
        ret.push_back(v);
        addOneToCounter(counter, count, flag);
    }
    return ret;
}
// Decode Ways
bool isValid(string &s) {
    if (s.size() == 0 || s[0] == '0')
        return false;
    for (int i = 1; i < s.length(); ++i) {
        int val = s[i - 1] - '0';
        if (s[i] == '0' && !(val == 1 || val == 2))
            return false;
    }
    return true;
}
int numDecodings(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int SZ = s.size();
    if (SZ == 0 || !isValid(s))
        return 0;
    vector<int> v(SZ + 1, 0);
    v[0] = 1;
    v[1] = 1;
    for (int i = 1; i < SZ; ++i) {
        int ival = s[i] - '0', jval = s[i - 1] - '0';
        if (jval == 1) {
            if (ival != 0)
                v[i + 1] = v[i] + v[i - 1];
            else
                v[i + 1] = v[i - 1];
        }
        else if (jval == 2) {
            if (ival > 0 && ival < 7)
                v[i + 1] = v[i] + v[i - 1];
            else if (ival == 0)
                v[i + 1] = v[i - 1];
            else
                v[i + 1] = v[i];
        }
        else
            v[i + 1] = v[i];
    }
    return v[SZ];
}
//Gray Code
size_t GrayToBinary(size_t num) {
    size_t num_bits = 8 * sizeof(num);
    for (size_t shift = 1; shift < num_bits; shift <<= 1)
        num = num ^ (num >> shift);
    return num;
}
size_t BinaryToGray(size_t num) {
    return num ^ (num >> 1);
}
vector<int> grayCode(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> ret;
    for (size_t i = 0; i < 1 << n; ++i)
        ret.push_back(BinaryToGray(GrayToBinary(BinaryToGray(i))));
    return ret;
}
//Merge Sorted Array
void merge(int A[], int m, int B[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    for (int i = m - 1; i >= 0; --i)
        A[i + n] = A[i];
    int k = 0, i = n, j = 0;
    while (k < m + n && i < n + m && j < n) {
        if (A[i] < B[j])
            A[k++] = A[i++];
        else
            A[k++] = B[j++];
    }
    while (j < n)
        A[k++] = B[j++];
}
//Scramble String
bool isMatch(string s1, int h1, int t1, string s2, int h2, int t2) {
    if (t1 - h1 != t2 - h2)
        return false;
    if (t1 < h1)
        return true;
    if (t1 == h1)
        return s1[h1] == s2[h2];
    unordered_map<char, int> count1, count2;
    unordered_map<char, int>::iterator it1, it2;
    for (int i = h1, j = h2; i <= t1 && j <= t2; ++i, ++j) {
        it1 = count1.find(s1[i]);
        if (it1 == count1.end())
            count1.insert(pair<char, int>(s1[i], 1));
        else
            ++(it1->second);
        it2 = count2.find(s2[j]);
        if (it2 == count2.end())
            count2.insert(pair<char, int>(s2[j], 1));
        else
            ++(it2->second);
    }
    for (it1 = count1.begin(); it1 != count1.end(); ++it1) {
        it2 = count2.find(it1->first);
        if (it2 == count2.end())
            return false;
        if (it2->second != it1->second)
            return false;
    }
    for (int i = h1; i < t1; ++i) {
        int k = i - h1 + h2, j = t2 - i + h1;
        if (isMatch(s1, h1, i, s2, h2, k) && isMatch(s1, i + 1, t1, s2, k + 1, t2))
            return true;
        if (isMatch(s1, h1, i, s2, j, t2) && isMatch(s1, i + 1, t1, s2, h2, j - 1))
            return true;
    }
    return false;
}
bool isScramble(string s1, string s2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return isMatch(s1, 0, s1.length() - 1, s2, 0, s2.length() - 1);
}
//Partition List
ListNode *partition(ListNode *head, int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    ListNode *cur = head, *nxt = NULL;
    ListNode *hsmaller = NULL, *pi = NULL, *hlarger = NULL, *pk = NULL;
    
    while (cur != NULL) {
        nxt = cur->next;
        cur->next = NULL;
        int v = cur->val;
        if (v < x) {
            if (hsmaller == NULL) {
                hsmaller = cur;
                pi = cur;
            }
            else {
                pi->next = cur;
                pi = cur;
            }
        }
        else {
            if (hlarger == NULL) {
                hlarger = cur;
                pk = cur;
            }
            else {
                pk->next = cur;
                pk = cur;
            }
        }
        cur = nxt;
    }
    
    if (hsmaller != NULL) {
        head = hsmaller;
        if (hlarger != NULL) {
            pi->next = hlarger;
        }
    }
    else
        head = hlarger;
    
    return head;
}
//Remove Duplicates from Sorted List II
ListNode *deleteDuplicates(ListNode *head) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    ListNode *prev = NULL, *cur = head, *nxt = NULL;
    head = NULL;
    while (cur != NULL) {
        nxt = cur->next;
        bool flag = false;
        while (nxt != NULL && cur->val == nxt->val) {
            flag = true;
            nxt = nxt->next;
        }
        if (prev != NULL && flag)
            prev->next = nxt;
        else if (flag)
            prev = nxt;
        else
            prev = cur;
        if (head == NULL && !flag)
            head = prev;
        cur = nxt;
    }
    return head;
}
//Remove Duplicates from Sorted List
ListNode *deleteDuplicates(ListNode *head) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    ListNode *cur = head, *nxt = NULL;
    
    while (cur != NULL) {
        nxt = cur->next;
        while (nxt != NULL && cur->val == nxt->val)
            nxt = nxt->next;
        cur->next = nxt;
        cur = nxt;
    }
    return head;
}
//Search in Rotated Sorted Array II
bool search(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int l = 0, h = n - 1;
    
    while (l <= h) {
        int mid = l + (h - l)/2;
        if (A[mid] == target)
            return true;
        if (A[mid] < target) {
            if (A[mid] > A[h] || A[h] >= target)
                l = mid + 1;
            else if (A[mid] < A[h])
                h = mid - 1;
            else
                --h;
        }
        else {
            if (A[mid] < A[h]|| A[l] <= target)
                h = mid - 1;
            else if (A[mid] > A[l])
                l = mid + 1;
            else
                ++l;
        }
    }
    return false;
}
//Search in Rotated Sorted Array
int search(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n == 0) return false;
    int l = 0, h = n - 1;
    
    while (l <= h) {
        int mid = l + (h - l)/2;
        if (A[mid] == target)
            return mid;
        if (A[mid] < target) {
            if (A[mid] > A[h] || A[mid] > A[l] || A[h] >= target)
                l = mid + 1;
            else
                h = mid - 1;
        }
        else {
            if (A[mid] < A[h] || A[mid] < A[l] || A[l] <= target)
                h = mid - 1;
            else
                l = mid + 1;
        }
    }
    return -1;
}
int search(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int l = 0, h = n - 1;
    
    while (l <= h) {
        int mid = l + (h - l)/2;
        if (A[mid] == target)
            return mid;
        if (A[l] <= A[mid]) {
            if (A[l] > target || A[mid] < target)
                l = mid + 1;
            else
                h = mid - 1;
        }
        else {
            if (A[h] < target || A[mid] > target)
                h = mid - 1;
            else
                l = mid + 1;
        }
    }
    return -1;
}
bool search(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int l = 0, h = n - 1;
    
    while (l <= h) {
        int mid = l + (h - l)/2;
        if (A[mid] == target)
            return true;
        if (A[l] < A[mid]) {
            if (A[l] > target || A[mid] < target)
                l = mid + 1;
            else
                h = mid - 1;
        }
        else if (A[l] > A[mid]) {
            if (A[h] < target || A[mid] > target)
                h = mid - 1;
            else
                l = mid + 1;
        }
        else
            ++l;
    }
    return false;
}
//Word Search
bool DFS(vector<vector<char> > &board, int i, int j, vector<vector<bool> > &visited, string &word, int index) {
    if (index >= word.length())
        return true;
    size_t n = visited.size(), m = visited[0].size();
    //top
    if (i + 1 < n && !visited[i + 1][j] && board[i + 1][j] == word[index]) {
        visited[i + 1][j] = true;
        if (DFS(board, i + 1, j, visited, word, index + 1))
            return true;
        visited[i + 1][j] = false;
    }
    //bottom
    if (i - 1 >= 0 && !visited[i - 1][j] && board[i - 1][j] == word[index]) {
        visited[i - 1][j] = true;
        if (DFS(board, i - 1, j, visited, word, index + 1))
            return true;
        visited[i - 1][j] = false;
    }
    //left
    if (j - 1 >= 0 && !visited[i][j - 1] && board[i][j - 1] == word[index]) {
        visited[i][j - 1] = true;
        if (DFS(board, i, j - 1, visited, word, index + 1))
            return true;
        visited[i][j - 1] = false;
    }
    //right
    if (j + 1  < m && !visited[i][j + 1] && board[i][j + 1] == word[index]) {
        visited[i][j + 1] = true;
        if (DFS(board, i, j + 1, visited, word, index + 1))
            return true;
        visited[i][j + 1] = false;
    }
    return false;
}
bool exist(vector<vector<char> > &board, string word) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    size_t n = board.size(), m = board[0].size();
    if (n == 0 || m == 0)
        return word == "";
    if (word == "")
        return true;
    vector<vector<bool> > visited(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] == word[0]) {
                visited[i][j] = true;
                if (DFS(board, i, j, visited, word, 1))
                    return true;
                visited[i][j] = false;
            }
        }
    }
    return false;
}
//Subset
vector<vector<int> > subsets(vector<int> &S) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret(1, vector<int>());
    int start = 0, SZ = S.size();
    sort(S.begin(), S.end());
    while (start < SZ) {
        int count = 0;
        int size = ret.size();
        for (int i = 0; i < size; ++i) {
            vector<int> v(ret[i].begin(), ret[i].end());
            v.push_back(S[start]);
            ret.push_back(v);
        }
        ++start;
    }
    return ret;
}
//Combination
vector<vector<int> > combine(int n, int k) {
    vector<vector<int> > ret;
    vector<int> entry;
    combine(n, k, 1, entry, ret);
    return ret;
}

void combine(int n, int k, int i, vector<int> &entry, vector<vector<int> > &ret) {
    if (entry.size() == k) {
        ret.push_back(entry);
        return;
    }
    for (int j = i; j <= n; j++) {
        entry.push_back(j);
        combine(n, k, j + 1, entry, ret);
        entry.pop_back();
    }
}
//Minimum Window Substring
string minWindow(string S, string T) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    unordered_map<char, int> m1, m2;
    unordered_map<char, int>::iterator it1, it2;
    int count = 0;
    for (int i = 0; i < T.length(); ++i) {
        it1 = m1.find(T[i]);
        if (it1 == m1.end()) {
            ++count;
            m1.insert(pair<char, int>(T[i], 1));
            m2.insert(pair<char, int>(T[i], 0));
        }
        else
            ++it1->second;
    }
    int i = 0, j = 0, c = 0, start = 0, end = S.length();
    bool flag = false;
    for (i = 0; i < S.length(); ++i) {
        it2 = m2.find(S[i]);
        if (it2 == m2.end())
            continue;
        ++it2->second;
        it1 = m1.find(S[i]);
        if (it2->second == it1->second)
            ++c;
        if (c == count)
            flag = true;
        while (flag && j <= i) {
            it1 = m1.find(S[j]);
            it2 = m2.find(S[j]);
            if (it1 == m1.end()) {
                ++j;
                continue;
            }
            if (it2->second >= it1->second) {
                if (i - j < end - start) {
                    start = j;
                    end = i;
                }
                if (it2->second == it1->second)
                    break;
                ++j;
                --it2->second;
            }
            else
                break;
        }
    }
    if (end - start == S.length())
        return "";
    return S.substr(start, end - start + 1);
}
//Permutations II
vector<vector<int> > permuteUnique(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret;
    sort(num.begin(), num.end());
    do {
        ret.push_back(num);
    } while (next_permutation(num.begin(), num.end()));
    return ret;
}
//Permutation
bool nextPermutation(vector<int>::iterator first, vector<int>::iterator last) {
    if (first == last)
        return false;
    vector<int>::iterator i = first;
    if (++i == last)
        return false;
    i = last;
    --i;
    while (true) {
        vector<int>::iterator ii = i;
        --i;
        if (*i < *ii) {
            vector<int>::iterator j = last;
            while (!(*i < *--j))
                ;
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}
bool prevPermutation(vector<int>::iterator first, vector<int>::iterator last) {
    if (first == last)
        return false;
    vector<int>::iterator i = first;
    if (++i == last)
        return false;
    i = last;
    --i;
    while (true) {
        vector<int>::iterator ii = i;
        --i;
        if (*i > *ii) {
            vector<int>::iterator j = last;
            while (!(*i > *--j))
                ;
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}
void nextPermutation(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    nextPermutation(num.begin(), num.end());
    prevPermutation(num.begin(), num.end());
    nextPermutation(num.begin(), num.end());
}
//Rotate Image
void rotate(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int n = matrix.size();
    
    for (int i = 0; i < n/2; ++i) {
        for (int j = i; j < n - 1 - i; ++j) {
            //(i, j), (j, n - 1 - i), (n - 1 - i, n - 1 - j), (n - 1 - j, i)
            int tmp = matrix[n - 1 - j][i];
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
            matrix[j][n - 1 - i] = matrix[i][j];
            matrix[i][j] = tmp;
        }
    }
}
//Anagram
vector<string> anagrams(vector<string> &strs) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    unordered_map<string, vector<string> > sorted_s;
    unordered_map<string, vector<string> >::iterator it;
    for (int i = 0; i < strs.size(); ++i) {
        string s = strs[i];
        sort(s.begin(), s.end());
        it = sorted_s.find(s);
        if (it == sorted_s.end()) {
            vector<string> v;
            v.push_back(strs[i]);
            sorted_s.insert(pair<string, vector<string> >(s, v));
        }
        else
            it->second.push_back(strs[i]);
    }
    vector<string> ret;
    for (it = sorted_s.begin(); it != sorted_s.end(); ++it) {
        if (it->second.size() > 1) {
            for (int i = 0; i < it->second.size(); ++i)
                ret.push_back(it->second[i]);
        }
    }
    
    return ret;
}
//Word Ladder I
class Solution {
    struct Node {
        int index, dist;
        bool visited;
        vector<int> adjList;
        Node(int i, int d, bool f, vector<int>& v)
        : index(i), dist(d), visited(f), adjList(v) {}
    };
    int getDiff(string &t, string &p) {
        if (t.length() != p.length())
            return 2;
        int count = 0;
        for (int i = 0; i < t.length(); ++i) {
            if (t[i] != p[i])
                ++count;
            if (count == 2)
                return 2;
        }
        return count;
    }
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //special case I
        if (dict.find(end) != dict.end() && getDiff(start, end) == 1)
            return 2;
        //special case II
        if (start.compare(end) == 0) {
            unordered_set<string>::iterator it;
            for (it = dict.begin(); it != dict.end(); ++it) {
                string s = *it;
                if (getDiff(s, end) == 1)
                    return 3;
            }
            return 0;
        }
        //strings other than the end
        vector<string> dictV;
        //graph
        vector<Node> wordsMap;
        //lable all the strings in dict
        int startIndex = -1;
        for (unordered_set<string>::iterator setIt = dict.begin(); setIt != dict.end(); ++setIt) {
            if (end.compare(*setIt) != 0)
                dictV.push_back(*setIt);
            if (start.compare(*setIt) == 0)
                startIndex = dictV.size() - 1;
        }
        dictV.push_back(start);
        dictV.push_back(end);
        int SZ = dictV.size();
        for (int i = 0; i < dictV.size(); ++i) {
            vector<int> v;
            Node node(i, INT_MAX, false, v);
            wordsMap.push_back(node);
        }
        //build a map for all possible substrings
        unordered_map<string, unordered_set<int> > substringMap;
        unordered_map<string, unordered_set<int> >::iterator mapIt;
        for (int i = 0; i < dictV.size(); ++i) {
            for (int j = 0; j < dictV[i].size(); ++j) {
                string s = dictV[i].substr(0, j) + '*' + dictV[i].substr(j + 1);
                mapIt = substringMap.find(s);
                if (mapIt == substringMap.end()) {
                    unordered_set<int> set;
                    set.insert(i);
                    substringMap.insert(pair<string, unordered_set<int> >(s, set));
                }
                else
                    mapIt->second.insert(i);
            }
        }
        //connect nodes
        unordered_set<int>::iterator iIt, jIt;
        for (mapIt = substringMap.begin(); mapIt != substringMap.end(); ++mapIt) {
            for (iIt = mapIt->second.begin(); iIt != mapIt->second.end(); ++iIt) {
                for (jIt = mapIt->second.begin(); jIt != mapIt->second.end(); ++jIt) {
                    int i = *iIt, j = *jIt;
                    if (i < j && !(i == SZ - 2 && j == SZ - 1) && !(i == startIndex && j == SZ - 2)) {
                        wordsMap[i].adjList.push_back(j);
                        wordsMap[j].adjList.push_back(i);
                    }
                }
            }
        }
        //BFS for shortest paths
        queue<int> q;
        q.push(SZ - 2);
        wordsMap[SZ - 2].dist = 1;
        while (!q.empty()) {
            int ni = q.front();
            q.pop();
            if (wordsMap[ni].visited)
                continue;
            wordsMap[ni].visited = true;
            if (ni == SZ - 1)
                return wordsMap[ni].dist;
            for (int i = 0; i < wordsMap[ni].adjList.size(); ++i) {
                int j = wordsMap[ni].adjList[i];
                if (!wordsMap[j].visited && wordsMap[j].dist > wordsMap[ni].dist + 1) {
                    wordsMap[j].dist = wordsMap[ni].dist + 1;
                    q.push(j);
                }
            }
        }
        return 0;
    }
};
//Word Ladder II
class Solution {
    struct Node {
        int index, dist;
        bool visited;
        vector<int> adjList;
        vector<vector<string> > paths;
        Node(int i, int d, bool f, vector<int>& v, vector<vector<string> > &p)
        : index(i), dist(d), visited(f), adjList(v), paths(p) {}
    };
    int getDiff(string &t, string &p) {
        if (t.length() != p.length())
            return 2;
        int count = 0;
        for (int i = 0; i < t.length(); ++i) {
            if (t[i] != p[i])
                ++count;
            if (count == 2)
                return 2;
        }
        return count;
    }
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string> > ret;
        //special case I
        if (dict.find(end) != dict.end()) {
            if (getDiff(start, end) == 1) {
                vector<string> stringV;
                stringV.push_back(start);
                stringV.push_back(end);
                ret.push_back(stringV);
                return ret;
            }
        }
        //special case II
        if (start.compare(end) == 0) {
            unordered_set<string>::iterator it;
            for (it = dict.begin(); it != dict.end(); ++it) {
                string s = *it;
                if (getDiff(s, end) == 1) {
                    vector<string> stringV;
                    stringV.push_back(start);
                    stringV.push_back(s);
                    stringV.push_back(end);
                    ret.push_back(stringV);
                }
            }
            return ret;
        }
        //strings other than the end
        vector<string> dictV;
        //graph
        vector<Node> wordsMap;
        //lable all the strings in dict
        int startIndex = -1;
        for (unordered_set<string>::iterator setIt = dict.begin(); setIt != dict.end(); ++setIt) {
            if (end.compare(*setIt) != 0)
                dictV.push_back(*setIt);
            if (start.compare(*setIt) == 0)
                startIndex = dictV.size() - 1;
        }
        dictV.push_back(start);
        dictV.push_back(end);
        int SZ = dictV.size();
        for (int i = 0; i < dictV.size(); ++i) {
            vector<int> v;
            vector<vector<string> > paths;
            Node node(i, INT_MAX, false, v, paths);
            wordsMap.push_back(node);
        }
        //build a map for all possible substrings
        unordered_map<string, unordered_set<int> > substringMap;
        unordered_map<string, unordered_set<int> >::iterator mapIt;
        for (int i = 0; i < dictV.size(); ++i) {
            for (int j = 0; j < dictV[i].size(); ++j) {
                string s = dictV[i].substr(0, j) + '*' + dictV[i].substr(j + 1);
                mapIt = substringMap.find(s);
                if (mapIt == substringMap.end()) {
                    unordered_set<int> set;
                    set.insert(i);
                    substringMap.insert(pair<string, unordered_set<int> >(s, set));
                }
                else
                    mapIt->second.insert(i);
            }
        }
        //connect nodes
        unordered_set<int>::iterator iIt, jIt;
        for (mapIt = substringMap.begin(); mapIt != substringMap.end(); ++mapIt) {
            for (iIt = mapIt->second.begin(); iIt != mapIt->second.end(); ++iIt) {
                for (jIt = mapIt->second.begin(); jIt != mapIt->second.end(); ++jIt) {
                    int i = *iIt, j = *jIt;
                    if (i < j && !(i == SZ - 2 && j == SZ - 1) && !(i == startIndex && j == SZ - 2)) {
                        wordsMap[i].adjList.push_back(j);
                        wordsMap[j].adjList.push_back(i);
                    }
                }
            }
        }
        //BFS for shortest paths
        queue<int> q;
        q.push(SZ - 2);
        wordsMap[SZ - 2].dist = 0;
        vector<string> sV;
        wordsMap[SZ - 2].paths.push_back(sV);
        while (!q.empty()) {
            int ni = q.front();
            q.pop();
            if (wordsMap[ni].visited)
                continue;
            wordsMap[ni].visited = true;
            for (int i = 0; i < wordsMap[ni].paths.size(); ++i) {
                wordsMap[ni].paths[i].push_back(dictV[ni]);
            }
            if (ni == SZ - 1)
                return wordsMap[ni].paths;
            for (int i = 0; i < wordsMap[ni].adjList.size(); ++i) {
                int j = wordsMap[ni].adjList[i];
                if (!wordsMap[j].visited) {
                    if (wordsMap[j].dist > wordsMap[ni].dist + 1) {
                        wordsMap[j].dist = wordsMap[ni].dist + 1;
                        wordsMap[j].paths.clear();
                        for (int i = 0; i < wordsMap[ni].paths.size(); ++i)
                            wordsMap[j].paths.push_back(wordsMap[ni].paths[i]);
                        q.push(j);
                    }
                    else if (wordsMap[j].dist == wordsMap[ni].dist + 1) {
                        for (int i = 0; i < wordsMap[ni].paths.size(); ++i)
                            wordsMap[j].paths.push_back(wordsMap[ni].paths[i]);
                    }
                }
            }
        }
        ret.clear();
        return ret;
    }
};
//Sudoku Solver
class Solution {
    static const int SZ = 9;
public:
    bool isValid(int iIndex, int jIndex, vector<vector<char> > &board) {
        //same row
        for (int k = 0; k < SZ; ++k)
            if (k != jIndex && board[iIndex][k] == board[iIndex][jIndex])
                return false;
        //same col
        for (int k = 0; k < SZ; ++k)
            if (k != iIndex && board[k][jIndex] == board[iIndex][jIndex])
                return false;
        //same block
        int is = iIndex/3, js = jIndex/3;
        for (int i = 3*is; i <= 3*is + 2; ++i)
            for (int j = 3*js; j <= 3*js + 2; ++j)
                if ((i != iIndex || j != jIndex) && board[i][j] == board[iIndex][jIndex])
                    return false;
        return true;
    }
    bool isSolvableSudoku(vector<vector<char> > &board) {
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j < SZ; ++j) {
                if (board[i][j] == '.') {
                    for (int k = 0; k < SZ; ++k) {
                        board[i][j] = '1' + k;
                        if (isValid(i, j, board) && isSolvableSudoku(board))
                            return true;
                    }
                    board[i][j] = '.';
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        isSolvableSudoku(board);
    }
};
//Valid Sudoku
class Solution {
    static const int SZ = 9;
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (int i = 0; i < SZ; ++i) {
            for (int j = 0; j < SZ; ++j) {
                if (board[i][j] != '.') {
                    //same row
                    for (int k = 0; k < SZ; ++k)
                        if (k != j && board[i][k] == board[i][j])
                            return false;
                    //same col
                    for (int k = 0; k < SZ; ++k)
                        if (k != i && board[k][j] == board[i][j])
                            return false;
                }
            }
        }
        //check block
        for (int index = 0; index < SZ; ++index) {
            vector<bool> v(SZ, false);
            int is = index / 3, js = index % 3;
            for (int i = 3*is; i <= 3*is + 2; ++i)
                for (int j = 3*js; j <= 3*js + 2; ++j)
                    if (board[i][j] != '.') {
                        int k = board[i][j] - '1';
                        if (v[k])
                            return false;
                        else
                            v[k] = true;
                    }
        }
        return true;
    }
};
//Insert Interval
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int newS = newInterval.start, newE = newInterval.end, SZ = intervals.size();
        //special cases
        if (SZ == 0 || intervals[SZ - 1].end < newS) {
            intervals.push_back(newInterval);
            return intervals;
        }
        if (intervals[0].start > newE) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        //find rightIndex with start = ceil(newE)
        int leftIndex = -1, rightIndex = -1;
        if (intervals[SZ - 1].start <= newE)
            rightIndex = SZ - 1;
        else {
            //binary search
            int l = 0, h = SZ - 1;
            while (h - l > 1) {
                int mid = l + (h - l)/2;
                if (intervals[mid].start == newE) {
                    l = mid;
                    break;
                }
                if (intervals[mid].start < newE)
                    l = mid;
                else
                    h = mid;
            }
            rightIndex = l;
        }
        if (intervals[rightIndex].end < newS) {
            intervals.insert(intervals.begin() + rightIndex + 1, newInterval);
            return intervals;
        }
        //find leftIndex with end = floor(newS)
        if (intervals[0].end >= newS)
            leftIndex = 0;
        else {
            //binary search
            int l = 0, h = SZ - 1;
            while (h - l > 1) {
                int mid = l + (h - l)/2;
                if (intervals[mid].end == newS) {
                    h = mid;
                    break;
                }
                if (intervals[mid].end > newS)
                    h = mid;
                else
                    l = mid;
            }
            leftIndex = h;
        }
        //get updated range
        intervals[leftIndex].start = min(newS, intervals[leftIndex].start);
        intervals[leftIndex].end = max(newE, intervals[rightIndex].end);
        intervals.erase(intervals.begin() + leftIndex + 1, intervals.begin() + rightIndex + 1);
        return intervals;
    }
};
//Merge Intervals
class Solution {
    struct intervalCompClass {
        bool operator() (Interval i, Interval j) { return i.start < j.start;}
    } intervalCompObject;
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(intervals.begin(), intervals.end(), intervalCompObject);
        vector<Interval> ret;
        if (intervals.empty())
            return ret;
        int s = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i].start <= intervals[s].end)
                intervals[s].end = max(intervals[s].end, intervals[i].end);
            else {
                ret.push_back(intervals[s]);
                s = i;
            }
        }
        if (s == 0 || s < intervals.size())
            ret.push_back(intervals[s]);
        return ret;
    }
};
//Jump Game
bool canJump(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int r = 0;
    vector<bool> isReachable(n, false);
    isReachable[0] = true;
    for (int i = 0; i < n; ++i) {
        if (A[i] != 0 && isReachable[i] && i + A[i] > r) {
            for (int j = r + 1; j <= min(n - 1, i + A[i]); ++j)
                isReachable[j] = true;
            r = i + A[i];
        }
        if (i > r)
            break;
    }
    return isReachable[n - 1];
}
//Jump Game II
int jump(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> steps(n, INT_MAX);
    steps[0] = 0;
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (r < i + A[i]) {
            for (int j = r + 1; j <= min(n - 1, i + A[i]); ++j)
                steps[j] = min(steps[j], steps[i] + 1);
            r = i + A[i];
        }
    }
    return steps[n - 1];
}
//Spiral Matrix
vector<int> spiralOrder(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> ret;
    if (matrix.empty())
        return ret;
    int n = matrix.size(), m = matrix[0].size();
    int SZ = min(m, n);
    for (int i = 0; i <= SZ / 2; ++i) {
        if ( i == SZ / 2 && SZ % 2 == 0)
            break;
        //top
        for (int j = i; j < m - i; ++j)
            ret.push_back(matrix[i][j]);
        //right
        for (int k = i + 1; k < n - 1 - i; ++k)
            ret.push_back(matrix[k][m - 1 - i]);
        //bottom
        if (n - 1 - i > i)
            for (int j = m - 1 - i; j >= i; --j)
                ret.push_back(matrix[n - 1 - i][j]);
        //left
        if (m - 1 - i > i)
            for (int k = n - 2 - i; k > i; --k)
                ret.push_back(matrix[k][i]);
    }
    return ret;
}
struct Car{
    double S, P;
    Car(double s, double p) : S(s), P(p) {}
};
bool positionComp(Car i, Car j) {return i.P < j.P;}
int changeLane(Car icar, vector<Car> &lane) {
    if (lane.size() == 0) {
        lane.push_back(icar);
        return 0;
    }
    for (int i = 0; i < lane.size(); ++i)
        if (abs(lane[i].P - icar.P) < L)
            return -2;
    int i = 0;
    for (; i < lane.size(); ++i)
        if (lane[i].P > icar.P)
            break;
    lane.insert(lane.begin() + i, icar);
    return i;
}
double nextEvent(vector<Car> &left, vector<Car> &right) {
    //get time slot
    double slot = INT_MAX;
    bool leftfound = false, rightfound = false;
    int index;
    //find in left
    for (int i = 0; i < (int)left.size() - 1; ++i)
        if (left[i].S > left[i + 1].S) {
            double t = (double)(left[i + 1].P - left[i].P - L) / (left[i].S - left[i + 1].S);
            if (slot > t) {
                slot = t;
                leftfound = true;
                index = i;
            }
        }
    //find in right
    for (int i = 0; i < (int)right.size() - 1; ++i)
        if (right[i].S > right[i + 1].S) {
            double t = (double)(right[i + 1].P - right[i].P - L) / (right[i].S - right[i + 1].S);
            if (slot > t) {
                slot = t;
                rightfound = true;
                index = i;
            }
        }
    if (!leftfound && !rightfound)
        return -1;
    if (slot == 0)
        return 0;
    //update positions after slot
    for (int i = 0; i < left.size(); ++i)
        left[i].P += slot*left[i].S;
    for (int i = 0; i < right.size(); ++i)
        right[i].P += slot*right[i].S;
    //car to change
    if (!rightfound)
        left.swap(right);
    double t1 = -2, t2 = -2;
    Car icar(right[index].S, right[index].P);
    right.erase(right.begin() + index);
    int i = changeLane(icar, left);
    if (i != -2) {
        t1 = nextEvent(left, right);
        left.erase(left.begin() + i);
        if (t1 == -1)
            return -1;
    }
    right.insert(right.begin() + index, icar);
    Car jcar(right[index + 1].S, right[index + 1].P);
    right.erase(right.begin() + index + 1);
    int j = changeLane(jcar, left);
    if (j != -2) {
        t2 = nextEvent(left, right);
        left.erase(left.begin() + j);
        if (t2 == -1)
            return -1;
    }
    right.insert(right.begin() + index + 1, jcar);
    if (t1 < 0 & t2 < 0)
        return slot;
    if (t1 < 0 && t2 >= 0)
        return slot + t2;
    if (t2 < 0 && t1 >= 0)
        return slot + t1;
    return slot + max(t1, t2);
}
double process(){
    int N;
    fin >> N;
    vector<Car> left, right;
    for (int i = 0; i < N; ++i) {
        char c;
        double s, p;
        fin >> c >> s >> p;
        Car car(s, p);
        if (c == 'L')
            left.push_back(car);
        else
            right.push_back(car);
    }
    sort(left.begin(), left.end(), positionComp);
    sort(right.begin(), right.end(), positionComp);
    return nextEvent(left, right);
}
//Sort Colors
void sortColors(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int s = -1, cur = 0, l = n, key = 1;
    while (cur < l) {
        if (A[cur] < key)
            swap(A[++s], A[cur++]);
        else if (A[cur] > key)
            swap(A[--l], A[cur]);
        else
            ++cur;
    }
}
//Search a 2D Matrix
bool searchMatrix(vector<vector<int> > &matrix, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (matrix.empty() || matrix[0].empty())
        return false;
    int n = matrix.size(), m = matrix[0].size();
    //locate row ceil(target)
    int l = 0, h = n - 1, i;
    if (matrix[h][0] <= target)
        i = h;
    else {
        while (h - l > 1) {
            int mid = l + (h - l)/2;
            if (matrix[mid][0] == target)
                return true;
            else if (matrix[mid][0] > target)
                h = mid;
            else
                l = mid;
        }
        i = l;
    }
    //locate row
    l = 0, h = m - 1;
    while (l <= h) {
        int mid = l + (h - l)/2;
        if (matrix[i][mid] == target)
            return true;
        else if (matrix[i][mid] > target)
            h = mid - 1;
        else
            l = mid + 1;
    }
    return false;
}
//Set Matrix Zero
void setZeroes(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (matrix.empty() || matrix[0].empty())
        return;
    int n = matrix.size(), m = matrix[0].size(), rowIndex = -1;
    //using row at rowIndex for constant storage
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 0 && rowIndex == -1)
                rowIndex = i;
            if (matrix[i][j] == 0 && rowIndex != -1) {
                for (int k = 0; k < j; ++k)
                    matrix[i][k] = 0;
                matrix[rowIndex][j] = 1;
                for (int k = j + 1; k < m; ++k)
                    if (matrix[i][k] == 0)
                        matrix[rowIndex][k] = 1;
                    else
                        matrix[i][k] = 0;
                break;
            }
        }
    }
    if (rowIndex != -1) {
        for (int j = 0; j < m; ++j) {
            if (matrix[rowIndex][j] == 1) {
                for (int k = 0; k < n; ++k)
                    matrix[k][j] = 0;
            }
        }
    }
}
//Edit Distance
int minDistance(string word1, string word2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int n = word1.size(), m = word2.size();
    if (n == 0 || m == 0)
        return max(m, n);
    vector<vector<int> > A(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; ++i)
        A[i][0] = i;
    for (int j = 0; j <= m; ++j)
        A[0][j] = j;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            A[i][j] = A[i - 1][j - 1] + ((word1[i - 1] == word2[j - 1]) ? 0 : 1);
            A[i][j] = min(A[i][j], 1 + min(A[i - 1][j], A[i][j - 1]));
        }
    return A[n][m];
}
//Simplify Path
string simplifyPath(string path) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int prev = -1, cur = 0, n = path.length();
    bool flag = false;
    stack<string> s;
    string str;
    while (cur < n) {
        if (cur < n - 1 && path[cur] == '/' && path[cur + 1] == '/')
            ;
        else if (!flag && path[cur] == '/') {
            prev = cur;
            flag = true;
        }
        else if (flag && (cur == n - 1 || path[cur + 1] == '/')) {
            if (path[cur] == '/')
                str = path.substr(prev + 1, cur - prev - 1);
            else
                str = path.substr(prev + 1, cur - prev);
            if (str != ".") {
                if (str != "..")
                    s.push(str);
                else if (!s.empty())
                    s.pop();
            }
            flag = false;
        }
        ++cur;
    }
    if (s.empty())
        return "/";
    str = "";
    while(!s.empty()) {
        str = '/' + s.top() + str;
        s.pop();
    }
    return str;
}
string simplifyPath(string path) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int start = 0, cur = 1, n = path.length();
    bool startMatched = false;
    stack<string> s;
    while (cur < n) {
        if (path[cur] == '/' || cur == n - 1) {
            if ((cur < n - 1 && path[cur + 1] == '/' && start != 0) && startMatched) {
                start = ++cur;
                continue;
            }
            string str = path.substr(start, cur - start);
            if (cur == n - 1 && path[cur] != '/')
                str = path.substr(start);
            if (str.empty() || str == "/" || str == "/.")
                ;
            else if (str != "/..")
                s.push(str);
            else if (!s.empty())
                s.pop();
            start = cur;
            startMatched = false;
        }
        ++cur;
    }
    if (s.empty())
        return "/";
    string str = "";
    while(!s.empty()) {
        str = s.top() + str;
        s.pop();
    }
    return str;
}
//Longest Consecutive Sequence
int longestConsecutive(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    unordered_set<int> numSet;
    for (int i = 0; i < num.size(); ++i)
        numSet.insert(num[i]);
    int longest = 0;
    while (!numSet.empty()) {
        int ival = *(numSet.begin());
        numSet.erase(ival);
        int count = 1;
        //look for bigger
        int i = ival;
        while (i < INT_MAX) {
            if (numSet.find(i + 1) != numSet.end()) {
                numSet.erase(++i);
                ++count;
            }
            else
                break;
        }
        if (i == INT_MAX && numSet.find(i) != numSet.end()) {
            numSet.erase(i);
            ++count;
        }
        //look for smaller
        i = ival;
        while (i > INT_MIN) {
            if (numSet.find(i - 1) != numSet.end()) {
                numSet.erase(--i);
                ++count;
            }
            else
                break;
        }
        if (i == INT_MIN && numSet.find(i) != numSet.end()) {
            numSet.erase(i);
            ++count;
        }
        longest = max(longest, count);
    }
    return longest;
}
class Solution {
    vector<int> sz, id;
    int find(int i) {
        int p = id[i];
        while (p != id[p]) {
            id[p] = id[id[p]];
            p = id[p];
        }
        return p;
    }
    void join(int i, int j) {
        int p = find(i), q = find(j);
        if (p == q)
            return;
        if (sz[p] > sz[q]) {
            id[q] = p;
            sz[p] += sz[q];
        }
        else {
            id[p] = q;
            sz[q] += sz[p];
        }
    }
public:
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        unordered_map<int, int> map;
        unordered_map<int, int>::iterator it;
        sz.clear();
        id.clear();
        int index = 0;
        for (int i = 0; i < num.size(); ++i) {
            if (map.find(num[i]) == map.end()) {
                map.insert(pair<int, int>(num[i], index));
                id.push_back(index);
                sz.push_back(1);
                ++index;
            }
        }
        //find connections
        for (int i = 0; i < num.size(); ++i) {
            if (num[i] != INT_MAX) {
                it = map.find(num[i] + 1);
                if (it != map.end())
                    join(map.find(num[i])->second, it->second);
            }
            if (num[i] != INT_MIN) {
                it = map.find(num[i] - 1);
                if (it != map.end())
                    join(map.find(num[i])->second, it->second);
            }
        }
        int l = 0;
        for (int i = 0; i < sz.size(); ++i)
            l = max(l, sz[i]);
        return l;
    }
};
//Sqrt(x)
int sqrt(int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (x == 0) return 0;
    if (x < 3) return 1;
    double r = 1;
    double delta = 0.1;
    while (true) {
        r = (r + x / r) / 2;
        if (abs(r*r - x) < delta)
            break;
    }
    return (int)r;
}
//Sum Root to Leaf Numbers
int getSum(TreeNode *node, int sum) {
    if (node == NULL)
        return 0;
    sum = sum*10 + node->val;
    if (node->left == NULL && node->right == NULL)
        return sum;
    int leftSum = 0, rightSum = 0;
    if (node->left != NULL)
        leftSum = getSum(node->left, sum);
    if (node->right != NULL)
        rightSum = getSum(node->right, sum);
    return leftSum + rightSum;
}
int sumNumbers(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    return getSum(root, 0);
}
//Unique Paths
int getCombination(int r, int n) {
    if (r == 0 || r == n)
        return 1;
    if (r == 1)
        return n;
    vector<vector<int> > matrix(r, vector<int>(n, 0));
    matrix[0][0] = 1;
    for (int j = 0; j < n; ++j)
        matrix[0][j] = j + 1;
    for (int i = 1; i < r; ++i)
        for (int j = 1; j < n; ++j)
            matrix[i][j] = matrix[i - 1][j - 1] + matrix[i][j - 1];
    return matrix[r - 1][n - 1];
}
int uniquePaths(int m, int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    --n;
    --m;
    int r = (m > n) ? n : m;
    n += m;
    return getCombination(r, n);
}
//Unique Paths II
int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    vector<vector<int> > matrix(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
        if (!obstacleGrid[i][0])
            matrix[i][0] = 1;
        else
            break;
    for (int j = 0; j < m; ++j)
        if (!obstacleGrid[0][j])
            matrix[0][j] = 1;
        else
            break;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
            if (!obstacleGrid[i][j])
                matrix[i][j] = matrix[i][j - 1] + matrix[i - 1][j];
    return matrix[n - 1][m - 1];
}
//Rotate List
ListNode *rotateRight(ListNode *head, int k) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (head == NULL)
        return head;
    int n = 0;
    ListNode *cur = head;
    while (cur != NULL) {
        ++n;
        cur = cur->next;
    }
    k = k % n;
    if (k == 0)
        return head;
    int index = 1;
    cur = head;
    while (index < n - k) {
        ++index;
        cur = cur->next;
    }
    ListNode *first = head, *next = cur->next;
    head = next;
    cur->next = NULL;
    while (next != NULL) {
        cur = next;
        next = cur->next;
    }
    cur->next = first;
    return head;
}
//Permutation Sequence
string getPermutation(int n, int k) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int A[] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    vector<bool> isUsed(n + 1, false);
    string s = "";
    int nVal = n;
    while (k > 0 && nVal > 0) {
        int count = 0;
        if (nVal > 1)
            count = (k - 1) / A[nVal - 1];
        k -= count * A[nVal - 1];
        char c = 'x';
        for (int i = 1; i <= n; ++i)
            if (!isUsed[i]) {
                if (count == 0) {
                    c = '0' + i;
                    isUsed[i] = true;
                    break;
                }
                --count;
            }
        s = s + c;
        --nVal;
    }
    if (s.length() < n)
        for (int i = 1; i <= n; ++i)
            if (!isUsed[i]) {
                char c = '0' + i;
                s = s + c;
            }
    return s;
}
//Spiral Matrix II
vector<vector<int> > generateMatrix(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> > ret(n, vector<int>(n, 0));
    int index = 0;
    for (int i = 0; i <= n / 2; ++i) {
        if ( i == n / 2 && n % 2 == 0)
            break;
        //top
        for (int j = i; j < n - i; ++j)
            ret[i][j] = ++index;
        //right
        for (int k = i + 1; k < n - 1 - i; ++k)
            ret[k][n - 1 - i] = ++index;
        //bottom
        if (n - 1 - i > i)
            for (int j = n - 1 - i; j >= i; --j)
                ret[n - 1 - i][j] = ++index;
        //left
        if (n - 1 - i > i)
            for (int k = n - 2 - i; k > i; --k)
                ret[k][i] = ++index;
    }
    return ret;
}
//Length of Last Word
int lengthOfLastWord(const char *s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int start = -1, cur = 0, l = 0;
    bool flag = false;
    if (s[0] == '\0')
        return 0;
    while (s[cur] != '\0') {
        if (!flag && s[cur] != ' ') {
            start = cur;
            flag = true;
            if (s[cur + 1] == '\0')
                return 1;
        }
        else if (flag && (s[cur] == ' ' || s[cur + 1] == '\0')) {
            flag = false;
            l = cur - start;
            if (s[cur] != ' ')
                l = cur - start + 1;
        }
        ++cur;
    }
    return l;
}
//Maximum Subarray
int maxSubArray(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int sum = A[0], maxSum = A[0];
    for (int i = 1; i < n; ++i) {
        if (A[i] + sum < A[i])
            sum = A[i];
        else
            sum += A[i];
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}
//Wildcard Matching
bool isMatch(const char *s, const char *p) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int i = 0, j = 0, sIndex, pIndex;
    bool flag = false;
    
    while (s[i] != '\0') {
        char c = p[j];
        switch (c) {
            case '*':
                flag = true;
                while (p[j] == '*')
                    ++j;
                if (p[j] == '\0')
                    return true;
                //store states
                sIndex = i;
                pIndex = j;
                break;
            case '?':
                ++i;
                ++j;
                break;
            default:
                if (s[i] != p[j]) {
                    if (!flag)
                        return false;
                    //fetch states
                    i = ++sIndex;
                    j = pIndex;
                }
                else {
                    ++i;
                    ++j;
                }
        }
    }
    while (p[j] == '*')
        ++j;
    return p[j] == '\0';
}
//Multiply Strings
string multiplyByI(string &s, int ival) {
    string ret = "";
    int carrier = 0;
    for (int i = (int)s.length() - 1; i >= 0; --i) {
        int d = ival * (s[i] - '0') + carrier;
        carrier = d / 10;
        ret = (char)('0' + d % 10) + ret;
    }
    if (carrier != 0)
        ret = (char)('0' + carrier) + ret;
    return ret;
}
void addStrings(string &num1, string &num2) {
    if (num1.length() < num2.length())
        num1 = string(num2.length() - num1.length(), '0') + num1;
    int carrier = 0;
    for (int i = (int)num2.length() - 1; i >= 0; --i) {
        int d = (num1[i] - '0') + (num2[i] - '0') + carrier;
        carrier = d / 10;
        num1[i] = '0' + d % 10;
    }
    for (int i = (int)num1.length() - 1; i >= num2.length(); --i) {
        int d = (num1[i] - '0') + carrier;
        carrier = d / 10;
        num1[i] = '0' + d % 10;
    }
    if (carrier != 0)
        num1 = (char)('0' + carrier) + num1;
}
string multiply(string num1, string num2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (num1 == "0" || num2 == "0")
        return "0";
    vector<string> table(10, "");
    table[0] = "0";
    for (int i = 1; i < 10; ++i)
        table[i] = multiplyByI(num1, i);
    string ret = table[num2[(int)num2.length() - 1] - '0'];
    for (int i = (int)num2.length() - 2; i >= 0; --i) {
        string s = table[num2[i] - '0'] + string((int)num2.length() - 1 - i, '0');
        addStrings(ret, s);
    }
    return ret;
}
//Trapping Rain Water
int trap(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n == 0) return 0;
    vector<int> left(n, 0);
    int h = A[0];
    for (int i = 1; i < n; ++i) {
        left[i] = h;
        h = max(h, A[i]);
    }
    int sum = 0;
    h = A[n - 1];
    for (int i = n - 2; i > 0; --i) {
        int allowed = min(left[i], h);
        if (A[i] < allowed)
            sum += allowed - A[i];
        h = max(h, A[i]);
    }
    return sum;
}
//First Missing Positive
int firstMissingPositive(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    for (int i = 0; i < n; ++i)
        while (A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i])
            swap(A[i], A[A[i] - 1]);
    for (int i = 0; i < n; ++i)
        if (A[i] != i + 1)
            return i + 1;
    return n + 1;
}
//Combination Sum II
vector<vector<int> > combinationSum2(vector<int> &num, int start, int end, int target) {
    vector<vector<int> > ret;
    if (start > end)
        return ret;
    if (start == end) {
        if (num[start] == target)
            ret.push_back(vector<int>(1, target));
        return ret;
    }
    bool flag = false;
    for (int i = start; i <= end; ++i) {
        if (i > start && num[i] == num[i - 1])
            continue;
        if (num[i] < target) {
            vector<vector<int> > v = combinationSum2(num, i + 1, end, target - num[i]);
            for (int j = 0; j < v.size(); ++j) {
                v[j].insert(v[j].begin(), num[i]);
                ret.push_back(v[j]);
            }
        }
        else if (num[i] == target && !flag) {
            ret.push_back(vector<int>(1, num[i]));
            flag = true;
        }
        else if (num[i] > target)
            break;
    }
    return ret;
}
vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    sort(num.begin(), num.end());
    return combinationSum2(num, 0, num.size() - 1, target);
}
//Combination Sum
vector<vector<int> > combinationSum(vector<int> &v, int start, int end, int target) {
    vector<vector<int> > ret;
    if (target == 0) {
        ret.push_back(vector<int>());
        return ret;
    }
    if (start > end)
        return ret;
    if (start == end) {
        int val = v[start];
        if (val != 0 && val <= target && target % val == 0)
            ret.push_back(vector<int>(target / val, val));
        return ret;
    }
    for (int i = start; i <= end; ++i) {
        if (v[i] <= target) {
            int val = v[i];
            int k = target / val;
            for (int j = 1; j <= k; ++j) {
                vector<int> vj(j, val);
                vector<vector<int> > r = combinationSum(v, i + 1, end, target - j * val);
                for (int p = 0; p < r.size(); ++p) {
                    r[p].insert(r[p].begin(), vj.begin(), vj.end());
                    ret.push_back(r[p]);
                }
            }
        }
        else
            break;
    }
    return ret;
}
vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (candidates.empty())
        return vector<vector<int> >();
    sort(candidates.begin(), candidates.end());
    vector<int> elements;
    elements.push_back(candidates[0]);
    for (int i = 1; i < candidates.size(); ++i)
        if (candidates[i] != elements.back())
            elements.push_back(candidates[i]);
    return combinationSum(elements, 0, elements.size() - 1, target);
}
//Count and Say
string countAndSay(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    string ret = "1";
    for (int i = 2; i <= n; ++i) {
        string s(ret);
        ret = "";
        for (int j = 0; j < s.size();) {
            int count = 0, end = j + 1;
            while (end < s.size() && s[end] == s[j])
                ++end;
            char c = '0' + (end - j);
            string str = "";
            str = s[j] + str;
            str = c + str;
            ret = ret + str;
            j = end;
        }
    }
    return ret;
}
//Surrounded Regions
class Solution {
    struct Node{
        int i, j;
        Node(int ival, int jval) : i(ival), j(jval) {}
    };
public:
    void BFS(vector<vector<char>> &board, int i, int j, queue<Node> &q) {
        int n = board.size(), m = board[0].size();
        board[i][j] = 'L';
        //top
        if (i > 0 && board[i - 1][j] == 'O')
            q.push(Node(i - 1, j));
        //bottom
        if (i < n - 1 && board[i + 1][j] == 'O')
            q.push(Node(i + 1, j));
        //left
        if (j > 0 && board[i][j - 1] == 'O')
            q.push(Node(i, j - 1));
        //right
        if (j < m - 1 && board[i][j + 1] == 'O')
            q.push(Node(i, j + 1));
    }
    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (board.empty() || board[0].empty())
            return;
        int n = board.size(), m = board[0].size();
        queue<Node> q;
        for (int i = 0; i < n; ++i)
            if (board[i][0] == 'O')
                q.push(Node(i, 0));
        for (int i = 0; i < n; ++i)
            if (board[i][m - 1] == 'O')
                q.push(Node(i, m - 1));
        for (int j = 0; j < m; ++j)
            if (board[0][j] == 'O')
                q.push(Node(0, j));
        for (int j = 0; j < m; ++j)
            if (board[n - 1][j] == 'O')
                q.push(Node(n - 1, j));
        while (!q.empty()) {
            int i = q.front().i, j = q.front().j;
            q.pop();
            BFS(board, i, j, q);
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (board[i][j] == 'L')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
    }
};
//Search Insert Position
int searchInsert(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n == 0)
        return 1;
    int l = 0, h = n - 1;
    if (target <= A[0])
        return 0;
    if (target > A[n - 1])
        return n;
    while (h - l > 1) {
        int mid = l + (h - l)/2;
        if (A[mid] == target)
            return mid;
        else if (A[mid] > target)
            h = mid;
        else
            l = mid;
    }
    return h;
}
//Search for a Range
vector<int> searchRange(int A[], int n, int target) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int start = -1, end = -1;
    vector<int> v;
    v.push_back(start);
    v.push_back(end);
    if (n == 0 || target < A[0] || target > A[n - 1])
        return v;
    int l = 0, h = n - 1;
    while (h - l > 1) {
        int mid = l + (h - l)/2;
        if (A[mid] >= target)
            h = mid;
        else
            l = mid;
    }
    if (A[l] == target)
        start = l;
    else if (A[h] == target)
        start = h;
    
    l = 0, h = n - 1;
    while (h - l > 1) {
        int mid = l + (h - l)/2;
        if (A[mid] <= target)
            l = mid;
        else
            h = mid;
    }
    if (A[h] == target)
        end = h;
    else if (A[l] == target)
        end = l;
    v.clear();
    v.push_back(start);
    v.push_back(end);
    return v;
}
//Longest Valid Parentheses
int getLength(string &s, int start, int end) {
    if (end - start < 1)
        return 0;
    int right = 0, len = 0, maxL = 0;
    for (int i = end; i >= start; --i) {
        if (s[i] == ')')
            ++right;
        else if (right > 0) {
            --right;
            len += 2;
        }
        else
            len = 0;
        maxL = max(maxL, len);
    }
    return maxL;
}
int longestValidParentheses(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int left = 0, right = 0, maxC = 0, start = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(')
            ++left;
        else
            ++right;
        if (right > left) {
            maxC = max(maxC, getLength(s, start, i - 1));
            start = i + 1;
            left = 0;
            right = 0;
        }
    }
    if (right <= left)
        maxC = max(maxC, getLength(s, start, (int)s.length() - 1));
    
    return maxC;
}
//Implement strStr()
void MismatchTable(const char *pat, vector<int> &v) {
    v.clear();
    if (pat[0] == '\0')
        return;
    v.push_back(-1);
    if (pat[1] == '\0')
        return;
    v.push_back(0);
    if (pat[2] == '\0')
        return;
    int i = 2, cnd = 0;
    while (pat[i] != '\0') {
        if (pat[i - 1] == pat[cnd]) {
            ++i;
            ++cnd;
            v.push_back(cnd);
        }
        else if (cnd > 0)
            cnd = v[cnd];
        else {
            v.push_back(0);
            ++i;
        }
    }
}
char *strStr(char *haystack, char *needle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> v;
    MismatchTable(needle, v);
    int i = 0, j = 0;
    while (haystack[i] != '\0' && needle[j] != '\0') {
        if (haystack[i + j] == needle[j])
            ++j;
        else {
            i = i + j - v[j];
            j = (v[j] != -1) ? v[j] : 0;
        }
    }
    if (needle[j] == '\0')
        return haystack + i;
    return NULL;
}
void BoyerMoore(const char *pat, vector<int> &right) {
    int R = 256;
    right.resize(R, -1);
    int i = 0;
    while (pat[i] != '\0') {
        right[pat[i]] = i;
        ++i;
    }
}
int BMAndKMP(const char *text, int N, const char *pat, int M) {
    vector<int> right;
    BoyerMoore(pat, right);
    int skip = 0;
    for (int i = 0; i <= N - M; i += skip) {
        skip = 0;
        for (int j = M - 1; j >= 0; --j) {
            if (text[i + j] != pat[j]) {
                skip = max(1, j - right[text[i + j]]);
                break;
            }
        }
        if (skip == 0)
            return i;
    }
    return -1;
}
char *strStr(char *haystack, char *needle) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int N = 0, M = 0;
    while (haystack[N] != '\0')
        ++N;
    while (needle[M] != '\0')
        ++M;
    int pos = BMAndKMP(haystack, N, needle, M);
    if (pos != -1)
        return haystack + pos;
    return NULL;
}
//Full Boyer Moore
void MismatchTable(const char *pat, vector<int> &v) {
    v.clear();
    v.clear();
    if (pat[0] == '\0')
        return;
    v.push_back(-1);
    if (pat[1] == '\0')
        return;
    v.push_back(0);
    if (pat[2] == '\0')
        return;
    int i = 2, cnd = 0;
    while (pat[i - 1] != '\0') {
        if (pat[i - 1] == pat[cnd]) {
            ++i;
            ++cnd;
            v.push_back(cnd);
        }
        else if (cnd > 0)
            cnd = v[cnd];
        else {
            v.push_back(0);
            ++i;
        }
    }
}

void BoyerMoore(const char *pat, vector<int> &right) {
    int R = 256;
    right.resize(R, -1);
    int i = 0;
    while (pat[i] != '\0') {
        right[pat[i]] = i;
        ++i;
    }
}
void BMAndKMP(const char *text, int N, const char *pat, int M) {
    vector<int> v, right;
    MismatchTable(pat, v);
    BoyerMoore(pat, right);
    int skip = 0, l = 0, l0 = v[M];
    for (int i = 0; i <= N - M; i += skip) {
        skip = 0;
        int j;
        for (j = M - 1; j >= l; --j) {
            if (text[i + j] != pat[j]) {
                skip = max(1, j - right[text[i + j]]);
                break;
            }
        }
        if (skip == 0) {
            cout<< i <<endl;
            l = l0;
            skip = M - l0;
        }
        else
            l = 0;
    }
    cout<< -1 <<endl;
}
//Output Duplicates
void outputDuplicates(int *A, int n) {
    for (int i = 0; i < n; ++i)
        while (A[A[i] - 1] != A[i])
            swap(A[i], A[A[i] - 1]);
    for (int i = 0; i < n; ++i)
        cout<<A[i]<<" ";
    cout<<endl;
    for (int i = 0; i < n; ++i) {
        if (A[i] > 0) {
            if (A[i] - 1 == i) {
                A[i] = -1;
                continue;
            }
            else
                --A[A[i] - 1];
        }
    }
    for (int i = 0; i < n; ++i)
        if (A[i] < 0)
            cout<< i + 1 << ": " << -A[i] <<endl;
}
//Palindrome Partitioning II
class Solution {
public:
    string preProcess(string & s) {
        int len = (int)s.length();
        if (len == 0) return NULL;
        string str = string(2 * len + 1, '#');
        for (int i = 0; i < len; i++)
            str[2 * i + 1] = s[i];
        return str;
    }
    char getContent(string & s, int i) {
        if (i < 0)
            return '-';
        if (i >= s.length())
            return '+';
        return s[i];
    }
    vector<int> palindromeArray(string& s) {
        int len = (int)s.length(), c = 0, R = 0, i = 1, i_mirror = -1;
        vector<int> r(len);
        r[0] = 0;
        for (i = 1; i < len; i++) {
            i_mirror = c + c - i;
            if ((i > R) || (i_mirror < 0))
                r[i] = 0;
            else
                r[i] = min(r[i_mirror], R - i);
            
            while (getContent(s, i - r[i] - 1) == getContent(s, i + r[i] + 1))
                r[i]++;
            
            if (i + r[i] > R) {
                c = i;
                R = i + r[i];
            }
        }
        return r;
    }
    bool isPalindrome(vector<int> &paliarr, int i, int j) {
        int len = (int)paliarr.size();
        i = 2*i + 1;
        j = 2*j + 1;
        if (i < 0 || i >= len || j < 0 || j >= len || i > j)
            return false;
        if (i == j)
            return true;
        int mid = i + (j - i)/2;
        if (paliarr[mid] >= j/2 - i/2 + 1)
            return true;
        else
            return false;
    }
    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s.length() == 0) return 0;
        string str = preProcess(s);
        vector<int> r = palindromeArray(str);
        vector<int> cuts(s.length());
        for (int i = 0; i < cuts.size(); ++i)
            cuts[i] = i;
        for (int i = 1; i < s.length(); ++i) {
            if (isPalindrome(r, 0, i))
                cuts[i] = 0;
            else {
                for (int j = 0; j < i; ++j) {
                    if (isPalindrome(r, j + 1, i) && cuts[i] > cuts[j] + 1)
                        cuts[i] = cuts[j] + 1;
                }
            }
        }
        return cuts[s.length() - 1];
    }
};
//Palindrome Partitioning I
class Solution {
public:
    string preProcess(string & s) {
        int len = (int)s.length();
        if (len == 0) return NULL;
        string str = string(2 * len + 1, '#');
        for (int i = 0; i < len; i++)
            str[2 * i + 1] = s[i];
        return str;
    }
    char getContent(string & s, int i) {
        if (i < 0)
            return '-';
        if (i >= s.length())
            return '+';
        return s[i];
    }
    vector<int> palindromeArray(string& s) {
        int len = (int)s.length(), c = 0, R = 0, i = 1, i_mirror = -1;
        vector<int> r(len);
        r[0] = 0;
        for (i = 1; i < len; i++) {
            i_mirror = c + c - i;
            if ((i > R) || (i_mirror < 0))
                r[i] = 0;
            else
                r[i] = min(r[i_mirror], R - i);
            
            while (getContent(s, i - r[i] - 1) == getContent(s, i + r[i] + 1))
                r[i]++;
            
            if (i + r[i] > R) {
                c = i;
                R = i + r[i];
            }
        }
        return r;
    }
    bool isPalindrome(vector<int> &paliarr, int i, int j) {
        int len = (int)paliarr.size();
        i = 2*i + 1;
        j = 2*j + 1;
        if (i < 0 || i >= len || j < 0 || j >= len || i > j)
            return false;
        if (i == j)
            return true;
        int mid = i + (j - i)/2;
        if (paliarr[mid] >= j/2 - i/2 + 1)
            return true;
        else
            return false;
    }
    void getPartitions(string &s, int start, vector<int> &r, vector<string> &cur, vector<vector<string> > &ret) {
        if (start >= s.length()) {
            ret.push_back(cur);
            return;
        }
        for (int i = start; i < s.length(); ++i) {
            if (isPalindrome(r, start, i)) {
                vector<string> v(cur.begin(), cur.end());
                v.push_back(s.substr(start, i - start + 1));
                getPartitions(s, i + 1, r, v, ret);
            }
        }
    }
    vector<vector<string>> partition(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string> > ret;
        if (s.length() == 0) return ret;
        string str = preProcess(s);
        vector<int> r = palindromeArray(str);
        vector<string> cur;
        getPartitions(s, 0, r, cur, ret);
        return ret;
    }
};
//
int LongestIncreasingSubsequence() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int n;
        IN >> n;
        vector<int> v(n);
        for (int i = 0; i < n; ++i)
            fin >> v[i];
        vector<int> M(n + 1, -1), P(n, -1);
        int maxL = 1;
        M[1] = 0;
        for (int i = 1; i < n; ++i) {
            //find maximum l such that v[M[l]] < v[i]
            int l = 1, h = maxL;
            //v[i] is smallest so far
            if (v[M[1]] >= v[i])
                l = 0;
            //v[i] is biggest so far
            else if (v[M[maxL]] < v[i])
                l = maxL;
            else {
                while (h - l > 1) {
                    int mid = l + (h - l)/2;
                    //make sure v[M[l]] < v[i]
                    if (v[M[mid]] < v[i])
                        l = mid;
                    else
                        h = mid;
                }
            }
            P[i] = M[l];
            //two posibilities
            if (l == maxL || v[M[l + 1]] > v[i]) {
                M[l + 1] = i;
                maxL = max(maxL, l + 1);
            }
        }
        OUT<<"Case #"<<index<<": "<<n - maxL<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
class BinStringTree {
private:
    int maxL;
    struct Node {
        bool isWordEnd; //A word ends here.
        int lc; //Count longest length of chars start from here to the left.
        int rc; //...right
        Node *left; //next char is 0.
        Node *right; //... 1.
        Node() : isWordEnd(false), lc(-1), rc(-1), left(NULL), right(NULL) {}
        ~Node() {
            delete left;
            delete right;
        }
    };
    Node *root;
    void insert(string &s, int i, Node *r) {
        int L = (int)s.length();
        if (i == L) {
            r->isWordEnd = true;
            maxL = max(maxL, max(r->lc, r->rc));
            return;
        }
        if (s[i] == '0') {
            if (r->left == NULL)
                r->left = new Node();
            r->lc = max(r->lc, L - i);
            if (r->rc != -1)
                maxL = max(maxL, r->lc + r->rc);
            if (r->isWordEnd)
                maxL = max(maxL, max(r->lc, r->rc));
            insert(s, i + 1, r->left);
        }
        else {
            if (r->right == NULL)
                r->right = new Node();
            r->rc = max(r->rc, L - i);
            if (r->lc != -1)
                maxL = max(maxL, r->lc + r->rc);
            if (r->isWordEnd)
                maxL = max(maxL, max(r->lc, r->rc));
            insert(s, i + 1, r->right);
        }
    }
public:
    BinStringTree() {
        root = new Node();
        maxL = 0;
    }
    ~BinStringTree() {
        delete root;
    }
    void insert(string &s) {
        insert(s, 0, root);
    }
    int maxDist() {
        return maxL;
    }
};
//
class Birthday{
    bool isSame(vector<long> &v1, vector<long> &v2) {
        for (int i = 0; i < v1.size(); ++i)
            if (v1[i] != v2[i])
                return false;
        return true;
    }
    
    int process() {
        //clock_t t = clock();
        //t = clock() - t;
        fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
        fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
        srand((unsigned)time(NULL));
        int T;
        IN >> T;
        for (int index = 1; index <= T; ++index) {
            vector<long> v1, v2;
            int n;
            IN >> n;
            vector<long> numbers(n);
            for (int i = 0; i < n; ++i)
                IN >> numbers[i];
            int t = 5e7, count = 6;
            tr1::unordered_map<long, vector<long> > map;
            while (map.size() < t) {
                tr1::unordered_set<long> set;
                vector<long> v;
                long sum = 0;
                while (set.size() < count)
                    set.insert(numbers[rand() % n]);
                
                for (auto it = set.begin(); it != set.end(); ++it) {
                    sum += *it;
                    v.push_back(*it);
                }
                sort(v.begin(), v.end());
                if (map.find(sum) == map.end())
                    map.insert(pair<long, vector<long> >(sum, v));
                else if (!isSame(map.find(sum)->second, v)) {
                    v1 = v;
                    v2 = map.find(sum)->second;
                    break;
                }
            }
            OUT<<"Case #"<<index<<": "<<endl;
            for (int i = 0; i < v1.size(); ++i)
                OUT<<v1[i]<<" ";
            OUT<<endl;
            for (int i = 0; i < v2.size(); ++i)
                OUT<<v2[i]<<" ";
            OUT<<endl;
            
        }
        //cout<<(float) t / CLOCKS_PER_SEC<<endl;
        return 0;
    }

};
//
bool isRotated(string &s1, string &s2) {
    if (s1.size() != s2.size())
        return false;
    if (s1.size() == 0)
        return true;
    int i = 0, j = 0, n = (int)s1.size();
    while (i < n && j < n) {
        int k = 0;
        while (k < n && (s1[(i + k) % n] == s2[(j + k) % n]))
            ++k;
        if (k == n)
            return true;
        if (s1[i + k] < s2[j + k])
            j += k + 1;
        else
            i += k + 1;
    }
    return false;
}
//IndexMinPQ
struct Node {
    int i, j;
    double C, F, t;
    Node(int ival = 0, int jval = 0, double Cval = 0, double Fval = 0, double tval = INT_MAX)
    : i(ival), j(jval), C(Cval), F(Fval), t(tval) {}
};

class MinPQ {
private:
    int NMAX, N;
    vector<Node> v;
    vector<int> pq, qp;
    vector<bool> visited;
    bool less(int i, int j){return v[pq[i]].t < v[pq[j]].t;}
    void exch(int i, int j){
        int temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }
    void swim(int i){
        while (i > 1 && less(i, i/2)) {
            exch(i, i/2);
            i /= 2;
        };
    }
    void sink(int i) {
        while (2*i <= N) {
            int j = 2*i;
            if (j < N && less(j + 1, j))
                ++j;
            if (less(i, j))
                break;
            exch(i, j);
            i = j;
        }
    }
public:
    MinPQ(int n){
        NMAX = n;
        N = 0;
        v.resize(NMAX + 1, Node());
        pq.resize(NMAX + 1);
        qp.resize(NMAX + 1, -1);
        visited.resize(NMAX + 1, false);
    }
    int size(){ return N;}
    void insert(int i, Node node) {
        ++N;
        pq[N] = i;
        qp[i] = N;
        v[i] = node;
        swim(N);
    }
    Node delMin() {
        assert(N > 0);
        int min = pq[1];
        Node node = v[min];
        exch(1, N--);
        sink(1);
        qp[min] = -1;
        return node;
    }
    void decreaseTime(int i, double t) {
        v[i].t = t;
        swim(qp[i]);
    }
    double getTime(int i, int j, int i1, int j1) {
        int index = i*DM + j + 1, adjIndex = i1*DM + j1 + 1;
        double t = v[index].t;
        double h = max(0.0, H - t*10);
        double ret = INT_MAX;
        if (!(i1 >= 0 && i1 < DN && j1 >= 0 && j1 < DM))
            return ret;
        if (v[adjIndex].C < GAP + max(v[adjIndex].F, v[index].F))
            return ret;
        if (v[index].C < GAP + v[adjIndex].F)
            return ret;
        if (v[adjIndex].C < GAP + h)
            ret = t + (GAP + h - v[adjIndex].C) / 10;
        else
            ret = t;
        if (t == 0.0 && v[adjIndex].C >= GAP + h)
            return 0.0;
        h = max(0.0, H - ret*10);
        if (h - v[index].F >= 20)
            return ret + 1.0;
        return ret + 10.0;
    }
    double Dijkstra(){
        decreaseTime(1, 0.0);
        while (true) {
            Node node = delMin();
            int i = node.i, j = node.j, index = i*DM + j + 1;
            double t = node.t;
            visited[index] = true;
            if (index == DN*DM)
                return t;
            int adjIndex = (i - 1)*DM + j + 1;
            double adjT = getTime(i, j, i - 1, j);
            if (i > 0 && !visited[adjIndex] && adjT < v[adjIndex].t)
                decreaseTime(adjIndex, adjT);
            adjIndex = (i + 1)*DM + j + 1;
            adjT = getTime(i, j, i + 1, j);
            if (i + 1 < DN && !visited[adjIndex] && adjT < v[adjIndex].t)
                decreaseTime(adjIndex, adjT);
            adjIndex = i*DM + j;
            adjT = getTime(i, j, i, j - 1);
            if (j > 0 && !visited[adjIndex] && adjT < v[adjIndex].t)
                decreaseTime(adjIndex, adjT);
            adjIndex = i*DM + j + 2;
            adjT = getTime(i, j, i, j + 1);
            if (j + 1 < DM && !visited[adjIndex] && adjT < v[adjIndex].t)
                decreaseTime(adjIndex, adjT);
        }
        return INT_MAX;
    }
};
//
struct Node {
    int index;
    double s, p;
    Node(int i = 0, double sval = 0.0, double pval = 0.0) : index(i), s(sval), p(pval) {}
};

bool lessIndex(Node i, Node j) {return i.index < j.index;}

bool lessScore(Node i, Node j) {return i.s < j.s;}

int SafetyinNumbers() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        IN >> N;
        vector<Node> v(N);
        double X = 0.0;
        for (int i = 0; i < N; ++i) {
            v[i].index = i;
            IN >> v[i].s;
            X += v[i].s;
        }
        sort(v.begin(), v.end(), lessScore);
        vector<double> sum(N);
        sum[0] = v[0].s;
        for (int i = 1; i < N; ++i)
            sum[i] = sum[i - 1] + v[i].s;
        for (int i = 0; i < N; ++i) {
            //find max l s.t. v[l].s <= v[i].s
            int l = i, h = N - 1;
            if (v[h].s == v[i].s)
                l = h;
            else {
                while (h - l > 1) {
                    int mid = l + (h - l)/2;
                    if (v[mid].s == v[i].s)
                        l = mid;
                    else
                        h = mid;
                }
            }
            //get p value for l + 1 elements (0...l) with same value
            h = N - 1;
            double pl = (sum[l] + X - (l + 1)*v[i].s)/X/(l + 1);
            double sl = v[i].s + X*pl;
            if (pl <= 0.0)
                v[i].p = 0.0;
            else if (l == h || sl <= v[l + 1].s)
                v[i].p = pl;
            else {
                while (h - l > 1) {
                    int mid = h - (h - l)/2;
                    double pmid = (sum[mid] + X - (mid + 1)*v[i].s)/X/(mid + 1);
                    double smid = v[i].s + X*pmid;
                    if (smid <= v[mid + 1].s)
                        h = mid;
                    else
                        l = mid;
                }
                v[i].p = (sum[h] + X - (h + 1)*v[i].s)/X/(h + 1);
            }
        }
        sort(v.begin(), v.end(), lessIndex);
        OUT<<"Case #"<<index<<": ";
        for (int i = 0; i < N; ++i)
            OUT<<fixed<<setprecision(6)<<100*v[i].p<<" ";
        OUT<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//dp
int BoxFactory() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int N, M;
        IN >> N >> M;
        vector<long> a(N + 1, 0), b(M + 1, 0);
        vector<int> A(N + 1, 0), B(M + 1, 0);
        for (int i = 1; i <= N; ++i)
            IN >> a[i] >> A[i];
        for (int i = 1; i <= M; ++i)
            IN >> b[i] >> B[i];
        vector<vector<long> > m(N + 1, vector<long>(M + 1, 0));
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                if (A[i] == B[j]) {
                    long aC = a[i], bC = b[j];
                    int k = i - 1, l = j - 1;
                    bool flag = false;
                    while (true) {
                        m[i][j] = max(m[i][j], m[k][l] + min(aC, bC));
                        if (aC <= bC) {
                            while (k > 0 && A[k] != A[i])
                                --k;
                            if (k > 0)
                                aC += a[k--];
                            else
                                flag = true;
                        }
                        else {
                            while (l > 0 && B[l] != A[i])
                                --l;
                            if (l > 0)
                                bC += b[l--];
                            else
                                flag = true;
                        }
                        if (flag)
                            break;
                    }
                }
                else
                    m[i][j] = max(m[i - 1][j], m[i][j - 1]);
            }
        }
        OUT<<"Case #"<<index<<": "<<m[N][M]<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//Descending in the dark
int main() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int rows, cols;
        IN >> rows >> cols;
        char field[rows][cols];
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                IN >> field[r][c];
        OUT<<"Case #"<<index<<": "<<endl;
        for (char caveId = '0'; caveId <= '9'; ++caveId) {
            int cr = -1;
            int cc = -1;
            for (int r = 0; r < rows; ++r)
                for (int c = 0; c < cols; ++c)
                    if (field[r][c] == caveId) {
                        cr = r;
                        cc = c;
                    }
            if (cr < 0) continue;
            vector<vector<bool> > reach(rows, vector<bool>(cols, false));
            reach[cr][cc] = true;
            int nc = 1;
            while (true) {
                bool updated = false;
                for (int r = 0; r < rows; ++r)
                    for (int c = 0; c < cols; ++c)
                        if (reach[r][c]) {
                            if (r > 0 && field[r - 1][c] != '#' && !reach[r - 1][c]) {
                                reach[r - 1][c] = true;
                                ++nc;
                                updated = true;
                            }
                            if (c > 0 && field[r][c - 1] != '#' && !reach[r][c - 1]) {
                                reach[r][c - 1] = true;
                                ++nc;
                                updated = true;
                            }
                            if (c + 1 < cols && field[r][c + 1] != '#' && !reach[r][c + 1]) {
                                reach[r][c + 1] = true;
                                ++nc;
                                updated = true;
                            }
                        }
                if (!updated) break;
            }
            vector<Segment> segments;
            for (int r = 0; r <= cr; ++r)
                for (int c = 0; c < cols; ++c)
                    if (reach[r][c] && (c == 0 || !reach[r][c - 1])) {
                        int c1 = c;
                        while (reach[r][c1 + 1]) ++c1;
                        Segment s;
                        s.len = c1 - c + 1;
                        for (int pos = c; pos <= c1; ++pos) {
                            if (r + 1 < rows && field[r + 1][pos] != '#') {
                                if (reach[r + 1][pos])
                                    s.goodExitMask |= 1L << (pos - c);
                                else
                                    s.badExitMask |= 1L << (pos - c);
                            }
                        }
                        segments.push_back(s);
                    }
            while (true) {
                int maxLen = 0;
                for (auto s = segments.begin(); s != segments.end(); ++s)
                    maxLen = max(maxLen, (*s).len);
                vector<long> badByLen(maxLen + 1, 0);
                for (auto s = segments.begin(); s != segments.end(); ++s) {
                    badByLen[(*s).len] |= (*s).badExitMask;
                }
                vector<long> possible(maxLen + 1);
                possible[1] = 1;
                for (int len = 1; len <= maxLen; ++len) {
                    possible[len] &= ~badByLen[len];
                    if (len < maxLen) {
                        possible[len + 1] = possible[len] | (possible[len] << 1);
                    }
                }
                for (int len = maxLen; len > 1; --len) {
                    possible[len - 1] &= possible[len] | (possible[len] >> 1);
                }
                vector<Segment> remaining;
                for (auto s = segments.begin(); s != segments.end(); ++s)
                    if (((*s).goodExitMask & possible[(*s).len]) == 0) {
                        remaining.push_back(*s);
                    }
                if (remaining.size() == segments.size()) break;
                segments = remaining;
            }
            OUT<< caveId << ": " << nc << " " << (segments.size() == 1 ? "Lucky" : "Unlucky")<<endl;
        }
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//Remove Element
int removeElement(int A[], int n, int elem) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int i = 0;
    for (; i < n; ++i) {
        if (A[i] == elem)
            A[i--] = A[--n];
    }
    return i;
}
//Remove Duplicates from Sorted Array
int removeDuplicates(int A[], int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if (n == 0) return 0;
    int prev = 0;
    for (int i = 1; i < n; ++i) {
        if (A[i] != A[i - 1])
            ++prev;
        A[prev] = A[i];
    }
    return prev + 1;
}
//Swinging Wild
int SwingingWild() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    vector<long> d, l, R;
    vector<bool> isValid;
    for (int index = 1; index <= T; ++index) {
        long N;
        IN >> N;
        d.resize(N + 1, 0);
        l.resize(N + 1, 0);
        R.resize(N + 1, 0);
        for (int i = 1; i <= N; ++i)
            IN >> d[i] >> l[i];
        long D, maxR = d[1] + min(d[1], l[1]);
        R[1] = maxR;
        IN >> D;
        bool flag = (maxR >= D) ? true : false;
        queue<int> q;
        q.push(1);
        for (int i = 2; i <= N; ++i) {
            if (d[i] <= maxR) {
                while (R[q.front()] < d[i])
                    q.pop();
                long dist = d[i] + min(d[i] - d[q.front()], l[i]);
                if (dist > maxR) {
                    maxR = dist;
                    R[i] = maxR;
                    q.push(i);
                }
                if (maxR >= D) {
                    flag = true;
                    break;
                }
            }
            else {
                flag = false;
                break;
            }
        }
        OUT<<"Case #"<<index<<": ";
        if (flag)
            OUT<<"YES"<<endl;
        else
            OUT<<"NO"<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
int MountainView() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    srand((unsigned)time(NULL));
    for (int index = 1; index <= T; ++index) {
        int N;
        IN >> N;
        vector<int> peak(N, -1);
        vector<int> height(N, -1);
        for (int i = 0; i < N - 1; ++i) {
            IN >> peak[i];
            --peak[i];
        }
        OUT<<"Case #"<<index<<": ";
        bool flag = false;
        int i = 0, end = 0, slope = 0;
        height[0] = 1e9;
        while (i < N - 1) {
            end = peak[i];
            slope = 0;
            for (int j = i; j < end; ++j) {
                int e = peak[j];
                for (int k = j + 1; k < e; ++k) {
                    if (peak[k] > e) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
            height[end] = 1e9;
            for (int j = i + 1; j < end; ++j) {
                if (height[j] == -1) {
                    int e = peak[j - 1], p = j;
                    slope = (int)((double)height[e] - height[j - 1])/(e - j + 1) + 1;
                    while (p < e) {
                        height[p] = height[e] - slope*(e - p);
                        p = peak[p];
                    }
                }
            }
            i = end;
        }
        if (!flag) {
            for (int i = 0; i < N; ++i)
                OUT<<height[i]<<" ";
            OUT<<endl;
        }
        else
            OUT<<"Impossible"<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
struct Node {
    int index, l, p;
};

bool timeComp(Node i, Node j) {
    long a = j.l*(100 - i.p) + i.l*100;
    long b = i.l*(100 - j.p) + j.l*100;
    if (a == b)
        return i.index < j.index;
    if (a < b)
        return true;
    return false;
}

int PerfectGame() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        IN >> N;
        vector<Node> v(N);
        for (int i = 0; i < N; ++i) {
            v[i].index = i;
            IN >> v[i].l;
        }
        for (int i = 0; i < N; ++i)
            IN >> v[i].p;
        sort(v.begin(), v.end(), timeComp);
        OUT<<"Case #"<<index<<": ";
        for (int i = 0; i < N; ++i)
            OUT << v[i].index<<" ";
        OUT << endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
struct Node {
    long long p, s;
    Node(long long pval = 0, long long sval = 0)
    : p(pval), s(sval) {}
};

bool sComp(Node i, Node j) {return i.s < j.s;}

long long getMaxDays(long long delivery, vector<Node> &v, long long M, long long F){
    long long m = M - F*delivery, Days = 0;
    if (m <= 0 || delivery == 0) {
        return Days;
    }
    for (int i = 1; i < v.size(); ++i) {
        long long d = v[i].s - v[i - 1].s;
        if (m/delivery/d >= v[i].p) {
            m -= delivery*d*v[i].p;
            Days = v[i].s*delivery;
        }
        else {
            Days += m/v[i].p;
            break;
        }
    }
    return Days;
}

int qualityFood() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        long long M, F, N;
        IN >> M >> F >> N;
        tr1::unordered_map<long long, long long> map;
        for (int i = 0; i < N; ++i) {
            long long p, s;
            IN >> p >> s;
            ++s;
            auto it = map.find(s);
            if (it == map.end())
                map.insert(make_pair(s, p));
            else if (it->second > p)
                it->second = p;
        }
        vector<Node> v;
        for (auto it = map.begin(); it != map.end(); ++it) {
            bool flag = true;
            for (auto jt = map.begin(); jt != map.end(); ++jt) {
                if (it->first < jt->first && it->second >= jt->second) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                Node n(it->second, it->first);
                v.push_back(n);
            }
        }
        Node dummy(0, 0);
        v.push_back(dummy);
        N = v.size();
        sort(v.begin(), v.end(), sComp);
        long long maxDays = 0, lo = 0, hi = M/F + 1;
        while (lo < hi) {
            //long long mid1 = lo + (hi - lo)/2;
            //long long mid2 = mid1 + 1;
            long long mid1 = lo + (hi - lo)/3;
            long long mid2 = lo + (hi - lo + 1)*2/3;
            if (getMaxDays(mid1, v, M, F) < getMaxDays(mid2, v, M, F)) {
                lo = mid1 + 1;
            }
            else {
                hi = mid2 - 1;
            }
        }
        maxDays = max(getMaxDays(lo, v, M, F), getMaxDays(hi, v, M, F));
        OUT<<"Case #"<<index<<": "<<maxDays<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
char getChar(char c) {
    switch (c) {
        case 'o':
            return '0';
        case 'i':
            return '1';
        case 'e':
            return '3';
        case 'a':
            return '4';
        case 's':
            return '5';
        case 't':
            return '7';
        case 'b':
            return '8';
        case 'g':
            return '9';
        default:
            return c;
    }
}

string getString(char a, char b){
    return string(1, a) + b;
}

int lostPassword() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int k;
        IN >> k;
        string text;
        IN >> text;
        tr1::unordered_set<string> wordSet;
        tr1::unordered_map<char, int> charMap;
        for (int i = 1; i < text.length(); ++i) {
            char a1 = text[i - 1], a2 = getChar(text[i - 1]), b1 = text[i], b2 = getChar(text[i]);
            wordSet.insert(getString(a1, b1));
            wordSet.insert(getString(a1, b2));
            wordSet.insert(getString(a2, b1));
            wordSet.insert(getString(a2, b2));
            charMap.insert(pair<char, int>(a1, 0));
            charMap.insert(pair<char, int>(a2, 0));
            charMap.insert(pair<char, int>(b1, 0));
            charMap.insert(pair<char, int>(b2, 0));
        }
        //out degree == in degree?
        for (tr1::unordered_set<string>::iterator it = wordSet.begin(); it != wordSet.end(); ++it) {
            string s = *it;
            charMap.find(s[0])->second += 1;
            charMap.find(s[1])->second -= 1;
        }
        int l = (int)wordSet.size(), diff = 0;
        for (tr1::unordered_map<char, int>::iterator it = charMap.begin(); it != charMap.end(); ++it) {
            diff += abs(it->second);
        }
        OUT<<"Case #"<<index<<": "<<l + max(diff/2, 1)<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
#define CHARGE 750
#define SPEED 100
#define DURATION 1000

struct Node {
    int index, x, y, m, t, lastUsed;
    Node(int ival = 0, int xval = 0, int yval = 0, int mval = 0, int tval = 0, int last = -1)
    : index(ival), x(xval), y(yval), m(mval), t(tval), lastUsed(last) {}
};

Node getTime(Node i, Node j, vector<vector<int> > &dist) {
    Node node = j;
    node.lastUsed = -1;
    if (i.t + dist[i.index][j.index] <= j.m + DURATION) {
        int t = max(i.t + dist[i.index][j.index], j.m);
        if (t - i.lastUsed <= CHARGE) {
            node.lastUsed = i.lastUsed + CHARGE;
            node.t = node.lastUsed;
            if (node.lastUsed > j.m + DURATION) {
                node.lastUsed = -1;
                return node;
            }
        }
        else {
            node.lastUsed = t;
            node.t = t;
        }
        return node;
    }
    return node;
}
int ZombieSmash() {
    //clock_t t = clock();
    //t = clock() - t;
    fin.open("/Users/zishirs/Documents/workspace/test/test/test.txt");
    fout.open("/Users/zishirs/Documents/workspace/test/test/output.txt");
    int T;
    IN >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        IN >> N;
        vector<Node> v(N + 1);
        for (int i = 1; i <= N; ++i) {
            v[i].index = i;
            IN >> v[i].x >> v[i].y >> v[i].m;
        }
        v[0].lastUsed = 0;
        vector<vector<int> > dist(N + 1, vector<int>(N + 1, -1));
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                //from i to j
                if (i != j) {
                    dist[i][j] = max(abs(v[i].x - v[j].x), abs(v[i].y - v[j].y))*SPEED;
                }
            }
        }
        tr1::unordered_map<int, Node> cur, next;
        tr1::unordered_map<int, Node>::iterator it, jt;
        //init
        for (int i = 1; i <= N; ++i) {
            Node node = v[i];
            node.lastUsed = -1;
            if (dist[0][node.index] <= node.m + DURATION) {
                int t = max(dist[0][node.index], node.m);
                node.t = t;
                node.lastUsed = t;
                cur.insert(pair<int, Node>(i, node));
            }
        }
        int count = (cur.empty()) ? 0 : 1;
        while (true) {
            next.clear();
            for (it = cur.begin(); it != cur.end(); ++it) {
                for (int j = 1; j <= N; ++j) {
                    int i = it->first;
                    if (i != j) {
                        Node node = getTime(it->second, v[j], dist);
                        if (node.lastUsed != -1) {
                            if (next.find(j) == next.end()) {
                                next.insert(pair<int, Node>(j, node));
                            }
                            else if (node.t < next.find(j)->second.t) {
                                next.find(j)->second = node;
                            }
                        }
                    }
                }
            }
            if (next.empty()) {
                break;
            }
            ++count;
            swap(cur, next);
        }
        OUT<<"Case #"<<index<<": "<<count<<endl;
    }
    //cout<<(float) t / CLOCKS_PER_SEC<<endl;
    return 0;
}
//
#define SIZE 3

struct Node {
    long a, b, c;
    long double p;
};

bool largerComp(Node i, Node j) {return i.a * j.b > i.b * j.a;}

// a 3*3 matrix
struct MarkovMatrix {
    vector<vector<long double> > m;
    MarkovMatrix() {m.resize(SIZE, vector<long double>(SIZE, 0));}
};

MarkovMatrix multiplyTwoMatrix(MarkovMatrix &Mi, MarkovMatrix &Mj) {
    MarkovMatrix ret;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ret.m[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                ret.m[i][j] += Mi.m[i][k] * Mj.m[k][j];
            }
        }
    }
    return ret;
}
int MarkovChain() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N, K;
        cin >> N >> K;
        vector<Node> vNode;
        vNode.resize(N);
        int F = 0;
        for (int i = 0; i < N; ++i) {
            char c;
            cin >> vNode[i].a >> c >> vNode[i].b >> vNode[i].c;
            F += vNode[i].c;
        }
        sort(vNode.begin(), vNode.end(), largerComp);
        vector<long double> prob;
        prob.resize(F);
        int idx = 0;
        for (int i = 0; i < N; ++i) {
            long double p = (long double)vNode[i].a / vNode[i].b;
            for (int j = 0; j < vNode[i].c; ++j) {
                prob[idx] = p;
                ++idx;
            }
        }
        vector<MarkovMatrix> vMatrix;
        vMatrix.resize(F);
        for (int i = 0; i < F; ++i) {
            long double p = prob[i];
            vMatrix[i].m[0][0] = p;
            vMatrix[i].m[0][1] = 1 - p;
            vMatrix[i].m[1][1] = 1 - p;
            vMatrix[i].m[1][2] = p;
            vMatrix[i].m[2][2] = 1;
        }
        vector<MarkovMatrix> prefixProduct, suffixProduct;
        prefixProduct.resize(K + 1);
        suffixProduct.resize(K + 1);
        MarkovMatrix unity;
        unity.m[0][0] = 1;
        unity.m[1][1] = 1;
        unity.m[2][2] = 1;
        prefixProduct[0] = unity;
        for (int i = 1; i <= K; ++i) {
            prefixProduct[i] = multiplyTwoMatrix(prefixProduct[i - 1], vMatrix[i - 1]);
        }
        suffixProduct[K] = unity;
        for (int i = K - 1; i >= 0; --i) {
            suffixProduct[i] = multiplyTwoMatrix(vMatrix[F + i - K], suffixProduct[i + 1]);
        }
        long double optimal = 1;
        for (int i = 0; i <= K; ++i) {
            MarkovMatrix product = multiplyTwoMatrix(prefixProduct[i], suffixProduct[i]);
            optimal = min(optimal, product.m[0][2]);
        }
        cout<<"Case #"<<index<<": "<<fixed<<setprecision(9)<<optimal<<endl;
    }
    return 0;
}
//
vector<string> getOps(string seq) {
    int last = -1, pushCount = 0, N = (int)seq.length();
    vector<string> v(2*N, "");
    for (int i = 0; i < N; ++i) {
        int index = seq[i] - '0';
        ++last;
        if (index > pushCount) {
            if (pushCount + 1 <= index - 1) {
                int head = i + 1, tail = N - 1;
                for (int j = index - 1; j >= pushCount + 1; --j) {
                    int pos = last + j - pushCount - 1;
                    while (head < N && seq[head] - '0' > index)
                        ++head;
                    while (tail >= 0 && seq[tail] - '0' > index)
                        --tail;
                    if (head == N || tail < 0) {
                        v.clear();
                        return v;
                    }
                    if (seq[head] - '0' == j) {
                        v[pos] = "pushBack";
                        ++head;
                    }
                    else if (seq[tail] - '0' == j) {
                        v[pos] = "pushFront";
                        --tail;
                    }
                    else {
                        v.clear();
                        return v;
                    }
                }
            }
            last += index - pushCount;
            pushCount = index;
            v[last - 1] = "pushBack";
        }
        v[last] = "POPBACK";
    }
    return v;
}
//
int PasswordProblem() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int A, B;
        cin >> A >> B;
        vector<double> pV(A + 1, 0), product(A + 1, 1);
        for (int i = 1; i <= A; ++i) {
            cin >> pV[i];
            product[i] = product[i - 1]*pV[i];
        }
        double best = product[A]*(B - A + 1) + (1 - product[A])*(B - A + 1 + B + 1);
        double p0 = product[A - 1]*(B - A + 3) + (1 - product[A - 1])*(B - A + 3 + B + 1);
        for (int i = A - 1; i >= 1; --i) {
            p0 = min ( p0, product[i - 1]*(B - A + 1 + 2*(A - i + 1)) + (1 - product[i - 1])*(B - A + 1 + 2*(A - i + 1) + B + 1));
        }
        best = min(best, p0);
        best = min(best, B + (double)2);
        cout<<"Case #"<<index<<": "<<fixed<<setprecision(9)<<best<<endl;
    }
    return 0;
}
//
struct Node {
    int index, first, second;
};

bool secondComp(Node i, Node j) {return  i.second > j.second;}

int KingdomRush() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        cin >> N;
        vector<Node> nodeV(N);
        for (int i = 0; i < N; ++i) {
            nodeV[i].index = i;
            cin >> nodeV[i].first >> nodeV[i].second;
        }
        sort(nodeV.begin(), nodeV.end(), secondComp);
        //0 for unused, 1 for 1 used but 2 not used, 2 for 2 used, 3 for curently reserved for 2
        vector<int> status(N, 0);
        int stars = 0, steps = 0;
        while (true) {
            int oldStars = stars;
            //complete level 2 if possible
            for (int i = 0; i < N; ++i) {
                if (stars >= nodeV[i].second) {
                    switch (status[nodeV[i].index]) {
                        case 0:
                            stars += 2;
                            ++steps;
                            status[nodeV[i].index] = 2;
                            break;
                        case 1:
                            stars += 1;
                            ++steps;
                            status[nodeV[i].index] = 2;
                            break;
                        default:
                            break;
                    }
                }
            }
            if (stars == 2*N)
                break;
            if (oldStars == stars) {
                //try to complete level 1
                bool found = false;
                for (int i = 0; i < N; ++i) {
                    if (stars >= nodeV[i].first && status[nodeV[i].index] == 0) {
                        stars += 1;
                        ++steps;
                        status[nodeV[i].index] = 1;
                        found = true;
                        break;
                    }
                }
                if (found)
                    continue;
            }
            else
                continue;
            if (oldStars == stars) {
                steps = -1;
                break;
            }
        }
        if (steps == -1)
            cout<<"Case #"<<index<<": Too Bad"<<endl;
        else
            cout<<"Case #"<<index<<": "<<steps<<endl;
    }
    return 0;
}
//
int BotTrust() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        cin >> N;
        vector<char> color(N);
        vector<int> points(N);
        for (int i = 0; i < N; ++i) {
            cin >> color[i] >> points[i];
        }
        int opos = 1, otime = 0, bpos = 1, btime = 0, t = 0;
        for (int i = 0; i < N; ++i) {
            if (color[i] == 'O') {
                int needed = abs(opos - points[i]);
                opos = points[i];
                if (needed <= t - otime) {
                    otime = ++t;
                }
                else {
                    otime += needed + 1;
                    t = otime;
                }
            }
            else {
                int needed = abs(bpos - points[i]);
                bpos = points[i];
                if (needed <= t - btime) {
                    btime = ++t;
                }
                else {
                    btime += needed + 1;
                    t = btime;
                }
            }
        }
        cout<<"Case #"<<index<<": "<<t<<endl;
    }
    return 0;
}
//
int getIndex(char c) {
    switch (c) {
        case 'Q':
            return 1;
        case 'W':
            return 2;
        case 'E':
            return 3;
        case 'R':
            return 4;
        case 'A':
            return 5;
        case 'S':
            return 6;
        case 'D':
            return 7;
        case 'F':
            return 8;
        default:
            return -1;
    }
}

int Magicka() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int C, D, N;
        string s;
        vector<char> ret;
        tr1::unordered_map<int, char> combined;
        tr1::unordered_map<int, char>::iterator cit;
        vector<vector<bool> > opposed(9, vector<bool>(9, false));
        
        cin >> C;
        for (int i = 0; i < C; ++i) {
            cin >> s;
            int c0 = getIndex(s[0])*10, c1 = getIndex(s[1]);
            combined.insert(make_pair(c0 + c1, s[2]));
            c0 = getIndex(s[1])*10, c1 = getIndex(s[0]);
            combined.insert(make_pair(c0 + c1, s[2]));
        }
        cin >> D;
        for (int i = 0; i < D; ++i) {
            cin >> s;
            int c0 = getIndex(s[0]), c1 = getIndex(s[1]);
            opposed[c0][c1] = true;
            opposed[c1][c0] = true;
        }
        cin >> N;
        cin >> s;
        for (int i = 0; i < N; ++i) {
            if (ret.empty()) {
                ret.push_back(s[i]);
                continue;
            }
            int c0 = getIndex(ret.back())*10, c1 = getIndex(s[i]);
            cit = combined.find(c0 + c1);
            if (c0 > 0 && cit != combined.end()) {
                ret[ret.size() - 1] = cit->second;
                continue;
            }
            bool isClear = false;
            for (int j = 0; j < ret.size(); ++j) {
                c0 = getIndex(ret[j]);
                if (c0 > 0 && opposed[c0][c1]) {
                    ret.clear();
                    isClear = true;
                    break;
                }
            }
            if (!isClear) {
                ret.push_back(s[i]);
            }
        }
        cout<<"Case #"<<index<<": [";
        for (int i = 0; i + 1 < ret.size(); ++i)
            cout<<ret[i]<<", ";
        if (!ret.empty())
            cout<<ret[ret.size() - 1]<<"]"<<endl;
        else
            cout<<"]"<<endl;
    }
    return 0;
}
//
int CandySplitting() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        cin >> N;
        vector<int> v(N);
        cin >> v[0];
        int sum = v[0], x = v[0];
        for (int i = 1; i < N; ++i) {
            cin >> v[i];
            sum += v[i];
            x ^= v[i];
        }
        if (x != 0) {
            cout<<"Case #"<<index<<": NO"<<endl;
        }
        else {
            sort(v.begin(), v.end());
            cout<<"Case #"<<index<<": "<<sum - v[0]<<endl;
        }
        //cout<<"Case #"<<index<<": "<<endl;
    }
    return 0;
}
//
struct Node {
    int index, val;
};

bool valComp(Node i, Node j) {return i.val < j.val;}

int GoroSort() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        cin >> N;
        vector<Node> v(N);
        for (int i = 0; i < N; ++i) {
            v[i].index = i;
            cin >> v[i].val;
        }
        sort(v.begin(), v.end(), valComp);
        int misplaced = 0;
        for (int i = 0; i < N; ++i) {
            if (i != v[i].index) {
                ++misplaced;
            }
        }
        cout<<"Case #"<<index<<": "<<misplaced<<endl;
    }
    return 0;
}
//
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % t;
        a = t;
    }
    return a;
}

int FreeCellStatistics() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        long long N, pd, pg;
        cin >> N >> pd >> pg;
        long long g = gcd(pd, 100);
        long long b = 100/g;
        if (N < b) {
            cout<<"Case #"<<index<<": Broken"<<endl;
            continue;
        }
        if ((pg == 0 && pd != 0) || (pg == 100 & pd != 100)) {
            cout<<"Case #"<<index<<": Broken"<<endl;
            continue;
        }
        cout<<"Case #"<<index<<": Possible"<<endl;
    }
    return 0;
}
//
#define MAXN 10005

char str[MAXN][20];
char patterns[MAXN][20];
int points[MAXN];
char guess[27];

int KillerWord() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < N; ++i) {
            cin >> str[i];
        }
        cout<<"Case #"<<index<<": ";
        for (int i = 0; i < M; ++i) {
            cin >> guess;
            for (int j = 0; j < N; ++j) {
                points[j] = 0;
                int k = 0;
                for (; str[j][k] != '\0'; ++k) {
                    patterns[j][k] = '_';
                }
                patterns[j][k] = '\0';
                for (k = 0; k < 26; ++k) {
                    if (strchr(str[j], guess[k]) != NULL) {
                        --points[j];
                    }
                }
            }
            tr1::unordered_set<string> aSet;
            for (int j = 0; j < 26; ++j) {
                aSet.clear();
                for (int k = 0; k < N; ++k) {
                    for (int p = 0; str[j][p] != '\0'; ++p) {
                        if (str[k][p] == guess[j]) {
                            aSet.insert(patterns[k]);
                            break;
                        }
                    }
                }
                for (int k = 0; k < N; ++k) {
                    if (aSet.find(patterns[k]) != aSet.end()) {
                        ++points[k];
                    }
                    for (int p = 0; str[j][p] != '\0'; ++p) {
                        if (str[k][p] == guess[j]) {
                            patterns[k][p] = guess[j];
                        }
                    }
                }
            }
            int best = 0;
            for (int j = 1; j < N; ++j) {
                if (points[best] < points[j]) {
                    best = j;
                }
            }
            cout<<str[best]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
//Fair and Square
vector< vector<char> > fair;

bool cmp(const vector<char> & a, const vector<char> & b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (int i=0; i<a.size(); ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return true;
}

void fill(int p, int l, vector<char> & result, int rest) {
    if (p*2 + 1 == l) {
        int i=0;
        while(i*i <= rest) {
            result[p] = i;
            fill(p+1, l, result, rest - i*i);
            ++i;
        }
    } else if (p*2 + 1 > l) {
        fair.push_back(vector<char>());
        for (int i=0; i<result.size(); ++i) {
            fair.back().push_back(result[i]);
        }
        if ((l & 1) == 0) {
            fair.back().push_back(result.back());
        }
        for (int i=result.size()-2; i>=0; --i) {
            fair.back().push_back(result[i]);
        }
    } else {
        int i=0;
        if (p==0) ++i;
        while (i*i*2 <= rest) {
            result[p] = i;
            fill(p+1, l, result, rest - i*i*2);
            ++i;
        }
    }
}

vector<char> square(vector<char> a) {
    vector<char> result(a.size() * 2, 0);
    for (int i=0; i<a.size(); ++i) {
        for (int j=0; j<a.size(); ++j) {
            result[i+j] += a[i] * a[j];
        }
    }
    while ((result.size() > 1) && (result.back() == 0)) {
        result.pop_back();
    }
    return result;
}

int find(vector<char> num) {
    int A = 0, B = fair.size(), C;
    while (B-A > 1) {
        C = (A+B)/2;
        if (cmp(fair[C], num)) {
            A = C;
        } else {
            B = C;
        }
    }
    return A;
}

void print(vector<char> a) {
    for (int i=0; i<a.size(); ++i) {
        printf("%d", a[i]);
    }
    printf("\n");
}

char A[200], B[200];
int counter = 0;
void make() {
    printf("Case #%d: ", ++counter);
    scanf(" %s %s", A, B);
    vector<char> AA, BB;
    for (int i=0; A[i] != NULL; ++i) {
        AA.push_back(A[i]-'0');
    }
    
    int i=AA.size() - 1;
    while(AA[i] == 0) {
        AA[i] = 9;
        --i;
    }
    --AA[i];
    
    for (int i=0; B[i] != NULL; ++i) {
        BB.push_back(B[i]-'0');
    }
    
    int a_pos = find(AA);
    int b_pos = find(BB);
    
    printf("%d\n", b_pos - a_pos);
}

void preprocessing() {
    
    vector<char> digit(1);
    digit[0] = 0;
    fair.push_back(digit);
    digit[0] = 1;
    fair.push_back(digit);
    digit[0] = 2;
    fair.push_back(digit);
    digit[0] = 3;
    fair.push_back(digit);
    
    for (int i=2; i<52; ++i) {
        vector<char> result((i+1)/2);
        fill(0, i, result, 9);
    }
    for (int i=0; i<fair.size(); ++i) {
        fair[i] = square(fair[i]);
    }
}

int main() {
    preprocessing();
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int t; scanf("%d", &t);
    while(t--) {
        make();
    }
    
    return 0;
}

//
#define MAXN 201

struct Node {
    
};

int N;
int initial[MAXN];
int allCount[MAXN];
bool visited[MAXN];
bool used[MAXN];

int key[MAXN];
vector<int> chests[MAXN];

void dfs(int index) {
    visited[index] = true;
    for (int i = 0; i < chests[index].size(); ++i) {
        for (int j = 1; j <= N; ++j) {
            if (chests[index][i] == key[j] && !visited[j] && !used[j]) {
                dfs(j);
            }
        }
    }
}

bool check() {
    for (int i = 0; i < MAXN; ++i) {
        allCount[i] = initial[i];
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            for (int k = 0; k < chests[i].size(); ++k) {
                ++allCount[chests[i][k]];
            }
        }
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i]) {
            if (allCount[key[i]] == 0) {
                return false;
            }
            else {
                --allCount[key[i]];
            }
        }
    }
    for (int i = 0; i < MAXN; ++i) {
        visited[i] = false;
    }
    for (int i = 1; i <= N; ++i) {
        if (initial[key[i]] > 0 && !visited[i] &&!used[i]) {
            dfs(i);
        }
    }
    for (int i = 1; i <= N; ++i) {
        if (!used[i] && !visited[i]) {
            return false;
        }
    }
    return true;
}

int Treasure() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int K;
        cin >> K >> N;
        for (int i = 0; i < MAXN; ++i) {
            visited[i] = false;
            used[i] = false;
            initial[i] = 0;
            chests[i].clear();
        }
        for (int i = 0; i < K; ++i) {
            int keyType;
            cin >> keyType;
            initial[keyType] += 1;
        }
        for (int i = 1; i <= N; ++i) {
            int k;
            cin >> key[i] >> k;
            for (int j = 0; j < k; ++j) {
                int keyType;
                cin >> keyType;
                chests[i].push_back(keyType);
            }
        }
        if (!check()) {
            cout<<"Case #"<<index<<": IMPOSSIBLE"<<endl;
            continue;
        }
        cout<<"Case #"<<index<<": ";
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (!used[j] && initial[key[j]] > 0) {
                    --initial[key[j]];
                    for (int k = 0; k < chests[j].size(); ++k) {
                        ++initial[chests[j][k]];
                    }
                    used[j] = true;
                    if (check()) {
                        cout<<j<<" ";
                        break;
                    }
                    used[j] = false;
                    for (int k = 0; k < chests[j].size(); ++k) {
                        --initial[chests[j][k]];
                    }
                    ++initial[key[j]];
                }
            }
        }
        cout<<endl;
    }
    return 0;
}

int main() {
    return 0;
}

#define MAXN 2005


int U[MAXN], V[MAXN];

void splitRoom(int index, vector<vector<int> >& rooms) {
    int a = U[index], b = V[index];
    if (a > b) {
        swap(a, b);
    }
    for (int i = 0; i < rooms.size(); ++i) {
        int idx = -1, jdx = -1;
        for (int j = 0; j < rooms[i].size(); ++j) {
            if (rooms[i][j] == a) {
                idx = j;
            }
            else if (rooms[i][j] == b) {
                jdx = j;
            }
        }
        if (idx != -1 && jdx != -1) {
            vector<int> v;
            for (int j = 0; j < rooms[i].size(); ++j) {
                v.push_back(rooms[i][j]);
            }
            rooms[i].clear();
            rooms[i].push_back(a);
            rooms[i].push_back(b);
            vector<int> r1;
            r1.push_back(a);
            r1.push_back(b);
            for (int j = 0; j < v.size(); ++j) {
                if (v[j] > a && v[j] < b) {
                    rooms[i].push_back(v[j]);
                }
            }
            for (int j = 0; j < v.size(); ++j) {
                if (v[j] < a || v[j] > b) {
                    r1.push_back(v[j]);
                }
            }
            rooms.push_back(r1);
            return;
        }
    }
}
int HouseOfKittens() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N, M;
        cin >> N >> M;
        for (int i = 0; i < M; ++i) {
            cin >> U[i];
            --U[i];
        }
        for (int i = 0; i < M; ++i) {
            cin >> V[i];
            --V[i];
        }
        vector<vector<int> > rooms;
        vector<int> color(N, -1);
        rooms.clear();
        
        vector<int> aV;
        for (int i = 0; i < N; ++i) {
            aV.push_back(i);
        }
        rooms.push_back(aV);
        for (int i = 0; i < M; ++i) {
            splitRoom(i, rooms);
        }
        
        cout<<"Case #"<<index<<": ";
        int C = 2*N;
        for (int i = 0; i < rooms.size(); ++i) {
            sort(rooms[i].begin(), rooms[i].end());
            C = min(C, (int)rooms[i].size());
        }
        cout << C <<endl;
        vector<bool> filled(rooms.size(), false);
        color[0] = 0, color[1] = 1;
        while (true) {
            for (int i = 0; i < rooms.size(); ++i) {
                if (!filled[i]) {
                    bool colored = false;
                    int idx;
                    for (int j = 0; j < rooms[i].size(); ++j) {
                        if (color[rooms[i][j]] != -1 && color[rooms[i][(j + 1)%rooms[i].size()]] != -1) {
                            colored = true;
                            idx = j;
                            break;
                        }
                    }
                    if (colored) {
                        vector<int> v;
                        for (int j = idx; j < idx + rooms[i].size(); ++j) {
                            v.push_back(rooms[i][j % rooms[i].size()]);
                        }
                        int a = color[v[0]], b = color[v[1]];
                        int it = 2;
                        for (int j = 0; j < C; ++j) {
                            if (j != a && j != b) {
                                color[v[it]] = j;
                                ++it;
                            }
                        }
                        
                        for (int it = C; it < v.size(); ++it) {
                            int j = 0;
                            while(j == color[v[it - 1]] || (it == v.size() - 1 && j == a)) j++;
                            color[v[it]] = j;
                        }
                        
                        filled[i] = true;
                        break;
                    }
                }
            }
            bool finish = true;
            for (int i = 0; i < N; ++i) {
                if (color[i] == -1) {
                    finish = false;
                    break;
                }
            }
            if (finish) {
                break;
            }
        }
        for (int i = 0; i < N; ++i) {
            cout << color[i] + 1 << " ";
        }
        cout<<endl;
    }
    return 0;
}

struct Node {
    double d, v;
};

double X, S, R, t;
int N;

bool comp(Node i, Node j) {return i.v < j.v;}

int AirportWalkways() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> X >> S >> R >> t >> N;
        vector<Node> v;
        int pos = 0;
        int B, E, w;
        for (int i = 0; i < N; ++i) {
            cin >> B >> E >> w;
            Node node;
            node.d = E - B;
            node.v = S + w;
            v.push_back(node);
            if (pos < B) {
                Node node;
                node.d = B - pos;
                node.v = S;
                v.push_back(node);
            }
            pos = E;
        }
        if (pos < X) {
            Node node;
            node.d = X - pos;
            node.v = S;
            v.push_back(node);
        }
        sort(v.begin(), v.end(), comp);
        double total = 0;
        for (int i = 0; i < v.size(); ++i) {
            if (t > 0) {
                double dist = (v[i].v + R - S)*t;
                if (dist <= v[i].d) {
                    total += t + (v[i].d - dist)/v[i].v;
                    t = 0;
                }
                else {
                    total += v[i].d/(v[i].v + R - S);
                    t -= v[i].d/(v[i].v + R - S);
                }
            }
            else {
                total += v[i].d / v[i].v;
            }
        }
        cout<<"Case #"<<index<<": "<<fixed<<setprecision(9)<<total<<endl;
    }
    return 0;
}

#define ll long long
#define MAXN 505

struct Node {
    
};

ll grid[MAXN][MAXN], row[MAXN], rowLeft[MAXN][MAXN], rowRight[MAXN][MAXN], col[MAXN], colTop[MAXN][MAXN], colBot[MAXN][MAXN];

bool check(int i, int j, int K) {
    ll w = 0, wSum = 0;
    for (int m = i; m <= i + K - 1; ++m) {
        ll weight = row[m] - rowLeft[m][j] - rowRight[m][j + K - 1];
        if (m == i || m == i + K - 1) {
            weight = row[m] - rowLeft[m][j + 1] - rowRight[m][j + K - 2];
        }
        w += weight;
        wSum += weight * (2*m + 1);
    }
    if (wSum != w*(2*i + K)) {
        return false;
    }
    
    wSum = 0;
    for (int m = j; m <= j + K - 1; ++m) {
        ll weight = col[m] - colTop[i][m] - colBot[i + K - 1][m];
        if (m == j || m == j + K - 1) {
            weight = col[m] - colTop[i + 1][m] - colBot[i + K - 2][m];
        }
        wSum += weight * (2*m + 1);
    }
    if (wSum != w*(2*j + K)) {
        return false;
    }
    return true;
}
int SpinningBlade() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll grid[MAXN][MAXN];
        int R, C, D;
        char c;
        cin >> R >> C >> D;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> c;
                grid[i][j] = (ll)(c - '0') + D;
            }
        }
        for (int i = 0; i < R; ++i) {
            rowLeft[i][0] = 0;
            ll sum = 0;
            for (int j = 1; j < C; ++j) {
                sum += grid[i][j - 1];
                rowLeft[i][j] = sum;
            }
            rowRight[i][C - 1] = 0;
            sum = 0;
            for (int j = C - 2; j >= 0; --j) {
                sum += grid[i][j + 1];
                rowRight[i][j] = sum;
            }
            sum = 0;
            for (int j = 0; j < C; ++j) {
                sum += grid[i][j];
            }
            row[i] = sum;
        }
        for (int j = 0; j < C; ++j) {
            colTop[0][j] = 0;
            ll sum = 0;
            for (int i = 1; i < R; ++i) {
                sum += grid[i - 1][j];
                colTop[i][j] = sum;
            }
            colBot[R - 1][j] = 0;
            sum = 0;
            for (int i = R - 2; i >= 0; --i) {
                sum += grid[i + 1][j];
                colBot[i][j] = sum;
            }
            sum = 0;
            for (int i = 0; i < R; ++i) {
                sum += grid[i][j];
            }
            col[j] = sum;
        }
        int K = min(R, C);
        bool found = false;
        for (; K >= 3; --K) {
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    if (i + K - 1 < R && j + K - 1 < C) {
                        if (check(i, j, K)) {
                            found = true;
                            break;
                        }
                    }
                }
                if (found)
                    break;
            }
            if (found)
                break;
        }
        cout<<"Case #"<<index<<": ";
        if (found) {
            cout<< K <<endl;
        }
        else {
            cout<< "IMPOSSIBLE" <<endl;
        }
    }
    return 0;
}

bool check(ll m, ll r, ll t) {
    ll d = 2*m + (2*r - 1);
    if (d > t/m)
        return false;
    return true;
}

int Bullseye() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll r, t;
        cin >> r >> t;
        ll l = 1, h = 1e9;
        while (h - l > 1) {
            ll mid = l + (h - l)/2;
            if (check(mid, r, t))
                l = mid;
            else
                h = mid;
        }
        cout<<"Case #"<<index<<": "<<l<<endl;
    }
    return 0;
}



int ManageyourEnergy() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int E, R, N;
        cin >> E >> R >> N;
        if (R > E) {
            R = E;
        }
        vector<ll> val(N), usedE(N);
        for (int i = 0; i < N; ++i) {
            cin >> val[i];
        }
        usedE[0] = E;
        for (int i = 1; i < N; ++i) {
            usedE[i] = R;
            for (int j = i - 1; j >= 0; --j) {
                if (val[j] >= val[i]) {
                    break;
                }
                if (usedE[i] + usedE[j] > E) {
                    usedE[j] -= E - usedE[i];
                    usedE[i] = E;
                    break;
                }
                else {
                    usedE[i] += usedE[j];
                    usedE[j] = 0;
                }
            }
        }
        ll sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += val[i]*usedE[i];
        }
        cout<<"Case #"<<index<<": "<<sum<<endl;
    }
    return 0;
}

#define ll long long

struct Node {
    
};

ll r, t;

bool check(ll m) {
    ll prod = 2*m*m + (2*r - 1)*m;
    assert(prod > 0);
    return prod <= t;
}

int Bullseye() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> r >> t;
        ll l = 1, h = 1;
        while (check(h)) {
            l = h;
            h *= 2;
        }
        
        while (h - l > 1) {
            ll mid = l + (h - l)/2;
            if (check(mid))
                l = mid;
            else
                h = mid;
        }
        cout<<"Case #"<<index<<": "<<l<<endl;
    }
    
    return 0;
}

int ManageyourEnergy() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll E, R, N;
        cin >> E >> R >> N;
        if (R > E) {
            R = E;
        }
        vector<ll> v(N), usedE(N, R);
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
        }
        stack<ll> s;
        usedE[0] = E;
        for (ll i = 0; i < N; ++i) {
            while (!s.empty() && v[s.top()] < v[i]) {
                if (usedE[i] + usedE[s.top()] > E) {
                    usedE[s.top()] -= E - usedE[i];
                    usedE[i] = E;
                    break;
                }
                else {
                    usedE[i] += usedE[s.top()];
                    usedE[s.top()] = 0;
                    s.pop();
                }
            }
            s.push(i);
        }
        ll ret = 0;
        for (int i = 0; i < N; ++i) {
            ret += usedE[i]*v[i];
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

const int M = 7, N = 12, K = 12;

char str[N + 1];
ll fact[N + 1];
ll product[K];

struct Node {
    string s;
    ll p;
    tr1::unordered_map<ll, ll> prob;
    tr1::unordered_map<ll, ll>::iterator it;
    double check() {
        double kp = 1;
        for (int i = 0; i < K; ++i) {
            it = prob.find(product[i]);
            if (it == prob.end()) {
                return 0;
            }
            kp *= it->second;
        }
        return kp / p;
    }
};

vector<Node> v;

void dfs(int idx) {
    if (idx == N) {
        Node n;
        n.s = string(str);
        n.p = 1;
        for (int j = 0, k = -1; j < N; ++j) {
            if (str[j] != str[j + 1]) {
                n.p *= fact[j - k];
                k = j;
            }
        }
        for (int i = 0; i < (1 << N); ++i) {
            ll p = 1;
            for (int j = 0; j < N; ++j) {
                if (i & (1 << j)) {
                    p *= str[j] - '0';
                }
            }
            ++n.prob[p];
        }
        v.push_back(n);
        return;
    }
    char c = (idx == 0) ? '2' : str[idx - 1];
    for (char i = c; i <= '0' + M + 1; ++i) {
        str[idx] = i;
        dfs(idx + 1);
    }
}

void init() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = fact[i - 1]*i;
    }
    v.clear();
    str[N] = '\0';
    dfs(0);
    return;
}

int GoodLuck() {
    
    init();
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll r, n, m , k;
        cin >> r >> n >> m >> k;
        cout<<"Case #"<<index<<": "<<endl;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < K; ++j) {
                cin >> product[j];
            }
            int ret = 0;
            double maxp = 0;
            for (int j = 0; j < v.size(); ++j) {
                double pr = v[j].check();
                if (maxp < pr) {
                    maxp = pr;
                    ret = j;
                }
            }
            cout<<v[ret].s<<endl;
        }
    }
    
    return 0;
}

#define ll long long

const int MAXN = 1000005;

ll N, cnt;
bool isPrime[MAXN];
ll primeV[MAXN];

void init() {
    for (int i = 0; i < MAXN; ++i) {
        isPrime[i] = true;
    };
    cnt = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (isPrime[i]) {
            primeV[cnt++] = i;
            ll p = i;
            while (p < MAXN) {
                p += i;
                isPrime[p] = false;
            }
        }
    }
}

int ExpensiveDinner() {
    
    init();
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> N;
        ll ret = 0;
        for (int i = 0; i < cnt; ++i) {
            ll p = primeV[i]*primeV[i];
            if (p <= N) {
                while (p <= N) {
                    ++ret;
                    p *= primeV[i];
                }
            }
            else
                break;
        }
        if (N > 1) {
            ++ret;
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

const int MAXD = 405;

struct Node{
    int d;
    bool visited;
    vector<int> edgeTo;
    Node(){
        d = -1;
        visited = false;
    }
};

int P, W, D;
bool hasEdge[MAXD][MAXD];
ll F[MAXD][MAXD];
Node graph[MAXD];
vector<int> vertex[MAXD];

void check(int idx, int jdx) {
    
}

int A.I.War() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        for (int i = 0; i < MAXD; ++i) {
            graph[i].d = -1;
            graph[i].visited = false;
            graph[i].edgeTo.clear();
            vertex[i].clear();
            for (int j = 0; j < MAXD; ++j) {
                hasEdge[i][j] = false;
                F[i][j] = 0;
            }
        }
        cin >> P >> W;
        for (int i = 0; i < W; ++i) {
            int u, v;
            char c;
            cin >> u >> c >> v;
            graph[u].edgeTo.push_back(v);
            graph[v].edgeTo.push_back(u);
            hasEdge[u][v] = true;
            hasEdge[v][u] = true;
        }
        graph[0].d = 0;
        graph[0].visited = true;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < graph[u].edgeTo.size(); ++i) {
                int v = graph[u].edgeTo[i];
                if (!graph[v].visited) {
                    graph[v].visited = true;
                    graph[v].d = graph[u].d + 1;
                    q.push(v);
                }
            }
        }
        D = graph[1].d - 1;
        for (int i = 0; i < P; ++i) {
            if (graph[i].d >= 0) {
                vertex[graph[i].d].push_back(i);
            }
        }
        for (int i = 0; i < graph[0].edgeTo.size(); ++i) {
            int v = graph[0].edgeTo[i];
            F[0][v] = graph[0].edgeTo.size();
            for (int j = 0; j < graph[v].edgeTo.size(); ++j) {
                int u = graph[v].edgeTo[j];
                if (!hasEdge[0][u]) {
                    ++F[0][v];
                }
            }
        }
        //d - 2, d - 1, d
        for (int i = 2; i <= D; ++i) {
            for (int j = 0; j < vertex[i].size(); ++j) {
                int c = vertex[i][j];
                for (int m = 0; m < graph[c].edgeTo.size(); ++m) {
                    int b = graph[c].edgeTo[m];
                    if (graph[b].d + 1 == graph[c].d) {
                        for (int n = 0; n < graph[b].edgeTo.size(); ++n) {
                            int a = graph[b].edgeTo[n];
                            if (graph[a].d + 1 == graph[b].d) {
                                ll r = F[a][b];
                                for (int k = 0; k < graph[c].edgeTo.size(); ++k) {
                                    int u = graph[c].edgeTo[k];
                                    if (u != a && u != b && !hasEdge[u][a] && !hasEdge[u][b]) {
                                        ++r;
                                    }
                                }
                                F[b][c] = max(F[b][c], r);
                            }
                        }
                    }
                }
            }
        }
        ll ret = 0;
        if (D == 0) {
            ret = graph[0].edgeTo.size();
        }
        else {
            for (int i = 0; i < vertex[D].size(); ++i) {
                int v = vertex[D][i];
                bool flag = false;
                for (int j = 0; j < graph[v].edgeTo.size(); ++j) {
                    if (graph[v].edgeTo[j] == 1) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    continue;
                }
                for (int j = 0; j < vertex[D - 1].size(); ++j) {
                    int u = vertex[D - 1][j];
                    ret = max(ret, F[u][v]);
                }
            }
            ret -= D + 1;
        }
        cout<<"Case #"<<index<<": "<<D<<" "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

const int MAXN = 105;

struct Node{
};

int LX[MAXN], LY[MAXN], UX[MAXN], UY[MAXN];

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int W, L, U, G;
        cin >> W >> L >> U >> G;
        for (int i = 0; i < L; ++i) {
            cin >> LX[i] >> LY[i];
        }
        for (int i = 0; i < U; ++i) {
            cin >> UX[i] >> UY[i];
        }
        int li = 1, ui = 1;
        double area = 0, pX = 0, pY = UY[0] - LY[0];
        vector<double> X, Y;
        X.push_back(pX);
        Y.push_back(pY);
        for (int i = 1; i <= W; ++i) {
            if (i < LX[li] && i < UX[ui]) {
                continue;
            }
            if (i == LX[li] && i == UX[ui]) {
                double y = UY[ui] - LY[li];
                area += (y + pY)*(i - pX)/2;
                pX = i;
                pY = y;
                ++li;
                ++ui;
                X.push_back(pX);
                Y.push_back(pY);
                continue;
            }
            if (i == LX[li] && i < UX[ui]) {
                double y = ((double)UY[ui] - UY[ui - 1])*(i - UX[ui - 1])/(UX[ui] - UX[ui - 1]) + UY[ui - 1] - LY[li];
                area += (y + pY)*(i - pX)/2;
                pX = i;
                pY = y;
                ++li;
                X.push_back(pX);
                Y.push_back(pY);
                continue;
            }
            if (i < LX[li] && i == UX[ui]) {
                double y = UY[ui] - (((double)LY[li] - LY[li - 1])*(i - LX[li - 1])/(LX[li] - LX[li - 1]) + LY[li - 1]);
                area += (y + pY)*(i - pX)/2;;
                pX = i;
                pY = y;
                ++ui;
                X.push_back(pX);
                Y.push_back(pY);
                continue;
            }
        }
        double slide = area / G;
        vector<double> ret;
        double prev = 0, cur = 0;
        assert(X.size() == Y.size());
        for (int i = 1; i < X.size(); ++i) {
            cur = prev + (Y[i] + Y[i - 1])*(X[i] - X[i - 1])/2;
            double px = X[i - 1], py = Y[i - 1];
            while (cur >= slide) {
                double a = slide - prev;
                double l = X[i - 1], h = X[i], y = 0;
                for (int k = 0 ; k < 1000; ++k) {
                    double mid = (l + h)/2;
                    y = py + (Y[i] - py)*(mid - px)/(X[i] - px);
                    double s = (mid - px)*(py + y)/2;
                    if (s < a) {
                        l = mid;
                    }
                    else {
                        h = mid;
                    }
                }
                ret.push_back(l);
                prev = 0;
                px = l;
                py = y;
                cur -= slide;
            }
            prev = cur;
        }
        cout<<"Case #"<<index<<": "<<endl;
        for (int i = 0; i < ret.size(); ++i) {
            if (abs(W - ret[i]) > 1e-9) {
                cout<<fixed<<setprecision(9)<<ret[i]<<endl;
            }
        }
    }
    
    return 0;
}

struct Node{
    int end, len;
};

bool lineComp(Node i, Node j) {return i.len < j.len;}


int DireStraights() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N;
        cin >> N;
        if (N == 0) {
            cout<<"Case #"<<index<<": "<<0<<endl;
            continue;
        }
        vector<int> cards(N);
        for (int i = 0; i < N; ++i) {
            cin >> cards[i];
        }
        sort(cards.begin(), cards.end());
        vector<Node> hand;
        for (int i = 0; i < N; ++i) {
            int idx = cards[i];
            bool fit = false;
            for (int j = 0; j < hand.size(); ++j) {
                if (hand[j].end + 1 == idx) {
                    ++hand[j].end;
                    ++hand[j].len;
                    fit = true;
                    break;
                }
            }
            if (!fit) {
                Node n;
                n.end = idx;
                n.len = 1;
                hand.push_back(n);
            }
            sort(hand.begin(), hand.end(), lineComp);
        }
        int ret = 1e6;
        for (int i = 0; i < hand.size(); ++i) {
            if (hand[i].len < ret) {
                ret = hand[i].len;
            }
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

const ll MOD = 1000003;

int PerpetualMotion() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        char c;
        int R, C;
        cin >> R >> C;
        int N = R*C;
        vector<vector<int> > edgeTo(N);
        vector<vector<int> > edgeFrom(N);
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                int i1 = i, j1 = j, i2 = i, j2 = j;
                cin >> c;
                switch (c) {
                    case '-':
                        i1 = i;
                        j1 = (j - 1 + C)%C;
                        i2 = i;
                        j2 = (j + 1)%C;
                        break;
                    case '|':
                        i1 = (i - 1 + R)%R;
                        j1 = j;
                        i2 = (i + 1)%R;
                        j2 = j;
                        break;
                    case '/':
                        i1 = (i - 1 + R)%R;
                        j1 = (j + 1)%C;
                        i2 = (i + 1)%R;
                        j2 = (j - 1 + C)%C;
                        break;
                    case '\\':
                        i1 = (i - 1 + R)%R;
                        j1 = (j - 1 + C)%C;
                        i2 = (i + 1)%R;
                        j2 = (j + 1)%C;
                        break;
                    default:
                        break;
                }
                int idx = i*C + j, idx1 = i1*C + j1, idx2 = i2*C + j2;
                edgeTo[idx].push_back(idx1);
                edgeTo[idx].push_back(idx2);
                edgeFrom[idx1].push_back(idx);
                edgeFrom[idx2].push_back(idx);
            }
        }
        vector<bool> left(N, false), right(N, false), inQueue(N, false);
        queue<int> toProcess;
        for (int i = 0; i < N; ++i) {
            if (edgeFrom[i].size() < 2) {
                toProcess.push(i);
                inQueue[i] = true;
            }
        }
        bool impossible = false;
        while (!toProcess.empty()) {
            int v = toProcess.front();
            toProcess.pop();
            if (right[v])
                continue;
            right[v] = true;
            inQueue[v] = false;
            if (edgeFrom[v].size() == 0) {
                impossible = true;
                break;
            }
            int u = edgeFrom[v][0];
            left[u] = true;
            int v1 = (edgeTo[u][0] != v) ? edgeTo[u][0] : edgeTo[u][1];
            for (int i = 0; i < edgeFrom[v1].size(); ++i) {
                if (edgeFrom[v1][i] == u) {
                    edgeFrom[v1].erase(edgeFrom[v1].begin() + i);
                    break;
                }
            }
            if (edgeFrom[v1].size() < 2 && !right[v1] && !inQueue[v1]) {
                toProcess.push(v1);
                inQueue[v1] = true;
            }
        }
        if (impossible) {
            cout<<"Case #"<<index<<": "<<0<<endl;
            continue;
        }
        int K = 0;
        for (int i = 0; i < N; ++i) {
            if (!left[i]) {
                ++K;
                left[i] = true;
                int cur = i, prev = -1;
                while (true) {
                    int right = (edgeTo[cur][0] != prev) ? edgeTo[cur][0] : edgeTo[cur][1];
                    int nxt = (edgeFrom[right][0] != cur) ? edgeFrom[right][0] : edgeFrom[right][1];
                    if (nxt == i) {
                        break;
                    }
                    left[nxt] = true;
                    prev = right;
                    cur = nxt;
                }
            }
        }
        ll ret = 1;
        while (K--) {
            ret = (ret*2)%MOD;
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

string ret, s;

bool process(string &s) {
    int i = 0;
    for (; i < s.length(); ++i) {
        if (s[i] == '?')
            break;
    }
    if (i < s.length()) {
        s[i] = '0';
        if (process(s))
            return true;
        s[i] = '1';
        if (process(s))
            return true;
        s[i] = '?';
        return false;
    }
    string str(s);
    reverse(str.begin(), str.end());
    ll num = 0;
    for (i = 0; i < str.length(); ++i) {
        if (str[i] == '1') {
            num |= 1ll << i;
        }
    }
    ll sq = sqrt(num);
    bool flag = false;
    if (num == sq*sq)
        flag = true;
    if (!flag && num == (sq + 1)*(sq + 1)) {
        ++sq;
        flag = true;
    }
    if (!flag && num == (sq - 1)*(sq - 1)) {
        --sq;
        flag = true;
    }
    if (!flag)
        return false;
    ret = s;
    return true;
}

int MysterySquare() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> s;
        process(s);
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

int N, K;

vector<vector<char> > table;

char getChar(int i, int j) {
    if (i >= 0 && i < N && j >= 0 && j < N)
        return table[i][j];
    return '.';
}

bool check(int i, int j, char c) {
    bool flag = true;
    for (int k = 0; k < K; ++k) {
        if (getChar(i, j + k) != c) {
            flag = false;
            break;
        }
    }
    if (flag)
        return true;
    flag = true;
    for (int k = 0; k < K; ++k) {
        if (getChar(i + k, j) != c) {
            flag = false;
            break;
        }
    }
    if (flag)
        return true;
    flag = true;
    for (int k = 0; k < K; ++k) {
        if (getChar(i + k, j + k) != c) {
            flag = false;
            break;
        }
    }
    if (flag)
        return true;
    flag = true;
    for (int k = 0; k < K; ++k) {
        if (getChar(i - k, j + k) != c) {
            flag = false;
            break;
        }
    }
    if (flag)
        return true;
    return false;
}

int Rotate() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        table.clear();
        cin >> N >> K;
        char ch;
        vector<vector<char> > board(N, vector<char>(N, '.'));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> ch;
                board[j][N - 1 - i] = ch;
            }
        }
        vector<vector<char> > t(N, vector<char>(N, '.'));
        for (int j = 0; j < N; ++j) {
            int pos = N - 1;
            for (int i = N - 1; i >= 0; --i) {
                if (board[i][j] != '.') {
                    t[pos--][j] = board[i][j];
                }
            }
        }
        table = t;
        bool isR = false, isB = false;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (check(i, j, 'R'))
                    isR = true;
                if (check(i, j, 'B'))
                    isB = true;
            }
        }
        cout<<"Case #"<<index<<": ";
        if (isR && isB) {
            cout<<"Both"<<endl;
            continue;
        }
        if (!isR && !isB) {
            cout<<"Neither"<<endl;
            continue;
        }
        if (isR && !isB) {
            cout<<"Red"<<endl;
            continue;
        }
        if (!isR && isB) {
            cout<<"Blue"<<endl;
            continue;
        }
    }
    
    return 0;
}

int Osmos() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int A, N;
        cin >> A >> N;
        vector<ll> v(N);
        for (int i = 0; i < N; ++i) cin >> v[i];
        sort(v.begin(), v.end());
        int ret = N;
        for(int i = 1; i <= N; ++i){
            int tmp = N-i;
            int x = A;
            for (int j = 0; j < i; ++j){
                while(x <= v[j]){
                    if(x == 1){
                        tmp = N;
                        break;
                    }
                    x = 2*x-1;
                    tmp++;
                }
                x += v[j];
            }
            ret = min(ret, tmp);
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

double dp[1500][1500];

double check() {
    int N, x, y, t;
    cin >> N >> x >> y;
    for (t = 0; ; t += 2) {
        if (N <= 2*t + 1) break;
        N -= 2*t + 1;
    }
    if (x < 0) x = -x;
    if (x + y < t) return 1.0;
    if (x + y > t) return 0.0;
    
    if (N == 2*t + 1) return 1.0;
    if (y == t) return 0.0;
    
    for (int i = 0; i <= t; ++i) {
        for (int j = 0; j <= t; ++j) {
            dp[i][j] = 0.0;
        }
    }
    dp[0][0] = 1.0;
    for (int i = 0; i <= t; ++i) {
        for (int j = 0; j <= t; ++j) {
            if (i == t && j < t)
                dp[i][j + 1] += dp[i][j];
            if (i < t && j == t)
                dp[i + 1][j] += dp[i][j];
            if (i < t && j < t) {
                dp[i + 1][j] += dp[i][j]*0.5;
                dp[i][j + 1] += dp[i][j]*0.5;
            }
        }
    }
    double ans = 0.0;
    for (int i = 0; i <= t; ++i) {
        for (int j = 0; j <= t; ++j) {
            if (i + j == N && i > y) {
                ans += dp[i][j];
            }
        }
    }
    return ans;
}

int FallingDiamonds() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cout<<"Case #"<<index<<": "<<fixed<<setprecision(9)<<check()<<endl;
    }
    
    return 0;
}

#define ll long long

int Consonants() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        string s;
        ll n, L, ret = 0, c = 0, r = 0;
        cin >> s >> n;
        L = s.length();
        for (int i = 0; i < L; ++i) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
                c = 0;
            else
                ++c;
            if (c >= n) {
                ret += (i - n + 2 - r)*(L - i);
                r = i - n + 2;
            }
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

#define ll long long

int Pogo() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll x, y, N = 0, sum = 0;
        cin >> x >> y;
        //parity: 1 + 2 +...+ N == |x| + |y| (mod 2)
        while (sum < abs(x) + abs(y) || (sum + abs(x) + abs(y)) % 2 == 1) {
            N += 1;
            sum += N;
        }
        string ret = "";
        for (ll i = N; i >= 1; --i) {
            if (abs(x) > abs(y)) {
                if (x > 0) {
                    ret += 'E';
                    x -= i;
                }
                else {
                    ret += 'W';
                    x += i;
                }
            }
            else {
                if (y > 0) {
                    ret += 'N';
                    y -= i;
                }
                else {
                    ret += 'S';
                    y += i;
                }
            }
        }
        reverse(ret.begin(), ret.end());
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}

const int SZ = 521196;

int dp[4005][5];
char dict[SZ][20];
ll len[SZ];
char s[4005];

int GarbledEmail() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/dict.txt", "r", stdin);
    for (int i = 0; i < SZ; ++i) {
        scanf("%s", dict[i]);
        len[i] = strlen(dict[i]);
    }
    fclose(stdin);
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    scanf("%d", &T);
    for (int index = 1; index <= T; ++index) {
        memset(dp, 50, sizeof(dp));
        dp[0][0] = 0;
        scanf("%s", s);
        ll l = strlen(s);
        for (int i = 0; i < l; ++i) {
            fprintf(stderr, "%d: %d\n", index, i);
            for (int j = 0; j < 5; ++j) {
                if (dp[i][j] < 1e5) {
                    for (int k = 0; k < SZ; ++k) {
                        if (i + len[k] > l)
                            continue;
                        int gap = j, er = dp[i][j];
                        bool flag = true;
                        for (int p = 0; p < len[k]; ++p) {
                            if (s[i + p] != dict[k][p]) {
                                if (gap > 0) {
                                    flag = false;
                                    break;
                                }
                                gap = 4;
                                ++er;
                            }
                            else
                                --gap;
                        }
                        if (gap < 0) gap = 0;
                        if (flag && er < dp[i + len[k]][gap])
                            dp[i + len[k]][gap] = er;
                        
                    }
                }
            }
        }
        int ret = 1e5;
        for (int i = 0; i < 5; ++i) {
            ret = min(ret, dp[l][i]);
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    
    return 0;
}
//trie[trie[cur_node].next[s[begin]]].char == s[begin]
void dfs(int begin, int end, int cur_node, int cost, int gap) {
    if (cur_node == 0) return;
    if (begin == end) {
        if (trie[cur_node].isWord) {
            gap = max(gap, 0);
            opt[gap] = min(opt[gap], cost);
        }
        return;
    }
    dfs(begin + 1, end, trie[cur_node].next[s[begin] - 'a'], cost, gap - 1);
    if (gap <= 0) {
        for (int i = 0; i < 26; ++i) {
            dfs(begin + 1, end, trie[cur_node].next[i], cost + 1, 4);
        }
    }
}

int GarbledEmail() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/dict.txt", "r", stdin);
    for (int i = 0; i < SZ; ++i) {
        scanf("%s", s);
        int cur = 1;
        for (int j = 0; s[j] != '\0'; ++j) {
            int pos = s[j] - 'a';
            if (trie[cur].next[pos] == 0)
                trie[cur].next[pos] = ++tot;
            cur = trie[cur].next[pos];
        }
        trie[cur].isWord = true;
    }
    fclose(stdin);
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        for (int i = 0; i < 4005; ++i)
            for (int j = 0; j < 5; ++j)
                dp[i][j] = INF;
        dp[0][0] = 0;
        scanf("%s", s);
        ll n = strlen(s);
        for (int i = 0; i < n; ++i) {
            //fprintf(stderr, "%d: %d\n", index, i);
            for (int j = 0; j < 5; ++j) {
                if (dp[i][j] < INF) {
                    //max word length is 10
                    for (int k = 0; k < 10 && i + k < n; ++k) {
                        for (int m = 0; m < 5; ++m) opt[m] = INF;
                        dfs(i, i + k + 1, 1, 0, j);
                        for (int m = 0; m < 5; ++m) {
                            dp[i + k + 1][m] = min(dp[i + k + 1][m], dp[i][j] + opt[m]);
                        }
                    }
                }
            }
        }
        int ret = INF;
        for (int i = 0; i < 5; ++i)
            ret = min(ret, dp[n][i]);
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    return 0;
}

#define SIZE(v) ((int)(v).size())

#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),(x))-BEGIN(v)

#define FOR(i,l,r) for(int i=(l);i<(r);i++)
#define FOREACH(i,v) for(typeof((v).begin()) i=(v).begin();i!=(v).end();i++)

const int MAXD = 1000000;

struct Segment {
	int lowest, fix;
    
	Segment() {}
    
	Segment(int lowest) : lowest(lowest), fix(0) {}
    
	Segment(int lowest, int fix) : lowest(lowest), fix(fix) {}
    
	int getLowest() const {
		return max(lowest, fix);
	}
    
	void update() {
		lowest = max(lowest, fix);
	}
    
	Segment operator + (const Segment &rhs) const {
		return Segment(min(getLowest(), rhs.getLowest()));
	}
};

struct SegmentTree {
	int n;
	vector<Segment> seg;
	
	static int LEFT(int idx) { return idx << 1; }
	static int RIGHT(int idx) { return (idx << 1) | 1; }
    
	void _build(int idx, int lower, int upper) {
		if (lower == upper) {
			seg[idx] = Segment(0);
			return ;
		}
		int middle = (lower + upper) >> 1;
		_build(LEFT(idx), lower, middle);
		_build(RIGHT(idx), middle + 1, upper);
		seg[idx] = seg[LEFT(idx)] + seg[RIGHT(idx)];
	}
    
	void init(int n) {
		this->n = n;
		seg = vector<Segment>(n << 2);
		_build(1, 0, n - 1);
	}
    
	void pushDown(int idx) {
		seg[LEFT(idx)].fix = max(seg[LEFT(idx)].fix, seg[idx].fix);
		seg[RIGHT(idx)].fix = max(seg[RIGHT(idx)].fix, seg[idx].fix);
		seg[idx].lowest = max(seg[idx].lowest, seg[idx].fix);
		seg[idx].fix = 0;
	}
    
	int l, r, v;
    
	void _modify(int idx, int lower, int upper) {
		if (l <= lower && upper <= r) {
			seg[idx].fix = max(seg[idx].fix, v);
			return ;
		}
		pushDown(idx);
		int middle = (lower + upper) >> 1;
		if (r <= middle) {
			_modify(LEFT(idx), lower, middle);
		} else if (middle < l) {
			_modify(RIGHT(idx), middle + 1, upper);
		} else {
			_modify(LEFT(idx), lower, middle);
			_modify(RIGHT(idx), middle + 1, upper);
		}
		seg[idx] = seg[LEFT(idx)] + seg[RIGHT(idx)];
	}
    
	void modify(int l, int r, int v) {
		this->l = l;
		this->r = r;
		this->v = v;
		_modify(1, 0, n - 1);
	}
    
	Segment _getMin(int idx, int lower, int upper) {
		if (l <= lower && upper <= r) {
			seg[idx].update();
			return seg[idx];
		}
		pushDown(idx);
		int middle = (lower + upper) >> 1;
		Segment res;
		if (r <= middle) {
			res = _getMin(LEFT(idx), lower, middle);
		} else if (middle < l) {
			res = _getMin(RIGHT(idx), middle + 1, upper);
		} else {
			res = _getMin(LEFT(idx), lower, middle) + _getMin(RIGHT(idx), middle + 1, upper);
		}
		seg[idx] = seg[LEFT(idx)] + seg[RIGHT(idx)];
		return res;
	}
    
	Segment getMin(int l, int r) {
		this->l = l;
		this->r = r;
		return _getMin(1, 0, n - 1);
	}
};

struct Attack {
	int w, e, s;
    
	Attack() {}
    
	Attack(int w, int e, int s) : w(w), e(e), s(s) {}
};

int N;
vector<Attack> attacks[MAXD];
vector<int> DIS;
SegmentTree smt;

void init() {
	DIS.clear();
	FOR(i, 0, MAXD) attacks[i].clear();
}

int TheGreatWall() {
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
	int taskNumber;
	scanf("%d", &taskNumber);
	for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
		init();
		scanf("%d", &N);
		FOR(_, 0, N) {
			int d, n, w, e, s, deltaD, deltaP, deltaS;
			scanf("%d%d%d%d%d%d%d%d", &d, &n, &w, &e, &s, &deltaD, &deltaP, &deltaS);
			for (int i = 0; i < n; i++) {
				DIS.push_back(w - 1);
				DIS.push_back(w);
				DIS.push_back(e - 1);
				DIS.push_back(e);
				attacks[d].push_back(Attack(w, e, s));
				w += deltaP; e += deltaP;
				d += deltaD;
				s += deltaS;
			}
		}
		UNIQUE(DIS);
		smt.init(SIZE(DIS));
		int res = 0;
		FOR(day, 0, MAXD) {
			FOREACH(it, attacks[day]) {
				int w = INDEX(DIS, it->w), e = INDEX(DIS, it->e) - 1;
				res += smt.getMin(w, e).lowest < it->s;
			}
			FOREACH(it, attacks[day]) {
				int w = INDEX(DIS, it->w), e = INDEX(DIS, it->e) - 1;
				smt.modify(w, e, it->s);
			}
		}
		printf("Case #%d: %d\n", taskIdx, res);
	}
	return 0;
}

#define ll long long
const ll MOD = 100003;

ll dp[505][505];
ll cnr[505][505];

int YourRankisPure() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    for (int i = 0; i < 505; ++i) {
        for (int j = 0; j < 505; ++j) {
            if (j > i) {
                cnr[i][j] = 0;
                continue;
            }
            if (j == 0 || j == i) {
                cnr[i][j] = 1;
                continue;
            }
            if (i > 0)
                cnr[i][j] = (cnr[i - 1][j - 1] + cnr[i - 1][j]) % MOD;
        }
    }
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int n;
        cin >> n;
        for (int i = 2; i < 505; ++i) {
            dp[i][1] = 1;
            for (int j = 2; j < 505; ++j) {
                dp[i][j] = 0;
            }
        }
        for (int i = 3; i <= n; ++i) {
            for (int l = 2; l <= n - 1; ++l) {
                for (int j = l - 1; j >= 1; --j) {
                    int needed = l - j - 1, had = i - l - 1;
                    if (had >= needed) {
                        dp[i][l] = (dp[i][l] + cnr[had][needed]*dp[l][j]) % MOD;
                    }
                }
            }
        }
        ll ret = 0;
        for (int j = 1; j < n; ++j) {
            ret = (ret + dp[n][j]) % MOD;
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    return 0;
}

int PickingUpChicks() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll N, K, B, T;
        cin >> N >> K >> B >> T;
        vector<int> x(N), v(N);
        for (int i = 0; i < N; ++i)
            cin >> x[i];
        for (int i = 0; i < N; ++i)
            cin >> v[i];
        if (K == 0) {
            cout<<"Case #"<<index<<": "<<0<<endl;
            continue;
        }
        reverse(x.begin(), x.end());
        reverse(v.begin(), v.end());
        int blocks = 0, counts = 0;
        ll ret = 0;
        for (int i = 0; i < N; ++i) {
            ll vmin = (B - x[i] + T - 1) / T;
            if (vmin <= v[i]) {
                ++counts;
                ret += blocks;
            }
            else
                ++blocks;
            if (counts == K)
                break;
        }
        if (counts < K) {
            cout<<"Case #"<<index<<": IMPOSSIBLE"<<endl;
            continue;
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    return 0;
}

class Tree {
private:
    int tot;
    vector<map<string, int> > tree;
    
public:
    Tree() {
        tot = 0;
        map<string, int> m;
        tree.push_back(m);
    }
    int insert(string &s) {
        int i = 0, index = 0, c = 0;
        while (i < s.length()) {
            if (s[i] == '/') {
                ++i;
                continue;
            }
            int j = i + 1;
            while (j < s.length() && s[j] != '/') ++j;
            string str = s.substr(i, j - i);
            if (tree[index].find(str) == tree[index].end()) {
                ++tot;
                map<string, int> m;
                tree.push_back(m);
                tree[index][str] = tot;
                index = tot;
                ++c;
            }
            else
                index = tree[index][str];
            i = j;
        }
        return c;
    }
};

int FileFix-it() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        Tree t;
        int N, M, ret = 0;
        cin >> N >> M;
        string s;
        for (int i = 0; i < N; ++i) {
            cin >> s;
            t.insert(s);
        }
        for (int i = 0; i < M; ++i) {
            cin >> s;
            ret += t.insert(s);
        }
        cout<<"Case #"<<index<<": "<<ret<<endl;
    }
    return 0;
}

#define ll long long

const ll MOD = 1000002013;

struct Node {
    ll o, e, p;
    Node() {}
    Node(ll o, ll e, ll p) : o(o), e(e), p(p) {}
};

bool eComp(Node i, Node j) { return i.e < j.e; }
bool oComp(Node i, Node j) { return i.o < j.o; }

int TicketSwapping() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll N, M, o, e, p;
        cin >> N >> M;
        vector<Node> vec;
        for (int i = 0; i < M; ++i) {
            cin >> o >> e >> p;
            Node node(o, e, p);
            vec.push_back(node);
        }
        vector<Node> oV(vec.begin(), vec.end());
        sort(oV.begin(), oV.end(), oComp);
        ll total = 0;
        for (int i = 0; i < M; ++i) {
            ll k = oV[i].e - oV[i].o;
            total = (total + (k * N - k*(k - 1)/2) % MOD * oV[i].p % MOD) % MOD;
        }
        stack<Node> s;
        sort(vec.begin(), vec.end(), eComp);
        ll ret = 0;
        int cur = 0;
        for (int i = 0; i < M; ++i) {
            while (cur < M && oV[cur].o <= vec[i].e) {
                s.push(oV[cur++]);
            }
            ll needed = vec[i].p;
            while (needed > 0) {
                ll k =  vec[i].e - s.top().o;
                if (s.top().p > needed) {
                    s.top().p -= needed;
                    ret = (ret + (k * N - k*(k - 1)/2) % MOD * needed % MOD) % MOD;
                    break;
                }
                needed -= s.top().p;
                ret = (ret + (k * N - k*(k - 1)/2) % MOD * s.top().p % MOD) % MOD;
                s.pop();
            }
        }
        cout<<"Case #"<<index<<": "<<(total + MOD - ret) % MOD<<endl;
    }
    return 0;
}

#define ll long long

ll lowestRankedToWin(ll N, ll P) {
    if (P == 0) return -1;
    ll wins = 0;
    ll group = 1ll << N;
    while (group > P) {
        ++wins;
        group >>= 1ll;
    }
    return (1ll << N) - (1ll << wins);
}

int ManyPrizes() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll N, P;
        cin >> N >> P;
        cout<<"Case #"<<index<<": "<<(1ll << N) - 2 - lowestRankedToWin(N, (1ll << N) - P)<<" "<<lowestRankedToWin(N, P)<<endl;
    }
    return 0;
}

//return min number consisting of digits from the first number num1 that larger than the second number num2
//return "-1" if no such number
string floorOfNumber(string &num1, string &num2) {
    if(num1.length() == 0 || num2.length() == 0)
        return "-1";
    if (num1.length() < num2.length())
        return "-1";
    vector<int> cnt(10, 0);
    string ret = '0' + num2;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < num1.length(); ++i) {
        ++cnt[num1[i] - '0'];
    }
    for (i = 1; i <= num2.length(); ++i) {
        if (cnt[num2[i - 1] - '0'] > 0)
            --cnt[num2[i - 1] - '0'];
        else
            break;
    }
    if (i > num2.length()) i = (int)num2.length();
    for (j = i; j > 0; --j) {
        if (j != i)
            ++cnt[num2[j - 1] - '0'];
        k = num2[j - 1] - '0' + 1;
        while (k < 10 && cnt[k] == 0)
            ++k;
        if (k < 10) {
            --cnt[k];
            ret[j] = '0' + k;
            break;
        }
    }
    for (i = j + 1; i < ret.size(); ++i) {
        //j = 0: need one carry on digit, cannot be '0'
        k = (j == 0) ? 1 : 0;
        for (; k < 10; ++k) {
            if (cnt[k] > 0) {
                ret[i] = '0' + k;
                --cnt[k];
                break;
            }
        }
    }
    if (ret[0] != '0')
        return ret;
    return ret.substr(1);
}

const int SZ = 37;

double check(vector<ll> &v, int pos, ll h, ll B) {
    ll need = 0, gain = 0;
    for (int i = 0; i <= pos; ++i) {
        need += h - v[i];
        gain += 36*(h - v[i]);
    }
    for (int i = pos + 1; i < SZ; ++i) {
        if (v[i] >= h + 1) break;
        need += h + 1 - v[i];
    }
    if (need > B) return -1;
    double r = (double)gain / (pos + 1) - need;
    return max(r, 0.0);
}

int cheater() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ll B, N;
        cin >> B >> N;
        vector<ll> v(SZ, 0);
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        double ret = 0.0;
        for (int i = 0; i < SZ - 1; ++i) {
            ll l = v[i], h = B + v[SZ - 1] + 1;
            double r = 0.0;
            while (h - l > 1) {
                ll mid = l + (h - l)/2;
                r = check(v, i, mid, B);
                if (r < 0.0)
                    h = mid;
                else
                    l = mid;
            }
            r = check(v, i, l, B);
            ret = max(ret, r);
        }
        cout<<"Case #"<<index<<": "<<fixed<<setprecision(9)<<ret<<endl;
    }
    return 0;
}

struct Node {
    Node *next;
    int val;
    Node () {
        val = 0;
        next = NULL;
    }
};
/* Check whether a singly linked list is palindrome */
bool isPalidrome(Node **head, Node *tail) {
    if (tail == NULL)
        return true;
    bool flag = isPalidrome(head, tail->next);
    if (!flag)
        return false;
    flag = (*head)->val == tail->val;
    *head = (*head)->next;
    return flag;
}

bool isPalidrome(Node *root) {
    Node *p = root;
    return isPalidrome(&p, root);
}

long R = 65536;
long Q = 587101997;
tr1::unordered_map<long, vector<char*> > keys[10];

long getHash(char *str, long n) {
    long h = 0;
    for (int i = 0; i < n; i++) {
        h = (R * h + str[i]) % Q;
    }
    return h;
}

void initWithString(char *str) {
    for (int l = 1; l <= 10; l++) {
        keys[l - 1].clear();
        // R ^ (l - 1) % Q
        long RM = 1;
        for (int i = 1; i <= l - 1; i++) {
            RM = (R * RM) % Q;
        }
        long h = getHash(str, l);
        keys[l - 1][h].push_back(str);
        for (int i = l; str[i] != '\0'; i++) {
            h = (h + Q - RM * str[i - l] % Q) % Q;
            h = (h * R + str[i]) % Q;
            keys[l - 1][h].push_back(str + i - l + 1);
        }
    }
}

bool existSubString(char *query) {
    long n = strlen(query);
    long h = getHash(query, n);
    if (keys[n - 1].find(h) != keys[n - 1].end()) {
        vector<char *> v = keys[n - 1].find(h) -> second;
        for (int i = 0; i < v.size(); i++) {
            if (strncmp(v[i], query, n) == 0)
                return true;
        }
        return false;
    }
    return false;
}

pair<ListNode*, ListNode*> merge(ListNode *lo, ListNode *hi, int n) {
    ListNode *head = NULL, *prev = NULL, *cur = NULL;
    int ln = n, hn = n;
    while (lo != NULL && ln > 0 && hi != NULL && hn > 0) {
        if (lo->val <= hi->val) {
            cur = lo;
            lo = lo->next;
            ln--;
        }
        else {
            cur = hi;
            hi = hi->next;
            hn--;
        }
        if (prev == NULL)
            head = cur;
        else
            prev->next = cur;
        prev = cur;
    }
    
    while (lo != NULL && ln > 0) {
        if (prev == NULL)
            head = lo;
        else
            prev->next = lo;
        prev = lo;
        lo = lo->next;
        ln--;
    }
    
    while (hi != NULL && hn > 0) {
        prev->next = hi;
        prev = hi;
        hi = hi->next;
        hn--;
    }
    return make_pair<ListNode*, ListNode*>(head, prev);
}

ListNode* sortLinkList(ListNode *head) {
    if (head == NULL || head->next == NULL)  return head;
    
    int n = 0;
    ListNode *cur = head;
    while (cur != NULL) {
        n++;
        cur = cur->next;
    }
    
    for (int l = 1; l < n; l = 2*l) {
        ListNode *prevTail = NULL, *nextHead = head;
        for (int i = 0; i < n; i += 2*l) {
            ListNode *lo = nextHead, *hi = lo;
            for (int j = 0; j < l && hi != NULL; j++)
                hi = hi->next;
            nextHead = hi;
            for (int j = 0; j < l && nextHead != NULL; j++)
                nextHead = nextHead->next;
            pair<ListNode*, ListNode*> p = merge(lo, hi, l);
            if (prevTail == NULL)
                head = p.first;
            else
                prevTail->next = p.first;
            prevTail = p.second;
        }
        prevTail->next = NULL;
    }
    
    return head;
}

#include <tr1/unordered_map>

tr1::unordered_map<GraphNode*, pair<GraphNode*, bool> > pairs;

void copyNodesDFS(GraphNode *node) {
    if (node == NULL)  return;
    GraphNode *newNode = new GraphNode(node->data);
    pairs[node] = make_pair<GraphNode*, bool>(newNode, false);
    for (int i = 0; i < node->neighbors.size(); i++) {
        if (pairs.find(node->neighbors[i]) == pairs.end())
            copyNodesDFS(node->neighbors[i]);
    }
}

void copyNeighborsDFS(GraphNode* node) {
    if (node == NULL)  return;
    pairs[node].second = true;
    for (int i = 0; i < node->neighbors.size(); i++) {
        pairs[node].first->neighbors.push_back(pairs[node->neighbors[i]].first);
    }
    for (int i = 0; i < node->neighbors.size(); i++) {
        if (!pairs[node->neighbors[i]].second)
            copyNeighborsDFS(node->neighbors[i]);
    }
}

GraphNode *cloneGraph(GraphNode *node) {
    if (node == NULL)  return node;
    pairs.clear();
    copyNodesDFS(node);
    copyNeighborsDFS(node);
    return pairs[node].first;
}

int findMinAllOne(int a) {
    if (a <= 0)  return -1;
    int p = 1, c = 1;
    while (p < a) {
        p = p*10 + 1;
        c++;
    }
    set<int> s;
    p = p % a;
    while (p != 0) {
        if (s.find(p) != s.end())
            return -1;
        s.insert(p);
        p = (p*10 + 1) % a;
        c++;
    }
    return c;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool canJump(int p, int q, int x, int y, int x2, int y2) {
    if (p == 0 && q == 0)  return x == x2 && y == y2;
    int g = gcd(p, q), dx = abs(x - x2), dy = abs(y - y2);
    if (dx % g != 0 || dy % g != 0)
        return false;
    p /= g, q /= g, dx /= g, dy /= g;
    if (abs(p - q) % 2 == 1)
        return true;
    return abs(dx - dy) % 2 == 0;
}

typedef int JobID;

/*
 * deps[id]表示任务id所依赖的任务
 * 如果存在合法的任务完成序列，返回true，否则返回false
 * 合法的任务序列请存放在参数result中（已经分配空间，不需要push_back）
 */

bool DFS(JobID i, const map<JobID, vector<JobID> > &deps, vector<JobID> &result, int &index, vector<bool> &visited, vector<bool> &onStack) {
    visited[i] = true;
    if (deps.find(i) == deps.end()) {
        result[index++] = i;
        return true;
    }
    onStack[i] = true;
    bool flag = true;
    for (int j = 0; j < deps.find(i)->second.size(); j++) {
        int vj = deps.find(i)->second[j];
        if (!visited[vj]) {
            flag = DFS(vj, deps, result, index, visited, onStack);
            if (!flag)  return false;
        }
        else if (onStack[vj])
            return false;
    }
    onStack[i] = false;
    result[index++] = i;
    return true;
}

bool jobSchedule(const map<JobID, vector<JobID> > &deps, int n,
                 vector<JobID> &result) {
    if (n == 0)
        return true;
    
    vector<bool> visited(n + 1, false), onStack(n + 1, false);
    int index = 0;
    bool flag = true;
    for (JobID i = 1; i <= n; i++) {
        if (!visited[i]) {
            flag = DFS(i, deps, result, index, visited, onStack);
            if (!flag)
                break;
        }
    }
    if (!flag)  return false;
    return true;
}

#include <map>

void DFS(int idx, vector<int> &x, vector<int> &y,
         map<int, vector<int> > &rows,
         map<int, vector<int> > &cols, vector<bool> &visited) {
    visited[idx] = true;
    for (int i = 0; i < rows[x[idx]].size(); ++i) {
        int j = rows[x[idx]][i];
        if (!visited[j])
            DFS(j, x, y, rows, cols, visited);
    }
    for (int i = 0; i < cols[y[idx]].size(); ++i) {
        int j = cols[y[idx]][i];
        if (!visited[j])
            DFS(j, x, y, rows, cols, visited);
    }
}

//如果存在满足条件的遍历,返回true,否则返回false
bool existPath(vector<int> &x, vector<int> &y) {
    if (x.size() == 0)  return true;
    map<int, vector<int> > rows, cols;
    map<int, vector<int> >::iterator it;
    vector<bool> visited(x.size(), false);
    
    for (int i = 0; i < x.size(); i++) {
        rows[x[i]].push_back(i);
        cols[y[i]].push_back(i);
    }
    
    DFS(0, x, y, rows, cols, visited);
    for (int i = 0; i < x.size(); i++) {
        if (!visited[i])
            return false;
    }
    
    // Euclidean path: rows as n vertices and cols as m vertices
    int r = 0, c = 0;
    for (it = rows.begin(); it != rows.end(); ++it) {
        if ((it->second).size() % 2 == 1)
            r++;
    }
    for (it = cols.begin(); it != cols.end(); ++it) {
        if ((it->second).size() % 2 == 1)
            c++;
    }
    if (r + c > 2)  return false;
    return true;
}

/*矩形的定义:
 struct Rect {
 int x1,y1,x2,y2;
 }*/

int calcOverlap(Rect A, Rect B) {
    int x = max(0, min(A.x2, B.x2) - max(A.x1, B.x1));
    int y = max(0, min(A.y2, B.y2) - max(A.y1, B.y1));
    return x * y;
}

int minOverlapping(vector<Rect> &rects, int W, int H, int w, int h) {
    if (rects.size() == 0) return 0;
    
    vector<int> x, y;
    x.push_back(0), x.push_back(H - h);
    y.push_back(0), y.push_back(W - w);
    
    for (int i = 0; i < rects.size(); i++) {
        if (rects[i].x1 - h >= 0) x.push_back(rects[i].x1 - h);
        if (rects[i].y1 - w >= 0) y.push_back(rects[i].y1 - w);
        if (rects[i].x2 + h <= H) x.push_back(rects[i].x2);
        if (rects[i].y2 + w <= W) y.push_back(rects[i].y2);
    }
    
    int overlap = h*w + 1;
    Rect r;
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            r.x1 = x[i], r.x2 = x[i] + h;
            r.y1 = y[j], r.y2 = y[j] + w;
            int o = 0;
            for (int k = 0; k < rects.size(); k++) {
                o += calcOverlap(r, rects[k]);
            }
            overlap = min(overlap, o);
        }
    }
    return overlap;
}

vector<int> arrayUnion(vector<int> &a, vector<int> &b) {
    vector<int> r;
    int i = 0, j = 0, n = a.size(), m = b.size();
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            r.push_back(a[i]);
            i++;
            while (i < n && a[i] == a[i - 1]) i++;
        }
        else if (a[i] > b[j]) {
            r.push_back(b[j]);
            j++;
            while (j < m && b[j] == b[j - 1]) j++;
        }
        else {
            r.push_back(a[i]);
            i++;
            while (i < n && a[i] == a[i - 1]) i++;
            j++;
            while (j < m && b[j] == b[j - 1]) j++;
        }
    }
    while (i < n) {
        r.push_back(a[i]);
        i++;
        while (i < n && a[i] == a[i - 1]) i++;
    }
    while (j < m) {
        r.push_back(b[j]);
        j++;
        while (j < m && b[j] == b[j - 1]) j++;
    }
    return r;
}

vector<int> arrayIntersect(vector<int> &a, vector<int> &b) {
    vector<int> r;
    int i = 0, j = 0, n = a.size(), m = b.size();
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
            while (i < n && a[i] == a[i - 1]) i++;
        }
        else if (a[i] > b[j]) {
            j++;
            while (j < m && b[j] == b[j - 1]) j++;
        }
        else {
            r.push_back(a[i]);
            i++;
            while (i < n && a[i] == a[i - 1]) i++;
            j++;
            while (j < m && b[j] == b[j - 1]) j++;
        }
    }
    return r;
}

//使用getLeftChildNode(TreeNode)获得左儿子结点
//使用getRightChildNode(TreeNode)获得右儿子结点
//使用isNullNode(TreeNode)判断结点是否为空
int count_complete_binary_tree_nodes(TreeNode root) {
    if (isNullNode(root))  return 0;
    TreeNode left = getLeftChildNode(root);
    TreeNode right = getRightChildNode(root);
    int l = 0, r = 0;
    while (!isNullNode(left)) {
        l++;
        left = getLeftChildNode(left);
    }
    while (!isNullNode(right)) {
        r++;
        right = getLeftChildNode(right);
    }
    left = getLeftChildNode(root);
    right = getRightChildNode(root);
    if (l > r)
        return (1<<r) + count_complete_binary_tree_nodes(left);
    return (1<<l) + count_complete_binary_tree_nodes(right);
}

/*
 struct Interval {
 int start;   //区间左端点
 int end;   //区间右端点
 };
 */

struct comp {
    vector<Interval> *p;
    bool operator() (int a, int b) {
        return (*p)[a].start < (*p)[b].start;
    }
};

// intervals包含n个区间
// 结果存放到isIntersected中(已分配空间,不需要push_back)
// isIntersected[i]表示第i个区间是否与其它区间相交
void intersected(vector<Interval> &intervals, vector<bool> &isIntersected) {
    int n = intervals.size();
    if (n <= 1) return;
    vector<int> index(n);
    for (int i = 0; i < n; i++) {
        index[i] = i;
        isIntersected[i] = false;
    }
    comp compObj;
    compObj.p = &intervals;
    sort(index.begin(), index.end(), compObj);
    int e = intervals[index[0]].end;
    for (int i = 0; i < n - 1; i++) {
        if (intervals[index[i]].end >= intervals[index[i+1]].start) {
            isIntersected[index[i]] = true;
            isIntersected[index[i+1]] = true;
        }
        if (i > 0 && intervals[index[i]].start <= e)
            isIntersected[index[i]] = true;
        e = max(e, intervals[index[i]].end);
    }
    if (intervals[index[n - 1]].start <= e)
        isIntersected[index[n - 1]] = true;
}

bool DFS(int idx, int i, int j, vector<vector<char> > &grid, string &pattern, vector<vector<int> > &visited) {
    if (idx == pattern.length())  return true;
    int n = grid.size(), m = grid[0].size();
    visited[i][j] = true;
    if (i > 0 && !visited[i-1][j] && grid[i-1][j] == pattern[idx])
        if (DFS(idx+1, i-1, j, grid, pattern, visited))
            return true;
    if (i+1 < n && !visited[i+1][j] && grid[i+1][j] == pattern[idx])
        if (DFS(idx+1, i+1, j, grid, pattern, visited))
            return true;
    if (j > 0 && !visited[i][j-1] && grid[i][j-1] == pattern[idx])
        if (DFS(idx+1, i, j-1, grid, pattern, visited))
            return true;
    if (j+1 < m && !visited[i][j+1] && grid[i][j+1] == pattern[idx])
        if (DFS(idx+1, i, j+1, grid, pattern, visited))
            return true;
    visited[i][j] = false;
    return false;
}

bool exists(vector<vector<char> > &grid, string pattern) {
    if (pattern.length() == 0)  return true;
    if (grid.size() == 0)  return false;
    int n = grid.size(), m = grid[0].size();
    vector<vector<int> > visited(n, vector<int>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == pattern[0])
                if (DFS(1, i, j, grid, pattern, visited))
                    return true;
        }
    }
    
    return false;
}

static const int R = 26;
struct Node {
    bool flag;
    vector<Node*> next;
    Node() {
        flag = false;
        next = vector<Node*>(R);
    }
};

struct Trie {
    Node *root;
    
    Trie() {root = new Node();}
    
    Node* put(Node *root, string &s, int d) {
        if (root == NULL) root = new Node();
        if (d == s.length()) {
            root->flag = true;
            return root;
        }
        root->next[s[d] - 'A'] = put(root->next[s[d] - 'A'], s, d+1);
        return root;
    }
    
    void put(string s) {
        root = put(root, s, 0);
    }
};

bool DFS(int i, int j, vector<vector<char> > &grid, vector<vector<int> > &visited, Node *root) {
    if (root == NULL)  return false;
    Node *nxt = root->next[grid[i][j] - 'A'];
    if (nxt == NULL)  return false;
    if (nxt->flag == true)  return true;
    int n = grid.size(), m = grid[0].size();
    visited[i][j] = true;
    if (i > 0 && !visited[i-1][j] && DFS(i-1, j, grid, visited, nxt))
        return true;
    if (i+1 < n && !visited[i+1][j] && DFS(i+1, j, grid, visited, nxt))
        return true;
    if (j > 0 && !visited[i][j-1] && DFS(i, j-1, grid, visited, nxt))
        return true;
    if (j+1 < m && !visited[i][j+1] && DFS(i, j+1, grid, visited, nxt))
        return true;
    visited[i][j] = false;
    return false;
}

bool exists(vector<vector<char> > &grid, vector<string> &patterns) {
    if (grid.size() == 0) return patterns.size() == 0;
    int n = grid.size(), m = grid[0].size();
    vector<vector<int> > visited(n, vector<int>(m, 0));
    Trie trie;
    for (int i = 0; i < patterns.size(); i++)
        trie.put(patterns[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (DFS(i, j, grid, visited, trie.root)) {
                return true;
            }
        }
    }
    return false;
}

//将十进制数转换为excel数
string decToExcel(int decNum) {
    string s = "";
    while (decNum > 0) {
        int r = decNum % 26;
        if (r == 0) {
            s.insert(s.begin(), 'Z');
            decNum = decNum/26 - 1;
            continue;
        }
        s.insert(s.begin(), 'A' + r - 1);
        decNum /= 26;
    }
    return s;
}
//将excel数转换为十进制数
int excelToDec(string excelNum) {
    int r = 0;
    for (int i = 0; i < excelNum.length(); i++) {
        r = 26*r + excelNum[i] - 'A' + 1;
    }
    return r;
}

int calcByCols(vector<vector<int> > &mat) {
    int sum = 0, n = mat.size(), m = mat[0].size();
    for (int j1 = 0; j1 < m; j1++) {
        for (int j2 = j1; j2 < m; j2++) {
            int s = 0, prev = 0;
            for (int i = 0; i < n; i++) {
                int val = mat[i][j2];
                if (j1 > 0)
                    val -= mat[i][j1-1];
                val -= prev;
                s = max(s + val, val);
                sum = max(sum, s);
                prev += val;
            }
        }
    }
    return sum;
}

int calcByRows(vector<vector<int> > &mat) {
    int sum = 0, n = mat.size(), m = mat[0].size();
    for (int i1 = 0; i1 < m; i1++) {
        for (int i2 = i1; i2 < n; i2++) {
            int s = 0, prev = 0;
            for (int j = 0; j < m; j++) {
                int val = mat[i2][j];
                if (i1 > 0)
                    val -= mat[i1-1][j];
                val -= prev;
                s = max(s + val, val);
                sum = max(sum, s);
                prev += val;
            }
        }
    }
    return sum;
}


int maxRectSum(vector<vector<int> > &matrix) {
    if (matrix.size() == 0)  return 0;
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int> > sumMat(n, vector<int>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sumMat[i][j] = matrix[i][j];
            if (i > 0)
                sumMat[i][j] += sumMat[i-1][j];
            if (j > 0)
                sumMat[i][j] += sumMat[i][j-1];
            if (i > 0 && j > 0)
                sumMat[i][j] -= sumMat[i-1][j-1];
        }
    }
    
    if (n >= m)
        return calcByCols(sumMat);
    return calcByRows(sumMat);
}

int maxConsSum2(const vector<int> &arr) {
    int maxSum = 0, minSum = 0, sum = 0, minVal = 0, maxVal = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        maxVal = max(maxVal + arr[i], arr[i]);
        minVal = min(minVal + arr[i], arr[i]);
        maxSum = max(maxSum, maxVal);
        minSum = min(minSum, minVal);
    }
    maxSum = max(maxSum, sum - minSum);
    return maxSum;
}

//返回结点node1和node2的最近公共祖先
TreeNode *getLCA(TreeNode *node1, TreeNode *node2) {
    if (node1 == NULL)  return node2;
    if (node2 == NULL)  return node1;
    int n1 = 1, n2 = 1;
    TreeNode *p = node1->parent;
    while (p != NULL) {
        p = p->parent;
        n1++;
    }
    p = node2->parent;
    while (p != NULL) {
        p = p->parent;
        n2++;
    }
    int n = abs(n1 - n2);
    if (n1 > n2) {
        while (n > 0) {
            node1 = node1->parent;
            n--;
        }
    }
    else {
        while (n > 0) {
            node2 = node2->parent;
            n--;
        }
    }
    while (node1 != node2) {
        node1 = node1->parent;
        node2 = node2->parent;
    }
    return node1;
}

/**
 链表结点的定义(请不要在代码中定义该类型)
 struct ListNode {
 ListNode *next;
 ListNode *random;
 };
 */
// 返回复制的新链表头结点
ListNode* copyListWithRandomPtr(ListNode *head) {
    if (head == NULL)  return NULL;
    ListNode *cur = head, *nxt = NULL;
    
    while (cur != NULL) {
        nxt = cur->next;
        cur->next = new ListNode();
        cur->next->next = nxt;
        cur = nxt;
    }
    
    cur = head;
    while (cur != NULL) {
        nxt = cur->next->next;
        if (cur->random != NULL)
            cur->next->random = cur->random->next;
        cur = nxt;
    }
    
    ListNode *newHead = head->next;
    cur = head;
    while (cur != NULL) {
        nxt = cur->next->next;
        cur->next->next = NULL;
        if (nxt != NULL)
            cur->next->next = nxt->next;
        cur->next = nxt;
        cur = nxt;
    }
    
    return newHead;
}

int evaluate(const string &expr, int idx, int op1) {
    if (idx == expr.length())  return 0;
    int op2 = 0, i = idx;
    while (i < expr.length() && isdigit(expr.at(i))) {
        op2 = op2*10 + expr.at(i) - '0';
        i++;
    }
    op2 *= op1;
    if (i == expr.length())  return op2;
    if (expr.at(i) == '+')
        return op2 + evaluate(expr, i+1, 1);
    else if (expr.at(i) == '-')
        return op2 + evaluate(expr, i+1, -1);
    else
        return evaluate(expr, i+1, op2);
}

//返回表达式expr的值
int evaluate(const string& expr) {
    return evaluate(expr, 0, 1);
}

bool validate(const string &expr, int start, int end) {
    if (start >= end) return false;
    int i = start, j = end;
    char c = expr.at(i);
    if (c == ')')
        return false;
    if (c == '(') {
        int n = 1;
        for (i = start + 1; i < end; i++) {
            c = expr.at(i);
            if (c == '(')  n++;
            else if (c == ')') {
                if (n == 1) {
                    if (i+1 == end)
                        return validate(expr, start+1, i);
                    c = expr.at(i+1);
                    if (c == '+' || c == '-')
                        return validate(expr, start+1, i) && validate(expr, i+2, end);
                    else
                        return false;
                }
                else
                    n--;
            }
        }
        if (i == end)  return false;
    }
    for (i = start; i < end; i++) {
        c = expr.at(i);
        if (isdigit(c))
            continue;
        else if (c == '+' || c == '-')
            return validate(expr, start, i) && validate(expr, i+1, end);
        else
            return false;
    }
    i = start;
    c = expr.at(i);
    while (i < end && isdigit(c)) {
        if ((c - '0') == 0 && i == start)  {
            if (i+1 < end && isdigit(expr.at(i+1)))
                return false;
        }
        i++;
        if (i < end)  c = expr.at(i);
    }
    if (i == end) return true;
    return false;
}

bool validate(const string& expr) {
    return validate(expr, 0, expr.length());
}

/*积木的定义(请不要在代码中定义该结构)
 struct Box {
 int vol, weight;
 };*/

struct comp {
    bool operator() (Box a, Box b) {
        return a.weight < b.weight;
    }
} compObj;

int maxBoxes(vector<Box> &boxes) {
    if (boxes.size() == 0)  return 0;
    sort(boxes.begin(), boxes.end(), compObj);
    int maxLen = 1;
    vector<int> dp(boxes.size(), 1);
    
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (boxes[i].vol > boxes[j].vol && boxes[i].weight > boxes[j].weight)
                dp[i] = max(dp[i], dp[j] + 1);
            maxLen = max(maxLen, dp[i]);
        }
    }
    return maxLen;
}

struct Node {
    int visited, dist;
    string prev;
    Node() {
        visited = 0;
        dist = 1 << 15;
        prev = "";
    }
};

vector<string> transform(set<string> &dict, string from, string to) {
    if (from == to)  return vector<string>(1, from);
    map<string, Node> graph;
    queue<string> q;
    vector<string> path;
    Node node;
    for (set<string>::iterator it = dict.begin(); it != dict.end(); ++it)
        graph[*it] = node;
    q.push(from);
    graph[from].dist = 0;
    while (!q.empty()) {
        string s = q.front(), adj = s;
        q.pop();
        if (graph[s].visited) continue;
        graph[s].visited = 1;
        for (int i = 0; i < s.length(); i++) {
            for (int j = 0; j < 26; j++) {
                adj[i] = 'A' + j;
                if (adj[i] != s[i] && dict.find(adj) != dict.end()) {
                    if (!graph[adj].visited) {
                        q.push(adj);
                        if (graph[adj].dist > graph[s].dist + 1) {
                            graph[adj].dist = graph[s].dist + 1;
                            graph[adj].prev = s;
                        }
                    }
                }
            }
            adj[i] = s[i];
        }
    }
    if (graph[to].prev == "") return path;
    stack<string> stk;
    stk.push(to);
    while (true) {
        to = graph[to].prev;
        if (to.length() == 0)  break;
        stk.push(to);
    }
    while (!stk.empty()) {
        path.push_back(stk.top());
        stk.pop();
    }
    return path;
}

//返回a*b的结果
string multiply(const string& a, const string& b) {
    bool aNeg = (a[0] == '-') ? true : false, bNeg = (b[0] == '-') ? true : false;
    int n = a.length(), m = b.length(), aEnd = aNeg ? 1 : 0, bEnd = bNeg ? 1 : 0;
    if (a[aEnd] == '0' || b[bEnd] == '0')  return "0";
    string s(n+m, '0');
    
    for (int j = m - 1; j >= bEnd; j--) {
        int carry = 0;
        for (int i = n - 1; i >= aEnd; i--) {
            carry += (b[j] - '0')*(a[i] - '0') + s[i + j + 1] - '0';
            s[i + j + 1] = '0' + carry % 10;
            carry /= 10;
        }
        s[aEnd + j] += carry;
    }
    
    int i = 0;
    while (i < s.length() && s[i] == '0')
        i++;
    
    if (i == s.length())  return "0";
    if (aNeg ^ bNeg)
        s[--i] = '-';
    return s.substr(i);
}

//返回a+b的结果
string add(const string& a, const string& b) {
    int n = a.length(), m = b.length(), carry = 0;
    string s(max(m, n) + 1, '0');
    
    for (int i = n - 1, j = m - 1, k = s.length() - 1; i >= 0 || j >= 0 || carry != 0; i--, j--, k--) {
        if (i >= 0)
            carry += a[i] - '0';
        if (j >= 0)
            carry += b[j] - '0';
        s[k] = '0' + carry % 10;
        carry /= 10;
    }
    
    int i = 0;
    while (i < s.length() && s[i] == '0')
        i++;
    if (i == s.length())  return "0";
    return s.substr(i);
}

#include <stack>

/*树结点的定义(请不要在代码中定义该结构)
 struct TreeNode {
 TreeNode *left, *right;
 bool isLeftThread, isRightThread;
 }*/
void convertToThreadedTree(TreeNode *root) {
    TreeNode *cur = root, *prev = NULL;
    stack<TreeNode*> stk;
    
    while (cur != NULL || !stk.empty()) {
        if (cur != NULL) {
            stk.push(cur);
            cur = cur->left;
        }
        else {
            cur = stk.top();
            stk.pop();
            if (prev == NULL)
                prev = cur;
            else {
                if (cur->left == NULL) {
                    cur->isLeftThread = true;
                    cur->left = prev;
                }
                if (prev->right == NULL) {
                    prev->isRightThread = true;
                    prev->right = cur;
                }
            }
            prev = cur;
            cur = cur->right;
        }
    }
}

int count(vector<int>& preorder, int rs, int re, vector<int>& postorder, int os, int oe) {
    int n = re - rs + 1, c = 0;
    if (n <= 0) return 1;
    if (preorder[rs] != postorder[oe]) return 0;
    set<int> dict;
    for (int i = rs + 1; i <= re; i++)
        dict.insert(preorder[i]);
    
    for (int i = os; i < oe; i++)
        if (dict.find(postorder[i]) == dict.end())
            return 0;
    
    for (int i = rs; i <= re; i++) {
        c += count(preorder, rs + 1, i, postorder, os, os + i - rs - 1) * count(preorder, i + 1, re, postorder, os + i - rs, oe - 1);
    }
    
    return c;
}

int countValidTrees(vector<int>& preorder, vector<int>& postorder) {
    int n = preorder.size();
    return count(preorder, 0, n - 1, postorder, 0, n - 1);
}

bool next_permutation(vector<int> &arr) {
    vector<int>::iterator first = arr.begin(), last = arr.end(), i = first;
    if (first == last)
        return false;
    ++i;
    if (i == last)
        return false;
    i = last;
    --i;
    while (true) {
        vector<int>::iterator ii = i;
        --i;
        if (*i < *ii) {
            vector<int>::iterator j = last;
            while (!(*i < *--j)) {
            }
            std::iter_swap(i, j);
            std::reverse(ii, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

bool next_permutation(vector<int> &arr) {
    vector<int>::iterator first = arr.begin(), last = arr.end(), i = first;
    if (first == last)
        return false;
    ++i;
    if (i == last)
        return false;
    i = last;
    --i;
    while (true) {
        vector<int>::iterator ii = i;
        --i;
        if (*i < *ii) {
            vector<int>::iterator j = last;
            while (!(*i < *--j)) {
            }
            std::iter_swap(i, j);
            std::reverse(ii, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

/*
 树结点的定义(请不要在代码中定义该类型)
 struct TreeNode {
 int val;
 vector<TreeNode*> children;  //该结点的儿子结点
 };
 */
pair<int, int> pathSum(TreeNode *root) {
    if (root == NULL) return pair<int, int>(0, 0);
    int first = max(0, root->val), second = root->val, n = root->children.size();
    vector<pair<int, int> > p(n);
    for (int i = 0; i < n; i++) {
        p[i] = pathSum(root->children[i]);
    }
    for (int i = 0; i < n; i++) {
        first = max(first, p[i].first);
        second = max(second, p[i].second + root->val);
        for (int j = i + 1; j < n; j++) {
            int sum = root->val + p[i].second + p[j].second;
            first = max(first, sum);
        }
    }
    first = max(first, second);
    return pair<int, int>(first, second);
}

int maxTreePathSum(TreeNode *root) {
    pair<int, int> p = pathSum(root);
    return max(p.first, p.second);
}

int maxBombValue(vector<int> &r, vector<int> &v) {
    int n = r.size(), maxVal = 0;
    
    for (int i = 0; i < n; i++) {
        int val = v[i];
        vector<int> dp(n, val), right(n, r[i]);
        for (int j = 1; j < n; j++) {
            int pos = (i + j) % n;
            for (int k = 0; k < j; k++) {
                int prev = (i + k) % n;
                bool front = false, back = false;
                if (j > right[prev] && j - right[prev] > r[pos]) {
                    front = true;
                }
                if (j + r[pos] < n && n - j - r[pos] > r[i]) {
                    back = true;
                }
                if (front && back && dp[pos] < dp[prev] + v[pos]) {
                    dp[pos] = dp[prev] + v[pos];
                    right[pos] = j + r[pos];
                }
            }
            val = max(val, dp[pos]);
        }
        maxVal = max(maxVal, val);
    }
    return maxVal;
}

void mergeSortedArray(int arr1[], int arr2[], int n, int m) {
    int i = n - 1, j = m - 1, k = n + m - 1;
    while (i >= 0 && j >= 0) {
        if (arr2[j] >= arr1[i]) {
            arr1[k] = arr2[j];
            j--;
        }
        else {
            arr1[k] = arr1[i];
            i--;
        }
        k--;
    }
    
    while (j >= 0) {
        arr1[k] = arr2[j];
        j--;
        k--;
    }
}

typedef tuple<int, int, int> ABC; //存放a,b,c三元组
//返回所有满足条件的(a,b,c)三元组
vector<ABC> threeSumZero(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    vector<ABC> v;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            break;
        if (arr[i] == 0) {
            if (i + 2 < n && arr[i + 2] == 0)
                v.push_back(ABC(0, 0, 0));
            break;
        }
        int j = i + 1, k = n - 1;
        while (j < n && arr[j] == arr[i])
            j++;
        if (j - i >= 2) {
            for (; k >= j; k--) {
                if (arr[k] == -2*arr[i]) {
                    v.push_back(ABC(arr[i], arr[i], arr[k]));
                    break;
                }
            }
            i += j - i - 2;
            continue;
        }
        j = i + 1;
        k = n - 1;
        while (j < k) {
            if (arr[i] + arr[j] + arr[k] == 0) {
                v.push_back(ABC(arr[i], arr[j], arr[k]));
                j++;
                k--;
                while (j < k && arr[j - 1] == arr[j])
                    j++;
                while (j < k && arr[k] == arr[k + 1])
                    k--;
            }
            else if (arr[i] + arr[j] + arr[k] < 0) {
                j++;
                while (j < k && arr[j - 1] == arr[j])
                    j++;
            }
            else {
                k--;
                while (j < k && arr[k] == arr[k + 1])
                    k--;
            }
        }
    }
    return v;
}

/*链表结点的定义(请不要在代码中定义该类型)
 struct ListNode {
 int val;
 ListNode *next;
 };
 */

class comp {
public:
    bool operator()(ListNode *a, ListNode *b) {
        return a->val >= b->val;
    }
};

//lists包含k个链表的头结点,返回合并后链表头结点
ListNode* merge(vector<ListNode*> &lists) {
    ListNode *head = NULL, *tail = NULL, *cur = NULL;
    priority_queue<ListNode*, vector<ListNode*>, comp> pq;
    
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != NULL)
            pq.push(lists[i]);
    }
    
    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();
        if (head == NULL) {
            head = cur;
            tail = cur;
        }
        else {
            tail->next = cur;
            tail = cur;
        }
        cur = cur->next;
        if (cur != NULL)
            pq.push(cur);
    }
    
    return head;
}

/*
 树结点的定义(请不要在代码中定义该结构)
 struct TreeNode {
 TreeNode *left;
 TreeNode *right;
 }*/
int check(TreeNode *root) {
    if (root == NULL)
        return 0;
    int l = check(root->left), r = check(root->right);
    if (l == -1 || r == -1 || abs(l - r) > 1)
        return -1;
    return 1 + max(l, r);
}
bool isBalancedTree(TreeNode *root) {
    return check(root) != -1;
}

vector<string> generate(int n) {
    if (n == 0)
        return vector<string>(1, "");
    if (n == 1)
        return vector<string>(1, "()");
    
    vector<string> ret;
    for (int i = 0; i < n; i++) {
        vector<string> l = generate(i), r;
        for (int j = 0; j < l.size(); j++)
            r.push_back("(" + l[j] + ")");
        l = generate(n - 1 - i);
        for (int j = 0; j < l.size(); j++)
            for (int k = 0; k < r.size(); k++)
                ret.push_back(l[j] + r[k]);
    }
    return ret;
}

/*
 树结点的定义(请不要在代码中定义该结构)
 struct TreeNode {
 int val;
 TreeNode *left, *right;
 }*/

#include <climits>

bool check(TreeNode *root, int minVal, int maxVal) {
    if (root == NULL)
        return true;
    if (root->val <= minVal || root->val >= maxVal)
        return false;
    return check(root->left, minVal, root->val + 1) && check(root->right, root->val, maxVal);
}
bool isBST(TreeNode *root) {
    return check(root, INT_MIN, INT_MAX);
}

int totalPath(vector<vector<bool> > &blocked) {
    if (blocked.size() == 0 || blocked[0].size() == 0)
        return 0;
    int n = blocked.size(), m = blocked[0].size();
    vector<vector<int> > dp(n, vector<int>(m, 0));
    if (!blocked[0][0]) dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blocked[i][j])
                dp[i][j] = 0;
            else {
                if (i > 0)
                    dp[i][j] += dp[i - 1][j];
                if (j > 0)
                    dp[i][j] += dp[i][j - 1];
            }
        }
    }
    return dp[n - 1][m - 1];
}

pair<int, int> binarySearch(vector<vector<int> > &matrix, int row, int lo, int hi, int target) {
    while (hi - lo > 1) {
        int mid = lo + (hi - lo)/2;
        if (matrix[row][mid] == target)
            return pair<int, int>(-1, -1);
        else if (matrix[row][mid] < target)
            lo = mid;
        else
            hi = mid;
    }
    return pair<int, int>(lo, hi);
}

bool exists(vector<vector<int> > &matrix, int target) {
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;
    int n = matrix.size(), m = matrix[0].size();
    if (target < matrix[0][0] || target > matrix[n - 1][m - 1])
        return false;
    int start = binarySearch(matrix, n - 1, 0, m - 1, target).first;
    int end = binarySearch(matrix, 0, 0, m - 1, target).second;
    
    if (start == -1 || end == -1)
        return true;
    
    for (int i = start; i <= end; i++) {
        int lo = 0, hi = n - 1;
        while (hi - lo > 1) {
            int mid = lo + (hi - lo)/2;
            if (matrix[mid][i] == target)
                return true;
            else if (matrix[mid][i] < target)
                lo = mid;
            else
                hi = mid;
        }
        if (matrix[lo][i] == target || matrix[hi][i] == target)
            return true;
    }
    
    return false;
}

int search(vector<int> &arr, int target) {
    
    int lo = 0, hi = arr.size() - 1;
    
    while (hi >= lo) {
        int mid = lo + (hi - lo)/2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target) {
            if (arr[mid] > arr[hi] || arr[hi] >= target)
                lo = mid + 1;
            else if (arr[mid] < arr[hi])
                hi = mid - 1;
            else
                hi--;
        }
        else {
            if (arr[mid] < arr[lo] || arr[lo] <= target)
                hi = mid - 1;
            else if (arr[mid] > arr[lo])
                lo = mid + 1;
            else
                lo++;
        }
    }
    return -1;
}

#include <climits>

// k starts from 0
int findKthElement(vector<int> &arr1, int s1, int e1, vector<int> &arr2, int s2, int e2, int k) {
    // array lengths
    int m = e1 - s1, n = e2 - s2;
    if (m < 0 || n < 0 || m + n == 0 || m + n <= k)
        return INT_MIN;
    if (m == 0) return arr2[s2 + k];
    if (n == 0) return arr1[s1 + k];
    if (k == 0) return min(arr1[s1], arr2[s2]);
    
    int k1 = (int)((double)k*m/(m + n)), k2 = k - k1;
    int v_k1 = arr1[s1 + k1];
    int v_k1_1 = (k1 - 1 >= 0) ? arr1[s1 + k1 - 1] : INT_MIN;
    int v_k2 = (k2 < n) ? arr2[s2 + k2] : INT_MAX;
    int v_k2_1 = (k2 - 1 >= 0) ? arr2[s2 + k2 - 1] : INT_MIN;
    
    if (v_k1 <= v_k2 && v_k1 >= v_k2_1)
        return v_k1;
    if (v_k2 <= v_k1 && v_k2 >= v_k1_1)
        return v_k2;
    
    if (v_k1 > v_k2)
        // arr1: first half; arr2: second half
        return findKthElement(arr1, s1, s1 + k1, arr2, s2 + k2 + 1, e2, k - (k2 + 1));
    else
        // arr1: second half; arr2: first half
        return findKthElement(arr1, s1 + k1 + 1, e1, arr2, s2, s2 + k2, k - (k1 + 1));
}

int median(vector<int> &arr1, vector<int> &arr2) {
    int m = arr1.size(), n = arr2.size();
    int mid = findKthElement(arr1, 0, m, arr2, 0, n, (m + n)/2);
    
    if ((m + n) % 2 == 1)
        return mid;
    
    mid += findKthElement(arr1, 0, m, arr2, 0, n, (m + n)/2 - 1);
    return (double)mid / 2.0;
}

vector<int> id;

void init(int N) {
    id.resize(N + 1, 0);
    for (int i = 0; i < N; i++) {
        id[i] = i;
    }
    id[N] = -1;
}

int find(int i) {
    while (id[i] != i && id[i] != -1) {
        id[i] = id[id[i]];
        if (id[i] == -1)
            break;
        i = id[i];
    }
    return id[i];
}

void unionSets(int p, int q) {
    int i = find(p), j = find(q);
    if (i != -1)
        id[i] = j;
}

void removeNum(int x) {
    unionSets(x, x + 1);
}

int query(int x) {
    return find(x);
}

/*点的定义
 struct Point {double x; double y}
 */

#include <climits>

const double eps = 1e-7;

bool isEqual(double p, double q) {
    return abs(p - q) < eps;
}

double slope(Point p, Point q) {
    if (isEqual(p.x, q.x) && isEqual(p.y, q.y))
        return std::numeric_limits<double>::min();
    if (isEqual(p.x, q.x))
        return std::numeric_limits<double>::max();
    if (isEqual(p.y, q.y))
        return 0.0;
    return (p.y - q.y) / (p.x - q.x);
}

int maxPointsOnLine(vector<Point> &points) {
    if (points.size() <= 2) return points.size();
    int n = points.size(), maxCount = 2;
    for (int i = 0; i < n; i++) {
        vector<double> v;
        for (int j = 0; j < n; j++) {
            if (i != j)
                v.push_back(slope(points[i], points[j]));
        }
        sort(v.begin(), v.end());
        int prev = 0;
        for (int j = 1; j < v.size(); j++) {
            if (isEqual(v[j - 1], v[j]))
                maxCount = max(maxCount, j - prev + 2);
            else
                prev = j;
        }
    }
    return maxCount;
}

/*点的定义
 struct Point {int x,y;}
 */
#define DOUBLE_MAX std::numeric_limits<double>::max()

double dist(Point p1, Point p2) {
    double x = p1.x - p2.x, y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

double minDist(vector<Point> &points) {
    int n = points.size();
    double minL = DOUBLE_MAX;
    vector<vector<double> > d(n, vector<double>(n, 0.0)), dp(n, vector<double>(n, DOUBLE_MAX));
    vector<vector<bool> > flag(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = dist(points[i], points[j]);
        }
    }
    if (n == 2) return 2*d[0][1];
    dp[0][0] = 0.0;
    flag[0][0] = true;
    for (int k = 1; k < n-1; k++) {
        for (int i = 0; i < k; i++) {
            if (flag[i][k - 1]) {
                dp[i][k] = min(dp[i][k], dp[i][k - 1] + d[k - 1][k]);
                flag[i][k] = true;
                dp[k][k - 1] = min(dp[k][k - 1], dp[i][k - 1] + d[i][k]);
                flag[k][k - 1] = true;
            }
        }
        for (int j = 0; j < k; j++) {
            if (flag[k - 1][j]) {
                dp[k][j] = min(dp[k][j], dp[k - 1][j] + d[k - 1][k]);
                flag[k][j] = true;
                dp[k - 1][k] = min(dp[k - 1][k], dp[k - 1][j] + d[k][j]);
                flag[k - 1][k] = true;
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (flag[i][n - 2])
            minL = min(minL, dp[i][n - 2] + d[n - 2][n - 1] + d[i][n - 1]);
    }
    for (int j = 0; j < n - 1; j++) {
        if (flag[n - 2][j])
            minL = min(minL, dp[n - 2][j] + d[n - 2][n - 1] + d[n - 1][j]);
    }
    return minL;
}

// Read Phone Number
int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    string numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string seqs[] = {"double", "triple", "quadruple", "quintuple", "sextuple", "septuple", "octuple", "nonuple", "decuple"};
    for (int index = 1; index <= T; ++index) {
        string N, F;
        cin >> N >> F;
        cout<<"Case #"<<index<<":";
        int i = 0, n = F.length(), idx = 0;
        while (i < n) {
            int c = F[i] - '0';
            i++;
            while (i < n && F[i] != '-') {
                c = c*10 + F[i] - '0';
                i++;
            }
            if (F[i] == '-')
                i++;
            int j = idx;
            while (j - idx + 1 <= c) {
                int successive = 1;
                while (j - idx + 1 < c && N[j] == N[j + 1]) {
                    successive++;
                    j++;
                }
                if (successive == 1)
                    cout<< " " << numbers[N[j] - '0'];
                else if (successive > 10) {
                    for (int k = 0; k < successive; k++)
                        cout << " " << numbers[N[j] - '0'];
                }
                else
                    cout<< " " << seqs[successive - 2] << " " << numbers[N[j] - '0'];
                j++;
            }
            idx = j;
        }
        cout<<endl;
        //cout<<"Case #"<<index<<": "<<N<<endl;
    }
    
    return 0;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        ull id = 0, n = 0, p = 0, q = 0;
        cin >> id;
        if (id == 1) {
            cin >> n;
            p = 1, q = 1;
            vector<int> digits;
            while (n != 0) {
                if (n & 1l)
                    digits.push_back(1);
                else
                    digits.push_back(0);
                n >>= 1;
            }
            reverse(digits.begin(), digits.end());
            for (int i = 1; i < digits.size(); i++) {
                ull p_child = (digits[i] == 0) ? p : p + q;
                ull q_child = (digits[i] == 0) ? p + q : q;
                p = p_child;
                q = q_child;
            }
            cout<<"Case #"<<index<<": "<<p<<" "<<q<<endl;
        }
        else if (id == 2) {
            cin >> p >> q;
            vector<int> digits;
            n = 0;
            while (p != q) {
                ull p_parent = (p < q) ? p : p - q;
                ull q_parent = (p < q) ? q - p : q;
                int d = (p < q) ? 0 : 1;
                digits.push_back(d);
                p = p_parent;
                q = q_parent;
            }
            digits.push_back(1);
            for (int i = 0; i < digits.size(); i++) {
                if (digits[i] == 1)
                    n |= 1l << i;
            }
            cout<<"Case #"<<index<<": "<<n<<endl;
        }
        //cout<<"Case #"<<index<<": "<<endl;
    }
    
    return 0;
}

// Cross the maze
const char dir[] = {'N', 'E', 'S', 'W'};
const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};
int N;

bool check(int x, int y, int d, vector<vector<int> > &grid) {
    d = (d + 3) % 4;
    x += di[d], y += dj[d];
    if (x < 0 || x >= N || y < 0 || y >= N)
        return true;
    return grid[x][y] == 1;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> N;
        int sx, sy, ex, ey, d;
        vector<vector<int> > grid(N, vector<int>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char c;
                cin >> c;
                if (c == '#')
                    grid[i][j] = 1;
            }
        }
        cin >> sx >> sy >> ex >> ey;
        sx--, sy--, ex--, ey--;
        if (sx == 0 && sy == 0)
            d = 2;
        else if (sx == 0 && sy == N - 1)
            d = 1;
        else if (sx == N - 1 && sy == 0)
            d = 3;
        else
            d = 0;
        vector<int> ret;
        for (int i = 0; i < 10000; i++) {
            if (!check(sx, sy, d, grid)) {
                d = (d + 3) % 4;
                sx += di[d];
                sy += dj[d];
                ret.push_back(d);
            }
            else {
                for (int j = 0; j < 4; j++) {
                    if (!check(sx, sy, d, grid)) {
                        break;
                    }
                    d = (d + 1) % 4;
                }
                if (!check(sx, sy, d, grid)) {
                    d = (d + 3) % 4;
                    sx += di[d];
                    sy += dj[d];
                    ret.push_back(d);
                }
            }
                        
            if (sx == ex && sy == ey) {
                cout<<"Case #"<<index<<": "<<ret.size()<<endl;
                for (int i = 0; i < ret.size(); i++)
                    cout<<dir[ret[i]];
                cout<<endl;
                break;
            }
        }
        if (!(sx == ex && sy == ey))
            cout<<"Case #"<<index<<": Edison ran out of energy."<<endl;
        //cout<<"Case #"<<index<<": "<<endl;
    }
    
    return 0;
}

// Spaceship Defence
#define ll long long
#define ull size_t
#define INF numeric_limits<long>::max()

struct Edge {
    int u, v;
    ll w;
};

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int N, M, V;
        vector<string> colors;
        map<int, vector<Edge> > adj;
        map<string, int> vertices;
        map<string, set<int> > colorToRoom;
        cin >> N;
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            colors.push_back(s);
            colorToRoom[s].insert(i);
        }
        V = 0;
        cin >> M;
        for (int i = 0; i < M; i++) {
            int a, b;
            Edge e;
            cin >> a >> b >> e.w;
            a--, b--;
            string ca = colors[a], cb = colors[b];
            if (vertices.find(ca) == vertices.end()) {
                vertices[ca] = V++;
                e.u = V - 1;
            }
            else
                e.u = vertices[ca];
            if (vertices.find(cb) == vertices.end()) {
                vertices[cb] = V++;
                e.v = V - 1;
            }
            else
                e.v = vertices[cb];
            if (e.u == e.v)
                continue;
            adj[e.u].push_back(e);
        }
        
        vector<vector<ll> > distTo(V, vector<ll>(V, INF));
        for (int i = 0; i < V; i++) {
            distTo[i][i] = 0;
            vector<int> onQueue(V, 0);
            queue<int> q;
            q.push(i);
            onQueue[i] = 1;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                onQueue[u] = 0;
                for (int j = 0; j < adj[u].size(); j++) {
                    Edge e = adj[u][j];
                    if (distTo[i][e.v] > distTo[i][u] + e.w) {
                        distTo[i][e.v] = distTo[i][u] + e.w;
                        if (!onQueue[e.v]) {
                            q.push(e.v);
                            onQueue[e.v] = 1;
                        }
                    }
                }
            }
        }
        
        cout<<"Case #"<<index<<":"<<endl;
        int S;
        cin >> S;
        for (int i = 0; i < S; i++) {
            int p, q;
            cin >> p >> q;
            p--, q--;
            string cp = colors[p], cq = colors[q];
            if (cp == cq) {
                cout<< 0 <<endl;
                continue;
            }
            if (vertices.find(cp) == vertices.end() || vertices.find(cq) == vertices.end()) {
                cout << -1 << endl;
                continue;
            }
            int u = vertices[cp], v = vertices[cq];
            if (distTo[u][v] == INF) {
                cout << -1 << endl;
                continue;
            }
            cout << distTo[u][v] <<endl;
        }
        
        //cout<<"Case #"<<index<<": "<<endl;
    }
    
    return 0;
}

// Meet and party
#define ll long long
#define ull size_t
#define INF numeric_limits<long>::max()

struct person {
    ll x, y, lxsum, rxsum, dysum, uysum, d;
    person() {x = 0; y = 0; rxsum = 0; dysum = 0; lxsum = 0; uysum = 0; d = 0;}
};

bool compX(person pi, person pj) {
    return pi.x < pj.x;
}

bool compY(person pi, person pj) {
    return pi.y < pj.y;
}

bool compD(person pi, person pj) {
    if (pi.d == pj.d) {
        if (pi.x == pj.x)
            return pi.y < pj.y;
        return pi.x < pj.x;
    }
    return pi.d < pj.d;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int B;
        vector<person> vp;
        cin >> B;
        for (int i = 0; i < B; i++) {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for (ll x = x1; x <= x2; x++) {
                for (ll y = y1; y <= y2; y++) {
                    person p;
                    p.x = x, p.y = y;
                    vp.push_back(p);
                }
            }
        }
        sort(vp.begin(), vp.end(), compX);
        ll n = vp.size(), rightSum = 0, upSum = 0;
        vector<ll> diffX(vp.size(), 0), diffY(vp.size(), 0);
        for (int i = 1; i < n; i++) {
            diffX[i] = vp[i].x - vp[i - 1].x;
            rightSum += vp[i].x - vp[0].x;
        }
        vp[0].rxsum = rightSum;
        vp[0].d += rightSum;
        for (int i = 1; i < n; i++) {
            vp[i].lxsum = vp[i - 1].lxsum + diffX[i]*i;
            vp[i].rxsum = vp[i - 1].rxsum - diffX[i]*(n - i);
            vp[i].d += vp[i].lxsum + vp[i].rxsum;
        }
        sort(vp.begin(), vp.end(), compY);
        for (int i = 1; i < n; i++) {
            diffY[i] = vp[i].y - vp[i - 1].y;
            upSum += vp[i].y - vp[0].y;
        }
        vp[0].uysum = upSum;
        vp[0].d += upSum;
        for (int i = 1; i < n; i++) {
            vp[i].dysum = vp[i - 1].dysum + diffY[i]*i;
            vp[i].uysum = vp[i - 1].uysum - diffY[i]*(n - i);
            vp[i].d += vp[i].dysum + vp[i].uysum;
        }
        sort(vp.begin(), vp.end(), compD);
        cout<<"Case #"<<index<<": "<< vp[0].x << " " << vp[0].y << " " << vp[0].d <<endl;
    }
    
    return 0;
}

// Hex
#define ll long long
#define ull size_t
#define INF numeric_limits<long>::max()

int N;
const int dx[] = {1, -1, 0, 0, -1, 1};
const int dy[] = {0, 0, 1, -1, 1, -1};

bool isOnBoard(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void clearUp(vector<vector<int> > &isVisited) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            isVisited[i][j] = 0;
        }
    }
}

bool dfs(int x, int y, vector<vector<char> > &board, vector<vector<int> > &isVisited, char color) {
    isVisited[x][y] = true;
    if (color == 'R' && x == N - 1) {
        clearUp(isVisited);
        return true;
    }
    if (color == 'B' && y == N - 1) {
        clearUp(isVisited);
        return true;
    }
    for (int k = 0; k < 6; k++) {
        int xk = x + dx[k], yk = y + dy[k];
        if (isOnBoard(xk, yk) && !isVisited[xk][yk] && board[xk][yk] == color)
            if (dfs(xk, yk, board, isVisited, color))
                return true;
    }
    return false;
}
bool check(vector<vector<char> > &board, vector<vector<int> > &isVisited, char color) {
    for (int j = 0; j < N; j++) {
        if (color == 'R' && board[0][j] == 'R') {
            bool flag = dfs(0, j, board, isVisited, color);
            clearUp(isVisited);
            if (flag)
                return true;
        }
        if (color == 'B' && board[j][0] == 'B') {
            bool flag = dfs(j, 0, board, isVisited, color);
            clearUp(isVisited);
            if (flag)
                return true;
        }
    }
    return false;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> N;
        vector<vector<char> > board(N, vector<char>(N, '.'));
        vector<vector<int> > isVisited(N, vector<int>(N, 0));
        int R_count = 0, B_count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'R')
                    R_count++;
                else if (board[i][j] == 'B')
                    B_count++;
            }
        }
        if (abs(R_count - B_count) > 1) {
            cout<<"Case #"<<index<<": Impossible"<<endl;
            continue;
        }
        bool isRedWin = false, isBlueWin = false, isRedValid = false, isBlueValid = false;
        isRedWin = check(board, isVisited, 'R');
        isBlueWin = check(board, isVisited, 'B');
        if (!isRedWin && !isBlueWin) {
            vector<pair<int, int> > vRed, vBlue;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == '.') {
                        board[i][j] = 'R';
                        if (check(board, isVisited, 'R'))
                            vRed.push_back(make_pair(i, j));
                        board[i][j] = 'B';
                        if (check(board, isVisited, 'B'))
                            vBlue.push_back(make_pair(i, j));
                        board[i][j] = '.';
                    }
                }
            }
            bool isRedPossible = false, isBluePossible = false;
            int left = N*N - R_count - B_count, R_left = left/2, B_left = left/2;
            if (R_count > B_count)
                B_left++;
            else if (R_count < B_count)
                R_left++;
            
            if (R_left > left - vRed.size())
                isRedPossible = true;
            if (B_left > left - vBlue.size())
                isBluePossible = true;
            if ((isRedPossible && isBluePossible) || (!isRedPossible && !isBluePossible) )
                cout<<"Case #"<<index<<": Nobody wins"<<endl;
            else if (isRedPossible)
                cout<<"Case #"<<index<<": Red wins"<<endl;
            else
                cout<<"Case #"<<index<<": Blue wins"<<endl;
            continue;
        }
        if (isRedWin && isBlueWin) {
            cout<<"Case #"<<index<<": Impossible"<<endl;
            continue;
        }
        if (isRedWin) {
            if (R_count < B_count) {
                cout<<"Case #"<<index<<": Impossible"<<endl;
                continue;
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == 'R') {
                        board[i][j] = '.';
                        if (!check(board, isVisited, 'R')) {
                            isRedValid = true;
                            break;
                        }
                        board[i][j] = 'R';
                    }
                }
                if (isRedValid)
                    break;
            }
            if (isRedValid)
                cout<<"Case #"<<index<<": Red wins"<<endl;
            else
                cout<<"Case #"<<index<<": Impossible"<<endl;
            continue;
        }
        if (isBlueWin) {
            if (B_count < R_count) {
                cout<<"Case #"<<index<<": Impossible"<<endl;
                continue;
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == 'B') {
                        board[i][j] = '.';
                        if (!check(board, isVisited, 'B')) {
                            isBlueValid = true;
                            break;
                        }
                        board[i][j] = 'B';
                    }
                }
                if (isBlueValid)
                    break;
            }
            if (isBlueValid)
                cout<<"Case #"<<index<<": Blue wins"<<endl;
            else
                cout<<"Case #"<<index<<": Impossible"<<endl;
            continue;
        }
        //cout<<"Case #"<<index<<": "<<endl;
    }
    
    return 0;
}

int N;
const int dx[] = {1, -1, 0, 0, -1, 1};
const int dy[] = {0, 0, 1, -1, 1, -1};

bool isOnBoard(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void clearUp(vector<vector<int> > &isVisited) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            isVisited[i][j] = 0;
        }
    }
}

bool dfs(int x, int y, vector<vector<char> > &board, vector<vector<int> > &isVisited, char color) {
    isVisited[x][y] = true;
    if (color == 'R' && x == N - 1) {
        clearUp(isVisited);
        return true;
    }
    if (color == 'B' && y == N - 1) {
        clearUp(isVisited);
        return true;
    }
    for (int k = 0; k < 6; k++) {
        int xk = x + dx[k], yk = y + dy[k];
        if (isOnBoard(xk, yk) && !isVisited[xk][yk] && board[xk][yk] == color)
            if (dfs(xk, yk, board, isVisited, color))
                return true;
    }
    return false;
}
bool check(vector<vector<char> > &board, vector<vector<int> > &isVisited, char color) {
    for (int j = 0; j < N; j++) {
        if (color == 'R' && board[0][j] == 'R') {
            bool flag = dfs(0, j, board, isVisited, color);
            clearUp(isVisited);
            if (flag)
                return true;
        }
        if (color == 'B' && board[j][0] == 'B') {
            bool flag = dfs(j, 0, board, isVisited, color);
            clearUp(isVisited);
            if (flag)
                return true;
        }
    }
    return false;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        cin >> N;
        vector<vector<char> > board(N, vector<char>(N, '.'));
        vector<vector<int> > isVisited(N, vector<int>(N, 0));
        int R_count = 0, B_count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'R')
                    R_count++;
                else if (board[i][j] == 'B')
                    B_count++;
            }
        }
        if (abs(R_count - B_count) > 1) {
            cout<<"Case #"<<index<<": Impossible"<<endl;
            continue;
        }
        if (check(board, isVisited, 'R')) {
            bool isCritical = false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == 'R') {
                        board[i][j] = '.';
                        if (!check(board, isVisited, 'R')) {
                            isCritical = true;
                            break;
                        }
                        board[i][j] = 'R';
                    }
                }
            }
            if (R_count < B_count || !isCritical) {
                cout<<"Case #"<<index<<": Impossible"<<endl;
                continue;
            }
            else
                cout<<"Case #"<<index<<": Red wins"<<endl;
            continue;
        }
        if (check(board, isVisited, 'B')) {
            bool isCritical = false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (board[i][j] == 'B') {
                        board[i][j] = '.';
                        if (!check(board, isVisited, 'B')) {
                            isCritical = true;
                            break;
                        }
                        board[i][j] = 'B';
                    }
                }
            }
            if (B_count < R_count || !isCritical) {
                cout<<"Case #"<<index<<": Impossible"<<endl;
                continue;
            }
            else
                cout<<"Case #"<<index<<": Blue wins"<<endl;
            continue;
        }
        cout<<"Case #"<<index<<": Nobody wins"<<endl;
        //cout<<"Case #"<<index<<": "<<endl;
    }
    
    return 0;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
int N, M;

struct Cell {
    int x, y, t = INT_MAX, v = INT_MIN;
};

struct comp {
    bool operator() (Cell ci, Cell cj) {
        return ci.t > cj.t;
    }
};

bool onBoard(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    
    int T;
    cin >> T;
    for (int index = 1; index <= T; ++index) {
        int enx, eny, exx, exy;
        cin >> N >> M >> enx >> eny >> exx >> exy;
        vector<vector<Cell> > dp(N, vector<Cell>(M));
        vector<vector<int> > isVisited(N, vector<int>(M, 0)), val(N, vector<int>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                dp[i][j].x = i;
                dp[i][j].y = j;
                cin >> val[i][j];
            }
        }
        priority_queue<Cell, vector<Cell>, comp> pq;
        dp[enx][eny].t = 0;
        dp[enx][eny].v = val[enx][eny];
        pq.push(dp[enx][eny]);
        
        while (!pq.empty()) {
            Cell c = pq.top();
            pq.pop();
            if (isVisited[c.x][c.y])
                continue;
            isVisited[c.x][c.y] = 1;
            if (c.x == exx && c.y == exy)
                break;
            for (int k = 0; k < 4; k++) {
                int x = c.x + dx[k], y = c.y + dy[k];
                if (onBoard(x, y) && !isVisited[x][y] && val[c.x][c.y] != -1) {
                    int v = dp[c.x][c.y].v + val[x][y];
                    if (dp[x][y].t > dp[c.x][c.y].t + 1) {
                        dp[x][y].t = dp[c.x][c.y].t + 1;
                        dp[x][y].v = v;
                    }
                    else if (dp[x][y].t == dp[c.x][c.y].t + 1 && dp[x][y].v < v)
                        dp[x][y].v = v;
                    pq.push(dp[x][y]);
                }
            }
            
        }
        if (!isVisited[exx][exy])
            cout<<"Case #"<<index<<": Mission Impossible."<<endl;
        else
            cout<<"Case #"<<index<<": "<<dp[exx][exy].v<<endl;
        //cout<<"Case #"<<index<<": "<<endl;
    }
    return 0;
}

// Ignore all my comments
int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    /*
     int T;
     cin >> T;
     for (int index = 1; index <= T; ++index) {
     
     //cout<<"Case #"<<index<<": "<<endl;
     }
     */
    cout<<"Case #1:"<<endl;
    char prev = '\0', cur = '\0';
    int leftCount = 0;
    
    while ((cur = getchar()) != EOF) {
        if (prev == '/' && cur == '*') {
            leftCount++;
            prev = '\0';
            continue;
        }
        if (prev == '*' && cur == '/' && leftCount > 0) {
            leftCount--;
            prev = '\0';
            continue;
        }
        if (leftCount == 0 && prev != '\0')
            putchar(prev);
        prev = cur;
    }
    putchar(prev);
    return 0;
}
int main() {
    
    freopen("/Users/zishirs/Documents/workspace/test/test/test.txt", "r", stdin);
    freopen("/Users/zishirs/Documents/workspace/test/test/output.txt", "w", stdout);
    /*
     int T;
     cin >> T;
     for (int index = 1; index <= T; ++index) {
     
     //cout<<"Case #"<<index<<": "<<endl;
     }
     */
    cout<<"Case #1:"<<endl;
    string text;
    stringstream buffer;
    ifstream myfile ("/Users/zishirs/Documents/workspace/test/test/test.txt");
    buffer << myfile.rdbuf();
    text = buffer.str();
    int i = 0, n = (int)text.length(), start = -1, leftCount = 0;
    for (; i < n; i++) {
        if (text[i] == '/' && i + 1 < n && text[i + 1] == '*') {
            if (leftCount == 0)
                start = i;
            leftCount++;
            i++;
        }
        else if (text[i] == '*' && i + 1 < n && (text[i + 1] == '/') && leftCount > 0) {
            leftCount--;
            start = -1;
            i++;
        }
        else if (leftCount == 0) {
            start = -1;
            putchar(text[i]);
        }
    }
    if (start < n && start != -1) {
        for (int j = start; j < n; j++)
            putchar(text[j]);
    }
    return 0;
}

bool isValid(vector<vector<int> > &board) {
    int sz = (int)board.size(), n = sqrt(sz);
    for (int i = 0; i < sz; i++) {
        vector<bool> checkX(sz, false), checkY(sz, false);
        for (int j = 0; j < sz; j++) {
            if (board[i][j] < 1 || board[i][j] > sz || board[j][i] < 1 || board[j][i] > sz)
                return false;
            if (checkX[board[i][j]] || checkY[board[j][i]])
                return false;
            else {
                checkX[board[i][j]] = true;
                checkY[board[j][i]] = true;
            }
        }
    }
    
    for (int i = 0; i < sz; i += n) {
        for (int j = 0; j < sz; j += n) {
            vector<bool> check(sz, false);
            for (int dx = 0; dx < n; dx++) {
                for (int dy = 0; dy < n; dy++) {
                    if (board[i + dx][j + dy] < 1 || board[i + dx][j + dy] > sz)
                        return false;
                    if (check[board[i + dx][j + dy]])
                        return false;
                    else
                        check[board[i][j]] = true;
                }
            }
        }
    }
    return true;
}

#endif /* defined(__test__leetcode__) */