#include "MATRIX.h"

Matrix::Matrix()
{
    this->_vec.clear();
    this->_size = 0;
}

Matrix::Matrix(const std::vector<int> &vec, int k)
{
    _size = k;
    double n = _size;
    if (n == floor(n))
    {
        _size = n;
        _vec = vec;
    }
    else
    {
        _size = 0;
        _vec.clear();
    }
}

Matrix::Matrix(int size)
{
    if (size < 0)
        throw INVALID;
    if (size != 0)
    {
        if (size % 2 == 0)
        {
            this->_size = size;
            this->_vec.resize(2 * size, 0);
        }
        else
        {
            this->_size = size;
            this->_vec.resize(2 * size - 1, 0);
        }
    }
    else
    {
        this->_size = 0;
        this->_vec.resize(0, 0);
    }
}

void Matrix::reSize(int size)
{
    if (size < 0)
        throw INVALID;
    if (size % 2 == 0)
    {
        this->_size = size;
        this->_vec.resize(2 * size, 0);
    }
    else
    {
        this->_size = size;
        this->_vec.resize(2 * size - 1, 0);
    }
}

int Matrix::ind(int i, int j) const
{
    /* if (j == 1 && j != i && _size % 2 == 0)
        return (i - 1) * 2;
    else if (j == 1 && j != i && _size % 2 == 1)
        return (i - 1) * 2 - 1;
    else  if (j == 1 && i == _size && _size % 2 == 0)
        return _size * 2 - 1;
    else if (j == 1 && i == _size && _size % 2 == 1)
        return _size * 2 - 2;
    else if (i == 1 && j == i)
        return 0;
    else if (i == 1 && j == _size)
        return i;
    else if (_size % 2 == 1 && i == j && j == (_size - 1) / 2)
        return j;
    else if (j == 2)
        return (i - 1) * 2;
    else if (j == _size - 1 && _size % 2 == 0)
        return i - 1 + j - 1;
    else if (j == _size - 1 && _size % 2 == 1)
        else if (j == i && j ==  (_size - 1) / 2 &&  % 2 == 1) 
        return (i - 1) * 2;
    else if (j == i && j == _size % 2 == 0)
        return (i - 1) * 2 + 1; */

    /*if (i == 1 && i == j)
    {
        return 0;
    }
    else if (i == j && i == this->_size)
        return this->_size * 2 - 2;
    else if (i == j && i != 1)
        return i - 2 + j;
    //return j + i * (i - 1) / 2 - 1;*/
    if (i == 1 && j == i)
        return 0;
    if (i == 1 && j == this->_size)
        return 1;

    if (this->_size % 2 == 1)
    {
        if (i == this->_size && j == 1)
            return this->_size * 2 - 3;
        else if (i == j && i == this->_size)
            return this->_size * 2 - 2;
        else if (i == j && i != 1)
            return i - 2 + j;
        else if (i + j == this->_size + 1)
            return i + 1;
    }
    else
    {
        if (j <= this->_size / 2)
            return i * 2 - 2;
        else
            return i * 2 - 1;
    }
}

int Matrix::getSize() const
{
    return this->_size;
}

/*void Matrix::setVec(const std::vector<int> &vec)
{
    double n = calcMatrixSize(vec.size());
    if (n == floor(n))
    {
        this->_size = n;
        this->_vec = vec;
    }
    else
    {
        this->_size = 0;
        this->_vec.clear();
    }
} */

int Matrix::getElement(int i, int j) const
{
    int s = this->getSize();
    if ((i > s || i <= 0) || (j > s || j <= 0))
        throw OVERINDEXED;
    if (i != j && j + i != this->_size + 1)
        return 0;
    else
        return this->_vec[ind(i, j)];
}

void Matrix::setElement(int i, int j, int e)
{
    int s = this->getSize();
    if ((i > s || i <= 0) || (j > s || j <= 0))
        throw OVERINDEXED;
    if (!(i != j && j != this->getSize() && j != 1))
        this->_vec[ind(i, j)] = e;
    else
        throw NULLPART;
}

Matrix operator+(const Matrix &a, const Matrix &b)
{
    int s = a.getSize();
    if (s != b.getSize())
        throw Matrix::DIFFERENT;

    Matrix sum(s);
    for (int i = 0; i < sum._vec.size(); i++)
        sum._vec[i] = a._vec[i] + b._vec[i];

    return sum;
}

Matrix operator*(const Matrix &a, const Matrix &b)
{
    int s = a.getSize();
    if (s != b.getSize())
        throw Matrix::DIFFERENT;

    Matrix mul(s);
    for (int i = 1; i <= s; i++)
        for (int j = 1; j <= s; j++)
            if (!(i != j && j != s && j != 1))
                for (int k = 1; k <= s; k++)
                    mul.setElement(i, j, mul.getElement(i, j) + a.getElement(i, k) * b.getElement(k, j));

    return mul;
}

std::ostream &operator<<(std::ostream &os, Matrix &m)
{
    os << m.getSize() << " x " << m.getSize() << std::endl;
    int k = 0;
    for (int i = 0; i < m.getSize(); i++)
    {
        for (int j = 0; j < m.getSize(); j++)
        {
            if (j != i && (i + j) != (m.getSize() - 1))
                os << 0 << " ";
            else
                os << m._vec[k++] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &m)
{
    int s;
    is >> s;
    m.reSize(s);
    if (s % 2 == 0)
        for (int i = 0; i < 2 * s; ++i)
        {
            is >> m._vec[i];
        }
    else
    {
        for (int i = 0; i < 2 * s - 1; ++i)
        {
            is >> m._vec[i];
        }
    }

    return is;
}

/*int Matrix::operator()(int i, int j) const
{
    int s = getSize();
    if ((i >= s || i < 0) || (j >= s || j < 0))
        throw OVERINDEXED;
    if (i != j)
        return 0;
    return _vec[i];
}

int &Matrix::operator()(int i, int j)
{
    int s = getSize();
    if ((i >= s || i < 0) || (j >= s || j < 0))
        throw OVERINDEXED;
    if (i != j)
        throw NULLPART;
    return _vec[i];
}
*/