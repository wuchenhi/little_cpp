#ifndef m_ITERATOR_H
#define m_ITERATOR_H

//iterator 能依序巡访容器的各个元素，又无需暴露该容器的内部表述方式
//iterator 最重要的就是对 oparator* operator-> 重载
#include <cstddef>   //ptrdiff_t

namespace poorstl
{

//五种迭代器类型 
//通过继承，不必再写“单纯只做传递调用”的函数
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

//iterator 模板
template <class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&>
    struct iterator
{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Distance    difference_type;
};

//traits
template <class Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    //如果Iterator有自己的value type，那么traits出来的value_type 就是 Iterator::value_type
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::difference_type   difference_type;
};

//偏特化版，迭代器是原生指针
template <class T>
struct iterator_traits<T*>    
{
    typedef random_access_iterator_tag   iterator_category;
    typedef T                            value_type;
    typedef T*                           pointer;
    typedef T&                           reference;
    typedef ptrdiff_t                    difference_type;
};

//偏特化版，迭代器是原生指针的引用
template <class T>
struct iterator_traits<const T*>
{
  typedef random_access_iterator_tag     iterator_category;
  typedef T                              value_type;
  typedef const T*                       pointer;
  typedef const T&                       reference;
  typedef ptrdiff_t                      difference_type;
};

//此函数可萃取某个迭代器的 category
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
    typedef typename iterator_traits<Iterator>::iterator_category  category;
    return category();
}

//此函数可萃取某个迭代器的 distance_type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 萃取某个迭代器的 value_type
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}


// distance 函数 input_iterator_tag 版本
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type    //是否需要 typename
m_distance(InputIterator first, InputIterator last, input_iterator_tag)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;         //是否需要 typename
    while (first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

// distance 函数 random_access_iterator_tag 版本
template <class RandomIter>
inline typename iterator_traits<RandomIter>::difference_type
m_distance(RandomIter first, RandomIter last,
                  random_access_iterator_tag)
{
    return last - first;
}

//distance 上层接口，调用各个重载的 m_distance
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
    typedef typename iterator_traits<InputIterator>::iterator_category  category;
    return m_distance(first, last, category());
}

// advance(让迭代器前进 n 个距离) input_iterator_tag 版本
template <class InputIterator, class Distance>
void m_advance(InputIterator& i, Distance n, input_iterator_tag)
{
    while (n--) 
        ++i;
}

// advance bidirectional_iterator_tag 版本
template <class BidirectionalIterator, class Distance>
void m_advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--)  ++i;
    else
        while (n++)  --i;
}

// advance random_access_iterator_tag 版本
template <class RandomIter, class Distance>
void m_advance(RandomIter& i, Distance n, random_access_iterator_tag)
{
    i += n;
}

//advance 上层接口,调用各个重载的 m_advance
template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n)
{
    m_advance(i, n, iterator_category(i));    //?
}



/*  测试学习用
template <class I>
typename iterator_traits<I>::value_type
func(I ite){
    return *ite;
}
*/




} // namespace poorstl
#endif

