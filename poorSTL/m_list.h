#ifndef m_LIST_H
#define m_LIST_H

#include "m_iterator.h"
#include "m_allocator.h"
#include "m_algo.h"

namespace poorstl
{

//双向链表节点
template <class T>
struct list_node
{
    typedef list_node<T>* node_pointer;
    node_pointer prev;
    node_pointer next;
    T data;

    list_node() = default;
    list_node(const T& value)
      :data(value), prev(nullptr), next(nullptr)
    {
    }

    void break_link()
    {
      prev = next = self();
    }

    node_pointer self()
    {
        return static_cast<node_pointer>(&*this);
    }
};

//list迭代器 双向链表，所以迭代器类型为 bidirectional_iterator_tag
template <class T>
struct list_iterator : public poorstl::iterator<poorstl::bidirectional_iterator_tag, T>
{
    typedef T                                 value_type;
    typedef T*                                pointer;
    typedef T&                                reference;
    typedef list_iterator<T>                  iterator;
    typedef bidirectional_iterator_tag        iterator_category;
    typedef size_t                            size_type;
    typedef ptrdiff_t                         difference_type;
    typedef list_node<T>*                     node_pointer;

    node_pointer node_;  // 指向当前节点

    // 构造函数
    list_iterator() = default;
    list_iterator(node_pointer x)
        :node_(x) {}
    list_iterator(const list_iterator& rhs)
        :node_(rhs.node_) {}

    // 重载操作符
    reference operator*()  const { return node_->data; }
    pointer   operator->() const { return &(operator*()); }

    iterator& operator++()
    {
        node_ = node_->next;
        return *this;
     }
    iterator operator++(int)
    {
        iterator tmp = *this;
        ++*this;
        return tmp;
    }
    iterator& operator--()
    {
        node_ = node_->prev;
        return *this;
    }
    iterator operator--(int)
    {
        iterator tmp = *this;
        --*this;
        return tmp;
    }

    // 重载比较操作符
    bool operator==(const iterator& rhs) const { return node_ == rhs.node_; }
    bool operator!=(const iterator& rhs) const { return node_ != rhs.node_; }
};

//模板类: list
template <class T>
class list
{
public:
    // list 的嵌套型别定义
    typedef poorstl::allocator<T>                    allocator_type;
    typedef poorstl::allocator<T>                    data_allocator;
    typedef poorstl::allocator<list_node<T>>         node_allocator;

    typedef typename allocator_type::value_type      value_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef list_iterator<T>                         iterator;

    typedef list_node<T>                             list_node;
    typedef list_node*                               node_pointer;
    allocator_type get_allocator() { return node_allocator(); }

private:
    node_pointer  node_;  // 指向末尾节点
    size_type     size_;  // 大小

public:
    // 构造、复制、移动、析构函数
    list() 
    { fill_init(0, value_type()); }

    explicit list(size_type n) 
    { fill_init(n, value_type()); }

    list(size_type n, const T& value)
    { fill_init(n, value); }

    template <class Iter, typename std::enable_if<poorstl::is_input_iterator<Iter>::value, int>::type = 0> list(Iter first, Iter last)
    { copy_init(first, last); }

    list(const list& rhs)
    { copy_init(rhs.cbegin(), rhs.cend()); }

    list(list&& rhs) noexcept
        :node_(rhs.node_), size_(rhs.size_)
    {
    rhs.node_ = nullptr;
    rhs.size_ = 0;
    }

    list& operator=(const list& rhs)
    {
        if (this != &rhs)
    {
      assign(rhs.begin(), rhs.end());
    }
    return *this;
    }

    list& operator=(list&& rhs) noexcept
    {
        clear();
        splice(end(), rhs);
        return *this;
    }

    ~list()
    {
        if (node_)
        {
            clear();
            node_allocator::deallocate(node_);
            node_ = nullptr;
            size_ = 0;
        }
    }

    // 容器与 [first, last] 结点断开连接
    void unlink_nodes(node_pointer first, node_pointer last)
    {
        first->prev->next = last->next;
        last->next->prev = first->prev;
    }

    // 在 pos 处连接 [first, last] 的结点
    void link_nodes(node_pointer pos, node_pointer first, node_pointer last)
    {
        pos->prev->next = first;
        first->prev = pos->prev;
        pos->prev = last;
        last->next = pos;
    }

    void list<T>::splice(const_iterator pos, list& x, const_iterator it)
    {
        if (pos.node_ != it.node_ && pos.node_ != it.node_->next)
        {
            auto f = it.node_;

            x.unlink_nodes(f, f);
            link_nodes(pos.node_, f, f);

            ++size_;
            --x.size_;
        }
    }

    template <class ...Args>
    node_pointer create_node(Args&& ...agrs)
    {
        node_pointer p = node_allocator::allocate(1);
        try
        {
            data_allocator::construct(poorstl::address_of(p->value), poorstl::forward<Args>(args)...);
            p->prev = nullptr;
            p->next = nullptr;
        }
        catch (...)
        {
            node_allocator::deallocate(p);
            throw;
        }
        return p;
    }

    void destroy_node(node_pointer p)
    {
        data_allocator::destroy(poorstl::address_of(p->value));
        node_allocator::deallocate(p);
    }

    // 在尾部连接 [first, last] 结点
    void link_nodes_at_back(node_pointer first, node_pointer last)
    {
        last->next = node_;
        first->prev = node_->prev;
        first->prev->next = first;
        node_->prev = last;
    }

    // 用 n 个元素初始化容器
    void fill_init(size_type n, const value_type& value)
    {
        node_ = node_allocator::allocate(1);
        node_->unlink();
        size_ = n;
        try
        {
            for (; n > 0; --n)
            {
                auto node = create_node(value);
                link_nodes_at_back(node, node);
            }
        }
        catch (...)
        {
            clear();
            node_allocator::deallocate(node_);
            node_ = nullptr;
            throw;
        }
    }

    //清空
    void clear()
    {
        if (size_ != 0)
        {
            auto cur = node_->next;
            for (node_pointer next = cur->next; cur != node_; cur = next, next = cur->next)
            {
                destroy_node(cur);
            }
            node_->unlink();
            size_ = 0;
        }
    }
public:
    // 迭代器相关操作
    iterator begin()  noexcept  //环状，node指向末端的空白节点
    { return node_->next; }
    iterator end()    noexcept 
    { return node_; }

    // 容量相关操作
    bool      empty()    const noexcept //末尾=头
    { return node_->next == node_; }

    size_type size()     const noexcept 
    { return size_; }           

    // 访问元素相关操作
    reference       front() 
    { 
        return *begin();
    }

    const_reference front() const 
    { 
        eturn *begin(); 
    }

    reference       back() 
    { 
        return *(--end());
    }

    const_reference back()  const 
    { 
        return *(--end());
    }

};

}
#endif