//file: 2jjalloc.h
#ifdef _JJALLOC_
#define _JJALLOC_
#include <new>		//for placement new
#include <cstdlib>	//for ptrdiff_t, size_t
#include <climits>	//for UNIT_MAX
#include <iostream>	//for cerr
namespace JJ {

template <typename T>
inline T* _allocate(ptrdiff_t size, T*) {
	set_new_handle(0);
	T *tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if (tmp == 0) {
		cerr << "out of memory" << endl;
		exit(1);
	}
	return tmp;
}

template <typename T>
inline void _deallocate(T* buffer) {
	::operator delete(buffer);
}

template <typename T1, typename T2>
inline void _construct(T1* p, const T2& value) {
	new(p) T1(value);	//placement new. invoke ctor of T1
}

template <typename T>
inline void _destory(T* ptr) {
	ptr->~T();
}

template <typename T>
class allocter {
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef const T*	const_pointer;
	typedef T&			reference;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	//rebind allocator of type U
	template <typename U>
	struct rebind {
		typedef allocator<U> other;
	};

	//hint used for locatity
	pointer allocate(size_type n, const void* hint = 0) {
		return _allocate((difference_type)n, (pointer)0);
	}

	void deallocate(pointer p, size_type n) { _deallocate(p); }

	void construct(pointer p, const T& value) {
		_construct(p, value);
	}

	void destory(pointer p) { _destory(p); }

	pointer address(reference x) { return (pointer)&x; }

	const_pointer const_address(const_reference x) {
		return (const_pointer)&x;
	}
		
	size_type max_size() const {
		return size_type(UINT_MAX / sizeof(T));
	}
};

}	//end of namespace JJ
#endif // _JJALLOC_
