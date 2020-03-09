#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cstdlib> // rand, qsort
#include "data_structs/base_struct.h"
#include "algorithm.h"
#include "sorts.h"
#include "utils.h"
#include "search_algs.h"
#include "dp_algs.h"
#include "greedy_algs.h"
#include "graph_algs.h"
#include "trace_back_algs.h"
#include "dfs_algs.h"
#include "bfs_algs.h"
#include "stack_algs.h"
#include "heap_algs.h"
#include "binary_search.h"
#include "merge_set.h"
#include "listnode_algs.h"
#include "binary_pointer.h"
#include "str_algs.h"
#include "topoloical_sort.h"
#include "memory_algs.h"

using namespace std;

/*
1.求树的最小深度：
递归： 若左右子树均不为null，则等于min(left_depth, right_depth) + 1;
queue: for (q.size()) q.pop(), 逐层遍历直到某个node的左右子树均为null，每遍历一遍则depth+1。
*/
void test_minmum_depth_binary_tree() {
    TreeNode* root = new TreeNode(0);
    TreeNode* left1 = new TreeNode(1);
    // TreeNode* right1 = new TreeNode(2);
    // TreeNode* right2 = new TreeNode(3);
    root->left = left1;
    // root->right = right1;
    // right1->right = right2;
    // int result = binary_tree::minimum_depth_binary_tree(root);
    int result = binary_tree::minimum_depth_binary_tree_by_queue(root);
    std::printf("result:%d\n", result);
}

/*
2. 后序遍历：
递归，
stack： 遍历root->val, root->right, root->left, 最后reverse 整个result数组。
*/
void test_postorderTraversal() {
    TreeNode* root = new TreeNode(1);
    TreeNode* r = new TreeNode(2);
    TreeNode* rr = new TreeNode(3);
    root->right = r;
    r->right = rr;
    vector<int> result;
    // binary_tree::postorderTraversal(root, result);
    binary_tree::postorderTraversalWithStack(root, result);
    for (int i=0; i<result.size(); i++) {
        std::printf("%d ,", result[i]);
    }
    std::printf("\n");
}

/*
3. 使用stack求逆波兰式
*/
void test_reverse_polish_notation(){
    vector<string> tokens;
    // string inputs[5] = {"2", "1", "+", "3", "*"};
    string inputs[5] = {"4", "13", "5", "/", "+"};
    for (int i=0; i<5; i++) tokens.push_back(inputs[i]);
    int result = reverse_polish_notation(tokens);
    std::printf("%d \n", result);
}

/*
4. 求最大共线点数：两层循环，分别求以点i为起点的最大共线点数。因为浮点数存在误差，斜率需要用向量表示，向量可由x,y除以最大公约数得到。并额外处理斜率为0，无穷大，及重合的点。
最大公约数：max_common_divisor(a,b) if (a%b==0) return b; else return max_common_divisor(b, a%b);
*/
void test_max_point_on_a_line(){
    vector<Point> inputs;
    inputs.push_back(Point(0, 0));
    int result = max_point_on_a_line(inputs);
    std::printf("%d \n", result);
}

/*
5. 对链表进行排序，使用二分法 + merge two listnode
6. 检测链表中是否存在环，并找出环的起点。（1）通过step=1,2两个指针遍历链表，若两者相等，则存在环，返回该重合的点；（2）分别从起点，重合的点以step=1走，当起点走到重合点时，
   则重合点的指针刚好走到环的起始位置。画可知，step=2的指针比step=1的指针多走的具体就是起点到重合点的距离== 重合点到环起点的距离。
*/
void test_sortListNode(){
    ListNode* root = new ListNode(1);
    ListNode* tmp = root;
    tmp->next = new ListNode(2);
    tmp = tmp->next;
    tmp->next = new ListNode(3);
    tmp = tmp->next;
    tmp->next = new ListNode(4);
    tmp = tmp->next;
    tmp->next = new ListNode(5);
    tmp->next = root->next;
    ListNode* src = root;
    // while(src != NULL) {
    //     std::printf("%d ,", src->val);
    //     src = src->next;
    // }
    // std::printf("\n");

    // ListNode* result = list_node::sortList(root);
    // ListNode* result = list_node::insertSortList(root);
    // ListNode* result = list_node::reorderList(root);
    // ListNode* result = list_node::reorderList_V2(root);
    ListNode* result = list_node::detectCycle_V2(root);
    std::printf("%d ,", result->val);
    // while(result != NULL) {
    //     std::printf("%d ,", result->val);
    //     result = result->next;
    // }
    std::printf("\n");
}

/*
7. 求得字符串由dicts中子串拆分的所有可能。
(1) dp[n]数组保存0到i的子串是否可由dicts中的构成。两重for循环(i=1->n-1, j=0->i) if (dp[j] && s.substr(j, i-j+1) in dict) dp[i]=true
(2) 根据dp由n反推到0，得到所有的子串。dfs(idx, dp[], result): for (i=idx-1->0) {if dp[i] && s.substr(i, idx-i+1) in dict} result[i]=result[idx] + substr, dfs(i-1, dp, result);
*/
void test_wordBreak(){
    string s = "catsanddog";
    std::unordered_set<string> dicts;
    // dicts.insert("leet");
    // dicts.insert("code");
    dicts = {"cat", "cats", "and", "sand", "dog"};
    // bool result = wordBreak(s, dicts);
    // printf("result:%d\n", result);
    // vector<string> result = wordBreak_v2(s, dicts);
    vector<string> result = wordBreak_v3(s, dicts);
    for(int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

int tmp_fetch(RandomListNode* head) {
    if (head != NULL) return head->label;
    return -1;
}

void print_random_list_node(RandomListNode* head) {
    RandomListNode* p = head;
    while(p != NULL) {
        printf("label:%d, next:%d, random:%d\n", p->label, 
               tmp_fetch(p->next), tmp_fetch(p->random));
        p = p->next;
    }
}

/*
8. 复制待随机指针的链表：这类指针复制分三步：
（1） 克隆节点，并插入原始节点中。即 src->next = src_copy; scr_copy->next = src->next;
 (2) 设置指针连接关系。即src_copy->random = src->random->next;
 (3) 分离src/copy
*/
void test_randomListNode() {
    RandomListNode arr[5];
    for (int i=1; i<4; i++) {
        arr[i].label = i;
        arr[i].next = &arr[i+1];
        arr[i].random = &arr[i-1];
    }
    arr[0].next = &arr[1];
    arr[0].label = 0;
    arr[3].next = NULL;
    RandomListNode* head = &arr[0];
    print_random_list_node(head);
    RandomListNode* copy_head = list_node::copyRandomList(head);
    print_random_list_node(copy_head);
}

/*
9. 从重复2次，3次的数组中找出唯一出现一次的数。
（1）重复两次，则相同的数按位异或会变0，所以异或所有的数，最终结果就为只出现一次的数。for(num=A[0]-->A[n]) result ^= num;
 (2) 重复三次，则使用one, two, three三个变量分别记录出现1，2，3次的每一比特，最终返回one即可。
     one=two=three=0;
     for（num=A[0]-->A[n]） {
         two |= (one & num); // 一个数出现两次
         one ^= num; // 某一比特位位1的条件
         three = one & two; // 出现三次的情况
         one &= ~three; // 如果出现三次，则将one对应位置0
         two &= ~three; // 如果出现三次，则将two对应位置0
     }
*/
void test_singleNumber() {
    int a[7] = {1,2,3,2,3,2,3};
    // int result = singleNumber(a, 7);
    int result = singleNumber_v2(a, 7);
    printf("%d\n", result);
    return;
}

/*
10. n个小朋友分糖，rating高的人必须比旁边低的人分的多，每人最少一个。
从1遍历到最后
如果当前rating大于前一个，则当前分糖数为前一个+1；
否则：从前一个节点一直往前遍历：直到不满足： ranting[j]>ranting[j+1] && result[j]<=result[j+1]： result[j]=result[j+1]+1;
*/
void test_candy() {
    int a[3]={2, 1, 3};
    vector<int> ratings(a, a+3);
    for(int i=0;i<ratings.size(); i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    int result = candy(ratings);
    printf("%d\n", result);
}

/*
11. 汽车是否能走完全程，并找到起点位置。
（1）start为n,end为0，如果res + cost[start]-gas[start]<0,则说明该点不能作为起点，start--；否则end++；直到start==end结束，即为该点。
*/
void test_complete_circuit() {
    // vector<int> gas(2);
    // vector<int> costs(2);
    // gas[0]=1;
    // gas[1]=2;
    // costs[0]=2;
    // costs[1]=1;
    int gas_arr[] = {1, 2};
    int costs_arr[] = {2, 1};
    vector<int> gas(gas_arr, gas_arr + 2);
    vector<int> costs(costs_arr, costs_arr + 2);
    int result = canCompleteCircuit_v2(gas, costs);
    printf("result:%d\n", result);
}

/*
12. 同8
*/
void test_clone_graph() {
    UndirectedGraphNode* zero = new UndirectedGraphNode(0);
    UndirectedGraphNode* one = new UndirectedGraphNode(1);
    UndirectedGraphNode* two = new UndirectedGraphNode(2);
    zero->neighbors.push_back(one);
    zero->neighbors.push_back(two);
    one->neighbors.push_back(two);
    two->neighbors.push_back(two);
    print_graph(zero);
    UndirectedGraphNode* copy_node = cloneGraph(zero);
    printf("clone graph\n");
    print_graph(copy_node);

    delete zero;
    delete one;
    delete two;
}

/*
13. 将字符串分割成回文子串的所有可能,每次回溯需要pop_back curr_vector。dfs(curr_str, curr_vector, result): for (i=0->curr_str.length()) 
    if (curr_str(0,i+1) is palindrome) curr_vector.push_back(curr_str(0,i+1)); dfs(curr_str(i,len-1), curr_vector, result);
*/
void test_palidrome() {
    string str = "aab";
    vector<vector<string> > result = palindrome_partition(str);
    printf("result size:%lu\n", result.size());
    for (vector<string> v_iter: result) {
        for (string iter: v_iter) {
            printf("%s,", iter.c_str());
        }
        printf("\n");
    }
}

/*
14. 最小回文子串的数量：两重循环，i=0->n;j=i->n; if (s.sub(i, j-i+1) is palindrome) dp[j]=min(dp[j],dp[i]+1)
*/
void test_palidrome_min_cut() {
    string str = "leet";
    // int result = palindrome_minCut(str);
    int result = palindrome_minCut_v2(str);
    printf("result:%d\n", result);
}

void print_surroundReigon(vector<vector<char> >& board) {
    int width = board.size();
    int length = board[0].size();
    for (int i=0; i<width; i++) {
        for(int j=0; j<length; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

/*
15. 保留边界‘0’的连通部分。使用queue/stack遍历边界‘0’部分，置为‘A’
*/
void test_surroundRegion() {
    char board_arr[4][4] = {{'X','X','X','X'}, 
                            {'X','O','O','X'}, 
                            {'X','X','O','X'}, 
                            {'X','O','X','X'}};
    vector<vector<char> > board(4);
    for(int i=0; i<4; i++) {
        vector<char> tmp(board_arr[i], board_arr[i]+4);
        board[i] = tmp;
    }
    print_surroundReigon(board);
    SurroundingReigon(board);
    printf("\n");
    print_surroundReigon(board);
    return;
}

void test_sum_number_binary_tree() {
    TreeNode* root = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    TreeNode* right = new TreeNode(3);
    root->left = left;
    root->right = right;
    int sum = binary_tree::sumNumbers(root);
    printf("sum:%d\n", sum);
}

/*
16. 找出最长连续数的个数。使用set/map存所有的数，遍历arr，得到第i个val， 依次val--， val++ 从set/map中找
*/
void test_longest_consecutive() {
    int arr[] = {100, 4, 200, 1, 3, 2};
    vector<int> vec(arr, arr+6);
    // int result = longestConsecutive(vec);
    int result = longestConsecutive_V2(vec);
    printf("result:%d\n", result);
}

void test_queue_vector() {
    std::queue<std::vector<std::string> > qu;
    std::vector<std::string*> str_vec(4);
    std::string str1 = "str1";
    std::string str2 = "str2";
    printf("str1 add:%p, str2 add:%p\n", &str1, &str2);
    str_vec.push_back(&str1);
    printf("str_vec add:%p str_vec[size -1] add:%p, size:%lu\n", str_vec.front(), str_vec[str_vec.size()-1], str_vec.size());
    printf("str_vec[size-1]:%s\n",(*(str_vec[str_vec.size()-1])).c_str());
    // qu.push(str_vec);

    str_vec.push_back(&str2);
    printf("str_vec add:%p str_vec[size -1] add:%p, size:%lu\n", str_vec.front(), str_vec[str_vec.size()-1], str_vec.size());
    printf("str_vec[size-1]:%s\n", (*(str_vec[str_vec.size()-1])).c_str());
    // printf("%d\n", qu.front().size());
}
void test_is_palindrome() {
    std::string s = "A man, a plan, a canal: Panama";
    bool result = search::isPalindrome(s);
    printf("result:%d\n", result);
}

void test_maxPathSum() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    int result = search::binary_tree::maxPathSum(root);
    printf("result:%d\n", result);
}

void test_maxprofix() {
    int arr[] = {3,2,1,3,4,5,4,6,1,7};
    std::vector<int> vec(arr, arr+10);
    int result = search::maxProfit_v3(vec);
    printf("result:%d\n", result);
}

void test_minimumTotal() {
    std::vector<std::vector<int> > triangle;
    int line1[]={2};
    int line2[]={3,4};
    int line3[]={6,5,7};
    int line4[]={4,1,8,3};
    std::vector<int> line1_v(line1, line1+1);
    std::vector<int> line2_v(line2, line2+2);
    std::vector<int> line3_v(line3, line3+3);
    std::vector<int> line4_v(line4, line4+4);
    triangle.push_back(line1_v);
    triangle.push_back(line2_v);
    triangle.push_back(line3_v);
    triangle.push_back(line4_v);

    int result = dp::minimumTotal(triangle);
    printf("result:%d\n", result);
}

void test_pascal_row() {
    // std::vector<int> result = dp::getRow(3);
    // for (int i=0; i<result.size(); i++) {
    //     printf("%d, ", result[i]);
    // }
    // printf("\n");

    std::vector<std::vector<int> > result = dp::generate(3);
    for (int i=0; i<result.size(); i++) {
        for(int j=0; j<=i; j++) {
            printf("%d ",result[i][j]);
        }
        printf("\n");
    }
}

void test_populating_next_right_pointer() {
    TreeLinkNode* root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2);
    root->right = new TreeLinkNode(3);
    // root->left->left = new TreeLinkNode(4);
    root->left->right = new TreeLinkNode(5);
    // root->right->left = new TreeLinkNode(6);
    // root->right->right = new TreeLinkNode(7);
    search::populating_next_right_pointers_in_each_node(root);

    TreeLinkNode* curr_left=root;
    while(curr_left != nullptr) {
        TreeLinkNode* curr = curr_left;
        while(curr != nullptr) {
            printf("%d ", curr->val);
            curr = curr->next;
        }
        printf("\n");
        curr_left = curr_left->left;
    }

    delete root->right->right;
    delete root->right->left;
    delete root->left->right;
    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;
}

void test_min_distance_of_string() {
    std::string S = "rabbbit"; // ""rabbbit";
    std::string T = "rabbit"; // "rabbit";
    int result = dp::min_distance_of_str(S, T);
    printf("result:%d\n", result);
}

void test_haspathsum() {
    TreeNode* root = new TreeNode(-2);
    root->left = new TreeNode(-3);
    // root->right = new TreeNode(1);
    // root->left->right = new TreeNode(11);
    // root->right->left = new TreeNode(13);
    // root->right->right = new TreeNode(4);
    int sum = -5;
    bool result = search::hasPathSum(root, sum);
    printf("result:%d\n", result);
    std::vector<std::vector<int>> results = search::pathSum(root, sum);
    // std::vector<std::vector<int>> results = search::pathSum_bfs(root, sum);
    for (int i=0; i< results.size(); i++) {
        for(int j=0; j<results[i].size(); j++) {
            printf("%d ", results[i][j]);
        }
        printf("\n");
    }
}

void test_qsort() {
    // int a[] = {6, 2, 1, 3, 5, 4};
    int len = 20;
    int a[len];
    int b[len];
    // int a[] = {3, 6, 7, 5, 3, 5, 6, 2, 9, 1};
    for (int i=0; i<len; i++) {
        a[i] = std::rand() % len;
        b[i] = a[i];
    }
    for (int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    std::qsort(b, len, sizeof(int), utils::compare);
    for(int i=0; i<len; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // sort::qsort(a, 0, len -1);
    sort::heap_sort(a, 0, len-1);
    for (int i=0; i<len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void test_add_two_numbers() {
    ListNode* l1 = new ListNode(9);
    l1->next = new ListNode(8);
    // l1->next->next = new ListNode(3);
    ListNode *l2 = new ListNode(1);
    // l2->next = new ListNode(6);
    // l2->next->next = new ListNode(4);
    ListNode *result = search::addTwoNumbers_v2(l1, l2);
    while(result != nullptr) {
        printf("%d ", result->val);
        result = result->next;
    }
}

void test_length_of_substr() {
    std::string s = "pwwkew";
    int result = search::lengthOfLongestSubstring(s);
    printf("result:%d\n", result);
}

void test_find_mid_num() {
    std::vector<int> a={1, 3};
    std::vector<int> b={2};
    // double result = search::findMedianSortedArrays(a, b);
    double result = search::findMedianSortedArrays_v2(a, b);
    printf("result:%f \n", result);
}

void test_length_palindrome() {
    std::string str = "abcdasdfghjkldcba";
    // std::string result = search::longestPalindrome(str);
    // std::string result = dp::longestPalindrome_v2(str);
    std::string result = dp::longestPalindrome_v3(str);
    printf("result: %s\n", result.c_str());
}

void test_z_convert() {
    std::string str = "LEETCODEISHIRING";
    int rows = 4;
    std::string result = search::z_convert(str, rows);
    printf("result:%s\n", result.c_str());
}

void test_my_atoi() {
    std::string str= "-2147483647";
    int result = search::myAtoi(str);
    printf("result:%d\n", result);
}

void test_regular_match() {
    std::string s= "a";
    std::string p = "a*";
    bool result = dp::regular_match(s, p);
    printf("result:%d\n", result);
}

void test_largest_rectangle_area() {
    std::vector<int> arr = {4, 1000, 1000, 1000, 1000};  // {7, 2, 1, 4, 5, 1, 3, 3}; // {3, 1, 6, 5, 2, 3}; // {2,1,5,6,2,3};
    int result = search::largestRectangleArea(arr);
    printf("result:%d\n", result);
}

void test_maximal_square() {
    std::vector<std::vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                             {'1', '0', '1', '1', '1'},
                                             {'1', '1', '1', '1', '1'},
                                             {'1', '0', '0', '1', '0'}};
    int result = dp::maximalSquare(matrix);
    printf("result:%d\n", result);
}

void test_max_area_in_water_tank() {
    std::vector<int> arr= {1,8,6,2,5,4,8,3,7}; //{1,2,4,3}; // {1,2}; // {1,8,6,2,5,4,8,3,7};
    // int result = search::maxArea(arr);
    int result = search::maxArea_v2(arr);
    printf("result:%d\n", result);
}

void test_int_to_map() {
    std::string result = search::intToRoman_v2(1994);
    
    printf("result:%s\n", result.c_str());
}

void test_is_subtree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->right->left = new TreeNode(2);
    // root->left->left = new TreeNode(0);
    TreeNode* sub = new TreeNode(3);
    sub->left = new TreeNode(1);
    sub->right = new TreeNode(2);
    bool result = search::isSubtree(root, sub);
    printf("result:%d\n", result);
}

void test_is_lowest_ancestor() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    TreeNode* p = root->left;
    TreeNode* q = root->left->right->right;
    TreeNode* result = search::lowestCommonAncestor2(root, p, q);
    printf("result:%lf\n", result->val);
}

void test_requent_tree_sum() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(-5);
    // root->left->left = new TreeNode(6);
    // root->left->right = new TreeNode(2);
    // root->left->right->left = new TreeNode(7);
    // root->left->right->right = new TreeNode(4);
    // root->right->left = new TreeNode(0);
    // root->right->right = new TreeNode(8);
    std::vector<int> result = search::findFrequentTreeSum(root);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_simple_path() {
    std::string path = "/a//b////c/d//././/.."; //"/a/../../b/../c//.//"; // "/a/./b/../../c/"; // "/home//foo/"; // "/../"; // "/home/";
    std::string result = search::simplifyPath(path);
    printf("result:%s\n", result.c_str());
}

void test_reverse_between() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* result = search::reverseBetween(head, 2, 2);
    while(result!=nullptr) {
        printf("%d ", result->val);
        result = result->next;
    }
    printf("\n");
}

void test_juge_point24() {
    // std::vector<int> nums = {1, 2, 1, 2}; // {4, 1, 8, 7};
    // bool result = search::judgePoint24(nums);
    std::vector<double> nums = {4, 1, 8, 7};
    char op_types[5] = {'*', '+', '/', '-'};
    bool result = search::judgePoint24_v2(nums, op_types);
    printf("result:%d\n", result);
}

void test_spiral_order() {
    std::vector<std::vector<int>> matrix = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}}; // {{1,2,3}, {4,5,6}, {7,8,9}};
    std::vector<int> result = search::spiralOrder(matrix);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_generate_matrix(){
    std::vector<std::vector<int>> result = search::generateMatrix(3);
    for (int i=0; i< result.size(); i++) {
        for (int j=0; j<result[0].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

void test_match_idx_val() {
    std::vector<int> data = {-5,1,2,3,6};
    std::vector<int> result;
    search::match_idx_val(data, result, 0, 4);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    result.clear();
    search::match_idx_val_v2(data, result, 0, 4);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_mct_from_leaf() {
    std::vector<int> data= {6,2,4};
    int result = dp::mctFromLeafValues(data);
    printf("result:%d\n", result);
}

void test_three_sum() {
    std::vector<int> data = {-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> result = search::threeSum(data);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}
void test_advantage_count() {
    std::vector<int> A = {2,0,4,1,2}; // {12,24,8,32}; //{2,7,11,15};
    std::vector<int> B = {1,3,0,0,2}; // {13,25,32,11}; // {1,10,4,11};
    std::vector<int> result = greedy::advantageCount(A, B);
    for (int i=0;i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_can_jump() {
    std::vector<int> data = {3,2,1,0,4}; //{2,3,1,1,4};
    // bool result = greedy::canJump(data);
    // printf("result:%d\n", result);
    int result = greedy::jump(data);
    printf("result:%d\n", result);
}

void test_can_complete_circuit() {
    std::vector<int> gas = {1,2,3,4,5}; // {2,3,4}; //{1,2,3,4,5};
    std::vector<int> costs = {3,4,5,1,2}; // {3,4,3}; // {3,4,5,1,2};
    int result = greedy::canCompleteCircuit(gas, costs);
    printf("results:%d\n", result);
}

void test_match_str() {
    std::string s = "aa"; // "adceb";
    std::string p = "*ab"; // "*a*b";
    bool result = greedy::isMatch(s, p);
    printf("result:%d\n", result);
}

void test_remove_duplicate_letters() {
    std::string s = "cbacdcbc"; // "bcabc";
    std:string result = greedy::removeDuplicateLetters(s);
    printf("result:%s\n", result.c_str());
}

void test_max_sub_array() {
    std::vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int result = dp::maxSubArray(nums);
    printf("result:%d\n", result);
}

void test_unique_path() {
    int result = dp::uniquePaths(7, 3);
    printf("result:%d\n", result);
}

void test_unique_path_with_obstacle() {
    std::vector<std::vector<int>> map = {{0,0,0}, {0,1,0}, {0,0,0}};
    int result = dp::uniquePathsWithObstacles(map);
    printf("result:%d\n", result);
}

void test_max_rectangle() {
    std::vector<std::vector<char>> matrix = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};
    int result = dp::maximalRectangle(matrix);
    printf("result:%d\n", result);
}

void test_clone_graph2() {
    graphNode* head = new graphNode(1);
    graphNode* node2 = new graphNode(2);
    graphNode* node3 = new graphNode(3);
    graphNode* node4 = new graphNode(4);
     
    head->neighbors.push_back(node2);
    head->neighbors.push_back(node4);
    node2->neighbors.push_back(head);
    node2->neighbors.push_back(node3);
    node3->neighbors.push_back(node2);
    node3->neighbors.push_back(node4);
    node4->neighbors.push_back(head);
    node4->neighbors.push_back(node3);

    graphNode* copy_head = graph::cloneGraph(head);
    
    std::set<int> visited;
    std::queue<graphNode*> q;
    graphNode* curr = copy_head;
    q.push(curr);
    while(!q.empty()) {
        curr = q.front();
        q.pop();
        if (visited.find(curr->val) != visited.end()) continue;
        visited.insert(curr->val);
        printf("%d: ", curr->val);
        for (int i=0; i<curr->neighbors.size(); i++) {
            printf("%d ", curr->neighbors[i]->val);
            if (visited.find(curr->neighbors[i]->val) == visited.end()) q.push(curr->neighbors[i]);
        }
        printf("\n");
    }
}

void test_can_finish() {
    std::vector<std::vector<int>>  data = {{0,1}, {0,2}, {1,2}};
    bool result = graph::canFinish(3, data);
    printf("result:%d\n", result);
}

void test_find_order() {
    std::vector<std::vector<int>>  data = {{0,1}, {0,2}, {1,2}};
    std::vector<int> result = graph::findOrder(3, data);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_find_highest_node() {
    std::vector<std::vector<int>> edges={{0, 3}, {1, 3}, {2, 3}, {4, 3}, {5, 4}}; //{{1,0},{1,2},{1,3}};
    std::vector<int> result = graph::findMinHeightTrees(6, edges);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void test_letter_combination() {
    std::string digits = "23";
    std::vector<std::string> result = track_back::letterCombinations(digits);
    for (int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

/*
回溯法生成合法括号：
1. 判断当前字符串中左括号的个数始终>=右括号的个数即合法，其他均不合法。
2. if (left_num>n||right_num>n) return;
   if (left_num==n&&right_num==n) collection result;
   if (left_num>=right_num) dfs(curr+'(', left_num+1, right_num, n); dfs(curr+')', left_num, irght_num+1, n);
*/
void test_generate_parenthesis() {
    std::vector<std::string> result = track_back::generateParenthesis(3);
    for (int i=0; i<result.size(); i++) {
        printf("%s\n", result[i].c_str());
    }
}

void test_combination_sum() {
    std::vector<int> candidates = {2,5,2,1,2}; // {10,1,2,7,6,1,5};
    int target = 5; //8;
    std::vector<std::vector<int>> result = track_back::combinationSum2(candidates, target);
    for (int i=0; i<result.size(); i++ ){
        for (int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

void test_dfs_isvalidtree() {
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(3);
    // root->right->left = new TreeNode(3);
    // root->right->right = new TreeNode(6);
    bool result = dfs::isValidBST(root);
    printf("result:%d\n", result);
}

void test_recover_tree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    dfs::recoverTree(root);
    TreeNode* curr = root;
    
}

void test_build_tree() {
    std::vector<int> preorder = {3,9,20,15,7};
    std::vector<int> inorder = {9,3,15,20,7};
    TreeNode* root = dfs::buildTree(preorder, inorder);

}

void test_is_symmetric() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(3);
    root->right->right = new TreeNode(4);

    bool result = bfs::isSymmetric(root);
    printf("result:%d\n", result);
}

void test_zigzag_level_order() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    std::vector<std::vector<int>> result = bfs::zigzagLevelOrder(root);
    for (int i=0; i<result.size(); i++) {
        for(int j=0; j<result[i].size(); j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}


/*
根据wordlist 从start过渡到end
1.先使用queue，bfs判断是否可以过渡到end，并记录path_map[curr].push_back(curr_in)
2.dfs（回溯）根据path_map,从end出发，反向遍历到start。
*/
void test_ladder_length_bfs() {
    std::string start = "red"; // "hit";
    std::string end = "tax"; // "cog";
    std::vector<std::string> wordlist = {"ted","tex","red","tax","tad","rex"}; // {"hot","dot","dog","lot","log","cog"};
    // int step = bfs::ladderLength(start, end, wordlist);
    // printf("result:%d\n", step);
    // std::vector<std::vector<std::string>> result = bfs::findLadders(start, end, wordlist);
    // std::vector<std::vector<std::string>> result = bfs::findLadders_v2(start, end, wordlist);
    std::vector<std::vector<std::string>> result = bfs::findLadders_v3(start, end, wordlist);
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            printf("%s ", result[i][j].c_str());
        }
        printf("\n");
    }
}

void test_eval_rpn() {
    std::vector<std::string> tokens = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"}; // {"4", "13", "5", "/", "+"}; //{"2", "1", "+", "3", "*"};
    int result = stack_algs::evalRPN(tokens);
    printf("result:%d\n", result);
}

void test_trap() {
    std::vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1}; // {2,1,0,2};
    int result = stack_algs::trap(height);
    printf("result:%d\n", result);
}

void test_find_k_largest() {
    std::vector<int> nums = {3,2,1,5,6,4};; // {7,6,5,4,3,2,1}; //{3,2,1,5,6,4};
    int k = 2; //5; //2;
    // int result = heap::findKthLargest(nums, k);
    int result = heap::findKthLargest_v2(nums, k);
    printf("result:%d\n", result);
}

void test_merge_k_list() {
    std::vector<ListNode*> lists;
    ListNode* root1 = new ListNode(1);
    root1->next = new ListNode(4);
    root1->next->next = new ListNode(5);
    ListNode* root2 = new ListNode(1);
    root2->next = new ListNode(3);
    root2->next->next = new ListNode(4);
    ListNode* root3 = new ListNode(2);
    root3->next = new ListNode(6);
    lists.push_back(root1);
    lists.push_back(root2);
    lists.push_back(root3);
    ListNode* root = heap::mergeKLists(lists);
    while(root!=nullptr) {
        printf("%d ", root->val);
        root = root->next;
    }
    printf("\n");
}

void test_divide() {
    int dividend = 2147483647; //2147483647;
    int divisor = 1; //3;
    int result = binary_search::divide(dividend, divisor);
    printf("result:%d\n", result);
}

void test_search() {
    std::vector<int> nums = {4,5,6,7,0,1,2}; //{3,1}; //{4,5,6,7,0,1,2};
    int target = 3;
    int result = binary_search::search(nums, target);
    printf("result:%d\n", result);
}

void test_find_median_num() {
    std::vector<int> nums1 = {1,2}; //{1,2}; //{1,3};
    std::vector<int> nums2 = {1,2,3}; //{3,4}; //{2};
    double result = binary_search::findMedianSortedArrays(nums1, nums2);
    printf("result:%f\n", result);
}

void test_merge_set() {
    std::vector<std::vector<char>> board={
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    merge_set::solve(board);
    for (int i=0; i<board.size(); i++) {
        for (int j=0; j<board[0].size(); j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}

void test_num_island() {
    // std::vector<std::vector<char>> grid={
    //     {'1', '1', '0', '0', '0'},
    //     {'1', '1', '0', '0', '0'},
    //     {'0', '0', '1', '0', '0'},
    //     {'0', '0', '0', '1', '1'}
    // };
    std::vector<std::vector<char>> grid = {{'1'},{'1'}};
    int result = merge_set::numIslands(grid);
    printf("result:%d\n", result);
}

void test_longest_consecutive2() {
    std::vector<int> data = {100, 4, 200, 1, 3, 2};
    // int result = merge_set::longestConsecutive(data);
    int result = merge_set::longestConsecutive_v2(data);
    printf("result:%d\n", result);
}

void test_bi_node() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(6);
    TreeNode* head = binary_search::convertBiNode(root);
    while(head!=nullptr) {
        printf("%f ", head->val);
        head = head->right;
    }
    printf("\n");
}

void test_remove_nth_node() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* new_head = listnode_alg::removeNthFromEnd(head, 2);
    while(new_head!=nullptr) {
        printf("%d ", new_head->val);
        new_head = new_head->next;
    }
    printf("\n");
}

void test_length_substr() {
    std::string str = "dvdf";
    int result = binary_pointer::lengthOfLongestSubstring(str);
    printf("result:%d\n", result);
}

void test_unordered_map() {
    std::unordered_map<int ,int> map = {{1,1},{2,2}};
    map.insert({3,3});
    for (std::pair<int ,int> pair: map) {
        printf("%d: %d\n", pair.first, pair.second);
    }
    for (std::unordered_map<int,int>::iterator iter=map.begin(); iter!=map.end(); iter++) {
        printf("%d: %d\n", (*iter).first, (*iter).second);
    }
}

void test_str_longest_palindrome() {
    std::string str = "abc";
    // std::string result = str_alg::longestPalindrome(str);
    std::string result = str_alg::longestPalindrome_dp(str);
    printf("result:%s\n", result.c_str());
}

void test_str_heap_topk() {
    std::vector<int> nums = {1,2,4,5,6,7};
    int k = 3;
    int result = str_alg::heap_topk(nums, k);
    printf("resbult:%d\n", result);
}

void test_dfs_bstTogst() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(1);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    root->right->right->right = new TreeNode(8);

    TreeNode* new_root = binary_search::bstToGst(root);
    TreeNode* curr = new_root;
    std::queue<TreeNode*> q;
    q.push(curr);
    while(!q.empty()) {
        TreeNode* tmp = q.front(); q.pop();
        printf("%f ", tmp->val);
        if (tmp->left!=nullptr) q.push(tmp->left);
        if (tmp->right!=nullptr) q.push(tmp->right);
    }
    printf("\n");
}

void test_swap_pair() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // ListNode* new_head = listnode_alg::swapPairs(head);
    ListNode* new_head = listnode_alg::reverseKGroup(head, 3);
    while(new_head!=nullptr) {
        printf("%d ", new_head->val);
        new_head = new_head->next;
    }
    printf("\n");
}

void test_min_window() {
    std::string s = "a"; //"ADOBECODEBANC";
    std::string t = "aa"; //"ABC";
    std::string result = binary_pointer::minWindow(s, t);
    printf("result:%s\n", result.c_str());
}

void test_find_substr() {
    std::string s = "foobarthefoobarman"; //"wordgoodgoodgoodbestword"; // "wordgoodgoodgoodbestword";
    std::vector<std::string> words = {"bar","foo"}; //{"word","good","best","good"}; // {"word","good","best","word"};
    // std::vector<int> result = binary_pointer::findSubstring(s, words);
    std::vector<int> result = binary_pointer::findSubstring_v2(s, words);
    for (int i=0; i<result.size(); i++)
        printf("%d ", result[i]);
    printf("\n");
}

void test_longest_valid_parentheses() {
    std::string s = "()(()";
    int result = stack_algs::longestValidParentheses(s);
    printf("result:%d\n", result);
}

void test_multiply() {
    std::string num1 = "123";
    std::string num2 = "456";
    std::string result = str_alg::multiply(num1, num2);
    printf("result:%s\n", result.c_str());
}

/*
 求矩阵中最长的连续递增串．将连续递增的关系表示为有向图，得到每个点的in_degrees[m][n], 将所有入度为０的点push到queue中，直到queue为空．
*/
void test_longest_increaseing_path() {
    std::vector<std::vector<int>> matrix = {{3,4,5},{3,2,6},{2,2,1}}; // {{9,9,4},{6,6,8},{2,1,1}};
    int result = topoloical_sort::longestIncreasingPath(matrix);
    printf("result:%d\n", result);
}

/*
从shorter, longer中选取k个数，求所有可能出现的和
*/
void test_diving_board() {
    int shorter = 1;
    int longer = 1;
    int k = 0;
    std::vector<int> result = memory_alg::divingBoard(shorter, longer, k);
    for (int i=0; i<result.size(); i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

/*
将字符串拆分，得到未匹配的字符个数
dp[i]表示0->1的字符串中未匹配的个数．则 从0遍历ｊ到ｉ, 如果str(j, i) in dict, dp[i]=  min(dp[i-1]+1, dp[j-1]) 否则　dp[i] = dp[i-1] +1;
*/
void test_respace() {
    std::vector<std::string> dict = {"looked","just","like","her","brother"};
    std::string sentence = "jesslookedjustliketimherbrother";
    int result = memory_alg::respace(dict, sentence);
    printf("result:%d\n", result);
}

int main() {
    // test_minmum_depth_binary_tree();
    // test_reverse_polish_notation();
    // test_max_point_on_a_line();
    // test_sortListNode();
    // test_postorderTraversal();
    // test_wordBreak();
    // test_randomListNode();
    // test_singleNumber();
    // test_candy();
    // test_complete_circuit();
    // test_clone_graph();
    // test_palidrome();
    // test_palidrome_min_cut();
    // test_surroundRegion();
    // test_sum_number_binary_tree();
    // test_longest_consecutive();
    // test_queue_vector();
    // test_is_palindrome();
    // test_maxPathSum();
    // test_maxprofix();
    // test_minimumTotal();
    // test_pascal_row();
    // test_populating_next_right_pointer();
    // test_min_distance_of_string();
    // test_haspathsum();
    // test_qsort();
    // test_add_two_numbers();
    // test_length_of_substr();
    // test_find_mid_num();
    // test_length_palindrome();
    // test_z_convert();
    // test_my_atoi();
    // test_regular_match();
    // test_largest_rectangle_area();
    // test_maximal_square();
    // test_max_area_in_water_tank();
    // test_int_to_map();
    // test_is_subtree();
    // test_is_lowest_ancestor();
    // test_requent_tree_sum();
    // test_simple_path();
    // test_reverse_between();
    // test_juge_point24();
    // test_spiral_order();
    // test_generate_matrix();
    // test_match_idx_val();
    // test_mct_from_leaf();
    // test_three_sum();
    // test_advantage_count();
    // test_can_jump();
    // test_can_complete_circuit();
    // test_match_str();
    // test_remove_duplicate_letters();
    // test_max_sub_array();
    // test_unique_path(); 
    // test_unique_path_with_obstacle();
    // test_max_rectangle();
    // test_clone_graph2();
    // test_can_finish();
    // test_find_order();
    // test_find_highest_node();
    // test_letter_combination();
    // test_generate_parenthesis();
    // test_combination_sum();
    // test_dfs_isvalidtree();
    // test_recover_tree();
    // test_build_tree();
    // test_is_symmetric();
    // test_zigzag_level_order();
    // test_ladder_length_bfs();
    // test_eval_rpn();
    // test_trap();
    // test_find_k_largest();
    // test_merge_k_list();
    // test_divide();
    // test_search();
    // test_find_median_num();
    // test_merge_set();
    // test_num_island();
    // test_longest_consecutive2();
    // test_bi_node();
    // test_remove_nth_node();
    // test_length_substr();
    // test_unordered_map();
    // test_string();
    // test_str_longest_palindrome();
    // test_str_heap_topk();
    // test_dfs_bstTogst();
    // test_swap_pair();
    // test_min_window();
    // test_find_substr();
    // test_longest_valid_parentheses();
    // test_multiply();
    // test_longest_increaseing_path();
    // test_diving_board();
    test_respace();


    return 0;
}