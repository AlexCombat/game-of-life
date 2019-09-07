#pragma once

#include <vector>

namespace gol
{
    template<class T>
    class Matrix
    {
    public:
        Matrix() = delete;
        Matrix(size_t width, size_t height);
        Matrix(const Matrix&) = default;
        Matrix(Matrix&&) = default;

        Matrix& operator=(const Matrix&) = default;
        Matrix& operator=(Matrix&&) = default;

        size_t getWidth() const;
        size_t getHeight() const;

        const T& get(size_t x, size_t y) const;
        void set(size_t x, size_t y, const T& value);
    private:
        size_t m_width;
        size_t m_height;
        // TODO replace with sparse matrix
        std::vector<T> m_values;
    };

    template<class T>
    Matrix<T>::Matrix(size_t width, size_t height)
        : m_width(width),
            m_height(height),
            m_values(std::vector<T>(m_width * m_height)) {}

    template<class T>
    size_t Matrix<T>::getWidth() const
    {
        return m_width;
    }

    template<class T>
    size_t Matrix<T>::getHeight() const
    {
        return m_height;
    }

    template<class T>
    const T& Matrix<T>::get(size_t x, size_t y) const
    {
        if (x > m_width - 1 && y > m_height - 1)
        {
            throw std::out_of_range("Element index is out of bounds");
        }

        return m_values[x + m_width * y];
    }

    template<class T>
    void Matrix<T>::set(size_t x, size_t y, const T& value)
    {
        if (x > m_width - 1 && y > m_height - 1)
        {
            throw std::out_of_range("Element index is out of bounds");
        }

        m_values[x + m_width * y] = value;
    }
}
