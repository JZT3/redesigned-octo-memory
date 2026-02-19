#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

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




/*------- Trivial Base Cases -------------- */

TEST(MemAllocUnit,MallocReturnsAlignedMemory)
{
  void* p = custom_malloc(24);

  std::cout << "custom malloc(24) returned: " << p << std::endl;
  ASSERT_NE(p, nullptr) << "Allocation failed!";
  EXPECT_TRUE(is_aligned(p));
  custom_free(p);
}


TEST(MemAllocUnit, ZeroSizeMallocReturnsNull)
{
  EXPECT_EQ(custom_malloc(0), nullptr);
}

TEST(MemAllocUnit, MallocZeroReturnNonNullSafeExec)
{
  void* p = custom_malloc(0);
  EXPECT_NO_FATAL_FAILURE( (void) p );
  custom_free(p);
}

TEST(MemAllocUnit, FreeNullIsSafe) 
{
  EXPECT_NO_FATAL_FAILURE(custom_free(nullptr));
}


/* ================================================
 *  Alignment, non-overlap, independent allocations
 *  =============================================== */

/*
 * TEST(MemAllocUnit, MultipleAllocationsDontOverlap)
{
  constexpr int N = 256;
  constexpr std::size_t SIZE = 64;

  std::vector<void*> ptrs;
  ptrs.reverse(N);

  for (int i = 0; i < N; i++)
  {
    void* p = custom_malloc(SIZE);
    ASSERT_NE(p, nullptr);
    EXPECT_TRUE(is_aligned(p));
    ptrs.push_back(p);
  }

  for (size_t i=0; i <ptrs.size(); i++)
  {
    auto ri = range_fr
  }
}
*/

/* =============================
 * Defensive / Invalid Tests
 * ============================*/

TEST(MemAllocUnit, DoubleFreeDoesNotCrash)
{
  void* p = custom_malloc(64);
  ASSERT_NE(p, nullptr);
  custom_free(p);

  EXPECT_NO_FATAL_FAILURE(custom_free(p));
}

TEST(MemallocUnit, FreeInvalidPointer)
{
  int stack_var { 0 };
  void* bad = &stack_var;
  EXPECT_NO_FATAL_FAILURE(custom_free(bad));
}


/* =====================================================
 * Equivalence partitions small medium large allocations
 * =====================================================*/


TEST(MemAllocUnit, SmallMedLargePartitions)
{
  void* small  = custom_malloc(8);           // tiny
  void* medium = custom_malloc(4097);        // a page
  void* large  = custom_malloc(200 * 1025);  // typical mmap threshold

  ASSERT_NE(small,  nullptr);
  ASSERT_NE(medium, nullptr);
  ASSERT_NE(large,  nullptr);

  EXPECT_TRUE(is_aligned(small));
  EXPECT_TRUE(is_aligned(medium));
  EXPECT_TRUE(is_aligned(large));

  custom_free(small);
  custom_free(medium);
  custom_free(large);

}

TEST(MemAllocUnit, SmallAllocStoresCorrectSize)
{
  void* p= custom_malloc(32);
  ASSERT_NE(p, nullptr);

  BlockHeader* h = header_from_ptr(p);

  EXPECT_TRUE(is_alloc(h));
  EXPECT_GE(get_size(h), 32 + HEADER_SIZE + FOOTER_SIZE);

  custom_free(p);
}


/* =====================================
 *  Footer & Boundary Tag Tests
 *  ============================== */

TEST(simple_alloc, FooterMatchesHeader)
{
  void* p = custom_malloc(64);
  ASSERT_NE(p, nullptr);

  BlockHeader* h = header_from_ptr(p);
  BlockFooter* f = ptr_add<BlockFooter*>(h, get_size(h) - FOOTER_SIZE);

  EXPECT_EQ(h->size_alloc, f->size_alloc);

  custom_free(p);
}

