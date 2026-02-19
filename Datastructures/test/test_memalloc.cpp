#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>

#include "../mem_allocate.hpp"

using namespace simple_alloc;

static bool is_aligned(void* ptr)
{
  return reinterpret_cast<std::uintptr_t>(ptr) % ALIGNMENT == 0;
}

static BlockHeader* header_from_ptr(void* p)
{
  return ptr_add<BlockHeader*>(p, -static_cast<std::ptrdiff_t>(HEADER_SIZE));
}


TEST(simple_alloc,MallocReturnsAlignedMemory)
{
  void* p = custom_malloc(24);

  std::cout << "custom malloc(24) returned: " << p << std::endl;
  ASSERT_NE(p, nullptr) << "Allocation failed!";
  EXPECT_TRUE(is_aligned(p));
  custom_free(p);
}


TEST(simple_alloc, ZeroSizeMallocReturnsNull)
{
  EXPECT_EQ(custom_malloc(0), nullptr);
}
