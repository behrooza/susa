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
 * along with Susa.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file search.h
 * @brief Search routines
 * This file containes special search routines.
 * @author Behrooz Kamary Aliabadi
 * @version 1.0.0
 *
 * @defgroup Search Search
 */

#ifndef SUSA_SEARCH_H
#define SUSA_SEARCH_H

#include "debug.h"

namespace susa {
/**
 * @brief Finds the <i>uint_num</i> least elements of the input vector.
 *
 * @param mat_arg Input vector
 * @param uint_num Number of elements to be find before the routine terminates
 * @return Returns a vector that contains indeces of elements in the input vector that have least values.
 *
 * @ingroup Search
 */
template <class T> matrix <unsigned int> select_least(const matrix <T> &mat_arg, unsigned int uint_num);

/**
 * @brief Finds the <i>uint_num</i> least elements of the input vector among a selected number of
 elements that their indeces are specified by <i>mat_limited_index</i>.
 *
 * @param mat_arg Input vector
 * @param uint_num Number of elements to be find before the routine terminates
 * @return Returns a vector that contains indeces of elements in the input vector that have least values.
 *
 * @ingroup Search
 */
template <class T> matrix <unsigned int> select_limited_least(const matrix <T> &mat_arg, const matrix <unsigned int> &mat_limited_index, unsigned int uint_num);


/**
 * @brief Finds the <i>uint_num</i> greatest elements of the input vector among a selected number of
 elements that their indeces are specified by <i>mat_limited_index</i>.
 *
 * @param mat_arg Input vector
 * @param uint_num Number of elements to be find before the routine terminates
 * @return Returns a vector that contains indeces of elements in the input vector that have least values.
 *
 * @ingroup Search
 */
template <class T> matrix <unsigned int> select_most(const matrix <T> &mat_arg, unsigned int uint_num);


/**
 * @brief Finds the first occurence of an element in a matrix
 * @param  mat_arg
 * @param  T_arg
 *
 * @return The index of the elements that are equal to T_arg
 * @ingroup Search
 */
template <class T> index_set find(const matrix <T> &mat_arg, T &T_arg);

template <class T> matrix <unsigned int> dijkstra(const matrix <T> &mat_graph, unsigned int uint_source);

// Implementation
template <class T> matrix <unsigned int> select_least(const matrix <T> &mat_arg, unsigned int uint_num) {

    unsigned int uint_size = mat_arg.size();
    matrix <T> mat_ret = mat_arg;
    matrix <unsigned int> mat_index(uint_num,1);

    SUSA_ASSERT_MESSAGE(uint_size > uint_num, "The number of elements to be selected is larger than the matrix size.");
    if (uint_size < uint_num) {
        return mat_index;
    }

    unsigned int uint_min_index;
    T T_min;

    for( unsigned int uint_i = 0; uint_i < uint_num; uint_i++) {
        uint_min_index = uint_i;
        T_min = mat_ret(uint_i);
        for (unsigned int uint_j = 0; uint_j < uint_size; uint_j++) {
            if (mat_ret(uint_j) < T_min) {
                uint_min_index = uint_j;
                T_min = mat_ret(uint_j);
            }
        }

        mat_index(uint_i) = uint_min_index;

        mat_ret(uint_min_index) = std::numeric_limits<T>::max();
    }

    return mat_index;
}

template <class T> matrix <unsigned int> select_limited_least(const matrix <T> &mat_arg, const matrix <unsigned int> &mat_limited_index, unsigned int uint_num) {

    unsigned int uint_size = mat_arg.size();
    matrix <T> mat_ret = mat_arg;
    matrix <unsigned int> mat_index(uint_num,1);

    SUSA_ASSERT_MESSAGE(uint_size > uint_num, "The number of elements to be selected is larger than the matrix size.");
    if (uint_size < uint_num) {
        return mat_index;
    }

    unsigned int uint_min_index;
    T T_min;

    for( unsigned int uint_i = 0; uint_i < uint_num; uint_i++) {
        uint_min_index = uint_i;
        T_min = mat_ret(uint_i);
        for (unsigned int uint_j = 0; uint_j < mat_limited_index.size(); uint_j++) {
            if (mat_ret(mat_limited_index(uint_j)) < T_min) {
                uint_min_index = mat_limited_index(uint_j);
                T_min = mat_ret(mat_limited_index(uint_j));
            }
        }

        mat_index(uint_i) = uint_min_index;

        mat_ret(uint_min_index) = std::numeric_limits<T>::max();
    }

    return mat_index;
}

template <class T> matrix <unsigned int> select_most(const matrix <T> &mat_arg, unsigned int uint_num) {

    unsigned int uint_size = mat_arg.size();
    matrix <T> mat_ret = mat_arg;
    matrix <unsigned int> mat_index(uint_num,1);


    SUSA_ASSERT_MESSAGE(uint_size > uint_num, "The number of elements to be selected is larger than the matrix size.");
    if (uint_size < uint_num) {
        return mat_index;
    }

    unsigned int uint_max_index;
    T T_max;

    for( unsigned int uint_i = 0; uint_i < uint_num; uint_i++) {
        uint_max_index = uint_i;
        T_max = mat_ret(uint_i);
        for (unsigned int uint_j = 0; uint_j < uint_size; uint_j++) {
            if (mat_ret(uint_j) > T_max) {
                uint_max_index = uint_j;
                T_max = mat_ret(uint_j);
            }
        }

        mat_index(uint_i) = uint_max_index;

        mat_ret(uint_max_index) = std::numeric_limits<T>::min();
    }

    return mat_index;
}


template <class T> index_set find(const matrix <T> &mat_arg, T &T_arg)
{
  susa::index_set iset(mat_arg.size() + 1); // lets have at least one index

  for (unsigned int uint_index = 0; uint_index < mat_arg.size(); uint_index++)
  {
    if (mat_arg(uint_index) == T_arg) iset.add(uint_index);
  }

  return iset;
}


template <class T> matrix <unsigned int> dijkstra(const matrix <T> &mat_graph, unsigned int uint_src)
{

  SUSA_ASSERT_MESSAGE(mat_graph.is_square(), "the weight matrix must be square");

  if (!mat_graph.is_square()) return (matrix <unsigned int> ());

  unsigned int uint_num_nodes = mat_graph.no_cols();
  susa::matrix <unsigned int> dist(uint_num_nodes, 1, std::numeric_limits<int>::max());
  susa::matrix <unsigned int> prev(uint_num_nodes, 1);

  dist(uint_src) = 0;

  index_set iset(uint_num_nodes);
  iset.add_all();


  unsigned int uint_min = 0;
  unsigned int uint_min_index = 0;
  unsigned int uint_alt = 0;
  while (iset.is_not_empty())
  {

    uint_min = std::numeric_limits <unsigned int>::max();
    for (unsigned int uint_index = 0; uint_index < uint_num_nodes; uint_index++)
    {
      if (iset.exists(uint_index) && dist(uint_index) < uint_min)
      {
        uint_min_index = uint_index;
        uint_min = dist(uint_index);
      }
    }

    iset.remove(uint_min_index);


    for (unsigned int uint_i = 0; uint_i < uint_num_nodes; uint_i++)
    {
      if (mat_graph(uint_min_index,uint_i)) // if zero then there is no way
      {
        uint_alt = dist(uint_min_index) + mat_graph(uint_min_index,uint_i);
        if (uint_alt < dist(uint_i))
        {
          dist(uint_i) = uint_alt;
          prev(uint_i) = uint_min_index;
        }
      }
    }
  }

  return prev;
}

}      // NAMESPACE SUSA
#endif // SUSA_SEARCH_H
