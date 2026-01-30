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
		: capacity_{ defaultCapacity }
		, size_{ 0 }
	{
		buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
	}

	DynamicArray(int32_t cap)
		: capacity_{ cap }
		, size_{ 0 }
	{
		buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
	}

	DynamicArray(const DynamicArray<T>& other)
		: capacity_{ other.capacity_ }
		, size_{ other.size_ }
	{
		std::cout << "Copied" << std::endl;

		if (capacity_ <= 0)
		{
			capacity_ = defaultCapacity;
		}

		T* p = static_cast<T*>(malloc(capacity_ * sizeof(T)));

		for (int32_t i = 0; i < size_; ++i)
		{
			new (p + i) T(other.buf_[i]);
		}

		buf_ = p;
	}

	DynamicArray(DynamicArray<T>&& other)
		: capacity_{ other.capacity_ }
		, size_{ other.size_ }
		, buf_ { other.buf_ }
	{
		std::cout << "Moved" << std::endl;

		if (capacity_ <= 0)
		{
			capacity_ = defaultCapacity;
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
			free(buf_);
		}
	}

	int32_t pushBack(const T& value)
	{
		if (capacity_ == 0)
		{
			capacity_ = defaultCapacity;
			buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
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
		}

		if (size_ == capacity_)
		{
			reallocate();
		}

		if (index < size_ && index >= 0)
		{
			T* temp = static_cast<T*>(malloc(capacity_ * sizeof(T)));

			for (int32_t i = 0; i < index; ++i)
			{
				new (temp + i) T(std::move(buf_[i]));
				buf_[i].~T();
			}

			new (temp + index) T(std::move(value));
			++size_;

			for (int32_t j = index + 1; j < size_; ++j)
			{
				new (temp + j) T(std::move(buf_[j - 1]));
				buf_[j - 1].~T();
			}

			free(buf_);
			buf_ = temp;
		}

		return index;
	}

	void remove(int32_t index)
	{
		if (index <= size_ - 1 && index >= 0 && size_ > 0)
		{
			T* temp = static_cast<T*>(malloc(capacity_ * sizeof(T)));

			for (int32_t i = 0; i < index; ++i)
			{
				new (temp + i) T(std::move(buf_[i]));
			}

			--size_;

			for (int32_t j = index; j < size_; ++j)
			{
				new (temp + j) T(std::move(buf_[j + 1]));
			}

			free(buf_);
			buf_ = temp;
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
		return buf_[index];
	}

	T& operator[](int32_t index)
	{
		assert(index >= 0 && index < size_);
		return buf_[index];
	}

	int32_t size() const
	{
		return size_;
	}

	int32_t capacity() const
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

		Iterator(T* arr, int32_t size, bool isReverse)
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

		bool hasNext() const
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
			: iter_{ nullptr }
			, isReverse_{ false }
		{
		}

		ConstIterator(T* arr, int32_t size, bool isReverse)
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

		bool hasNext() const
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
		capacity_ *= 2;
		T* p = static_cast<T*>(malloc(capacity_ * sizeof(T)));

		for (int32_t i = 0; i < size_; ++i)
		{
			new (p + i) T(std::move(buf_[i]));
			buf_[i].~T();
		}

		free(buf_);
		buf_ = p;
	}
};
