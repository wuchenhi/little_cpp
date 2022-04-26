#ifndef m_ALLOCATOR_H
#define m_ALLOCATOR_H

#include <new>
#include <cstddef>
#include <assert.h>
#include <climits>  //UNIT_MAX

namespace poorstl{

template <class T>
inline T* _allocate(ptrdiff_t size, T*)
{
    T* tmp =(T*) (::operator new ((size_t)(size * sizeof(T))));
    assert(tmp >= 0);
    return tmp;
}

template <class T>
inline void _deallocate(T* Mem)
{
    ::operator delete Mem;
}

//placement new
template <class T1, class T2>
inline void _construct(T1 p, const T2& value)
{
    new(p) T1(value);
}

template <class T>
inline void _destroy(T* ptr)
{
    ptr->~T();
}

template <class T>
class allocator{
public:
    typedef T            value_type;
    typedef T*           pointer;
    typedef const T*     const_pointer;
    typedef T&           reference;
    typedef const T&     const_reference;
    typedef size_t       size_type;
    typedef ptrdiff_t    difference_type;

public:
    allocator();    //default constructor
    allocator(const allocator& );    //copy constructor
    ~allocator();

    pointer allocator(size_type n, const void* addr=0)  //addr ?
    {
        return _allocate((difference_type)n, pointer(0))
    }

    void dealloctor(pointer p, size_type n)
    {
        _deallocate(p);
    }

    void construct(pointer p, const T& value) //== new ((void*)p)  T(x) 
    {
        _construct(p, value);
    }

    void construct(pointer p, size_type n, const T& value) //== new ((void*)p)  T(x) 
    {
        for(size_type i=0; i < n; ++i){
            _construct(p+i, value);
        }
    }


    void destroy(pointer p)      //== ~T()
    {
        _destroy(p);
    }  

    void destroy_n(pointer first, pointer end)      //== ~T()
    {
        for( ;first != end, ++first)
            _destroy(first);
    } 

    pointer addr(reference addr)
    {
        return (pointer)&aadr;
    }

    const_pointer const_addr(const_reference addr)
    {
        return (const_pointer)&aadr;
    }

    size_type max_size() const {
        return size_type(UNIT_MAX/sizeof(T));
    }
    
    };
}


#endif