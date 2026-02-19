#include "mem_allocate.hpp"

namespace simple_alloc {



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

  void* custom_malloc(std::size_t size) 
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
                       -1,0);

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


  void custom_free(void* ptr) 
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




  void* custom_calloc(std::size_t n, std::size_t size)
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



  void* custom_realloc(void* ptr, std::size_t size)
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





