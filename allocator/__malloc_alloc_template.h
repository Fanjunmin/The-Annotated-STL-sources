//2.2.5 第一级空间配置器：malloc_alloc_template
//以c语言中的malloc(),realloc(),free()等函数执行实际的内存分配与释放
//filename: __malloc_alloc_template.h
#ifndef __MALLOC_ALLOC_TEMPLATE_H_INCLUDED
#define __MALLOC_ALLOC_TEMPLATE_H_INCLUDED
# if 0
# include <new>
# define __THROW_BAD_ALLOC throw bad_alloc
#elif !define(__THROW_BAD_ALLOC)
# include <iostream>
# define __THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1)
#endif // 0
template <int inst>
class __malloc_alloc_template {
private:
    //下列函数处理内存不足
    //oom:out of memory
    static void *oom_malloc(size_t);
    static void *oom_realloc(void*, size_t);
    static void (* __malloc_alloc_oom_handler)();    //函数指针

public:
    static void * allocate(size_t n)
    {
        void *result = malloc(n);   //一级配置器直接使用malloc()
        //无法分配，改用oom_malloc()
        if(0 == result) result = oom_malloc(n);
        return result;
    }

    static void deallocate(void *p, size_t /* n */)
    {
        free(p);    //一级配置器直接使用free()
    }

    static void * reallocate(void *p, size_t /* old_sz */, size_t new_sz)
    {
        void *result = realloc(p, new_sz);  //使用realloc(),p是要改变内存大小的指针名
        //无法分配，改用oom_realloc()
        if(0 == result) result = oom_realloc(p, new_sz);
        return result;
    }

    static void(* set_malloc_handler(void (*f)()))()
    {   //函数指针作为形参，返回类型也是函数指针
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return(old);
    }
};

template <int, inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int, inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (* my_malloc_handler)();
    void *result;
    for(;;) {   //不断尝试释放，配置，再释放，再配置
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)(); //调用处理例程，企图释放内存
        result = malloc(n);     //尝试重新分配内存
        if (result) return result;
    }
}

template <int, inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (* my_malloc_handler)();
    void *result;
    for(;;) {   //不断尝试释放，配置，再释放，再配置
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)();     //调用处理例程，企图释放内存
        result = realloc(p, n);     //尝试重新分配内存
        if (result) return result;
    }
}

//将inst参数指定为0
typedef __malloc_alloc_oom_template<0> malloc_alloc;

#endif // __MALLOC_ALLOC_TEMPLATE_H_INCLUDED
