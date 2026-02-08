#ifndef SPARESET_H
#define SPARESET_H

#include <numeric>

template<class T>
class SparseSet
{
public:
    explicit SparseSet(size_t capacity)
        : _index(capacity)
		, _capacity(capacity)
        , _id(capacity)
        , _data(capacity)
        , _size(0)
		, _max_size_ever(0)
    {}

    explicit SparseSet(const std::vector<T>& nums)
        : _index(nums.size())
		, _capacity(nums.size())
        , _id(nums.size())
        , _data(nums)
        , _size(nums.size())
		, _max_size_ever(nums.size())
    {
        std::iota(_index.begin(), _index.end(), 0);
        std::iota(_id.begin(), _id.end(), 0);
    }

    SparseSet(const SparseSet&) = default;
    SparseSet(SparseSet&&) noexcept = default;
    SparseSet& operator=(const SparseSet&) = default;
    SparseSet& operator=(SparseSet&&) noexcept = default;
    ~SparseSet() = default;

	// Iterators
	auto begin() { return _data.begin(); }
	auto end() { return _data.begin() + _size; }
	auto begin() const { return _data.begin(); }
	auto end() const { return _data.end() + _size; }

	auto id_begin() const { return _id.begin(); }
	auto id_end() const { return _id.begin() + _size; }

    [[nodiscard]] std::vector<size_t> activeIds() const {
        return {_id.begin(), _id.begin() + _size};
    }

	template<typename Func>
    void forEachWithId(Func&& func) {
        for (size_t i = 0; i < _size; ++i) {
            func(_id[i], _data[i]);
        }
    }

	// insert an element and return the its ID
    size_t insert(const T& value)
    {
		if (_size >= _capacity)
		    throw std::out_of_range("SparseSet is full");

	    // assert(_size < _capacity);

		if (_size >= _max_size_ever) {
			_index[_size] = _size;
			_id[_size] = _size;
			++_max_size_ever;
		}
		_data[_size] = std::move(value);
		++_size;
		return _id[_size-1];
    }

    void erase(size_t id)
    {
        if (!contains(id)) {
            throw std::out_of_range("Invalid id for erase");
        }
	    // assert(_size < _capacity);

        if (_index[id] == _size - 1) {
            --_size;
            return;
        }

        std::swap(_data[_index[id]], _data[_size-1]);
        std::swap(_id[_index[id]], _id[_size-1]);
        std::swap(_index[_id[_size-1]], _index[_id[_index[id]]]);
        --_size;
    }

    const T& valueOf(size_t id) const
    {
        if (!contains(id)) {
            throw std::out_of_range("Invalid id");
        }
        return _data[_index[id]];
    }

    void setValue(size_t id, const T& value)
    {
        if (!contains(id)) {
            throw std::out_of_range("Invalid id");
        }
        _data[_index[id]] = std::move(value);
    }

    T& operator[](size_t id)
    {
        if (!contains(id)) {
            throw std::out_of_range("Invalid id");
        }
        return _data[_index[id]];
    }

    const T& operator[](size_t id) const
    {
        if (!contains(id)) {
            throw std::out_of_range("Invalid id");
        }
        return _data[_index[id]];
    }

    [[nodiscard]] bool contains(size_t id) const noexcept
    {
        return id < _max_size_ever && _index[id] < _size;
    }

	[[nodiscard]] size_t size() const noexcept { return _size; }
	[[nodiscard]] size_t capacity() const noexcept { return _capacity; }
    [[nodiscard]] bool empty() const noexcept { return _size == 0; }

    void clear() noexcept
    {
        _size = 0;
		_max_size_ever = 0;
    }

private:

    std::vector<size_t> _index; // id -> index
    std::vector<size_t> _id; // index -> id
    std::vector<T> _data; // data
    size_t _size;
	size_t _max_size_ever;
	size_t _capacity;
};

#endif //SPARESET_H
