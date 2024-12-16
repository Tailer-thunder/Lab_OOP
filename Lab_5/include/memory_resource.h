#ifndef MEM_RES
#define MEM_RES

#include <memory_resource>
#include <vector>
#include <cstddef>

class CustomMemoryResource : public std::pmr::memory_resource {
private:
    std::vector<void*> allocated_blocks;
    std::pmr::memory_resource* upstream;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit CustomMemoryResource(std::pmr::memory_resource* upstream_resource = std::pmr::get_default_resource());
    ~CustomMemoryResource();
};
#endif