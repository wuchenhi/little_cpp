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

    typedef list_node<T>*                            node_pointer;

    allocator_type get_allocator() { return node_allocator(); }

private:
    node_pointer  node_;  // 指向末尾节点
    //size_type     size_;  // 大小       不需要

public:
    // 构造、复制、移动、析构函数
    //默认构造，不设元素值
    list() 
    {
        init_empty();
    }

    list(const T& value) 
    {
        init_empty();
        insert(end(), value);
    }

    list(size_type n, const T& value) 
    {
        init_empty();
        for(; n>0; --n)
            insert(end(), value);
    }

/*
    template <class Iter, typename std::enable_if<poorstl::is_input_iterator<Iter>::value, int>::type = 0> list(Iter first, Iter last)
    { 
        init_empty();
        init_copy(first, last); 
    }
*/
    list(list& rhs)
    { 
        init_empty();
        init_copy(rhs.begin(), rhs.end()); 
    }


    list(list&& rhs) noexcept
        :node_(rhs.node_)
    {
        rhs.node_ = nullptr;
    }

    list& operator=(list& rhs) noexcept
    {
        if (this != &rhs){
            clear();
            init_copy(rhs.begin(), rhs.end());
        }
        return *this;
    }

    //右值版本，rhs将被splice清空
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
        }
    }

    void push_front(const T& value){
        insert(begin(), value);
    }

    void push_back(const T& value){
        insert(end(), value);
    }

    void pop_front(){
        erase(begin());
    }

    void pop_back(){
        iterator tmp = end();
        erase(--tmp);
    }

    //清空
    void clear()
    {
        if (node_->next != node_)  //不为空
        {
            //头节点
            auto cur = node_->next;
            for (node_pointer next = cur->next; cur != node_; cur = next, next = cur->next)
            {
                destroy_node(cur);
            }
            node_->break_link();
        }
    }

    //移除值为value 的节点
    void remove(const T& value){
        iterator begin_ = begin();
        iterator end_   = end();
        while(begin_ != end_){
            iterator next = begin_;
            ++next;
            if(*begin_ == value) {
                erase(begin_);
            }
            begin_ = next;
        }
    }

    //删除 连续相同元素 只保留一个
    void unique(){
        if(node_->next == node_)
            return;
        iterator begin_ = begin();
        iterator end_   = end();
        iterator next = begin_;
        while(++next != end_){
            if(*begin_ == * next)
                erase(next);
            else
                begin_ = next;
            next = begin();  //修正next
        }
    }

    //接合，x接合于pos之前
    void splice(iterator pos, list& x)
    {
        if(!x.empty())
            trans(pos, x.begin(), x.end());
    }

    //接合，it所指元素接合于pos之前
    void splice(iterator pos, list&, iterator it)
    {
        auto tmp = it;
        ++tmp;
        if(pos == it || pos == tmp)
            return;
        trans(pos, it, tmp);
    }

    //接合，it所指元素接合于pos之前
    void splice(iterator pos, list&, iterator begin_, iterator end_)
    {
        if (begin_ != end_)
            trans(pos, begin_, end_);
    }

    //x 合并到*this,两者必须已经递增排序
    void merge(list& x)
    {
        iterator begin1 = begin();
        iterator end1 = end();
        iterator begin2 = x.begin();
        iterator end2 = x.end();

        while (begin1 != end1 && begin2 != end2)
        {
            if(*begin1 > *begin2){
                iterator next = begin2;
                trans(begin1, begin2, ++next);
                begin2 = next;
            }else
                ++begin1;
            if(begin2 != end2) 
                trans(end1, begin2, end2);
        }
    }

    void reverse()
    {
        //空或只有一个元素，返回
        if(node_->next == node_ || node_->next->next == node_)
            return;
        iterator begin_ = begin();
        ++begin_;
        while (begin_ != end())
        {
            iterator tmp = begin_;
            ++begin_;
            trans(begin(), tmp, begin_);
        } 
    }

    //不能使用STL的sort，只接受 RamdonAcessIterator
    void sort(){
        //空或只有一个元素，返回
        if(node_->next == node_ || node_->next->next == node_)
            return;
        //TODO
    }
protected:

    void init_empty()
    {
        node_ = node_allocator::allocate(1);
        node_->next = node_;
        node_->prev = node_;
    }

    //在pos位置插入值为value节点
    iterator insert(iterator pos, const T& value)
    {
        node_pointer tmp = create_node(value);
        //常规插入tmp
        tmp->next = pos.node_;
        tmp->prev = pos.node_->prev; 
        pos.node_->prev->next = tmp;
        pos.node_->prev = tmp;
        return static_cast<iterator>(tmp);
    }

    //删除pos位置节点
    iterator erase(iterator pos)
    {
        //常规删除
        node_pointer node_next = pos.node_->next;
        node_pointer node_prev = pos.node_->prev;
        node_prev->next = node_next;
        node_next->prev = node_prev;
        destroy_node(pos.node_);
        return static_cast<iterator>(node_next);
    }

    //产生一个节点
    node_pointer create_node(const T& value)
    {
        node_pointer p = node_allocator::allocate(1);
        try
        {
            data_allocator::construct(data_allocator::addr(p->data), value);
            p->prev = p;
            p->next = p;
        }
        catch (...)
        {
            node_allocator::deallocate(p);
            throw;
        }
        return p;
    }

    //销毁一个节点
    void destroy_node(node_pointer p)
    {
        data_allocator::destroy(data_allocator::addr(p->data));
        node_allocator::deallocate(p);
    }

    //迁移操作
    void trans(iterator pos, iterator begin_, iterator end_){
        if(pos != end_){
           (*(*end_.node_).prev).next = pos.node_;
           (*(*begin_.node_).prev).next = end_.node_;
           (*(*pos.node_).prev).next = begin_.node_;
           node_pointer tmp = (*pos.node_).prev;
           (*pos.node_).prev = (*end_.node_).prev;
           (*end_.node_).prev = (*begin_.node_).prev;
           (*begin_.node_).prev = tmp;
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

    // 在尾部连接 [first, last] 结点
    void link_nodes_at_back(node_pointer first, node_pointer last)
    {
        last->next = node_;
        first->prev = node_->prev;
        first->prev->next = first;
        node_->prev = last;
    }

    // 以 [first, last) 初始化容器
    void init_copy(iterator first, iterator last)
    {
        iterator begin_ = begin();
        size_type n = poorstl::distance(first, last);
        try
        {
            for (; n > 0; --n, ++first, ++begin_)
            {
                insert(end(), first.node_->data);
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

public:
    // 迭代器相关操作
    iterator begin()  noexcept  //环状，node指向末端的空白节点
    { return node_->next; }

    //TODO
    const iterator cbegin()  const noexcept
    { return begin(); }

    const iterator cend()   const noexcept 
    { return node_; }

    iterator end()    noexcept 
    { return node_; }

    // 容量相关操作
    bool      empty()    const noexcept
    { return node_->next == node_; }

    size_type size()     noexcept //const
    { 
        size_type ans = 0;
        ans = static_cast<size_type>(distance(begin(), end()));
        return ans;
    }           

    // 访问元素相关操作
    reference       front() 
    { 
        return *begin();
    }

    const_reference front() const 
    { 
        return *begin(); 
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