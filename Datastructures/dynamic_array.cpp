/*
Modern C++ implementation of William Fiset Dynamic Array code
*/
#include <algorithm>
#include <utility>
// #include <cassert>
// #include <cstddef>


class IntArray 
{
public:
  // Type Aliasing 
  using value_type     = int; 
  using size_type      = std::size_t;
  using iterator       = int*;
  using const_iterator = const int*;

private:
  static constexpr size_type DEFAULT_CAP {1u << 3};
  /* 
  This variable belongs to the class itself rather than a specific instance.
  Ensuring only one copy of the DEFAULT_CAPACITY exists in memory.

  We are explicity telling the compiler to evaluate this value at compile time.
  I dont use 'inline' because it is implied in c++17 
  "A constexpr specifier used in a function or static member variable (since C++17) declaration implies inline."

  1u << 3 Explained.
  1u is the unsigned integer 1.
  << 3 shifts the bits of 1 three positions to the left
  0001 --> 1000
  in binary the resulting capacity is now 8 or 1 x 2^3=8
  */

  // Private member variables
  iterator  m_data{nullptr};
  size_type m_len { 0 };
  size_type m_capacity { 0 };

  void reallocate(size_type new_cap)
  {
    iterator new_data = new int[new_cap]{}; // Request a contiguous block of memory from the Free store (heap). Memory allocator
    std::copy_n(m_data, m_len, new_data); // copy length num of old elements and stores them in temp new_data
  
    /* 
    if new allocation fails it would throw std::bad_alloc leaving original data untouched
    */

    delete[] m_data; 
    // new[] allocator stores the size of the array in a header before the pointer
    // delete[] uses this header to know how many bytes to free to the heap

    m_data     = new_data; // shallow copy, preventing dangling pointer by overwriting data
    m_capacity = new_cap;
  }


  static iterator allocate_initial_buffer(size_type cap)
  {
    if (cap == 0) return nullptr;
    return new int[cap] {};
    // If capacity is 0, avoid allocating an empty array and set m_data to nullptr.
  }

public:
/*--------------------Constructors----------------------------*/
  IntArray() : IntArray(DEFAULT_CAP) {}

  // Capacity Constructor
  explicit IntArray(size_type capacity)
    : m_data {allocate_initial_buffer(capacity)},
      m_len  { 0 }, // set the current num of elements to zero
      m_capacity {capacity} {} 

  /*
    Explicit prevents implicit conversions. Otherwise the compiler could turn a raw
    integer into an IntArray object.

    new int[capcity]{} prevents junk data from being stored as capacity value
  */

  // Raw Array Constructor
  explicit IntArray(const_iterator array, size_type n)
    : m_data     { new int[n] }, // We dont need to zero-initialize here because we immediately overwrite this memory with std::copy_n
      m_len      { n },
      m_capacity { n } { std::copy_n(array, n, m_data); } // Copy exactly n elements from source array into our new m_data block.


  // Initializer List Constructor
  IntArray(std::initializer_list<int> init)
    : m_data     { new int[ init.size() ] },
      m_len      { init.size() },
      m_capacity { init.size() } { std::copy_n(init.begin(), init.end(), m_data); }


/* ------------------ Rule of Five -------------*/
  // Destructor -- Clean up memory
  ~IntArray() { delete[] m_data; }

  // Copy Constructor -- Create deep copy of data
  IntArray(const IntArray& other) 
    : m_data { new int[other.m_capacity] },
      m_len { other.m_len },
      m_capacity {other.m_capacity } { std::copy_n(other.m_data, m_len, m_data);}

  // Copy Assignment -- Safely Replace current data with a deep copy of another
  IntArray& operator=(const IntArray& other) 
  {
    if (this == &other) return *this;
    IntArray temp{other};
    // std::swap(temp);
    return *this;
  }

  // Move Constructor -- Steal the pointer from a temporary object
  IntArray(IntArray&& other) noexcept
    : m_data     {other.m_data},
      m_len      {other.m_len},
      m_capacity {other.m_capacity} 
      {
        other.m_data = nullptr;
        other.m_len  = other.m_capacity = 0;
      }

  // Move Assignment -- Transfer ownership from one existing object to another
  IntArray& operator=(IntArray&& other) noexcept
  {
    if (this == &other) return *this;

    delete[] m_data;
    m_data = other.m_data;
    m_len = other.m_len;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_len = other.m_capacity = 0;
    return *this;
  }
};
