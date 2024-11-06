#include <cstdint>
#include <vector>

const size_t PAGE_SIZE = 4096;  // Standard 4KB page size

struct Page {
    uint32_t page_id;
    uint32_t table_id;
    std::vector<uint8_t> data;

    Page() : data(PAGE_SIZE) {}
};
