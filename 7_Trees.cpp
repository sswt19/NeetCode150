#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <list>
#include <sstream>
#include <climits>
#include <unordered_set>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *next;

    Node(int x)
    {
        key = x;
        left = NULL;
        right = NULL;
        next = NULL;
    }
};

/*

Binary Tree:
1. Invert Binary Tree/Convert a Binary Tree into its Mirror Tree: https://leetcode.com/problems/invert-binary-tree/description/
2. Maximum-Depth/Height of Binary Tree: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
3. Diameter of Binary Tree: https://leetcode.com/problems/diameter-of-binary-tree/description/
4. Balanced Binary Tree: https://leetcode.com/problems/balanced-binary-tree/description/
5. Same Tree: https://leetcode.com/problems/same-tree/description/
6. Subtree of Another Tree: https://leetcode.com/problems/subtree-of-another-tree/description/
7. Binary Tree Level Order Traversal: https://leetcode.com/problems/binary-tree-level-order-traversal/description/
8. Binary Tree Right Side View: https://leetcode.com/problems/binary-tree-right-side-view/description/
9. Count Good Nodes in Binary Tree: https://leetcode.com/problems/count-good-nodes-in-binary-tree/description/
10. Construct Binary Tree from Preorder and Inorder Traversal: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
11. Binary Tree Maximum Path Sum: https://leetcode.com/problems/binary-tree-maximum-path-sum/
12. Serialize and Deserialize Binary Tree: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/
13. Populating Next Right Pointers in Each Node: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

Binary Search Tree:
1. Lowest Common Ancestor of a Binary Search Tree: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
2. Validate Binary Search Tree: https://leetcode.com/problems/validate-binary-search-tree/description/
3. Kth Smallest Element in a BST: https://leetcode.com/problems/kth-smallest-element-in-a-bst/
4. Construct BST from given keys: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
5. Find the inorder predecessor/successor of a given Key in BST: https://www.geeksforgeeks.org/problems/predecessor-and-successor/1
*/

// ============================================= Binary Tree ==============================================

// 1
class InvertBinaryTree
{
    /*
    =======Top Down========
        Swap left and right using temp and recursively do the same for left and right sub trees
        T: O(n)
        S: O(height of tree) => O(n) worst case
    */
public:
    TreeNode *invertTree(TreeNode *node)
    {
        if (!node)
            return node;

        auto temp = node->right;
        node->right = invertTree(node->left);
        node->left = invertTree(temp);

        return node;
    }
};

// 2
class HeightOfBT
{
    /*
    =======Bottom Up========
        Add 1 to height to include current node
        T: O(n)
        S: O(h)=>O(n) worst case
    */
public:
    int maxDepth(TreeNode *root)
    {
        if (!root)
            return 0;

        int left_height = maxDepth(root->left);
        int right_height = maxDepth(root->right);
        return 1 + max(left_height, right_height);
    }
};

// 3
class DiameterOfBT
{
    /*
    =======Bottom Up========
        We will compute the diameter in each node with bottom up approach,
        The helper function returns the longest path from subtree which can be connected to root

        *IMPORTANT*
        We are computing number of nodes in diameter but the problem wants no of edges in diameter,
        so edges would be edges = (no of nodes - 1)

        T:O(n)
        S:O(height) => O(n) worst case
    */

    int diameterOfBinaryTree_helper(TreeNode *root, int &diameter)
    {
        if (!root)
            return 0;

        auto left_path_length = diameterOfBinaryTree_helper(root->left, diameter);
        auto right_path_length = diameterOfBinaryTree_helper(root->right, diameter);

        diameter = max(diameter, left_path_length + right_path_length + 1);

        return 1 + max(left_path_length, right_path_length);
    }

public:
    int diameterOfBinaryTree(TreeNode *root)
    {
        int ans = 0;
        diameterOfBinaryTree_helper(root, ans);
        return ans == 0 ? 0 : ans - 1;
    }
};

// 4
class IsBalancedBT
{
    /*
    =======Bottom Up========
        We will check if the tree is balanced in each node with bottom up approach, and return height of the subtree
        T: O(n)
        S: O(h)=>O(n) worst case
    */
    int isBalanced_helper(TreeNode *root, bool &balanced)
    {
        if (!root)
            return 0;

        int left_height = isBalanced_helper(root->left, balanced);
        int right_height = isBalanced_helper(root->right, balanced);

        // at each node the height diff between 2 subtrees should not be >1
        if (abs(left_height - right_height) > 1)
            balanced = false;

        return 1 + max(left_height, right_height);
    }

public:
    bool isBalanced(TreeNode *root)
    {
        // all subtrees should be balanced as well
        bool balanced = true;
        isBalanced_helper(root, balanced);
        return balanced;
    }
};

// 5
bool isSameTree_helper(TreeNode *p, TreeNode *q)
{
    // =======Top Down========
    if (!p && !q) // both do not exist
        return true;
    if (p && q)
        return (p->val == q->val) && isSameTree_helper(p->left, q->left) &&
               isSameTree_helper(p->right, q->right);
    else // one exist and one do not
        return false;
}
class IsSameTree
{
    /*
    =======Top Down========
    Check if the node values are same, then recursively check for both left and right subtrees
    T: O(n)
    S: O(h)=>O(n) worst case
    */
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        return isSameTree_helper(p, q);
    }
};
// 6
class IsSubTree
{
    /*
    =======Top Down========
        For each node in tree we will check if that node and subtree are same trees
        T:O(n*m) where n and m are size of each tree
        S:O(m) max height of second tree
    */
public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        // both do not exist
        if (!root && !subRoot)
            return true;
        if (root && subRoot)
            return isSameTree_helper(root, subRoot) ||
                   isSubtree(root->left, subRoot) ||
                   isSubtree(root->right, subRoot);
        else // one exist and one do not
            return false;
    }
};

// 7
class LevelOrderTraversal
{
    /*
    =======Level Order Traversal========
        T:O(n)
        S:O(max size of level)=> O(n) leaves will have n/2 nodes
    */
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (!root)
            return {};
        vector<vector<int>> level_order;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int level_size = q.size();
            vector<int> level(level_size);
            for (int i = 0; i < level_size; i++)
            {
                auto temp = q.front();
                q.pop();
                level[i] = temp->val;
                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
            level_order.push_back(level);
        }
        return level_order;
    }
};

// 8
class RightViewOfTree
{
    /*
    =======Level Order Traversal========
        Use level order traversal and store the last node of each level
        T:O(n)
        S:O(max size of level)=> O(n) leaves will have n/2 nodes
    */
public:
    vector<int> rightSideView(TreeNode *root)
    {
        if (!root)
            return {};
        vector<int> right_view;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int level_size = q.size();
            for (int i = 0; i < level_size; i++)
            {
                auto temp = q.front();
                q.pop();

                if (i == level_size - 1)
                    right_view.push_back(temp->val);

                if (temp->left)
                    q.push(temp->left);
                if (temp->right)
                    q.push(temp->right);
            }
        }
        return right_view;
    }
};

// 9
class GoodNodesInTree
{
    /*
    =======Top Down========
        pass the maxValue till now to both left and right subtree and use it to compute good node
        T:O(n)
        S:O(height)=>O(n) height worst case can be n
    */
    void goodNodes_helper(TreeNode *root, int &ans, int maxValue)
    {
        if (!root)
            return;
        if (root->val >= maxValue)
            ans++;
        maxValue = max(maxValue, root->val);
        goodNodes_helper(root->left, ans, maxValue);
        goodNodes_helper(root->right, ans, maxValue);
    }

public:
    int goodNodes(TreeNode *root)
    {
        int goodCount = 0;
        goodNodes_helper(root, goodCount, INT_MIN);
        return goodCount;
    }
};

// 10
class BTFromPreAndIn
{
    /*
    =======Top Down========
        We will use preorder to know the root node which we will create and inorder to know the left and right subtrees
        T:O(n)
        S:O(n)
    */
    TreeNode *buildTree_helper(vector<int> &preorder, int &index_preorder, unordered_map<int, int> &inorder_index, int inorder_start, int inorder_end)
    {

        if (inorder_start > inorder_end)
            return NULL;

        TreeNode *root = new TreeNode(preorder[index_preorder]);
        index_preorder++;
        // which values will now go to left and right sutree will depend upon inorder_start, inorder_index[root->val] and
        root->left = buildTree_helper(preorder, index_preorder, inorder_index, inorder_start, inorder_index[root->val] - 1);
        root->right = buildTree_helper(preorder, index_preorder, inorder_index, inorder_index[root->val] + 1, inorder_end);
        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        unordered_map<int, int> inorder_index;
        for (int i = 0; i < inorder.size(); i++)
            inorder_index[inorder[i]] = i;
        int index_preorder = 0;
        return buildTree_helper(preorder, index_preorder, inorder_index, 0, preorder.size() - 1);
    }
};

// 11
class BTMaxPathSum
{
    /*
    The helper function returns the longest path from subtree which can be connected to root
        T:O(n)
        S:O(height)=>O(n)
    */
    int maxPathSum_helper(TreeNode *root, int &ans)
    {
        if (!root)
            return 0;

        int left_path_sum = maxPathSum_helper(root->left, ans);
        int right_path_sum = maxPathSum_helper(root->right, ans);

        // path_with_root can be > root+left+right because there can be negative numbers in BT
        int path_with_root = max({root->val, left_path_sum + root->val, right_path_sum + root->val});
        // all cases: root, root+left, root+right, root+left+right, first 3 are in path_with_root
        ans = max({ans, path_with_root, root->val + left_path_sum + right_path_sum});

        return path_with_root;
    }

public:
    int maxPathSum(TreeNode *root)
    {
        int ans = INT_MIN;
        maxPathSum_helper(root, ans);
        return ans;
    }
};

// 12
class Codec
{
    /*
        preorder and post order traversal with NULL values will always be unique for each tree
        We will use prorder to serialize the tree:
        Serialize:
        T:O(n) S:O(n)
        DeSerialize
        T:O(n) S:O(n)
    */
    TreeNode *deserialize_helper(stringstream &tree)
    {
        string temp;
        getline(tree, temp, ',');
        if (temp == "#")
            return NULL;
        TreeNode *root = new TreeNode(stoi(temp));
        root->left = deserialize_helper(tree);
        root->right = deserialize_helper(tree);

        return root;
    }

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        // for leaf nodes
        if (!root)
            return "#";
        // we will use preorder traversal
        return to_string(root->val) + ',' + serialize(root->left) + ',' + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        stringstream tree(data);
        return deserialize_helper(tree);
    }
};

// 13
class Solution
{
    /*
    we will use Level order traversal for any kind of tree to set right pointers
        T:O(n)
        S:O(n)
    */
public:
    Node *connect(Node *root)
    {
        if (!root)
            return root;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int level_size = q.size();
            for (int i = 0; i < level_size; i++)
            {
                auto top = q.front();
                q.pop();
                // populating the next pointer
                if (i == level_size - 1)
                    top->next = NULL;
                else
                    top->next = q.front();
                // push children
                if (top->left)
                    q.push(top->left);
                if (top->right)
                    q.push(top->right);
            }
        }
        return root;
    }
};
//  ============================================= Binary Search Tree ==============================================

// 1
class LCAInBST
{
    /*
    =======Top Down========
        LCA will be the node, where both p and q are divided into 2 diff subtrees
        *IMPORTANT*
        In the problem it is given both p and q exists in tree, if not first check if p and q are present in tree

        T:O(logn)
        S:O(1)
    */
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // check first if p and q exists in tree, if not stated that p and q exists in tree
        // we want p->val to be <= q->val
        if (p->val > q->val)
            return lowestCommonAncestor(root, q, p);

        TreeNode *temp = root;
        while (temp)
        {
            // found the LCA
            if (p->val <= temp->val && temp->val <= q->val)
                break;
            // if node is bigger than both p and q go left in BST
            else if (temp->val > q->val)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return temp;
    }
};

// 2
class IsValidBST
{
    /*
    Two Ways:
        1. Inorder Traversal and check if the array is sorted
        2. Top Down: pass a range between which the value of node should be

    Both Ways:
        T:O(n)
        S:O(n)
    */
    bool isValidBST_helper(TreeNode *root, long minAllow, long maxAllow)
    {
        if (!root)
            return true;

        // check if current root is valid and then check for subtrees
        return (root->val > minAllow && root->val < maxAllow) &&
               isValidBST_helper(root->left, minAllow, root->val) &&
               isValidBST_helper(root->right, root->val, maxAllow);
    }
    void isValidBST_inorder(TreeNode *root, vector<int> &inorder)
    {
        if (!root)
            return;

        isValidBST_inorder(root->left, inorder);
        inorder.push_back(root->val);
        isValidBST_inorder(root->right, inorder);
    }

public:
    bool isValidBSTTopDown(TreeNode *root)
    {
        return isValidBST_helper(root, LONG_MIN, LONG_MAX);
    }
    bool isValidBST(TreeNode *root)
    {
        vector<int> inorder;
        isValidBST_inorder(root, inorder);
        for (int i = 0; i < inorder.size() - 1; i++)
            if (inorder[i] >= inorder[i + 1])
                return false;
        return true;
    }
};

// 3
class KthSmallestInBST
{
    /*
    Iterative & Recursive
        T:O(k)=>O(n) worst case k can be n
        S:O(height)=>O(n) worst case
    */
    void isValidBST_inorder(TreeNode *root, int &k, int &ans)
    {
        if (!root)
            return;

        isValidBST_inorder(root->left, k, ans);
        if (k == 1)
            ans = root->val;
        k--;
        isValidBST_inorder(root->right, k, ans);
    }

public:
    int kthSmallest_iterative(TreeNode *root, int k)
    {
        stack<TreeNode *> s;
        while (root)
        {
            s.push(root);
            root = root->left;
        }

        while (!s.empty())
        {
            if (k == 1)
                return s.top()->val;
            k--;
            auto inorder_next_element = s.top();
            s.pop();
            auto node = inorder_next_element->right;
            while (node)
            {
                s.push(node);
                node = node->left;
            }
        }
        return -1;
    }
    int kthSmallest(TreeNode *root, int k)
    {
        int ans = -1;
        isValidBST_inorder(root, k, ans);
        return ans;
    }
};

// 4
class ConstructBalancedBST
{
    /*
        get the mid and use it for parent and set two halfs for left and right subtrees
        T:O(n)
        S:O(n)
    */
    TreeNode *sortedArrayToBST_helper(vector<int> &nums, int s, int e)
    {
        if (s > e)
            return NULL;
        int mid = s + (e - s) / 2;
        auto parent = new TreeNode(nums[mid]);
        parent->left = sortedArrayToBST_helper(nums, s, mid - 1);
        parent->right = sortedArrayToBST_helper(nums, mid + 1, e);

        return parent;
    }

public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return sortedArrayToBST_helper(nums, 0, nums.size() - 1);
    }
};
// 4
class InorderPreAndSuc
{
    /*
    We can use inorder but that will take O(n) time so We will use BST to our advantage and dicard other half while searching
        T:O(2*h)
        S:O(1)
    */
public:
    void findPreSuc(Node *root, Node *&pre, Node *&suc, int key)
    {
        auto temp = root;
        while (temp)
        {
            // the temp can be the answer but we will try to find more close value
            if (temp->key > key)
            {
                suc = temp;
                temp = temp->left;
            }
            else
                temp = temp->right;
        }
        temp = root;
        while (temp)
        {
            // the temp can be the answer but we will try to find more close value
            if (temp->key < key)
            {
                pre = temp;
                temp = temp->right;
            }
            else
                temp = temp->left;
        }
    }
};
//