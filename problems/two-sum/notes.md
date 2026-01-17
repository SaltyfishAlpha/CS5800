## Problem
- **Name**: Two Sum
- **Link**: (add URL)
- **Difficulty**: Easy
- **Tags**: hashmap

## Final approach (explain to future me)
- **Core insight**: store previously seen values in a map so you can find the needed complement in O(1) average time.
- **Algorithm**:
  - iterate `nums`
  - for each `nums[i]`, check whether `target - nums[i]` already exists in the map
  - if yes, return the pair of indices
  - otherwise store `nums[i] -> i`

## Complexity
- **Time**: O(n) average
- **Space**: O(n)

## Edge cases checklist
- [ ] duplicates (e.g., `[3,3]`, target `6`)
- [ ] negative numbers
- [ ] multiple valid answers (problem guarantees one)

## Implementation notes (framework)
- **Input file used**: `input.txt` / `input2.txt`
- **Parsing notes**: first line is array like `[2,7,11,15]`, second line is target.

