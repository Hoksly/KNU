#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int val;
    Node *next;

    Node(int v) : val(v) {}
};

int main()
{
    int n;
    cin >> n;

    Node *head, *cur, *toRemove;
    head = new Node(1);
    cur = head;

    for (int i = 2; i < n + 1; ++i)
    {
        cur->next = new Node(i);
        cur = cur->next;
    }
    cur->next = head;
    cur = head;
    while (cur->next != cur)
    {
        toRemove = cur->next;

        cur->next = toRemove->next;
        cout << toRemove->val << ' ';
        delete toRemove;
        cur = cur->next;
    }
    cout << cur->val;
    delete cur;
    cout << '\n';
}