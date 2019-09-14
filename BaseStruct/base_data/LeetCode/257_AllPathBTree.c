/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
void countDepthAndPaths(struct TreeNode *n, int *depth, int *paths, int d) {
    if (__builtin_expect(!!(!n), 0)) return ;
    if (__builtin_expect(!!(*depth < d), 0)) *depth = d;
    if (__builtin_expect(!!(!n->left && !n->right), 0)) {
        ++(*paths); return ;
    }
    countDepthAndPaths(n->left, depth, paths, d + 1);
    countDepthAndPaths(n->right, depth, paths, d + 1); 
}

void solveOne(struct TreeNode *n, int d, int *path, char **ret, int *rn, int len, FILE *null) {
    if (__builtin_expect(!!(!n), 0)) return ;
    path[d++] = n->val;
    len += fprintf(null, "%d", n->val);
    if (__builtin_expect(!!(!n->left && !n->right), 0)) {
        ret[*rn] = malloc(len + 1);
        int plen = 0, i = 0;
        while (plen < len) {
            plen += sprintf(ret[*rn] + plen, "%d", path[i]);
            if (__builtin_expect(!!(plen < len), 1)) {
                plen += sprintf(ret[*rn] + plen, "->");
            }
            i++;
        }
        ++(*rn);
        return ;
    }
    len += 2;
    solveOne(n->left, d, path, ret, rn, len, null);
    solveOne(n->right, d, path, ret, rn, len, null);
    return ;
}

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
    int depth = 0, paths = 0, rn = 0;
    countDepthAndPaths(root, &depth, &paths, 1);
    *returnSize = paths;
    char **ret = malloc(paths * sizeof(char *));
    int *path = malloc(depth * sizeof(int));
    FILE *null = fopen("/dev/null", "w");
    solveOne(root, 0, path, ret, &rn, 0, null);
    fclose(null);
    free(path);
    return ret;
}
