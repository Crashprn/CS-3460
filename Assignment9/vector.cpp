#include "vector.hpp"

#include "cmath"
namespace usu
{

    // Reference
    //
    // Constructors
    usu::vector<bool>::reference::reference(pointer data, size_type index, size_type bitIndex) :
        m_index(index), m_bitIndex(bitIndex), m_data(data)
    {
    }

    usu::vector<bool>::reference::reference(const reference& obj)
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;
    }

    usu::vector<bool>::reference::reference(reference&& obj) noexcept
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;

        obj.m_data = nullptr;
        obj.m_index = 0;
    }

    // Operators
    usu::vector<bool>::reference& usu::vector<bool>::reference::operator=(const value_type& rhs)
    {
        this->setIndex(rhs);
        return *this;
    }

    usu::vector<bool>::reference& usu::vector<bool>::reference::operator=(value_type&& rhs) noexcept
    {
        this->setIndex(rhs);
        return *this;
    }

    usu::vector<bool>::reference::operator bool()
    {
        return this->getIndex();
    }

    usu::vector<bool>::value_type usu::vector<bool>::reference::getIndex()
    {
        auto temp_byte = m_data[m_index];

        for (size_type i = 7; i > m_bitIndex; i--)
        {
            temp_byte = temp_byte % static_cast<std::uint8_t>(std::pow(2.0, i));
        }

        return !(temp_byte == temp_byte % static_cast<std::uint8_t>(std::pow(2.0, m_bitIndex)));
    }

    void usu::vector<bool>::reference::setIndex(value_type value)
    {
        auto& temp_byte = m_data[m_index];

        if (value)
        {
            temp_byte = temp_byte | static_cast<std::uint8_t>(std::pow(2.0, m_bitIndex));
        }
        else if (this->getIndex())
        {
            temp_byte = temp_byte ^ static_cast<std::uint8_t>(std::pow(2.0, m_bitIndex));
        }
    }

    // Iterator
    //
    // Constructors
    usu::vector<bool>::iterator::iterator(pointer ptr, size_type size, size_reference parentSize) :
        iterator(ptr, size, parentSize, 0, 0)
    {
    }

    usu::vector<bool>::iterator::iterator(pointer ptr, size_type size, size_reference parentSize, size_type index, size_type bitIndex) :
        m_index(index), m_bitIndex(bitIndex), m_dataSize(size), m_data(ptr), m_parentSize(parentSize)
    {
    }

    usu::vector<bool>::iterator::iterator(const iterator& obj)
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;
        this->m_bitIndex = obj.m_bitIndex;
        this->m_dataSize = obj.m_dataSize;
        this->m_parentSize = obj.m_parentSize;
    }

    usu::vector<bool>::iterator::iterator(iterator&& obj) noexcept
    {
        this->m_data = obj.m_data;
        this->m_index = obj.m_index;
        this->m_bitIndex = obj.m_bitIndex;
        this->m_dataSize = obj.m_dataSize;
        this->m_parentSize = obj.m_parentSize;

        obj.m_data = nullptr;
        obj.m_index = 0;
        obj.m_bitIndex = 0;
        obj.m_dataSize = 0;
        obj.m_parentSize = nullptr;
    }
    // Operators
    usu::vector<bool>::iterator usu::vector<bool>::iterator::operator++()
    {
        if ((8 * m_index + m_bitIndex + 1) > m_dataSize)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }

        if (m_bitIndex == 7)
        {
            m_index += 1;
            m_bitIndex = 0;
        }
        else
        {
            m_bitIndex += 1;
        }
        return *this;
    }

    usu::vector<bool>::iterator usu::vector<bool>::iterator::operator++(int)
    {
        if ((8 * m_index + m_bitIndex + 1) > m_dataSize)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        iterator i = *this;

        if (m_bitIndex == 7)
        {
            m_index += 1;
            m_bitIndex = 0;
        }
        else
        {
            m_bitIndex += 1;
        }
        return i;
    }

    usu::vector<bool>::iterator usu::vector<bool>::iterator::operator--()
    {
        if (m_index == 0 and m_bitIndex <= 0)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        if (m_bitIndex <= 0)
        {
            m_index -= 1;
            m_bitIndex = 7;
        }
        else
        {
            m_bitIndex -= 1;
        }

        return *this;
    }

    usu::vector<bool>::iterator usu::vector<bool>::iterator::operator--(int)
    {
        if (m_index == 0 and m_bitIndex <= 0)
        {
            throw std::range_error("Iterator incremented out of array range");
        }
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }

        iterator i = *this;

        if (m_bitIndex <= 0)
        {
            m_index -= 1;
            m_bitIndex = 7;
        }
        else
        {
            m_bitIndex -= 1;
        }

        return i;
    }

    usu::vector<bool>::iterator& usu::vector<bool>::iterator::operator=(const iterator& rhs)
    {
        this->m_data = rhs.m_data;
        this->m_dataSize = rhs.m_dataSize;
        this->m_index = rhs.m_index;
        this->m_bitIndex = rhs.m_bitIndex;
        this->m_parentSize = rhs.m_parentSize;
        return *this;
    }

    usu::vector<bool>::iterator& usu::vector<bool>::iterator::operator=(iterator&& rhs) noexcept
    {
        this->m_data = rhs.m_data;
        this->m_dataSize = rhs.m_dataSize;
        this->m_index = rhs.m_index;
        this->m_bitIndex = rhs.m_bitIndex;
        this->m_parentSize = rhs.m_parentSize;

        rhs.m_data = nullptr;
        rhs.m_dataSize = 0;
        rhs.m_index = 0;
        rhs.m_bitIndex = 0;
        rhs.m_parentSize = nullptr;

        return *this;
    }

    usu::vector<bool>::reference usu::vector<bool>::iterator::operator*()
    {
        if (m_dataSize != **m_parentSize)
        {
            throw std::range_error("Data for iterator has changed");
        }
        return reference(m_data, m_index, m_bitIndex);
    }

    bool usu::vector<bool>::iterator::operator==(const iterator& rhs)
    {
        return (this->m_data == rhs.m_data) && (this->m_index == rhs.m_index) && (this->m_bitIndex == rhs.m_bitIndex);
    }

    bool usu::vector<bool>::iterator::operator!=(const iterator& rhs)
    {
        return !(*this == rhs);
    }

    // Vector
    //
    // Constructors
    usu::vector<bool>::vector() :
        vector(0)
    {
    }

    usu::vector<bool>::vector(size_type size) :
        vector(size, DEFAULT_RESIZE)
    {
    }

    usu::vector<bool>::vector(resize_type resize) :
        vector(0, resize)
    {
    }

    usu::vector<bool>::vector(size_type size, resize_type resize) :
        m_size(size), m_resize(resize)
    {
        m_capacity = (size > DEFAULT_CAPACITY) ? size * 2 : DEFAULT_CAPACITY;

        m_pointer = std::make_shared<std::uint8_t[]>(this->getActualSize(m_capacity));
    }

    usu::vector<bool>::vector(std::initializer_list<bool> list) :
        vector(list, DEFAULT_RESIZE)
    {
    }

    usu::vector<bool>::vector(std::initializer_list<bool> list, resize_type resize) :
        m_size(0), m_capacity(DEFAULT_CAPACITY), m_resize(resize)
    {
        m_pointer = std::make_shared<std::uint8_t[]>(this->getActualSize(m_capacity));
        for (auto i = list.begin(); i < list.end(); i++)
        {
            this->add(*i);
        }
    }

    usu::vector<bool>::reference usu::vector<bool>::operator[](size_type index)
    {
        if (index >= m_size)
        {
            throw std::range_error("Index out of range");
        }

        size_type byteIndex = index / 8;
        size_type bitIndex = index % 8;
        return reference(m_pointer, byteIndex, bitIndex);
    }

    void usu::vector<bool>::add(value_type value)
    {
        if (m_size == m_capacity)
        {
            increaseCap();
        }
        m_size++;
        auto i = operator[](m_size - 1);

        i = value;
    }

    void usu::vector<bool>::insert(size_type index, value_type value)
    {
        if (index > m_size)
        {
            throw std::range_error("Insert index out of range");
        }
        if (m_size == m_capacity)
        {
            increaseCap();
        }

        m_size++;

        auto counter = index;
        bool curr = value;
        while (counter < m_size)
        {
            bool temp = operator[](counter).operator bool();
            operator[](counter) = curr;
            curr = temp;
            counter++;
        }
    }

    void usu::vector<bool>::remove(size_type index)
    {
        if (index >= m_size)
        {
            throw std::range_error("Remove index out of range");
        }

        auto counter = index;
        while (counter < m_size - 1)
        {
            operator[](counter) = operator[](counter + 1).operator bool();
            counter++;
        }
        m_size--;
    }

    void usu::vector<bool>::clear()
    {
        m_size = 0;
    }

    usu::vector<bool>::size_type usu::vector<bool>::size()
    {
        return m_size;
    }

    usu::vector<bool>::size_type usu::vector<bool>::capacity()
    {
        return m_capacity;
    }

    usu::vector<bool>::size_type usu::vector<bool>::getActualSize(size_type capacity)
    {
        return capacity / 8 + 1;
    }

    void usu::vector<bool>::increaseCap()
    {
        m_capacity = m_resize(m_capacity);
        auto temp_array = std::make_shared<std::uint8_t[]>(getActualSize(m_capacity));
        for (size_type i = 0; i < m_size; i++)
        {
            temp_array[i] = m_pointer[i];
        }
        m_pointer = temp_array;
    }

    usu::vector<bool>::iterator usu::vector<bool>::begin()
    {
        return iterator(m_pointer, m_size, std::make_shared<size_type*>(&m_size));
    }

    usu::vector<bool>::iterator usu::vector<bool>::end()
    {
        return iterator(m_pointer, m_size, std::make_shared<size_type*>(&m_size), getActualSize(m_size) - 1, m_size % 8);
    }

} // namespace usu
