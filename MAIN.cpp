#include <iostream>
#include "MATRIX.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE1

class Menu
{
public:
    Menu() : m() {}
    void run();

private:
    Matrix m;

    void menuWrite();
    void get() const;
    void set();
    void read();
    void write();
    void sum();
    void multiply();
};

int main()
{
    Menu m;
    m.run();
}

void Menu::run()
{
    int choice = 0;
    do
    {
        menuWrite();
        cout << endl
             << "->";
        cin >> choice;
        switch (choice)
        {
        case 1:
            get();
            break;
        case 2:
            set();
            break;
        case 3:
            read();
            break;
        case 4:
            write();
            break;
        case 5:
            sum();
            break;
        case 6:
            multiply();
            break;
        }
    } while (choice != 0);
}

void Menu::menuWrite()
{
    system("Color 0A");
    cout << endl;
    cout << " 0. - Quit" << endl;
    cout << " 1. - Get an element of the matrix" << endl;
    cout << " 2. - Overwrite an element of the matrix" << endl;
    cout << " 3. - Read matrix" << endl;
    cout << " 4. - Write matrix" << endl;
    cout << " 5. - Add matrices" << endl;
    cout << " 6. - Multiply matrices" << endl;
}

void Menu::get() const
{
    int i, j;
    cout << "Give the index of the row: ";
    cin >> i;
    cout << "Give the index of the column: ";
    cin >> j;
    try
    {
        cout << "a[" << i << "," << j << "]= " << m.getElement(i, j) << endl;
    }
    catch (Matrix::Exceptions ex)
    {
        if (ex == Matrix::OVERINDEXED)
            cout << "Overindexing!" << endl;
        else
            cout << "Unhandled ecxeption!" << endl;
    }
}

void Menu::set()
{
    int i, j, e;
    cout << "Give the index of the row: ";
    cin >> i;
    cout << "Give the index of the column: ";
    cin >> j;
    cout << "Give the value: ";
    cin >> e;
    try
    {
        m.setElement(i, j, e);
    }
    catch (Matrix::Exceptions ex)
    {
        if (ex == Matrix::OVERINDEXED)
            cout << "Overindexing!" << endl;
        if (ex == Matrix::NULLPART)
            cout << "These indexes do not point to the Matrixonal!" << endl;
    }
}

void Menu::read()
{
    try
    {
        cout << "Give the size and the items of the matrix: ";
        cin >> m;
    }
    catch (Matrix::Exceptions ex)
    {
        if (ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        else
            cout << "Unhandled ecxeption!" << endl;
    }
}

void Menu::write()
{
    cout << m << endl;
}

void Menu::sum()
{
    try
    {
        Matrix b;

        cout << "Give the size and the items of the second  matrix: " << endl;
        cin >> b;
        Matrix sum;
        sum = m + b;
        cout << "Sum of the matrices: " << endl;
        cout << sum << endl;
    }
    catch (Matrix::Exceptions ex)
    {
        if (ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        if (ex == Matrix::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

void Menu::multiply()
{
    try
    {
        Matrix b;

        cout << "Give the size and the items of the second  matrix: " << endl;
        cin >> b;
        Matrix multiply;
        multiply = m * b;
        cout << "Product of the matrices: " << endl;
        cout << multiply << endl;
    }
    catch (Matrix::Exceptions ex)
    {
        if (ex == Matrix::INVALID)
            cout << "Invalid size!" << endl;
        if (ex == Matrix::DIFFERENT)
            cout << "Different sizes!" << endl;
    }
}

#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
TEST_CASE("create", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if (in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix c;
    in >> c; // 3
    CHECK(c.getElement(1, 1) == 1);
    CHECK(c.getElement(2, 2) == 3);
    CHECK(c.getElement(3, 3) == 5);

    Matrix b;
    in >> b; // 2
    CHECK(b.getElement(1, 1) == 1);
    CHECK(b.getElement(2, 2) == 4);

    Matrix a;
    in >> a; // 1
    CHECK(a.getElement(1, 1) == 1);
}

TEST_CASE("getting and changing an element of the matrix", "")
{
    Matrix a({1, 2, 3, 4, 5}, 3);

    CHECK(a.getElement(1, 1) == 1);
    a.setElement(1, 1, 2);
    CHECK(a.getElement(1, 1) == 2);
}

TEST_CASE("copy constructor", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if (in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a;
    in >> a; // 3

    Matrix b = a;

    CHECK(a.getElement(1, 1) == b.getElement(1, 1));
    CHECK(a.getElement(2, 2) == b.getElement(2, 2));
    CHECK(a.getElement(3, 3) == b.getElement(3, 3));
}

TEST_CASE("assignment operator", "inp.txt")
{
    const string fileName = "inp.txt";

    ifstream in(fileName.c_str());
    if (in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b; // 3
    in >> a;

    b = a; // check every non-zero item
    CHECK(a.getElement(1, 1) == b.getElement(1, 1));
    CHECK(a.getElement(2, 2) == b.getElement(2, 2));
    CHECK(a.getElement(3, 3) == b.getElement(3, 3));

    Matrix c;  // 3
    c = b = a; // check every non-zero item
    CHECK(a.getElement(1, 1) == c.getElement(1, 1));
    CHECK(a.getElement(2, 2) == c.getElement(2, 2));
    CHECK(a.getElement(3, 3) == c.getElement(3, 3));

    a = a; // check every non-zero item
    CHECK(a.getElement(1, 1) == 1);
    CHECK(a.getElement(2, 2) == 3);
    CHECK(a.getElement(3, 3) == 5);
}

TEST_CASE("add", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if (in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a + b; // check every non-zero item
    CHECK(c.getElement(1, 1) == 4);
    CHECK(c.getElement(2, 2) == 6);
    CHECK(c.getElement(3, 3) == 8);

    d = b + a; // check every non-zero item
    CHECK(c.getElement(1, 1) == d.getElement(1, 1));
    CHECK(c.getElement(2, 2) == d.getElement(2, 2));
    CHECK(c.getElement(3, 3) == d.getElement(3, 3));

    d = (a + b) + c;
    f = a + (b + c); // check every non-zero item
    CHECK(d.getElement(1, 1) == f.getElement(1, 1));
    CHECK(d.getElement(2, 2) == f.getElement(2, 2));
    CHECK(d.getElement(3, 3) == f.getElement(3, 3));

    c = a + z; // check every non-zero item
    CHECK(c.getElement(1, 1) == a.getElement(1, 1));
    CHECK(c.getElement(2, 2) == a.getElement(2, 2));
    CHECK(c.getElement(3, 3) == a.getElement(3, 3));
}

TEST_CASE("multiplytiply", "inp2.txt")
{
    const string fileName = "inp2.txt";

    ifstream in(fileName.c_str());
    if (in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    Matrix a, b, c, d, f, e, z; // 3
    in >> a >> b >> z >> e;

    c = a * b;
    CHECK(c.getElement(1, 1) == 15);
    CHECK(c.getElement(2, 2) == 9);
    CHECK(c.getElement(3, 3) == 21);

    d = b * a;
    // Checking for false as a * b !=  b * a in current type of matrix
    CHECK_FALSE(c.getElement(1, 1) == d.getElement(1, 1));
    CHECK(c.getElement(2, 2) == d.getElement(2, 2));
    CHECK_FALSE(c.getElement(3, 3) == d.getElement(3, 3));

    d = (a * b) * c;
    f = a * (b * c);
    CHECK(d.getElement(1, 1) == f.getElement(1, 1));
    CHECK(d.getElement(2, 2) == f.getElement(2, 2));
    CHECK(d.getElement(3, 3) == f.getElement(3, 3));

    c = a * e;
    // Checking for false as a * 1 != a in a current type of matrix
    CHECK_FALSE(c.getElement(1, 1) == a.getElement(1, 1));
    CHECK(c.getElement(2, 2) == a.getElement(2, 2));
    CHECK_FALSE(c.getElement(3, 3) == a.getElement(3, 3));
}

TEST_CASE("exceptions", "")
{

    Matrix a(3);

    try
    {
        a.setElement(3, 3, 4);
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    try
    {
        a.setElement(-1, 4, 4);
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    Matrix b(2);
    Matrix c(3);

    try
    {
        a = b;
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a + b;
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::DIFFERENT);
    }

    try
    {
        a.setElement(1, 0, 4);
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }

    try
    {
        int k = a.getElement(1, 0);
    }
    catch (Matrix::Exceptions ex)
    {
        CHECK(ex == Matrix::OVERINDEXED);
    }
}
#endif
