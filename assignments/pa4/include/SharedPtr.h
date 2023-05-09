#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Object" << std::endl;
	delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
	std::cout << "Dealloc Array" << std::endl;
	delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
	ObjectType* m_object;
	int* m_ref_counter;

	// ======= ADD CODE HERE IF NEEDED =========
				
public:
	////////////////////////////////////////////
	// Constructors & destructor
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	explicit SharedPtr(ObjectType *ptr) : m_object(ptr) {
		if (m_object == nullptr)
			m_ref_counter = nullptr;
		else
			m_ref_counter = new int(1);
	}
	SharedPtr(const SharedPtr<ObjectType, Dealloc> &sptr)
		: m_object(sptr.m_object), m_ref_counter(sptr.m_ref_counter) {
		if (m_ref_counter != nullptr)
			*m_ref_counter += 1;
	}
	SharedPtr() : m_object(nullptr), m_ref_counter(nullptr) {}

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========
	SharedPtr<ObjectType, Dealloc> &operator=(const SharedPtr<ObjectType, Dealloc> &that) {
		if (&that == this)
			return *this;
		if (m_object != nullptr) {
			*m_ref_counter -= 1;
			if (*m_ref_counter == 0) {
				Dealloc(m_object);
				delete m_ref_counter;
			}
		}
		m_object = that.m_object;
		m_ref_counter = that.m_ref_counter;
		if (m_ref_counter != nullptr)
			*m_ref_counter += 1;
		return *this;
	}
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	// ======= ADD CODE HERE IF NEEDED =========
	ObjectType &operator*() { return *m_object; }
	const ObjectType &operator*() const { return *m_object; }
	ObjectType *operator->() { return m_object; }
	const ObjectType *operator->() const { return m_object; }
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	// ======= ADD CODE HERE IF NEEDED =========
	const ObjectType &operator[](int index) const { return m_object[index]; }
	ObjectType &operator[](int index) { return m_object[index]; }

	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	////////////////////////////////////////////
	// Type casting operators
	////////////////////////////////////////////
	// operator ObjectType const*() const
	// operator ObjectType*()
	
	// ======= ADD CODE HERE IF NEEDED =========
	operator ObjectType const *() const {
		return static_cast<ObjectType const *>(m_object);
	}
	operator ObjectType *() const { return m_object; }
	~SharedPtr() {
		if (m_object == nullptr)
			return;
		*m_ref_counter -= 1;
		if (*m_ref_counter == 0) {
			Dealloc(m_object);
			delete m_ref_counter;
		}
	}
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
