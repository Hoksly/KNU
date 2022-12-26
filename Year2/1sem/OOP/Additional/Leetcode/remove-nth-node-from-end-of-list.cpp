
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *toDelete = head, *last = head, *tmpDelete;

        for (int i = 0; i < n; ++i)
            last = last->next;
        if (!last)
        {
            tmpDelete = head;
            head = head->next;
            delete tmpDelete;
            return head;
        }

        while (last->next)
        {
            last = last->next;
            toDelete = toDelete->next;
        }

        tmpDelete = toDelete->next;
        toDelete->next = toDelete->next->next;
        delete tmpDelete;

        return head;
    }
};

int main()
{
}