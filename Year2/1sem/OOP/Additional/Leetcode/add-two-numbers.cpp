// https://leetcode.com/problems/add-two-numbers

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {

        ListNode *res = nullptr, *head;

        int val, add;
        val = 0;
        add = 0;

        while (l1 && l2)
        {

            val = l1->val + l2->val + add;

            if (val > 9)
            {
                val -= 10;
                add = 1;
            }
            else
                add = 0;

            if (res)
            {
                res->next = new ListNode(val);
                res = res->next;
            }
            else
            {
                res = new ListNode(val);
                head = res;
            }
            // cout << val << endl;

            l1 = l1->next;
            l2 = l2->next;
        }
        if (l1)
            push_back(l1, res, add);
        else if (l2)
            push_back(l2, res, add);
        else if (add)
            res->next = new ListNode(1);

        return head;
    }

    inline void push_back(ListNode *from, ListNode *to, int add = 0)
    {
        int val = 0;
        while (from)
        {

            val = from->val + add;
            if (val > 9)
            {
                val -= 10;
                add = 1;
            }
            else
                add = 0;

            to->next = new ListNode(val);
            from = from->next;
            to = to->next;
        }
        if (add == 1)
            to->next = new ListNode(1);
    }
};
