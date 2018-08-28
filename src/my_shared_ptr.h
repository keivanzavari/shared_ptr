#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

#include<cstdio>
#include <stdlib.h>
/* Reference Count: A simple class for maanging the number of active smart pointers*/
class ReferenceCount
{
private:
    int refcount_{ 0 };
public:

    ReferenceCount() {refcount_=0;}
    void increment()
    {
        ++refcount_;
    }
    int decrement()
    {
        return --refcount_;
    }
    int getCount() const
    {
        return refcount_;
    }
};


template<typename T>
class my_shared_ptr
{
private:
    T* shared_ptr_ ;
    ReferenceCount* refcount_ptr_;


    void release() {
        if (refcount_ptr_) {
            refcount_ptr_->decrement();
            if (refcount_ptr_->getCount() <= 0) {
                delete refcount_ptr_;
                delete shared_ptr_;
            }
        }
    }

    ReferenceCount * getRefCountPtr() const {
        return refcount_ptr_;
    }
public:
    my_shared_ptr(): shared_ptr_(nullptr), refcount_ptr_(nullptr) {}

    explicit my_shared_ptr(T* shared_ptr) : 
    shared_ptr_(shared_ptr),
    refcount_ptr_(new ReferenceCount())
    {
        // printf("constructor call, refcount: %d ", refcount_ptr_->getCount());

        refcount_ptr_->increment();

        // printf("ref count increased to %d \n", refcount_ptr_->getCount() );
    }

    explicit my_shared_ptr(my_shared_ptr<T> & other) :
    shared_ptr_{ other.shared_ptr_ } ,
    refcount_ptr_{ other.refcount_ptr_ }
    {
        // shared_ptr_ = ptr.get();
        if (refcount_ptr_ != nullptr)
            refcount_ptr_->increment();
            // printf("ref count is nullptr" );
            // refcount_ptr_ = new ReferenceCount();

    }

    ~my_shared_ptr() {
        release();
    }



    T* get() const { return shared_ptr_; }
    int refcount() { return refcount_ptr_->getCount(); }

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
    my_shared_ptr<T>& operator=(my_shared_ptr<T> & other)
    {
        if (shared_ptr_ == nullptr && other.get() == nullptr) {
            // printf("both rhs & lhs are nullptr");
            return *this;
        } else if (shared_ptr_ == nullptr && other.get() != nullptr) {
            // printf("lhs is nullptr & rhs is not");
            // printf("\nrefcount of rhs: %d",other.refcount());

            // release();
            // shared_ptr_ = malloc(sizeof(T*));
            // refcount_ptr_ = malloc(sizeof(ReferenceCount*));
            shared_ptr_   = other.get();
            refcount_ptr_ = other.getRefCountPtr();
            refcount_ptr_->increment();
            return *this;
        } else if (shared_ptr_ != nullptr && other.get() == nullptr) {
            // printf("lhs is not nullptr & rhs is");

            release();
            shared_ptr_ = nullptr;
            refcount_ptr_ = nullptr;
            return *this;
        } else {
            release();
            shared_ptr_   = other.get();
            refcount_ptr_ = other.getRefCountPtr();
            refcount_ptr_->increment();

            return *this;
        }

        // if (this != &other) {
        //  // this->refcount_--;
        //  if (refcount_ <= 0) {
        //      refcount_ = 0;
        //      delete shared_ptr_;
        //      // shared_ptr_ = nullptr;
        //  }

        //  this->shared_ptr_ = other.get();
        //  this->refcount_++;
        // }
        
        
    }

};




// template<typename T>
// int my_shared_ptr<T>::refcount_ = 0;

#endif // !MY_SHARED_PTR_H
