#include <vector>
#include "../problem506/solution.cpp"
using namespace std;

static long long comparisons = 0;
static long long swaps = 0;

static void reset() {
	comparisons = 0;
	swaps = 0;
}

template<typename T>
struct Instrumented {
	T value;

	Instrumented(int v = 0) : value(v) {}

	bool operator<(const Instrumented& other) const {
		++comparisons;
		return value < other.value;
	}

	bool operator>(const Instrumented& other) const {
		++comparisons;
		return value > other.value;
	}

	bool operator!=(const Instrumented& other) const {
		return value != other.value;
	}
};

typedef Instrumented<int> CountedInt;

void swap(CountedInt& a, CountedInt& b) {
	++swaps;
	std::swap(a.value, b.value);
}

class Solution {
public:
	// quick sort [st, ed]
	void quick_sort_lomuto(vector<CountedInt>& a, int l, int r) {
		if (l >= r) return;

		int pivotIndex = l + rand() % (r - l + 1);
		swap(a[pivotIndex], a[r]);
		CountedInt pivot = a[r];

		int i = l - 1;
		for (int j = l; j < r; ++j) {
			if (a[j] < pivot) {
				swap(a[++i], a[j]);
			}
		}
		swap(a[i + 1], a[r]);
		quick_sort_lomuto(a, l, i);
		quick_sort_lomuto(a, i + 2, r);
	}

	void quick_sort_hoare(vector<CountedInt>& a, int l, int r) {
		if (l >= r) return;

		CountedInt pivot = a[l + rand() % (r - l + 1)];
		int i = l - 1, j = r + 1;

		while (true) {
			do i++; while (a[i] < pivot);
			do j--; while (a[j] > pivot);
			if (i >= j) break;
			swap(a[i], a[j]);
		}

		quick_sort_hoare(a, l, j);
		quick_sort_hoare(a, j + 1, r);
	}

	void quick_sort_3way(vector<CountedInt>& a, int l, int r) {
		if (l >= r) return;

		CountedInt pivot = a[l + rand() % (r - l + 1)];
		int lt = l, i = l, gt = r;

		while (i <= gt) {
			if (a[i] < pivot) {
				swap(a[lt++], a[i++]);
			} else if (a[i] > pivot) {
				swap(a[i], a[gt--]);
			} else { // a[i] == pivot
				i++;
			}
		}

		quick_sort_3way(a, l, lt - 1);
		quick_sort_3way(a, gt + 1, r);
	}

	void heap_sort(vector<CountedInt>& a) {
		using namespace problem506;
		for (int i = (static_cast<int>(a.size())>>1)-1; i >= 0; i--) {
			heapify<CountedInt>(a, a.size(), i);
		}
		for (int i = a.size() - 1; i > 0; --i) {
			swap(a[0], a[i]);
			heapify(a, i, 0);
		}
	}

	// vector<int> sortArray(vector<int>& nums) {
	// 	quick_sort_hoare(nums, 0, nums.size()-1);
	// 	return nums;
	// }
};