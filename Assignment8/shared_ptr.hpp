#pragma once

#include <stdexcept>
#include <utility>
namespace usu
{

    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr();
        shared_ptr(T* pntr);
        shared_ptr(const shared_ptr& rhs);
        shared_ptr(shared_ptr&& rhs) noexcept;
        ~shared_ptr();

        shared_ptr& operator=(const shared_ptr& rhs);
        shared_ptr& operator=(shared_ptr&& rhs);
        T* operator->();
        T operator*();

        T* get() { return m_ptr; };
        int use_count() { return *m_refCount; };

        unsigned int* m_refCount;
        T* m_ptr;
    };

    // Constructors
    template <typename T>
    shared_ptr<T>::shared_ptr()
    {
        shared_ptr(nullptr);
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(T* ptr)
    {
        m_ptr = ptr;
        m_refCount = new unsigned int;
        *m_refCount = 1;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr& rhs)
    {
        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;
        *m_refCount += 1;
    }

    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr&& rhs) noexcept
    {
        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;

        rhs.m_ptr = nullptr;
        rhs.m_refCount = nullptr;
    }

    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        if (m_refCount == nullptr)
        {
            return;
        }
        else if (*m_refCount == 1)
        {
            delete m_ptr;
            delete m_refCount;
        }
        else
        {
            *m_refCount -= 1;
        }
    }
    // Operators

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs)
    {
        this->~shared_ptr();

        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;
        *m_refCount += 1;

        return *this;
    }

    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_refCount, rhs.m_refCount);

        return *this;
    }

    template <typename T>
    T* shared_ptr<T>::operator->()
    {
        return m_ptr;
    }

    template <typename T>
    T shared_ptr<T>::operator*()
    {
        return *m_ptr;
    }

    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        shared_ptr();
        shared_ptr(T* list, int size);
        shared_ptr(const shared_ptr& rhs);
        shared_ptr(shared_ptr&& rhs);
        ~shared_ptr();

        shared_ptr& operator=(const shared_ptr& rhs);
        shared_ptr& operator=(shared_ptr&& rhs);
        T& operator[](int index);

        T* get() { return m_ptr; };
        int use_count() { return *m_refCount; };
        unsigned int size() { return m_size; }

        int m_size;
        unsigned int* m_refCount;
        T* m_ptr;
    };

    // Constructors

    template <typename T>
    shared_ptr<T[]>::shared_ptr()
    {
        shared_ptr(nullptr, 0);
    }

    template <typename T>
    shared_ptr<T[]>::shared_ptr(T* list, int size)
    {
        m_size = size;
        m_ptr = list;
        m_refCount = new unsigned int;
        *m_refCount = 1;
    }

    template <typename T>
    shared_ptr<T[]>::shared_ptr(const shared_ptr& rhs)
    {
        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;
        *m_refCount += 1;
        m_size = rhs.m_size;
    }

    template <typename T>
    shared_ptr<T[]>::shared_ptr(shared_ptr&& rhs)
    {
        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;
        m_size = rhs.m_size;

        rhs.m_ptr = nullptr;
        rhs.m_refCount = nullptr;
        rhs.m_size = nullptr;
    }

    template <typename T>
    shared_ptr<T[]>::~shared_ptr()
    {
        if (m_refCount == nullptr)
        {
            return;
        }
        else if (*m_refCount == 1)
        {
            delete[] m_ptr;
            delete m_refCount;
        }
        else
        {
            *m_refCount -= 1;
        }
    }

    // Operators

    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(const shared_ptr<T[]>& rhs)
    {
        this->~shared_ptr();

        m_ptr = rhs.m_ptr;
        m_refCount = rhs.m_refCount;
        *m_refCount += 1;
        m_size = rhs.m_size;

        return *this;
    }

    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(shared_ptr&& rhs)
    {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_refCount, rhs.m_refCount);
        std::swap(m_size, rhs.m_size);

        return *this;
    }

    template <typename T>
    T& shared_ptr<T[]>::operator[](int index)
    {
        if (index > m_size || index < 0)
        {
            throw std::out_of_range("Array index out of range");
        }
        else
        {
            return *(m_ptr + index);
        }
    }

    // Make shared functions
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
} // namespace usu
