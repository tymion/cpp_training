#pragma once
#include <memory>

//template<class T>
//static void destroy (ImageAllocator& alloc, T* p);

template<class T>
class ImageAllocator
{
    public:

        using value_type = T;

        ImageAllocator() noexcept = default;
        ImageAllocator(ImageAllocator<T> const&) noexcept;
        ~ImageAllocator() = default;

        T* allocate(size_t n);
        void deallocate(T* p, size_t n);

        void destroy(T *p);


        /*
        template<class U>
        void destroy(U *u)
        {
            u->~U();
        }
        */
};
