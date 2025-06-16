#pragma once
#include <iostream>

template <typename T>
class PolymorphicPtr
{
public:
	PolymorphicPtr();
	PolymorphicPtr(T* ptr);
	PolymorphicPtr(const PolymorphicPtr<T>& other);
	PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
	PolymorphicPtr<T>& operator=(const PolymorphicPtr<T>& other);
	PolymorphicPtr<T>& operator=(PolymorphicPtr<T>&& other) noexcept;

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;

	void reset(T* ptr);

	~PolymorphicPtr();
private:
	T* data;
	void free();
	void CopyFrom(const PolymorphicPtr<T>& other);
	void MoveFrom(PolymorphicPtr<T>&& other);
};


template <typename T>
void PolymorphicPtr<T>::free()
{
	delete data;
}

template <typename T>
void PolymorphicPtr<T>::CopyFrom(const PolymorphicPtr<T>& other)
{
	this->data = other.data->clone();
}

template <typename T>
void PolymorphicPtr<T>::MoveFrom(PolymorphicPtr<T>&& other)
{
	this->data = other.data;
	other.data = nullptr;
}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr() : data(nullptr)
{

}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : data(ptr)
{

}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other)
{
	CopyFrom(other);
}

template <typename T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept
{
	MoveFrom(std::move(other));
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other)
{
	if (this != &other)
	{
		free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		MoveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
T* PolymorphicPtr<T>::operator->()
{
	return data;
}

template <typename T>
const T* PolymorphicPtr<T>::operator->() const
{
	return data;
}

template <typename T>
T& PolymorphicPtr<T>::operator*()
{
	if (data == nullptr) throw std::runtime_error("Pointer was nullptr.");
	return (*data);
}

template <typename T>
const T& PolymorphicPtr<T>::operator*() const
{
	if (data == nullptr) throw std::runtime_error("Pointer was nullptr.");
	return (*data);
}

template <typename T>
PolymorphicPtr<T>::~PolymorphicPtr()
{
	free();
}


template <typename T>
PolymorphicPtr<T>::operator bool() const
{
	return data != nullptr;
}

template <typename T>
void PolymorphicPtr<T>::reset(T* ptr)
{
	if (this->data != ptr)
	{
		free();
		this->data = ptr;
	}
}