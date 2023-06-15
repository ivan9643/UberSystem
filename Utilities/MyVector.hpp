#pragma once
#include <iostream>
#include <fstream>

template<typename T>
class MyVector {
	T* data = nullptr;
	size_t currentSize = 0;
	size_t capacity = 0;

	void Resize(size_t newCapacity);
	void MoveFrom(MyVector&&) noexcept;
	void CopyFrom(const MyVector<T>& other);
	void Free();
public:
	MyVector();
	explicit MyVector(size_t capacity);
	MyVector(const T* arr, size_t size);

	MyVector(const MyVector<T>& other);
	MyVector(MyVector&& other) noexcept;

	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other);

	void Print(const char* delimiter) const;

	size_t GetCapacity() const;
	size_t GetCurrentSize() const;
	size_t IndexOf(const T& el) const;
	bool IsEmpty() const;
	bool Contains(const T& el) const;

	T& operator[](size_t i);
	const T& operator[](size_t i) const;

	void Clear();
	void PushBack(const T& el);
	void PopBack();
	void Remove(const T& el);
	void Insert(size_t index, const T& el);
	void Swap(size_t i, size_t j);

	~MyVector();
};

template<typename T>
void MyVector<T>::Resize(size_t newCapacity)
{
	if (newCapacity <= capacity) throw std::runtime_error("new capacity must be > old capacity");
	T* newArr = new T[newCapacity];
	for (size_t i = 0; i < capacity; i++)
	{
		newArr[i] = data[i];
	}
	delete[] data;
	data = newArr;
	capacity = newCapacity;
}

template<typename T>
void MyVector<T>::MoveFrom(MyVector&& other) noexcept
{
	capacity = other.capacity;
	currentSize = other.currentSize;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
void MyVector<T>::CopyFrom(const MyVector<T>& other)
{
	capacity = other.capacity;
	currentSize = other.currentSize;
	data = new T[capacity];
	for (size_t i = 0; i < currentSize; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void MyVector<T>::Free()
{
	delete[] data;
	currentSize = capacity = 0;
}

template<typename T>
MyVector<T>::MyVector()
{
	capacity = 8;
	data = new T[capacity];
}

template<typename T>
MyVector<T>::MyVector(size_t capacity)
{
	this->capacity = capacity;
	this->currentSize = capacity;
	data = new T[capacity];
}

template<typename T>
MyVector<T>::MyVector(const T* arr, size_t size)
{
	currentSize = capacity = size;
	this->data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		this->data[i] = arr[i];
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	CopyFrom(other);
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept
{
	MoveFrom(std::move(other));
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other)
{
	if (this != &other)
	{
		Free();
		MoveFrom(other);
	}
	return *this;
}

template<typename T>
void MyVector<T>::Print(const char* delimiter) const
{
	if (IsEmpty()) return;
	for (size_t i = 0; i < currentSize - 1; i++)
	{
		std::cout << data[i] << delimiter;
	}
	std::cout << data[currentSize - 1];
	std::cout << std::endl;
}

template<typename T>
size_t MyVector<T>::GetCapacity() const
{
	return capacity;
}

template<typename T>
size_t MyVector<T>::GetCurrentSize() const
{
	return currentSize;
}

template<typename T>
size_t MyVector<T>::IndexOf(const T& el) const
{
	for (size_t i = 0; i < currentSize; i++)
	{
		if (data[i] == el) return i;
	}
	throw std::runtime_error("vector doesn't contain such element");
}

template<typename T>
bool MyVector<T>::IsEmpty() const
{
	return currentSize == 0;
}

template<typename T>
bool MyVector<T>::Contains(const T& el) const
{
	for (size_t i = 0; i < currentSize; i++)
	{
		if (data[i] == el) return true;
	}
	return false;
}

template<typename T>
T& MyVector<T>::operator[](size_t i)
{
	if (i >= currentSize) throw std::runtime_error("index out of range");
	return data[i];
}

template<typename T>
const T& MyVector<T>::operator[](size_t i) const
{
	if (i >= currentSize) throw std::runtime_error("index out of range");
	return data[i];
}

template<typename T>
void MyVector<T>::Clear()
{
	currentSize = 0;
}

template<typename T>
void MyVector<T>::PushBack(const T& el)
{
	if (currentSize == capacity) Resize(capacity * 2);
	data[currentSize++] = el;
}

template<typename T>
void MyVector<T>::PopBack()
{
	if (IsEmpty()) return;
	currentSize--;
}

template<typename T>
void MyVector<T>::Remove(const T& el)
{
	size_t ind = IndexOf(el);
	for (size_t i = ind; i < currentSize - 1; i++)
	{
		data[i] = data[i + 1];
	}
	currentSize--;
}

template<typename T>
void MyVector<T>::Insert(size_t index, const T& el)
{
	if (index >= currentSize) throw std::runtime_error("index out of range");
	if (currentSize == capacity) Resize(capacity * 2);
	for (size_t i = currentSize; i > index; i--)
	{
		data[i] = data[i - 1];
	}
	data[index] = el;
	currentSize++;
}

template<typename T>
void MyVector<T>::Swap(size_t i, size_t j)
{
	if (i >= currentSize || j >= currentSize) throw std::runtime_error("index out of range");
	T temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

template<typename T>
MyVector<T>::~MyVector()
{
	Free();
}
