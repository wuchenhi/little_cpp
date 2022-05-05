#ifndef MYTINYSTL_ALGOBASE_H_
#define MYTINYSTL_ALGOBASE_H_

// poorstl 的基本算法

#include <cstring>
#include <type_traits>

#include <cstddef>

#include "m_iterator.h"

namespace poorstl{


// equal，比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
template <class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)  
            return false;
    }
    return true;
}

// copy
// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
// input_iterator_tag 版本
template <class InputIter, class OutputIter>
OutputIter 
copy_tag(InputIter first, InputIter last, OutputIter result, 
                   poorstl::input_iterator_tag)
{
    for (; first != last; ++first, ++result)
    {
        *result = *first;
    }
    return result;
}

// ramdom_access_iterator_tag 版本
template <class RandomIter, class OutputIter>
OutputIter 
copy_tag(RandomIter first, RandomIter last, OutputIter result,
                   poorstl::random_access_iterator_tag)
{
  for (auto n = last - first; n > 0; --n, ++first, ++result)
  {
        *result = *first;
  }
  return result;
}

// input_iterator_tag 版本
template <class InputIter, class OutputIter>
OutputIter 
copy_tag_backward(InputIter first, InputIter last, OutputIter result, 
                   poorstl::input_iterator_tag)
{
    for (auto n = last -first; n>0; --n)
    {
        *--result = *--last;
    }
    return result;
}

// ramdom_access_iterator_tag 版本
template <class RandomIter, class OutputIter>
OutputIter 
copy_tag_backward(RandomIter first, RandomIter last, OutputIter result,
                   poorstl::random_access_iterator_tag)
{
    while (first != last)
        *--result = *--last;
    return result;
}

template <class InputIter, class OutputIter>
OutputIter copy_backward(InputIter first, InputIter last, OutputIter result)
{
    return copy_tag_backward(first, last, result, iterator_category(first));
}

template <class InputIter, class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result)
{
    return copy_tag(first, last, result, iterator_category(first));
}

// uninitialized_copy
// 把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
/*****************************************************************************************/
template <class InputIter, class ForwardIter>
ForwardIter 
unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
{
    return poorstl::copy(first, last, result);
}

template <class InputIter, class ForwardIter>
ForwardIter
unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
{
    auto cur = result;
    try
    {
        for (; first != last; ++first, ++cur)
        {
            poorstl::_construct(&*cur, *first);
        }
    }
    catch (...)
    {
        for (; result != cur; --cur)
            poorstl::_destroy(&*cur);
    }
    return cur;
}

template <class InputIter, class ForwardIter>
ForwardIter uninit_copy(InputIter first, InputIter last, ForwardIter result)
{
    return poorstl::unchecked_uninit_copy(first, last, result, 
                                            std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>:: value_type>{});//如果类型 Ty 是具有普通复制赋值运算符的类，则类型谓词的实例为 true；否则为 false。
}

// move
template <class T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward
template <class T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept
{
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T&&>(arg);
}

// swap
template <class Tp>
void swap(Tp& lhs, Tp& rhs)
{
    auto tmp(poorstl::move(lhs));
    lhs = poorstl::move(rhs);
    rhs = poorstl::move(tmp);
}

}
#endif