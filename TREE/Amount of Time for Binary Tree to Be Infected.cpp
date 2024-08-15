/* Two Pass Approach Using BFS and Adjency List */

/* TC : O(n)  |  SC : O(n)

class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {

      // Giving tle on using vector instead of set
        unordered_map<int, unordered_set<int>> map;
        convert(root, 0, map);
        queue<int> q;
        q.push(start);
        int minute = 0;
        unordered_set<int> visited;
        visited.insert(start);

        while (!q.empty()) {
            int levelSize = q.size();
            while (levelSize > 0) {
                int current = q.front();
                q.pop();

                for (int num : map[current]) {
                    if (visited.find(num) == visited.end()) {
                        visited.insert(num);
                        q.push(num);
                    }
                }
                levelSize--;
            }
            minute++;
        }
        return minute - 1;
    }

  void convert(TreeNode* current, int parent, unordered_map<int, unordered_set<int>>& map) {
        if (current == nullptr) {
            return;
        } 
 
        unordered_set<int> adj;
        if (parent != 0) {
            adj.insert(parent);
        } 
        if (current->left != nullptr) {
            adj.insert(current->left->val);
        } 
        if (current->right != nullptr) {
            adj.insert(current->right->val);
        }

        map[current->val] = adj;
        convert(current->left, current->val, map);
        convert(current->right, current->val, map);
    }
};

******************************************************************************************************************************************

// One pass using DFS
// Intuition : Height of a BT 
// TC : O(n)  |  SC : O(n)

class Solution {
public:

    int DFS(TreeNode* &root, int st, int &res) {
        if (root==NULL) return 0;

        int LT = DFS(root->left,st,res);
        int RT = DFS(root->right,st,res);

        if (LT < 0 || RT < 0) {
            // niche vala node infected ha
            res = max(res, abs(LT) + abs(RT));
            return min(LT,RT)-1;
        }

        if (root->val==st) {
            res = max(res,max(LT,RT));
            return -1;
        }

        return max(LT,RT) + 1;
    }

    int amountOfTime(TreeNode* root, int start) {
        int res = 0;
        DFS(root,start,res);
        return res;
    }
};
