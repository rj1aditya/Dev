Node *findIntersection(Node *head1, Node *head2)
{
    Node *intsct = new Node(-1);
    Node *cur3 = intsct;
    Node *cur1 = head1;
    Node *cur2 = head2;
    unordered_map<int, int> mp;

    while (cur2)
    {
        mp[cur2->data] = 1;
        cur2 = cur2->next;
    }
    while (cur1)
    {
        if (mp[cur1->data])
        {
            Node *temp = new Node(cur1->data);
            cur3->next = temp;
            cur3 = temp;
        }
        cur1 = cur1->next;
    }
    return intsct->next;
}