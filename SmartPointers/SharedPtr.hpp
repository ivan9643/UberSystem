#pragma once

template<class T>
class SharedPtr {
private:

	T* data = nullptr;
	size_t* count;

	void Free();
	void CopyFrom(const SharedPtr<T>&);
	void MoveFrom(SharedPtr<T>&&);
public:
	SharedPtr();
	SharedPtr(T*);

	void Reset();

	SharedPtr(const SharedPtr<T>&);
	SharedPtr(SharedPtr<T>&&);

	const T& operator*() const;
	T& operator*();

	const T* operator->() const;
	T* operator->();

	bool operator==(const SharedPtr<T>& other);
	bool operator!=(const SharedPtr<T>& other);

	bool Unique() const;
	bool IsNullPtr() const;

	bool operator!() const;


	size_t RefCount() const;

	SharedPtr<T>& operator=(const SharedPtr<T>&);
	SharedPtr<T>& operator=(SharedPtr<T>&&) noexcept;

	~SharedPtr();
};

template<class T>
void SharedPtr<T>::Free() {
	if (count && --(*count) == 0) {
		delete data;
		delete count;
		data = nullptr;
		count = nullptr;
	}
}

template<class T>
void SharedPtr<T>::CopyFrom(const SharedPtr<T>& other) {
	data = other.data;
	count = other.count;
	(*count)++;
}

template<class T>
void SharedPtr<T>::MoveFrom(SharedPtr<T>&& other) {
	data = other.data;
	count = other.count;
	other.data = nullptr;
	other.count = nullptr;
}

template<class T>
SharedPtr<T>::SharedPtr() {
	data = nullptr;
	count = new size_t(1);
}

template<class T>
SharedPtr<T>::SharedPtr(T* ptr) {
	this->data = ptr;
	count = new size_t(1);
}

template<class T>
void SharedPtr<T>::Reset() {
	*this = SharedPtr();
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
	CopyFrom(other);
}

template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) {
	MoveFrom(std::move(other));
}

template<class T>
bool SharedPtr<T>::Unique() const {
	return RefCount() == 1;
}

template<class T>
bool SharedPtr<T>::IsNullPtr() const
{
	return data == nullptr;
}

template<class T>
bool SharedPtr<T>::operator!() const {
	return data == nullptr;
}

template<class T>
const T& SharedPtr<T>::operator*() const {
	return *data;
}

template<class T>
T& SharedPtr<T>::operator*() {
	return *data;
}

template<class T>
const T* SharedPtr<T>::operator->() const {
	return data;
}

template<class T>
T* SharedPtr<T>::operator->() {
	return data;
}

template<class T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& other)
{
	return data == other.data;
}

template<class T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& other)
{
	return !(this == other);
}

template<class T>
size_t SharedPtr<T>::RefCount() const {
	return *count;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
	if (this != &other) {
		Free();
		CopyFrom(other);
	}

	return *this;
}

template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
	if (this != &other) {
		Free();
		MoveFrom(std::move(other));
	}

	return *this;
}

template<class T>
SharedPtr<T>::~SharedPtr() {
	Free();
}
