#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <sys/mman.h>
#include <unistd.h>


namespace simple_alloc {

  constexpr std::size_t ALIGNMENT   =        16;
  constexpr std::size_t CHUNK_SIZE  =   1 << 20; //   1MB
  constexpr std::size_t MMAP_THRESH = 128 << 10; // 128KB

  template <typename T> constexpr T align_up(T n) 
  {
    return (n + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
  }


/* ------------ Block Layout ------------- */
  
  struct BlockHeader 
  {
    std::size_t size_alloc;
    BlockHeader* prev_free;
    BlockHeader* next_free;
  };

  struct BlockFooter 
  {
    std::size_t size_alloc;
  };



  // COMPILE-TIME CHECKS
  static_assert(sizeof(BlockHeader)  % ALIGNMENT == 0, "Header must be aligned");
  static_assert(sizeof(BlockFooter) <= ALIGNMENT,      "Footer fits in padding");

  constexpr std::size_t HEADER_SIZE = sizeof(BlockHeader);
  constexpr std::size_t FOOTER_SIZE = sizeof(BlockFooter);
  constexpr std::size_t MIN_BLOCK_SIZE = align_up(HEADER_SIZE + FOOTER_SIZE + ALIGNMENT);

  // BITMASKS
  constexpr std::size_t MASK_ALLOC =  0x1;
  constexpr std::size_t MASK_MMAP  =  0x2;
  constexpr std::size_t MASK_SIZE  = ~0xF;


  // Pointer Arithmetic wrapper
  template <typename RetT = std::byte*> RetT ptr_add(void* ptr, std::ptrdiff_t offset)
  {
    return reinterpret_cast<RetT> (static_cast<std::byte*>(ptr) + offset);
  }



/* ------------ Header Operations --------- */

  inline std::size_t get_size(const BlockHeader* b)
  {
    return b->size_alloc & MASK_SIZE;
  }

  inline bool is_alloc(const BlockHeader* b) 
  {
    return (b->size_alloc & MASK_ALLOC) != 0;
  }

  inline bool is_mmap(const BlockHeader* b)
  {
    return (b->size_alloc & MASK_MMAP) != 0;
  }



  inline void set_alloc(BlockHeader* b, bool v)
  {
    if (v) b->size_alloc |= MASK_ALLOC;
    else   b->size_alloc &= ~MASK_ALLOC;
  }

  inline void set_mmap(BlockHeader* b, bool v)
  {
    if (v) b->size_alloc |= MASK_MMAP;
    else   b->size_alloc &= ~MASK_MMAP;
  }


  inline void write_footer(BlockHeader* b) 
  {
    auto* footer = ptr_add<BlockFooter*>(b, get_size(b) - FOOTER_SIZE);
    *footer = BlockFooter{ .size_alloc = b->size_alloc };
  }


  inline BlockHeader* next_block(BlockHeader* b) 
  {
    return ptr_add<BlockHeader*>(b, get_size(b));
  }

  inline BlockHeader* prev_block(BlockHeader* b)
  {
    auto* prev_footer = ptr_add<BlockFooter*>(b, -static_cast<std::ptrdiff_t>(FOOTER_SIZE));
    std::size_t prev_size = prev_footer->size_alloc & MASK_SIZE;
    return ptr_add<BlockHeader*>(b, -static_cast<std::ptrdiff_t>(prev_size));
  }



  /* -------- API ----------------*/

  [[nodiscard]] void* custom_malloc(std::size_t size);
                void  custom_free(void* ptr);
  [[nodiscard]] void* custom_calloc(std::size_t n, std::size_t size);
  [[nodiscard]] void* custom_realloc(void* ptr, std::size_t size);

}
