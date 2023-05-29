#include <iostream>

template <typename T>
class UniquePtr
{
	T* data;
public:
	UniquePtr(T* ptr);

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	UniquePtr(UniquePtr&&) noexcept;
	UniquePtr& operator=(UniquePtr&&) noexcept;

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();

	bool isNullPtr() const;

	~UniquePtr();
};

template <typename T>
UniquePtr<T>::UniquePtr(T* ptr) : data(ptr)
{}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept
{
	data = other.data;
	other.data = nullptr;
}
template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept
{
	if (this != &other)
	{
		delete data;
		data = other.data;
		other.data = nullptr;
	}
	return *this;
}

template <typename T>
T& UniquePtr<T>::operator*()
{
	return *data;
}

template<typename T>
const T* UniquePtr<T>::operator->() const
{
	return data;
}

template<typename T>
inline T* UniquePtr<T>::operator->()
{
	return data;
}

template<typename T>
bool UniquePtr<T>::isNullPtr() const
{
	return data == nullptr;
}

template <typename T>
const T& UniquePtr<T>::operator*() const
{
	return *data;
}

template <typename T>
UniquePtr<T>::~UniquePtr()
{
	delete data;
}