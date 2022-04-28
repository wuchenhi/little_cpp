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
    delete Mem;
    //::operator delete Mem;
}

//placement new
template <class T1, class T2>
inline void _construct(T1* p, const T2& value)
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
    allocator() = default;        //default constructor

    allocator(const allocator& ) = default;    //copy constructor
    ~allocator() = default;
    //static 不用构建对象即可调用
    //内存配置
    static pointer allocate(size_type n, const void* addr = 0)  //第二参数是提示，增进区域性或忽略
    {
        return _allocate((difference_type)n, (pointer)0);
    }
    //内存释放
    static void deallocate(pointer p)
    {
        _deallocate(p);
    }
    //内存释放  重载版本
    static void deallocate(pointer p, size_type n)
    {
        for(; n>0; --n)
            _deallocate(p+n);
    }
    //对象构造
    static void construct(pointer p, const T& value) //== new ((void*)p)  T(x) 
    {
        _construct(p, value);
    }
    //对象构造  重载版本
    static void construct(pointer p, size_type n, const T& value) //== new ((void*)p)  T(x) 
    {
        for(size_type i=0; i < n; ++i){
            _construct(p+i, value);
        }
    }

    //对象析构
    static void destroy(pointer p)      //== ~T()
    {
        _destroy(p);
    }  
    //对象析构 重载版本
    static void destroy(pointer first, pointer end)      //== ~T()
    {
        for( ;first != end; ++first)
            _destroy(first);
    } 

    static pointer addr(reference addr)
    {
        return (pointer)&addr;
    }

    static const_pointer const_addr(const_reference addr)
    {
        return (const_pointer)&addr;
    }

    size_type max_size() const {
        return size_type(UINT_MAX/sizeof(T));
    }
    
    };
}


#endif