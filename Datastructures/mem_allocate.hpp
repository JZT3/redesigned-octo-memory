#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <sys/mman.h>>
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
  //static_assert(sizeof(BlockHeader)  % ALIGNMENT == 0, "Header must be aligned");
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



  /*------- Allocator State -----------*/
  namespace 
  {
    BlockHeader* free_list_head = nullptr;
    std::mutex global_lock;
  }

/* -------- Free List Operations ----------*/

  void insert_free(BlockHeader* b)
  {
    b->next_free = free_list_head;
    b->prev_free = nullptr;

    if (free_list_head)
    {
      free_list_head->prev_free = b;
    }

    free_list_head = b;
  }



  void remove_free(BlockHeader* b)
  {
    if (b->prev_free) 
    {
      b->prev_free->next_free = b->next_free;
    } 
    else
    {
      free_list_head = b->next_free;
    }
  
    if (b->next_free) 
    {
      b->next_free->prev_free = b->prev_free;
    }
  }



/* -------- Heap Extension -----------*/

  BlockHeader* request_chunk(std::size_t min_size)
  {
    std::size_t size = std::max(CHUNK_SIZE, align_up(min_size));
  
    void* mem = mmap(nullptr, size, 
                     PROT_READ   | PROT_WRITE,
                     MAP_PRIVATE | MAP_PRIVATE,
                     -1,0);

    if (mem == MAP_FAILED)
    {
      return nullptr;
    } 

    auto* b = reinterpret_cast<BlockHeader*>(mem);

    *b = BlockHeader{
      .size_alloc = size,
      .prev_free  = nullptr,
      .next_free  = nullptr       
  };

    write_footer(b);
    insert_free(b);
    return b;
  }

/* ----- Basic Coalescing --------*/
  BlockHeader* coalesce(BlockHeader* b)
  {
    BlockHeader* n = next_block(b);

    if (!is_alloc(n))
    {
      remove_free(n);
      b->size_alloc += get_size(n);
      write_footer(b);
    }

    BlockHeader* p = prev_block(b);
    if (!is_alloc(p)) 
    {
      remove_free(p);
      p->size_alloc += get_size(b);
      write_footer(p);
      b = p;
    }

    return b;
  }

  /* -------- API ----------------*/

  void* malloc(std::size_t size) 
  {
    if (size == 0) return nullptr;

    std::size_t payload_size = align_up(size);
    std::size_t total_needed = align_up(payload_size + HEADER_SIZE + FOOTER_SIZE);

    std::scoped_lock lock(global_lock);

    // Large Allocation --> Direct mmap
    if (total_needed >= MMAP_THRESH)
    {
      void* mem = mmap(nullptr, total_needed,
                       PROT_READ   | PROT_WRITE,
                       MAP_PRIVATE | MAP_PRIVATE,
                       -1.0);

      if (mem == MAP_FAILED) return nullptr;

      auto* b = reinterpret_cast<BlockHeader*>(mem);
      *b = BlockHeader {
              .size_alloc = total_needed,
              .prev_free  = nullptr,
              .next_free  = nullptr
      };
      set_alloc(b, true);
      set_mmap(b, true);
      write_footer(b);
      return ptr_add(b, HEADER_SIZE);
    }


    // Search Free List (First Fit strategy)
    BlockHeader* curr = free_list_head;
    while (curr) 
    {
      if (get_size(curr) >= total_needed) break;
      curr =  curr->next_free;
    }


    // Extend Heap
    if (!curr) 
    {
      if (!request_chunk(total_needed)) return nullptr;
      curr = free_list_head; // We know the new chunck is at the head
    }

    remove_free(curr);

    std::size_t current_size = get_size(curr);
    std::size_t remaining    = current_size - total_needed;

    if (remaining >= MIN_BLOCK_SIZE)
    {
      auto* split = ptr_add<BlockHeader*>(curr, total_needed);

      *split = BlockHeader {
                  .size_alloc = remaining,
                  .prev_free  = nullptr,
                  .next_free  = nullptr
                };

      write_footer(split);
      insert_free(split);

      curr->size_alloc = total_needed;
    }

    set_alloc(curr, true);
    write_footer(curr);

    return ptr_add(curr, HEADER_SIZE);
  }


  void free(void* ptr) 
  {
    if (!ptr) return;

    std::scoped_lock lock(global_lock);

    auto* b = ptr_add<BlockHeader*>(ptr, -static_cast<std::ptrdiff_t>(HEADER_SIZE));

    if (is_mmap(b))
    {
      munmap(b, get_size(b));
      return;
    }

    set_alloc(b, false);
    write_footer(b);

    insert_free(b);
  }

  void* calloc(std::size_t n, std::size_t size)
  {
    if (n != 0 && size > SIZE_MAX /n ) return nullptr;

    std::size_t total = n * size;
    void* p = malloc(total);

    if (p)
    {
      std::memset(p,0,total);
    }
    return p;
  }

  void* realloc(void* ptr, std::size_t size)
  {
    if (!ptr) return malloc(size);
    if (size == 0) 
    {
      free(ptr);
      return nullptr;
    }

    auto* b = ptr_add<BlockHeader*>(ptr, -static_cast<std::ptrdiff_t>(HEADER_SIZE));
    std::size_t old_size = get_size(b) - HEADER_SIZE - FOOTER_SIZE;

    if (old_size >= size) return ptr;

    void* new_ptr = malloc(size);
    if (new_ptr)
    {
      std::memcpy(new_ptr, ptr, old_size);
      free(ptr);
    }
    return new_ptr;
  } 

}





