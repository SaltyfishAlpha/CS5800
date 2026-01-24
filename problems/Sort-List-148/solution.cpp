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

class Solution {
public:
    // const int THRESHOLD = 2;
    const int THRESHOLD = 16;

    ListNode* insertionSortList(ListNode* head, ListNode* head_prev, ListNode* tail) {
        for (ListNode *tp1 = head->next, *tp1_prev = head;
            tp1 != tail; tp1_prev = tp1, tp1 = tp1->next)
        {
            for (ListNode *tp2 = head, *tp2_prev = head_prev;
                    tp2 != tp1;
                    tp2_prev = tp2, tp2 = tp2->next)
            {
                if (tp2->val > tp1->val)
                {
                    tp1_prev->next = tp1->next;
                    tp1->next = tp2;
                    if (tp2_prev == head_prev)
                    {
                        head = tp1;
                        if (head_prev)
                            head_prev->next = head;
                    }
                    else
                        tp2_prev->next = tp1;
                    tp1 = tp1_prev;
                    break;
                }
            }
        }
        return head;
    }

    ListNode* MergeSort(ListNode* head, ListNode* head_prev, ListNode* tail)
    {
        auto mid = head;
        auto mid_prev = head_prev;
        auto r = head;
        int count = 0;
        while (r != tail && r->next != tail)
        {
            mid_prev = mid;
            mid = mid->next;
            r = r->next->next;
            count++;
        }

        if (count*2 <= THRESHOLD)
        {
            head = insertionSortList(head, head_prev, tail);
            return head;
        }

        auto r_sorted = MergeSort(mid, mid_prev, tail);
        auto l_sorted = MergeSort(head, head_prev, r_sorted);
        auto l_sorted_tail = r_sorted;
        auto r_sorted_tail = tail;

        ListNode* newHead;
        if (l_sorted->val < r_sorted->val)
        {
            newHead = l_sorted;
            l_sorted = l_sorted->next;
        } else
        {
            newHead = r_sorted;
            r_sorted = r_sorted->next;
        }

        auto tp = newHead;
        while(l_sorted != l_sorted_tail && r_sorted != r_sorted_tail)
        {
            if (l_sorted->val < r_sorted->val)
            {
                tp->next = l_sorted;
                tp = tp->next;
                l_sorted = l_sorted->next;
            } else
            {
                tp->next = r_sorted;
                tp = tp->next;
                r_sorted = r_sorted->next;
            }
        }

        while (l_sorted != l_sorted_tail)
        {
            tp->next = l_sorted;
            tp = tp->next;
            l_sorted = l_sorted->next;
        }

        while (r_sorted != r_sorted_tail)
        {
            tp->next = r_sorted;
            tp = tp->next;
            r_sorted = r_sorted->next;
        }

        tp->next = tail;

        head = newHead;
        if (head_prev)
            head_prev->next = newHead;

        return head;
    }

    ListNode* sortList(ListNode* head) {
        if (head == nullptr) return head;

        return MergeSort(head, nullptr, nullptr);
    }
};