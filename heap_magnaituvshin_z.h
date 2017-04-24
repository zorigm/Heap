#ifndef HEAP_MAGNAITUVSHIN_Z
#define HEAP_MAGNAITUVSHIN_Z

#include <climits>
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

typedef unsigned int uint;

/**
 * a generic heap class for use in analyzing build_heap and heap_sort
 * algorithms
 * @author Zorig Magnaituvshin
 * @version 31 March 2017
 */
template< typename Comparable >
class Heap
{
 public:
  /**
   * The constructor for an empty heap
   */
  Heap( )
    : build_count{ 0 }, sort_count{ 0 } {}

  /**
   * The constructor that takes in an array and builds them into a heap
   * @param items a vector of items to go into the heap
   */
  explicit Heap( const vector<Comparable> & items )
    : build_count{ 0 }, sort_count{ 0 }, array{ items }
  {
    build_heap( );
  }

  /* since there are no dynamically allocated fields, all the rest of
     the big six do not need to be implemented */

  /**
   * accessor to determine whether there are any elements on the heap
   * @return true if the heap is empty; false otherwise
   */
  bool is_empty( ) const
  {
    
    return array.empty();
  }

  /**
   * accessor to determine how many basic operations were performed the
   * last time heap_sort was called. this would not be in a production
   * heap class
   * @return the count of the basic operations
   */
  uint heap_sort_count() const
  {
    return sort_count;
  }

  /**
   * accessor to determine how many basic operations were performed
   * the last time build_heap was called. this would not be in a
   * production heap class
   * @return the count of the basic operations
   */
  uint build_heap_count() const
  {
    return build_count;
  }

  /**
   * insert an element into the heap
   * @param value the value to be inserted
   */
  void insert( const Comparable & value )
  {
    uint nodeIndex = array.size() - 1;

    array.push_back(value);
    if(array.size() != 0)
    {
       bubble_up(nodeIndex);
    }
  }

  /**
   * delete the maximum element from the heap. should be called
   * "delete" but that's a reserved word in C++
   * @return the element with the largest value in the heap
   */
  Comparable delete_max( )
  {
    assert( !is_empty() );

    uint index = 0;
    uint max = array[0];
    array[0] = array[array.size()-1];
    array.pop_back();
    
    if(array.size() > 0)
    {
       percolate_down(index, array.size());
    }
    
    return max;
  }

  /**
   * uses the heap_sort algorithm as described in Levitin 3rd pp 231
   * et seq sets the sort_count field. fills result vector with the
   * elements in order
   * @param result a vector that will be filled with the items in
   * ascending order
   */
   
  void heap_sort( vector< Comparable > & result )
  {
    result = array;
   
    uint imaginarySize = result.size() - 1;
    uint temp;
    
    for(uint i = result.size() - 1; i != 0; i--)
    {
       temp = result[0];
       result[0] = result[imaginarySize];
       result[imaginarySize] = temp;
       imaginarySize--;
       percolate_down(0 ,imaginarySize, result);
    }
  }

  /**
   * generate a string representation of the array in its current
   * state requires the heap elements to implement the << operator
   * this is for debugging purposes; it would not be included in a
   * production class
   * @return string representation of the heap value in their current order
   */
  string to_string( ) const
  {
    if( is_empty() )
    {
      return "";
    }
    stringstream buffer;
    for( auto value : array )
    {
      buffer << value << ' ';
    }
    return buffer.str();
  }

 private:
  uint build_count;
  uint sort_count;
  vector<Comparable> array;
  
  uint getParentIndex(uint nodeIndex)
  {
     return (nodeIndex-1)/2;
  }
  
  uint getLeftChildIndex(uint nodeIndex)
  {
     return (nodeIndex*2)+1;
  }
  
  uint getRightChildIndex(uint nodeIndex)
  {
     return (nodeIndex*2)+2;
  }

  /**
   * establish a valid heap from an arbitrary arrangement of items
   */
  void build_heap( )
  {
    
    uint size = array.size();
    
    for( uint i = (size/ 2) - 1 ; i != UINT_MAX; i--)
    {
       percolate_down(i,size);
    }
    
  }

  void bubble_up( uint index )
  {
    
    uint temp;
    uint parentIndex;
    parentIndex = getParentIndex(index);
    
    if(index == 0)
    {
       return;
    }
    
    if(array[parentIndex] < array[index])
    {
       temp = array[parentIndex];
       array[parentIndex] = array[index];
       array[index] = temp;
       bubble_up(parentIndex);
    }
    
  }

  void percolate_down( uint index, uint size )
  {
    
    uint leftChild, rightChild, temp, maxIndex;
    leftChild = getLeftChildIndex(index);
    rightChild = getRightChildIndex(index);
    
    build_count++; //comparison is basic operation; runs every time.
    
    if(leftChild >= size)
    {
       return;
    }
    
    maxIndex = index;
    
    if(array[index] < array[leftChild])
    {
       maxIndex = leftChild;
    }
    
    if((rightChild < size) && (array[maxIndex] < array[rightChild]))
    {
       maxIndex = rightChild;
    }
    
    if(maxIndex != index)
    {
       temp = array[index];
       array[index] = array[maxIndex];
       array[maxIndex] = temp;
       percolate_down(maxIndex, size);
    }
    
  }
  
  void percolate_down( uint index, uint size, vector< Comparable > & result )
  {
    
    uint leftChild, rightChild, temp, maxIndex;
    leftChild = getLeftChildIndex(index);
    rightChild = getRightChildIndex(index);
    
    sort_count++; //comparison is basic operation; runs every time.
    
    if(leftChild >= size)
    {
       return;
    }
    
    maxIndex = index;
    
    if(result[index] < result[leftChild])
    {
       maxIndex = leftChild;
    }
    
    if((rightChild < size) && (result[maxIndex] < result[rightChild]))
    {
       maxIndex = rightChild;
    }
    
    if(maxIndex != index)
    {
       temp = result[index];
       result[index] = result[maxIndex];
       result[maxIndex] = temp;
       percolate_down(maxIndex, size, result);
    }
  }
  
};
#endif
