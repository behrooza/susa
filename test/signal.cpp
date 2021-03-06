/*
 * This file is part of Susa.

 * Susa is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * Susa is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.

 * You should have received a copy of the Lesser GNU General Public License
 * along with Susa. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file signal.cpp
 * @brief Unit Test Suit
 * @author Behrooz Kamary
 */

#include "test.h"

int main(void)
{
    {
        susa::matrix<int> mat_a("[1 1 1]");
        susa::matrix<int> mat_exp("[1 2 3 2 1]");
        susa::matrix<int> mat_res = conv(mat_a, mat_a);
        SUSA_TEST_EQ(mat_res, mat_exp, "convolution.");
    }

    {
        susa::matrix<int> mat_a("[3 4 5]");
        susa::matrix<int> mat_b("[6 7 8]");
        susa::matrix<int> mat_exp("[18 45 82 67 40]");
        susa::matrix<int> mat_res = conv(mat_a, mat_b);
        SUSA_TEST_EQ(mat_res, mat_exp, "convolution.");
    }

    {
        susa::matrix<int> mat_a("[1 2; 3 4]");
        susa::matrix<int> mat_b("[0 5; 6 7]");
        susa::matrix<int> mat_exp("[0 5 0 10;6 7 12 14;0 15 0 20;18 21 24 28]");
        susa::matrix<int> mat_res = kron(mat_a, mat_b);
        SUSA_TEST_EQ(mat_res, mat_exp, "Kronecker product");
    }

    {
        susa::matrix<int> mat_a("1 2 3 4 5");
        susa::matrix<int> mat_exp("1   2   3   4   5;"
                                  "2   1   2   3   4;"
                                  "3   2   1   2   3;"
                                  "4   3   2   1   2;"
                                  "5   4   3   2   1");
        SUSA_TEST_EQ(susa::toeplitz(mat_a), mat_exp, "single row toeplitz");
    }
    {
        susa::matrix<int> mat_a = susa::toeplitz(susa::matrix<int> ("1 2 3 4 5"),susa::matrix<int> ("1 6 7 8 9"));
        susa::matrix<int> mat_exp("1   6   7   8   9;"
                                  "2   1   6   7   8;"
                                  "3   2   1   6   7;"
                                  "4   3   2   1   6;"
                                  "5   4   3   2   1");
        SUSA_TEST_EQ(mat_a, mat_exp, "row and column toeplitz");
    }

    {
        susa::matrix<int> mat_a = susa::toeplitz(susa::matrix<int> ("1 2 3 4 5"),susa::matrix<int> ("1 6 7 8 9 10"));
        susa::matrix<int> mat_exp("1  6  7  8  9  10;"
                                  "2  1  6  7  8  9;"
                                  "3  2  1  6  7  8;"
                                  "4  3  2  1  6  7;"
                                  "5  4  3  2  1  6");

        SUSA_TEST_EQ(mat_a, mat_exp, "asymetric row and column toeplitz");
    }

    {
        susa::matrix<int> mat_a = susa::toeplitz(susa::matrix<int> ("1 6 7 8 9 10"),susa::matrix<int> ("1 2 3 4 5"));
        susa::matrix<int> mat_exp("1  2  3  4  5;"
                                  "6  1  2  3  4;"
                                  "7  6  1  2  3;"
                                  "8  7  6  1  2;"
                                  "9  8  7  6  1;"
                                  "10  9  8  7  6");

        SUSA_TEST_EQ(mat_a, mat_exp, "asymetric row and column toeplitz");
    }
    SUSA_TEST_PRINT_STATS();

    return (uint_failed);
}