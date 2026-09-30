#pragma once

#include <cstdint>
#include <cassert>
#include <iostream>
#include <utility>

template<typename T>
class DynamicArray final
{
public:
	static constexpr int32_t defaultCapacity{ 4 };

	DynamicArray()
		: size_{ 0 }
		, capacity_{ defaultCapacity }
	{
		buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
	}

	explicit DynamicArray(const int32_t cap)
		: size_{ 0 }
		, capacity_{ cap }
	{
		buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
	}

	DynamicArray(const DynamicArray<T>& other)
		: size_{ other.size_ }
		, capacity_{ other.capacity_ }
	{
		if (capacity_ <= 0)
		{
			capacity_ = defaultCapacity;
		}

		T* p = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));

		for (int32_t i = 0; i < size_; ++i)
		{
			new (p + i) T(other.buf_[i]);
		}

		buf_ = p;
	}

	DynamicArray(DynamicArray<T>&& other) noexcept
		: buf_ { other.buf_ }
		, size_{ other.size_ }
		, capacity_{ other.capacity_ }
	{
		if (capacity_ <= 0)
		{
			capacity_ = defaultCapacity;
			buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
		}

		other.capacity_ = 0;
		other.size_ = 0;
		other.buf_ = nullptr;
	}

	~DynamicArray()
	{
		if (buf_)
		{
			for (int32_t i = 0; i < size_; ++i)
			{
				buf_[i].~T();
			}
			std::free(buf_);
		}
	}

	int32_t pushBack(const T& value)
	{
		if (capacity_ == 0)
		{
			capacity_ = defaultCapacity;
			buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
		}

		if (size_ == capacity_)
		{
			reallocate();
		}

		new (buf_ + size_) T(value);
		++size_;

		return size_;
	}

	int32_t insert(int32_t index, T& value)
	{
		if (index == size_)
		{
			pushBack(value);
			return index;
		}

		if (size_ == capacity_)
		{
			reallocate();
		}

		if (index < size_ && index >= 0)
		{
			if (size_ + 1 >= capacity_) reallocate();

			for (int32_t i = size_; i > index; --i)
			{
				new(buf_ + i) T(std::move(buf_[i - 1]));
				buf_[i - 1].~T();
			}

			new(buf_ + index) T(std::move(value));
			++size_;
		}

		return index;
	}

	void remove(const int32_t index)
	{
		if (index < size_ && index >= 0 && size_ > 0)
		{
			for (int32_t i = index; i < size_ - 1; ++i)
			{
				buf_[i].~T();
				new(buf_ + i) T(std::move(buf_[i + 1]));
			}
			buf_[size_ - 1].~T();
			--size_;
		}
	}

	DynamicArray<T>& operator=(DynamicArray<T> rhs)
	{
		if (this != &rhs)
		{
			std::swap(buf_, rhs.buf_);
			std::swap(size_, rhs.size_);
			std::swap(capacity_, rhs.capacity_);
		}

		return *this;
	}

	const T& operator[](int32_t index) const
	{
		assert(index >= 0 && index < size_);
		return buf_[index];
	}

	T& operator[](int32_t index)
	{
		assert(index >= 0 && index < size_);
		return buf_[index];
	}

	[[nodiscard]] int32_t size() const
	{
		return size_;
	}

	[[nodiscard]] int32_t capacity() const
	{
		return capacity_;
	}

	class Iterator
	{
	public:
		Iterator()
			: iter_{ nullptr }
			, first_{ nullptr }
			, last_{ nullptr }
			, isReverse_{ false }
		{
		}

		Iterator(T* arr, int32_t size, const bool isReverse)
			: first_{ arr }
			, last_{ arr + size }
			, isReverse_{ isReverse }
		{
			if (isReverse)
			{
				iter_ = arr + size - 1;
				first_ = arr - 1;
			}
			else
			{
				iter_ = arr;
			}
		}

		const T& get() const
		{
			return *iter_;
		}

		void set(const T& value)
		{
			*iter_ = value;
		}

		[[nodiscard]] bool hasNext() const
		{
			if (isReverse_)
			{
				return iter_ > first_;
			}

			return iter_ < last_;
		}

		void next()
		{
			if (hasNext())
			{
				if (isReverse_)
				{
					--iter_;
				}
				else
				{
					++iter_;
				}
			}
		}

	private:
		T* iter_;
		T* first_;
		T* last_;
		bool isReverse_;
	};

	Iterator iterator()
	{
		return Iterator(buf_, size_, false);
	}

	Iterator reverseIterator()
	{
		return Iterator(buf_, size_, true);
	}

	class ConstIterator
	{
	public:
		ConstIterator()
			: iter_{nullptr}
			, first_(nullptr)
			, last_(nullptr)
			, isReverse_{false}
		{
		}

		ConstIterator(T* arr, int32_t size, const bool isReverse)
			: iter_{ nullptr }
			, first_{ arr }
			, last_{ arr + size }
			, isReverse_{ isReverse }
		{
			if (isReverse)
			{
				iter_ = arr + size - 1;
				first_ = arr - 1;
			}
			else
			{
				iter_ = arr;
			}
		}

		const T& get() const
		{
			return *iter_;
		}

		[[nodiscard]] bool hasNext() const
		{
			if (isReverse_)
			{
				return iter_ > first_;
			}

			return iter_ < last_;
		}

		void next()
		{
			if (hasNext())
			{
				if (isReverse_)
				{
					--iter_;
				}
				else
				{
					++iter_;
				}
			}
		}

	private:
		const T* iter_;
		const T* first_;
		const T* last_;
		bool isReverse_;
	};

	ConstIterator iterator() const
	{
		return ConstIterator(buf_, size_, false);
	}

	ConstIterator reverseIterator() const
	{
		return ConstIterator(buf_, size_, true);
	}

private:
	T* buf_;
	int32_t size_;
	int32_t capacity_;

	void reallocate()
	{
		capacity_ = (capacity_ > 0) ? capacity_ * 2 : defaultCapacity;
		T* p = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));

		for (int32_t i = 0; i < size_; ++i)
		{
			new (p + i) T(std::move(buf_[i]));
			buf_[i].~T();
		}

		std::free(buf_);
		buf_ = p;
	}
};
