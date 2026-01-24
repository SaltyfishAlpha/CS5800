#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    static void insertNode(ListNode& node, int value)
    {
        node.next = new ListNode(value, node.next);
    }

    ListNode* insertionSortList(ListNode* head) {
        for (ListNode *tp1 = head->next, *tp1_prev = head;
            tp1 != nullptr; tp1_prev = tp1, tp1 = tp1->next)
        {
            for (ListNode *tp2 = head, *tp2_prev = nullptr;
                    tp2 != tp1;
                    tp2_prev = tp2, tp2 = tp2->next)
            {
                if (tp2->val > tp1->val)
                {
                    tp1_prev->next = tp1->next;
                    tp1->next = tp2;
                    if (tp2_prev == nullptr)
                        head = tp1;
                    else
                        tp2_prev->next = tp1;
                    tp1 = tp1_prev;
                    break;
                }
            }
        }
        return head;
    }
};