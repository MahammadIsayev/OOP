#pragma once
#include <iostream>
#include <vector>
#include <math.h>
/*
Implement the X matrix type which contains integers. These are square matrices that
can contain nonzero entries only in their two diagonals. Don't store the zero entries.
Store only the entries that can be nonzero in a sequence. Implement as methods:
getting the entry located at index (i, j), adding and multiplying two matrices, and
printing the matrix (in a square shape). */
class Matrix
{
private:
    std::vector<int> _vec;

    int _size;
    double calcSize(unsigned int size);
    void reSize(int size);

public:
    enum Exceptions
    {
        OVERINDEXED,
        NULLPART,
        DIFFERENT,
        INVALID
    };

    Matrix();
    Matrix(const std::vector<int> &vec, int k);
    Matrix(int size);
    int ind(int i, int j) const;
    void setVec(const std::vector<int> &vec);
    void setElement(int i, int j, int e);
    // int operator()(int i, int j) const;
    //int &operator()(int i, int j);
    int getSize() const;
    int getElement(int i, int j) const;
    std::vector<int> getVec();

    friend Matrix operator+(const Matrix &a, const Matrix &b);
    friend Matrix operator*(const Matrix &a, const Matrix &b);
    friend std::ostream &operator<<(std::ostream &os, Matrix &m);
    friend std::istream &operator>>(std::istream &s, Matrix &m);
};

//#endif // MATRIX_H_INCLUDED