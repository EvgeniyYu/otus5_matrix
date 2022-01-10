#define BOOST_TEST_MODULE test_matrix

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>
#include "matrix.h"

BOOST_AUTO_TEST_SUITE(test_matrix)

BOOST_AUTO_TEST_CASE(test_result)
{
    Matrix<int, -1> matrix;

    auto a = matrix[0][0];
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix.size() == 0);

    matrix[100][100] = 314;		//size = 1
    BOOST_CHECK(matrix[100][100] == 314);
    BOOST_CHECK(matrix.size() == 1);

    matrix[10][10] = 300;	//size = 2
    matrix[50][50] = 350;	//size = 3
    BOOST_CHECK(matrix[10][10] == 300);
    BOOST_CHECK(matrix.size() == 3);
    auto b = matrix[30][30];
    auto c = matrix[10][10];
    BOOST_CHECK(b == -1);
    BOOST_CHECK(c == 300);
    BOOST_CHECK(matrix.size() == 3);
    BOOST_CHECK(matrix[11][10] == -1);

    matrix[50][50] = 400;	//size = 3
    BOOST_CHECK(matrix[50][50] == 400);
    matrix[50][50] = -1;
    BOOST_CHECK(matrix.size() == 2);

    std::stringstream out;
    for (const auto& c: matrix)
    {
        int x, y, v;
        std::tie(x, y, v) = c;
        out << x << y << v;
    }
    BOOST_CHECK(out.str() == "1001003141010300");
}

BOOST_AUTO_TEST_CASE(test_canonical_form)
{
    Matrix<int, 0> matrix;
    ((matrix[100][100] = 314) = 0) = 217;
    BOOST_CHECK(matrix[100][100] == 217);
}

BOOST_AUTO_TEST_SUITE_END()
