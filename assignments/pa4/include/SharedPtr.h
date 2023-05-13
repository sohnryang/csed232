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

	// Default constructor. Same as SharedPtr(nullptr).
	SharedPtr() : SharedPtr(nullptr) {}

	// Constructor with raw pointer.
	explicit SharedPtr(ObjectType *ptr) : m_object(ptr) {
		if (m_object == nullptr) // check if we are pointing to null pointer
			m_ref_counter = nullptr; // null pointers need not refcount
		else
			m_ref_counter = new int(1);
	}

	// Copy constructor, though this only does shallow-copy.
	SharedPtr(const SharedPtr<ObjectType, Dealloc> &sptr)
		: m_object(sptr.m_object), m_ref_counter(sptr.m_ref_counter) {
		if (m_ref_counter != nullptr)
			*m_ref_counter += 1; // increment refcount
	}

	////////////////////////////////////////////
	// Assignment operator
	////////////////////////////////////////////
	
	// ======= ADD CODE HERE IF NEEDED =========

	// Assignment operator.
	SharedPtr<ObjectType, Dealloc> &operator=(const SharedPtr<ObjectType, Dealloc> &that) {
		if (&that == this) // check self-assignment
			return *this;
		// Check if we were managing null pointer
		if (m_object != nullptr) {
			*m_ref_counter -= 1; // decrement refcount
			if (*m_ref_counter == 0) { // dealloc if refcount is zero
				Dealloc(m_object);
				delete m_ref_counter;
			}
		}
		m_object = that.m_object; // copy pointer
		m_ref_counter = that.m_ref_counter; // copy refcount pointer
		if (m_ref_counter != nullptr) // if we are managing non-null pointer
			*m_ref_counter += 1; // increment refcount
		return *this;
	}
	
	////////////////////////////////////////////
	// Pointer operators
	////////////////////////////////////////////
	// operator->
	// operator*

	// ======= ADD CODE HERE IF NEEDED =========

	// Pointer reference operator.
	ObjectType &operator*() { return *m_object; }

	// Pointer reference operator, const version.
	const ObjectType &operator*() const { return *m_object; }

	// Pointer member access operator.
	ObjectType *operator->() { return m_object; }

	// Pointer member access operator, const version.
	const ObjectType *operator->() const { return m_object; }
	
	////////////////////////////////////////////
	// Array element access operators
	////////////////////////////////////////////
	// operator[]
	
	// ======= ADD CODE HERE IF NEEDED =========

	// Index operator, const version.
	ObjectType &operator[](int index) { return m_object[index]; }

	// Index operator.
	const ObjectType &operator[](int index) const { return m_object[index]; }

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

	// Typecast operator.
	operator ObjectType *() const { return m_object; }

	// Typecast operator, const version.
	operator ObjectType const *() const {
		return static_cast<ObjectType const *>(m_object);
	}

	// Destructor.
	~SharedPtr() {
		// Check if we were managing null pointer.
		if (m_object == nullptr)
			return;

		*m_ref_counter -= 1; // decrement refcount
		if (*m_ref_counter == 0) { // dealloc if refcount is zero
			Dealloc(m_object);
			delete m_ref_counter;
		}
	}
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif
