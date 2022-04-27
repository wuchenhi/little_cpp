#ifndef m_VECTOR_H
#define m_VECTOR_H

#include <initializer_list>
#include <string.h>

#include "m_iterator.h"
#include "m_allocator.h"
#include "m_algo.h"

#include "memory.h"

namespace poorstl
{
    template <class T>
    class vector
    {
        static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in poorstl");

    public:
        // vector 的嵌套型别定义
        typedef T             value_type;
        typedef value_type    *iterator;
        typedef value_type    *pointer;
        typedef value_type    &reference;
        typedef size_t        size_type;
        typedef ptrdiff_t     difference_type;

    private:
        typedef poorstl::allocator<T>       allocator_type;
        typedef poorstl::allocator<T>       data_allocator;

        iterator begin_; // 表示目前使用空间的头部
        iterator end_;   // 表示目前使用空间的尾部
        iterator cap_;   // 表示目前储存空间的尾部

        iterator fill_n(iterator ans,size_type n, const T &value)
        {
            if (n > 0)
            {
                std::memset(ans, (unsigned char)value, (size_t)(n));
            }
            return ans + n;
        }

        iterator allocate_and_fill(size_type n, const T &value)
        {
            iterator ans = data_allocator::allocate(n);
            fill_n(ans, n, value);
            return ans;
        }

        void init(size_type n, const T &value)
        {
            begin_ = allocate_and_fill(n ,value);
            end_ = begin_ + n;
            cap_ = end_;
        }

        public:
        // default constructor
        vector() noexcept : begin_(nullptr), end_(nullptr), cap_(nullptr) {}
        vector(size_type n, const T &value) noexcept
        {
            init(n, value);
        }

        vector(int n, const T &value) noexcept
        {
            init(n, value);
        }

        vector(long n, const T &value) noexcept
        {
            init(n, value);
        }

        explicit vector(size_type n) noexcept
        {
            init(n, T());
        }
        //destructor
        ~vector()
        {
            begin_ = end_ = cap_ = nullptr;
            destroy_and_deallocate(begin_, end_);
        }

        vector &operator=(const vector &rhs)
        {
            if (this != &rhs)
            {
                const auto len = rhs.size();
                if (size() >= len)
                {
                    auto i = poorstl::copy(rhs.begin(), rhs.end(), begin());
                    data_allocator::destroy((pointer)i, (pointer)end());
                    end_ = begin_ + len;
                }
                else
                { 
                    poorstl::copy(rhs.begin(), rhs.begin() + size(), begin_);
                    poorstl::uninit_copy(rhs.begin() + size(), rhs.end(), end_);//TODO
                    cap_ = end_ = begin_ + len;
                }
            }
            return *this;
        }

    public:
        // 迭代器相关操作
        iterator begin() noexcept
        {
            return begin_;
        }

        const iterator begin() const noexcept
        {
            return begin_;
        }

        iterator end()  noexcept
        {
            return end_;
        }
        const iterator end() const noexcept
        {
            return end_;
        }

        // 容量相关操作
        const bool empty() const noexcept
        {
            return begin_ == end_;
        }

        const size_type size() const noexcept
        {
            return static_cast<size_type>(end_ - begin_);
        }


        const size_type capacity() const noexcept
        {
            return static_cast<size_type>(cap_ - begin_);
        }

        // 访问元素相关操作
        reference operator[](size_type n) const
        {
            return *(begin_ + n);
        }

        reference at(size_type n) const
        {
            return (*this)[n];
        }

        reference front() const
        {
            return *begin_;
        }

        reference back() const
        {
            return *(end_ - 1);
        }

        pointer data() const noexcept 
        {
            return begin_; 
        }

        // 修改容器相关操作
        // push_back / pop_back
        void push_back(const value_type &value)
        {
            if(end_ != cap_){
                data_allocator::allocate(end_, value);
                end_ = value;
                ++end_;
            }
        }

        void pop_back()
        {
            --end_;
            data_allocator::destroy(end_);
        }

        // insert
        iterator insert(iterator pos, const value_type &value)
        {
            if(end != cap_){
                copy(pos +1, end_, pos);  //TODO
                data_allocator::construct(data_allocator::addr(*(begin() + pos)), value);
                begin() + pos = value;                  
                }
            ++end_;
            return pos;
        }

        iterator insert(iterator pos, size_type n, const value_type &value)
        {
            if(end + n-1 != cap_){
                copy(pos + n, end_, pos);  //TODO
                //范围操作
                data_allocator::construct(data_allocator::addr(*(begin() + pos)),n, value);
                for(int i=0; i< n; ++i)
                    begin() + pos + i  = value;                  
                }
            end_ += n; //TODO
            return pos;
        }

        // erase / clear
        iterator erase(iterator pos)
        {
            if(pos + 1 != end())
                copy(pos +1, end_, pos);
            --end_;
            data_allocator::destroy(end_);
            return pos;
        }

        iterator erase(iterator pos, size_type n)
        {
            if(pos + n != end())
                copy(pos + n, end_, pos); 
            end_ -= n;  //TODO
            data_allocator::destroy(end_ - n, end_);
            return pos;
        }

        void clear()
        { 
            erase(begin(), end()); 
        }

        // resize / reverse
        void resize(size_type new_size) { return resize(new_size, value_type()); }
        void resize(size_type new_size, const value_type &value)
        {
            if(new_size < size())
                erase(begin() + new_size, size - new_size);
            else  
                insert(end(), new_size - size, value);
        }

    private:
        // inside functions
        void destroy_and_deallocate(iterator first, iterator end);
};

// destroy_and_deallocate 函数
template <class T>
void vector<T>::destroy_and_deallocate(iterator first, iterator end)
{
    data_allocator::destroy(first, end);
    data_allocator::deallocate(first);
}


// 非成员函数，重载比较操作符
template <class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
    return lhs.size() == rhs.size() &&
        poorstl::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
{
    return !(lhs == rhs);
}

} // namespace poorstl
#endif