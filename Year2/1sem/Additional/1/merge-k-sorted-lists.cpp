#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void print_all(ListNode *list)
{
    while (list != nullptr)
    {
        cout << list->val << ' ';
        list = list->next;
    }
    cout << endl;
}

ListNode *count_merge(vector<ListNode *> &lists)
{
    int mn;

    int counts[100000000];
    memset(counts, 0, 20000);

    for (ListNode *list : lists)
    {
        while (list != nullptr)
        {
            counts[(list->val) + 10000]++;
            list = list->next;
        }
    }
    ListNode node, *nodeptr = nullptr;

    for (int i = 0; i < 20000; ++i)
    {
        for (int j = 0; j < counts[i]; ++j)
        {
            node = (ListNode(i - 10000, nodeptr));
            nodeptr = &node;
        }
    }
    return nodeptr;
}

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        }
};