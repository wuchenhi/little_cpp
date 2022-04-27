#ifndef MYTINYSTL_ALGOBASE_H_
#define MYTINYSTL_ALGOBASE_H_

// poorstl 的基本算法

#include <cstring>
#include <type_traits>

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
            poorstl::construct(&*cur, *first);
        }
    }
    catch (...)
    {
        for (; result != cur; --cur)
            poorstl::destroy(&*cur);
    }
    return cur;
}

template <class InputIter, class ForwardIter>
ForwardIter uninit_copy(InputIter first, InputIter last, ForwardIter result)
{
    return poorstl::unchecked_uninit_copy(first, last, result, 
                                            std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>:: value_type>{});//如果类型 Ty 是具有普通复制赋值运算符的类，则类型谓词的实例为 true；否则为 false。
}

}

#endif