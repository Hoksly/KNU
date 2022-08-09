#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int find_min(vector<ListNode *> &lists)
{
    int mn = 2000000;
    for (ListNode *list : lists)
    {
        if (list != nullptr)
            mn = min(mn, list->val);
    }
    return mn;
}

ListNode *no_additional_memory_merge(vector<ListNode *> &lists)
{
}

ListNode *append(ListNode *head, const int &val)
{
    return new ListNode(val, head);
}

ListNode *reverseList(ListNode *head)
{
    ListNode *prev = NULL, *cur = head, *tmp;
    while (cur)
    {
        tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    return prev;
}

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        bool gatherd = true;
        int mn = 200000, n = lists.size();
        ListNode *List = nullptr;
        while (gatherd)
        {
            mn = find_min(lists);

            if (mn == 2000000)
                break;

            for (int i = 0; i < n; ++i)
            {
                if (lists[i] && lists[i]->val == mn)
                {
                    List = append(List, mn);
                    lists[i] = lists[i]->next;
                }
            }
        }

        return reverseList(List);
    }
};

int main()
{
    /*
    ListNode *list = nullptr;
    list = new ListNode(5, list);
    list = new ListNode(4, list);
    list = new ListNode(3, list);
    vector<ListNode *> V;
    V.push_back(list);
    list = nullptr;
    list = new ListNode(2, list);
    list = new ListNode(1, list);
    V.push_back(list);

    Solution s;
    list = s.mergeKLists(V);
    */
    return 0;
}