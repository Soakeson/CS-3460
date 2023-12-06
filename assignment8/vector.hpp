#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace usu
{
    template <typename T>
    class vector
    {
      public:
        //--- Type alias' ---
        using size_type = std::size_t;
        using reference = T&;
        using pointer = std::shared_ptr<T[]>;
        using value_type = T;
        using resize_type = std::function<size_type(size_type)>;

        // --- Iterator Definition ---
        class iterator
        {
          public:
            using iterator_category = std::bidirectional_iterator_tag;
            iterator();
            iterator(pointer ptr);
            iterator(size_type pos, pointer ptr);
            iterator(const iterator& obj);            // Copy Constructor
            iterator(iterator&& obj) noexcept;        // Move Constructor
            iterator& operator=(const iterator& rhs); // CopyAssignable
            iterator& operator=(iterator&& rhs);      // CopyAssignable, MoveAssignable
            reference operator*() { return m_data[m_pos]; };
            T* operator->() { return m_data.get() + m_pos; };
            iterator operator++();
            iterator operator++(int);
            iterator operator--();
            iterator operator--(int);
            bool operator==(const iterator& rhs) { return m_pos == rhs.m_pos; }
            bool operator!=(const iterator& rhs) { return m_pos != rhs.m_pos; }

          private:
            size_type m_pos;
            pointer m_data;
        };

        //--- Vector Constructors ---
        vector(); // Default Constructor
        vector(size_type size);
        vector(resize_type resize);
        vector(size_type size, resize_type resize);
        vector(const std::initializer_list<T>& list);
        vector(const std::initializer_list<T>& list, resize_type resize);

        //--- Vector Operators ---
        reference operator[](const unsigned int& index);

        //--- Vector Methods ---
        size_type capacity() { return m_cap; };
        size_type size() { return m_size; };
        void remove(size_type index);
        void insert(size_type index, T value);
        void add(T value);
        void clear();
        iterator begin();
        iterator end();

      private:
        const size_type DEFAULT_INITIAL_CAPACITY = 10;
        pointer m_array;
        size_type m_size;
        size_type m_cap;
        void resize();
        resize_type m_resize =
            [](size_type currentCapacity) -> size_type
        {
            return currentCapacity * 2;
        };
    };

    // --- ITERATOR DEFINITIONS ---
    template <typename T>
    vector<T>::iterator::iterator() :
        iterator(nullptr) // DefaultConstructable
    {
    }

    template <typename T>
    vector<T>::iterator::iterator(pointer ptr) :
        m_data(ptr),
        m_pos(0)
    {
    }

    template <typename T>
    vector<T>::iterator::iterator(size_type pos, pointer ptr) :
        m_pos(pos),
        m_data(ptr)
    {
    }

    template <typename T>
    vector<T>::iterator::iterator(const iterator& obj)
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
    }

    template <typename T>
    vector<T>::iterator::iterator(iterator&& obj) noexcept
    {
        this->m_pos = obj.m_pos;
        this->m_data = obj.m_data;
        obj.m_pos = 0;
        obj.m_data = nullptr;
    }

    template <typename T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(const iterator& rhs)
    {
        this->m_pos = rhs.m_pos;
        this->m_data = rhs.m_data;
        return *this;
    }

    template <typename T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(iterator&& rhs)
    {
        if (this != &rhs)
        {
            std::swap(this->m_pos, rhs.m_pos);
            std::swap(this->m_data, rhs.m_data);
        }
        return *this;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::iterator::operator++()
    {
        m_pos++;
        return *this;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::iterator::operator++(int)
    {
        iterator i = *this;
        m_pos++;
        return i;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::iterator::operator--()
    {
        m_pos--;
        return *this;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::iterator::operator--(int)
    {
        iterator i = *this;
        m_pos--;
        return i;
    }

    // --- VECTOR DEFINITIONS ---
    template <typename T>
    vector<T>::vector()
    {
        m_size = 0;
        m_cap = DEFAULT_INITIAL_CAPACITY;
        m_array = std::make_shared<T[]>(m_cap);
    };

    template <typename T>
    vector<T>::vector(size_type size) :
        vector()
    {
        this->m_size = size;
        if (size >= DEFAULT_INITIAL_CAPACITY)
        {
            this->m_cap = size * 2;
            this->m_array = std::make_shared<T[]>(this->m_cap);
        }
    };

    template <typename T>
    vector<T>::vector(resize_type resize) :
        vector()
    {
        this->m_resize = resize;
    }

    template <typename T>
    vector<T>::vector(size_type size, resize_type resize) :
        vector()
    {
        this->m_resize = resize;
        this->m_size = size;
        if (size >= DEFAULT_INITIAL_CAPACITY)
        {
            this->m_cap = size * 2;
            this->m_array = std::make_shared<T[]>(this->m_cap);
        }
    }

    template <typename T>
    vector<T>::vector(const std::initializer_list<T>& list) :
        vector()
    {
        for (auto&& i = list.begin(); i != list.end(); i++)
        {
            this->add(*i);
        }
    }

    template <typename T>
    vector<T>::vector(const std::initializer_list<T>& list, resize_type resize) :
        vector()
    {
        this->m_resize = resize;
        for (auto&& i = list.begin(); i != list.end(); i++)
        {
            this->add(*i);
        }
    }

    template <typename T>
    typename vector<T>::reference vector<T>::operator[](const unsigned int& index)
    {
        if (index >= m_size)
        {
            throw std::range_error{ "Index out of bounds." };
        }
        return m_array[index];
    }

    template <typename T>
    void vector<T>::resize()
    {
        m_cap = m_resize(m_cap);
        pointer rep = std::make_shared<T[]>(m_cap);
        for (size_type i = 0; i < m_size; i++)
        {
            rep[i] = m_array[i];
        }
        m_array = rep;
    }

    template <typename T>
    void vector<T>::add(T value)
    {
        if (m_size >= m_cap)
        {
            this->resize();
        }
        m_array[m_size] = value;
        m_size++;
    }

    template <typename T>
    void vector<T>::insert(size_type index, T value)
    {
        if (index > m_size)
        {
            throw std::range_error{ "index out of bounds." };
        }
        if (m_size >= m_cap)
        {
            this->resize();
        }
        for (size_type i = m_size; i > index; i--)
        {
            m_array[i] = m_array[i - 1];
        }
        m_array[index] = value;
        m_size++;
    }

    template <typename T>
    void vector<T>::remove(size_type index)
    {
        if (index >= m_size)
        {
            throw std::range_error{ "index out of bounds." };
        }
        for (size_type i = index; i < m_size; i++)
        {
            m_array[i] = m_array[i + 1];
        }
        m_size--;
    }

    template <typename T>
    void vector<T>::clear()
    {
        for (size_type i = 0; i < m_size; i++)
        {
            m_array[i] = 0;
        }
        m_size = 0;
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::begin()
    {
        return vector<T>::iterator(0, m_array);
    }

    template <typename T>
    typename vector<T>::iterator vector<T>::end()
    {
        return vector<T>::iterator(m_size, m_array);
    }
} // namespace usu
