#pragma once
#include <iostream>

template<typename T>
class Vector {
	T* arr = nullptr;
	size_t currentSize = 0;
	size_t capacity = 0;

	void Resize(size_t newCapacity);
	void CopyFrom(const Vector<T>& other); // if current has enough space dont allocate new memory !!
	void Free();
public:
	Vector();
	explicit Vector(size_t capacity);
	Vector(const T* arr, size_t size);
	Vector(const Vector<T>& other);

	Vector<T>& operator=(const Vector<T>& other);

	void Print(const char* delimiter) const;

	size_t GetCapacity() const;
	size_t GetCurrentSize() const;
	bool IsEmpty() const;

	T& operator[](size_t i);
	const T& operator[](size_t i) const;

	void Clear();
	void PushBack(const T el);
	void PopBack();
	void Insert(size_t index, const T el);
	void Swap(size_t i, size_t j);

	~Vector();
};

template<typename T>
void Vector<T>::Resize(size_t newCapacity)
{
	if (newCapacity <= capacity) throw std::runtime_error("new capacity must be > old capacity");
	T* newArr = new T[newCapacity];
	for (size_t i = 0; i < capacity; i++)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
	capacity = newCapacity;
}

template<typename T>
inline void Vector<T>::CopyFrom(const Vector<T>& other)
{
	capacity = other.capacity;
	currentSize = other.currentSize;
	arr = new T[capacity];
	for (size_t i = 0; i < currentSize; i++)
	{
		arr[i] = other.arr[i];
	}
}

template<typename T>
void Vector<T>::Free()
{
	delete[] arr;
	currentSize = capacity = 0;
}

template<typename T>
Vector<T>::Vector()
{
	capacity = 1;
	arr = new T[capacity];
}

template<typename T>
inline Vector<T>::Vector(size_t capacity)
{
	this->capcity = capacity;
	arr = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const T* arr, size_t size)
{
	currentSize = capacity = size;
	this->arr = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		this->arr[i] = arr[i];
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	CopyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template<typename T>
inline void Vector<T>::Print(const char* delimiter) const
{
	if (IsEmpty()) return;
	for (size_t i = 0; i < GetCurrentSize() - 1; i++)
	{
		std::cout << arr[i] << delimiter;
	}
	std::cout << arr[GetCurrentSize() - 1];
	std::cout << std::endl;
}

template<typename T>
size_t Vector<T>::GetCapacity() const
{
	return capacity;
}

template<typename T>
size_t Vector<T>::GetCurrentSize() const
{
	return currentSize;
}

template<typename T>
inline bool Vector<T>::IsEmpty() const
{
	return currentSize == 0;
}

template<typename T>
inline T& Vector<T>::operator[](size_t i)
{
	if (i >= currentSize) throw std::runtime_error("index out of range");
	return arr[i];
}

template<typename T>
inline const T& Vector<T>::operator[](size_t i) const
{
	if (i >= currentSize) throw std::runtime_error("index out of range");
	return arr[i];
}

template<typename T>
void Vector<T>::Clear()
{
	currentSize = 0;
}

template<typename T>
inline void Vector<T>::PushBack(const T el)
{
	if (currentSize == capacity) Resize(capacity * 2);
	arr[capacity++] = el;
}

template<typename T>
inline void Vector<T>::PopBack()
{
	if (IsEmpty()) return;
	currentSize--;
}

template<typename T>
void Vector<T>::Insert(size_t index, const T el)
{
	if (index >= currentSize) throw std::runtime_error("index out of range");
	if (currentSize == capacity) Resize(capacity * 2);
	for (size_t i = currentSize; i > index; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = el;
	currentSize++;
}

template<typename T>
void Vector<T>::Swap(size_t i, size_t j)
{
	if (i >= currentSize || j >= currentSize) throw std::runtime_error("index out of range");
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template<typename T>
Vector<T>::~Vector()
{
	Free();
}
