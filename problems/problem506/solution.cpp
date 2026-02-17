#include <vector>
using namespace std;

namespace problem506 {
	// typedef vector<int> max_heap;
	template<class T>
	using max_heap = vector<T>;

	size_t inline getL(size_t i) {
		return (i<<1)+1;
	}

	size_t inline getR(size_t i) {
		return (i+1)<<1;
	}

	template<class T>
	void heapify(max_heap<T>& heap, int size, size_t index) {
		int l = getL(index);

		// no children
		if (l >= size) return;

		int r = getR(index);

		// no right child
		if (r >= size) {
			if (heap[l] > heap[index]) {
				swap(heap[l], heap[index]);
				heapify(heap, size, l);
			}
			return;
		}

		int tmp = heap[l] > heap[r] ? l : r;
		if (heap[tmp] > heap[index]) {
			swap(heap[tmp], heap[index]);
			heapify(heap, size, tmp);
		}
	}


	template<class T>
	auto pop(max_heap<T>& heap) {
		swap(heap[0], heap[heap.size()-1]);
		auto val = heap[heap.size()-1];
		heap.pop_back();
		heapify(heap, heap.size(), 0);
		return val;
	}

	class Solution {
	public:
		vector<string> findRelativeRanks(vector<int>& score) {
			int size = score.size();
			vector<string> result(size);
			max_heap<pair<int, int>> heap;

			for (int i = 0; i < size; ++i) {
				heap.emplace_back(score[i], i);
			}

			for (int i = (size>>1)-1; i >= 0; i--) {
				heapify(heap, heap.size(), i);
			}

			const char* strs[] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
			int i = 0;
			while (!heap.empty()) {
				auto p = pop(heap);
				int index = get<1>(p);
				if (i < 3) result[index] = strs[i];
				else result[index] = to_string(i+1);
				i++;
			}

			return result;
		}
	};
}