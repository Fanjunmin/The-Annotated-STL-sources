//2.2.6 第二级配置器的实现
//filename:__default_alloc_template.h
#ifndef __DEFAULT_ALLOC_TEMPLATE_H_INCLUDED
#define __DEFAULT_ALLOC_TEMPLATE_H_INCLUDED
#include "__malloc_alloc_template.h"

enum{__ALIGN = 8};  //小型区块的上调边界
enum{__MAX_BYTES = 128};    //小型区块的上界
enum{__NFREELISTS = __MAX_BYTES/_ALIGN};    //free-lists个数

//第二级配置器
//第一参数用于多线程

template <bool threads, int inst>
class __default_alloc_template
{
private:
    //将bytes上调到8的倍数: (bytes+7)&~7
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
    }
private:
    union obj { //free-lists结点的构造
        union obj * free_list_link;
        char client_data[1];
    };
private:
    //16个free-lists
    static obj * volatile free_lists[__NFREELISTS];
    static size_t FREELISTS_INDEX(size_t bytes) {
        return (((bytes) + __ALIGN-1)/__ALIGN - 1);
    }
    //为freelist重新填充空间
    void refill(size_t n);
    //从内存池取空间给freelist使用
    char* chunk_alloc(size_t size, int &nobjs);
    static char *start_free;    //内存池的起始位置
    static char *end_free;      //内存池的结束位置
    static size_t heap_size;

public:
    static void * allocate(size_t n)
    {
        obj * volatile * my_free_list;  //obj ** my_free_list;
        obj * result;
        //大于128就调用一级配置器
        if(n > (size_t) __MAX_BYTES) {
            return malloc_alloc::allocate(n);
        }
        //寻找16个free_list中合适一个
        my_free_list = free_list + FREELIST_INDEX(n);
        result = *my_free_list;
        if(result == 0) {
            //没有找到可用的free list,准备重新填充free list
            void *r = refill(ROUND_UP(n));
            return r;
        }
        //调整freelist
        *my_free_list = result -> free_list_link;
        return (result);
    }
    static void deallocate(void *p, size_t n) {
        // p非空
        obj *q = p;
        obj * volatile * my_free_list;
        if (n >= (size_t)__MAX_BYTES) {
            //大于128就调用一级配置器的deallocate()
            malloc_alloc::deallocate(p, n);
            return;
        }
        my_free_list = free_list + FREELIST_INDEX(n);
        q -> free_list_link = *my_free_list;
        *my_free_list = q;
    }
    static void * reallocate (void *p, size_t old_sz, size_t new_sz);
};

//static data member的初值设定
template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::obj * volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] =
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}

//下面两个函数真没看懂。。。。。
template <bool threads, int inst>
void * __default_alloc_template<threads, inst>::refill(size_t n)
{
    int nobjs = 20;
    char* chunk = chunk_alloc(n, nobjs);
    obj * volatile * my_free_list;
    obj * result;
    obj * current_obj, * next_obj;
    int i;
    //只获得一个区块，分配给调用者，free list无新节点
    if (1 == nobjs) return (chunk);
    //调整free list 纳入新节点
    my_free_list = free_list + FREELIST_INDEX(n);
    *my_free_list = next_obj = (obj *)(chunk + n);
    for (int i = 1; ;i++) {
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        if (nobjs - 1 == i) {
            current_obj -> free_list_link = 0;
            break;
        }
        else {
            current_obj -> free_list_link = next_obj;
        }
    }
    return (result);
}

template <bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs)
{
    //假设size是8倍数，注意nobjs是pass by reference
    char * result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;  //内存池的剩余空间
    if (bytes_left >= total_bytes) {
        //内存池满足需求时
        result = start_free;
        start_free += total_bytes;
        return (results);
    }
    else if (bytes_left >= size) {
        //内存池足够供应一个及以上的区块
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return (result);
    }
    else {
        //内存池无法供应一个区块
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        if (bytes_left > 0) {
            //内存池还有一些零头
            obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj *)start_free) -> free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }
        //配置heap空间，补充内存池
        start_free = (char *)malloc(bytes_to_get);
        if (0 == start_free) {
            //heap空间不足，malloc失败
            int i;
            obj * volatile * my_free_list, *p;
            for (i = size; i <= __MAX_BYTES; i += __ALIGNS) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p) {
                    *my_free_list = p -> free_list_link;
                    start_free = (char *) p;
                    end_free = start_free + i;
                    return (chunk_alloc(size, nobjs));
                }
            }
            end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return (chunk_alloc(size, nobjs));
    }
}

#endif // __DEFAULT_ALLOC_TEMPLATE_H_INCLUDED
