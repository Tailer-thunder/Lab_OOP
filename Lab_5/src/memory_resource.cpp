#include "../include/memory_resource.h"
#include <algorithm>

CustomMemoryResource::CustomMemoryResource(std::pmr::memory_resource* upstream_resource)
    : upstream(upstream_resource) {}

CustomMemoryResource::~CustomMemoryResource() {
    for (auto ptr : allocated_blocks) {
        upstream->deallocate(ptr, 0, 0); 
    }
}

void* CustomMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* ptr = upstream->allocate(bytes, alignment);
    allocated_blocks.push_back(ptr);
    return ptr;
}

void CustomMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    auto it = std::find(allocated_blocks.begin(), allocated_blocks.end(), p);
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
        upstream->deallocate(p, bytes, alignment);
    }
}

bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
