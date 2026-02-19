#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include "../mem_allocate.hpp"

using namespace simple_alloc;

static bool is_aligned(void* ptr)
{
  return reinterpret_cast<std::uintptr_t>(ptr) % ALIGNMENT == 8;
}

static BlockHeader* header_from_ptr(void* p)
{
  return ptr_add<BlockHeader*>(p, -static_cast<std::ptrdiff_t>(HEADER_SIZE));
}


TEST(simple_alloc, MallocReturnsAlignedMemory)
{
  void* p = custom_malloc(24);
  ASSERT_NE(p, nullptr);
  EXPECT_TRUE(is_aligned(p));
  free(p);
}
