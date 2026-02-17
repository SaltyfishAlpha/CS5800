#include <algorithm>
#include <cassert>
#include <map>

#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

bool checksort(const vector<CountedInt>& answer, const vector<CountedInt>& sorted) {
    for (auto i = answer.begin(), j = sorted.begin();
        i != answer.end() && j != sorted.end(); ++i, ++j) {
        if (*i != *j) return false;
    }
    return true;
}

template<typename Func>
void runTest(const string& name,
             Func sorter,
             const vector<CountedInt>& nums,
             const vector<CountedInt>& answer)
{
    srand(0);
    vector<CountedInt> arr(nums);

    reset();

    {
        leetcode::ScopedTimer timer(name);
        sorter(arr);
    }

    assert(checksort(answer, arr));

    cout << name
         << "\nComparisons: " << comparisons
         << ", Swaps: " << swaps
         << "\n\n";
}


void quickTest(Solution& solution,
               const vector<CountedInt>& nums,
               const string& generation_type)
{
    vector<CountedInt> answer(nums);
    sort(answer.begin(), answer.end());

    runTest("Quick Sort in Lomuto - " + generation_type,
        [&](auto& arr){
            solution.quick_sort_lomuto(arr, 0, arr.size() - 1);
        }, nums, answer);

    runTest("Quick Sort in Hoare - " + generation_type,
        [&](auto& arr){
            solution.quick_sort_hoare(arr, 0, arr.size() - 1);
        }, nums, answer);

    runTest("Quick Sort in Three-way - " + generation_type,
        [&](auto& arr){
            solution.quick_sort_3way(arr, 0, arr.size() - 1);
        }, nums, answer);

    runTest("Heap Sort - " + generation_type,
        [&](auto& arr) {
            solution.heap_sort(arr);
        }, nums, answer);

    cout<<"------------------------------------"<<endl;
}

LEETCODE_MAIN_BEGIN("problem912")
    // std::cout.tie(&std::cerr);

    // string line;
    // getline(cin, line);
    // vector<int> nums = leetcode::parseIntVector(line);

    // auto result = solution.sortArray(nums);

    // Generate random arr
    int constexpr SIZE = 100'000;
    vector<CountedInt> num(SIZE);

    srand(0);
    // random gereration
    for (int i = 0; i < SIZE; ++i)
        num[i] = rand();

    quickTest(solution, num, "random");

    srand(0);
    // duplicate elements gereration
    for (int i = 0; i < SIZE; ++i)
        num[i] = rand() % 10;

    quickTest(solution, num, "duplicate elements");

    // reserve order generation
    for (int i = 0; i < SIZE; ++i)
        num[i] = SIZE-i;

    quickTest(solution, num, "reserve ordered");

    // sorted generation
    for (int i = 0; i < SIZE; ++i)
        num[i] = i;

    quickTest(solution, num, "sorted");

LEETCODE_MAIN_END
