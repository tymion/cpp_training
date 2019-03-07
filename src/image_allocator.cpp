#include "image_factory.h"

template<class T> inline T*
ImageAllocator<T>::allocate(size_t n)
{
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template<class T> inline void
ImageAllocator<T>::deallocate(T* p, size_t n)
{
    ::operator delete(p);
}

template<class T, class U> inline bool
operator ==(ImageAllocator<T> const&, ImageAllocator<U> const&) noexcept
{
    return true;
}

template<class T, class U> inline bool
operator !=(ImageAllocator<T> const&, ImageAllocator<U> const&) noexcept
{
    return false;
}

template<class T> inline void
destroy(T *p)
{
    p->~T();
//    alloc.destory(p);
}

