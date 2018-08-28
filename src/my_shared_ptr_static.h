#ifndef my_shared_ptr_static_H
#define my_shared_ptr_static_H

#include<cstdio>

template<typename T>
class my_shared_ptr_static
{
private:
	T* shared_ptr_;
	static int refcount_ ;

	void release() {
		refcount_--;
		if (refcount_ <= 0) {
			refcount_ = 0;
			delete shared_ptr_;
		}
	}
public:
	explicit my_shared_ptr_static() : shared_ptr_(nullptr) {  }

	explicit my_shared_ptr_static(T* shared_ptr) : shared_ptr_(shared_ptr) {
		/*if (shared_ptr_ != shared_ptr_) {
			shared_ptr_ == shared_ptr_
		}*/
		printf("constructor call, refcount: %d ", refcount_);

		refcount_++;

		printf("ref count increased to %d \n", refcount_);
	}
	explicit my_shared_ptr_static(const my_shared_ptr_static<T> & ptr) {
		this->shared_ptr_ = ptr.get();
		refcount_++;
	}

	~my_shared_ptr_static() {
		release();
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
    When overwriting one my_shared_ptr_static with another one (p = q), the following steps
    need to be taken:

    *    p loses its link to its current pointee. So, it must first decrease
         its refcount, check if it reaches 0, and if so, free the pointee and refcount.
         In other words, this steps mimics the destructor.

    *    p then copies q's members and increases the refcount. This mimics the copy constructor.
	*/
	my_shared_ptr_static<T>& operator=(T* p){
        if (shared_ptr_ != p){
            shared_ptr_ = p;
            // refcount_ = 1;
        }
        return *this;
    }
	my_shared_ptr_static<T>& operator=(const my_shared_ptr_static<T> & other)
	{
		if (shared_ptr_ == nullptr && other.get() ==nullptr) {
			return *this;
		} else if (shared_ptr_ == nullptr && other.get() != nullptr) {
			shared_ptr_ = other.get();
			refcount_++;
		} else if (shared_ptr_ != nullptr && other.get() == nullptr) {
			shared_ptr_ = nullptr;
			release();
		}

		// if (this != &other) {
		// 	// this->refcount_--;
		// 	if (refcount_ <= 0) {
		// 		refcount_ = 0;
		// 		delete shared_ptr_;
		// 		// shared_ptr_ = nullptr;
		// 	}

		// 	this->shared_ptr_ = other.get();
		// 	this->refcount_++;
		// }
		
		return *this;
		
	}

};




template<typename T>
int my_shared_ptr_static<T>::refcount_ = 0;

#endif // !my_shared_ptr_static_H
