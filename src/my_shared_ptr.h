#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

#include<cstdio>

template<typename T>
class my_shared_ptr
{
private:
	T* shared_ptr_;
	static int refcount_ ;

public:
	my_shared_ptr() : shared_ptr_(nullptr) {  }

	my_shared_ptr(T* shared_ptr) : shared_ptr_(shared_ptr) {
		/*if (shared_ptr_ != shared_ptr_) {
			shared_ptr_ == shared_ptr_
		}*/
		printf("constructor call, refcount: %d", refcount_);

		refcount_++;

		printf("ref count increased to %d \n", refcount_);
	}

	~my_shared_ptr() {
		refcount_--;
		if (refcount_ <= 0) {
			refcount_ = 0;
			delete shared_ptr_;
		}
	}

	my_shared_ptr(my_shared_ptr & ptr) {
		this->shared_ptr_ = ptr.get();
		refcount_++;
	}


	T* get() const { return shared_ptr_; }
	int refcount() { return refcount_; }

	T & operator*() const
	{
		return  *shared_ptr_;
	}
	T* operator->() {
		return shared_ptr_;
	}
	
	/*
    Overload the operator =.
    When overwriting one my_shared_ptr with another one (p = q), the following steps
    need to be taken:

    *    p loses its link to its current pointee. So, it must first decrease
         its refcount, check if it reaches 0, and if so, free the pointee and refcount.
         In other words, this steps mimics the destructor.

    *    p then copies q's members and increases the refcount. This mimics the copy constructor.
	*/
	void operator=(const my_shared_ptr<T> & other)
	{
		refcount_--;
		if (refcount_ <= 0) {
			refcount_ = 0;
			// delete shared_ptr_;
			// shared_ptr_ = nullptr;
		}

		this->shared_ptr_ = other.get();
		refcount_++;
	}

};




template<typename T>
int my_shared_ptr<T>::refcount_ = 0;

#endif // !MY_SHARED_PTR_H
