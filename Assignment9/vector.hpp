#pragma once
#include <functional>
#include <initializer_list>
#include <memory>
#include <stdexcept>

const std::size_t DEFAULT_CAPACITY = 10;
const std::function<std::size_t(std::size_t)> DEFAULT_RESIZE = [](std::size_t currentCapacity) -> std::size_t
{
    return currentCapacity * 2;
};

namespace usu
{

    template <typename T>
    class vector
    {
      public:
        using size_type = std::size_t;
        using reference = T&;
        using pointer = std::shared_ptr<T[]>;
        using value_type = T;
        using resize_type = std::function<size_type(size_type)>;

        vector();
        vector(size_type size);
        vector(resize_type resize);
        vector(size_type size, resize_type resize);
        vector(std::initializer_list<T> list);
        vector(std::initializer_list<T> list, resize_type resize);

        reference operator[](size_type index);
        void add(value_type value);
        void insert(size_type index, value_type value);
        void remove(size_type index);
        void clear();

        size_type size();
        size_type capacity();

        class iterator
        {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            using size_reference = std::shared_ptr<size_type*>;

            iterator(pointer ptr, size_type size, size_reference parentSize);
            iterator(pointer ptr, size_type size, size_reference parentSize, size_type index);
            iterator(const iterator& obj);
            iterator(iterator&& obj) noexcept;

            iterator operator++();
            iterator operator++(int);

            iterator operator--();
            iterator operator--(int);

            iterator& operator=(const iterator& rhs);
            iterator& operator=(iterator&& rhs);

            reference operator*();
            value_type* operator->();

            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);

          private:
            size_type m_index;
            size_type m_dataSize;
            pointer m_data;
            size_reference m_parentSize;
        };

        usu::vector<T>::iterator begin();
        usu::vector<T>::iterator end();

      private:
        size_type m_size;
        size_type m_capacity;
        resize_type m_resize;
        pointer m_pointer;
        void increaseCap();
    };

    template <>
    class vector<bool>
    {
      public:
        using size_type = std::size_t;
        using pointer = std::shared_ptr<std::uint8_t[]>;
        using value_type = bool;
        using resize_type = std::function<size_type(size_type)>;

        class reference
        {
          public:
            reference(pointer data, size_type index, size_type bitIndex);
            reference(const reference& obj);
            reference(reference&& obj) noexcept;

            reference& operator=(const value_type& rhs);
            reference& operator=(value_type&& rhs) noexcept;

            operator bool();

          private:
            value_type getIndex();
            void setIndex(value_type value);
            size_type m_index;
            size_type m_bitIndex;
            pointer m_data;
        };
        class iterator
        {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            using size_reference = std::shared_ptr<size_type*>;

            iterator(pointer ptr, size_type size, size_reference parentSize);
            iterator(pointer ptr, size_type size, size_reference parentSize, size_type index, size_type bitIndex);
            iterator(const iterator& obj);
            iterator(iterator&& obj) noexcept;

            iterator operator++();
            iterator operator++(int);

            iterator operator--();
            iterator operator--(int);

            iterator& operator=(const iterator& rhs);
            iterator& operator=(iterator&& rhs) noexcept;

            reference operator*();

            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);

          private:
            size_type m_index;
            size_type m_bitIndex;
            size_type m_dataSize;
            pointer m_data;
            size_reference m_parentSize;
        };

        vector();
        vector(size_type size);
        vector(resize_type resize);
        vector(size_type size, resize_type resize);
        vector(std::initializer_list<bool> list);
        vector(std::initializer_list<bool> list, resize_type resize);

        reference operator[](size_type index);
        void add(value_type value);
        void insert(size_type index, value_type value);
        void remove(size_type index);
        void clear();

        size_type size();
        size_type capacity();

        iterator begin();
        iterator end();

      private:
        pointer m_pointer;
        size_type m_size;
        size_type m_capacity;
        resize_type m_resize;
        void increaseCap();
        size_type getActualSize(size_type capacity);
    };

    // Constructors
    template <typename T>
    usu::vector<T>::vector() :
        vector(0)
    {
    }

    template <typename T>
    usu::vector<T>::vector(size_type size) :
        vector(size, DEFAULT_RESIZE)
    {
    }

    template <typename T>
    usu::vector<T>::vector(resize_type resize) :
        vector(0, resize)
    {
    }

    template <typename T>
    usu::vector<T>::vector(size_type size, resize_type resize) :
        m_size(size), m_resize(resize)
    {
        m_capacity = (size > DEFAULT_CAPACITY) ? size * 2 : DEFAULT_CAPACITY;

        m_pointer = std::make_shared<T[]>(m_capacity);
    }

    template <typename T>
    usu::vector<T>::vector(std::initializer_list<T> list) :
        vector(list, DEFAULT_RESIZE)
    {
    }

    template <typename T>
    usu::vector<T>::vector(std::initializer_list<T> list, resize_type resize) :
        m_resize(resize), m_size(0), m_capacity(DEFAULT_CAPACITY)
    {
        m_pointer = std::make_shared<T[]>(m_capacity);
        for (auto i = list.begin(); i < list.end(); i++)
        {
            this->add(*i);
        }
    }

    // Operators
    template <typename T>
    typename usu::vector<T>::reference usu::vector<T>::operator[](size_type index)
    {
        if (index >= m_size)
        {
            throw std::range_error("Index out of range");
        }

        return m_pointer[index];
    }

    // Methods
    template <typename T>
    void usu::vector<T>::add(value_type value)
    {
        if (m_size == m_capacity)
        {
            usu::vector<T>::increaseCap();
        }

        m_pointer[m_size++] = value;
    }

    template <typename T>
    void usu::vector<T>::insert(size_type index, value_type value)
    {
        if (index > m_size)
        {
            throw std::range_error("Insert index out of range");
        }
        if (m_size == m_capacity)
        {
            usu::vector<T>::increaseCap();
        }

        m_size++;
        auto counter = index;
        auto curr = value;
        while (counter < m_size)
        {
            auto temp = m_pointer[counter];
            m_pointer[counter] = curr;
            curr = temp;
            counter++;
        }
    }

    template <typename T>
    void usu::vector<T>::remove(size_type index)
    {
        if (index >= m_size)
        {
            throw std::range_error("Remove index out of range");
        }

        auto counter = index;
        while (counter < m_size - 1)
        {
            m_pointer[counter] = m_pointer[counter + 1];
            counter++;
        }
        m_size--;
    }

    template <typename T>
    void usu::vector<T>::clear()
    {
        m_size = 0;
    }

    template <typename T>
    typename usu::vector<T>::size_type usu::vector<T>::size()
    {
        return m_size;
    }

    template <typename T>
    typename usu::vector<T>::size_type usu::vector<T>::capacity()
    {
        return m_capacity;
    }

    template <typename T>
    void usu::vector<T>::increaseCap()
    {
        m_capacity = m_resize(m_capacity);
        auto temp_array = std::make_shared<T[]>(m_capacity);
        for (size_type i = 0; i < m_size; i++)
        {
            temp_array[i] = m_pointer[i];
        }
        m_pointer = temp_array;
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::begin()
    {
        return iterator(m_pointer, m_size, std::make_shared<size_type*>(&m_size));
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::end()
    {
        return iterator(m_pointer, m_size, std::make_shared<size_type*>(&m_size), m_size);
    }

    // Iterator

    template <typename T>
    usu::vector<T>::iterator::iterator(pointer ptr, size_type size, size_reference parentSize) :
        iterator(ptr, size, parentSize, 0)
    {
    }

    template <typename T>
    usu::vector<T>::iterator::iterator(pointer ptr, size_type size, size_reference parentSize, size_type index) :
        m_data(ptr), m_dataSize(size), m_index(index), m_parentSize(parentSize)
    {
    }

    template <typename T>
    usu::vector<T>::iterator::iterator(const iterator& obj)
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;
        this->m_dataSize = obj.m_dataSize;
        this->m_parentSize = obj.m_parentSize;
    }

    template <typename T>
    usu::vector<T>::iterator::iterator(iterator&& obj) noexcept
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;
        this->m_dataSize = obj.m_dataSize;
        this->m_parentSize = obj.m_parentSize;

        obj.m_data = nullptr;
        obj.m_index = 0;
        obj.m_dataSize = 0;
        obj.m_parentSize = nullptr;
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::iterator::operator++()
    {
        if (m_index >= m_dataSize)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        m_index++;
        return *this;
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::iterator::operator++(int)
    {
        if (m_index >= m_dataSize)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        iterator i = *this;
        m_index++;
        return i;
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::iterator::operator--()
    {
        if (static_cast<int>(m_index) - 1 < 0)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        m_index--;
        return *this;
    }

    template <typename T>
    typename usu::vector<T>::iterator usu::vector<T>::iterator::operator--(int)
    {
        if (static_cast<int>(m_index) - 1 < 0)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        iterator i = *this;
        m_index--;
        return i;
    }

    template <typename T>
    typename usu::vector<T>::iterator& usu::vector<T>::iterator::operator=(const iterator& rhs)
    {
        this->m_data = rhs.m_data;
        this->m_index = rhs.m_index;
        this->m_dataSize = rhs.m_dataSize;
        this->m_parentSize = rhs.m_parentSize;
        return *this;
    }

    template <typename T>
    typename usu::vector<T>::iterator& usu::vector<T>::iterator::operator=(iterator&& rhs)
    {
        this->m_data = rhs.m_data;
        this->m_index = rhs.m_index;
        this->m_dataSize = rhs.m_dataSize;
        this->m_parentSize = rhs.m_parentSize;

        rhs.m_index = 0;
        rhs.m_data = nullptr;
        rhs.m_dataSize = 0;
        rhs.m_parentSize = nullptr;
        return *this;
    }

    template <typename T>
    typename usu::vector<T>::reference usu::vector<T>::iterator::operator*()
    {
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        return m_data[m_index];
    }

    template <typename T>
    typename usu::vector<T>::value_type* usu::vector<T>::iterator::operator->()
    {
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        return &m_data[m_index];
    }

    template <typename T>
    bool usu::vector<T>::iterator::operator==(const iterator& rhs)
    {
        return (this->m_data == rhs.m_data && this->m_index == rhs.m_index);
    }

    template <typename T>
    bool usu::vector<T>::iterator::operator!=(const iterator& rhs)
    {
        return !(*this == rhs);
    }

} // namespace usu