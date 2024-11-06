#include <string>
#include <vector>
#include "page.hpp"

struct Column {
    std::string name;
    enum Type { INT, VARCHAR, FLOAT, TIMESTAMP } type;
    size_t size;  // For VARCHAR
};

struct Table {
    std::string name;
    std::vector<Column> columns;
    std::vector<Page> pages;
    std::string file_path;  // Path to the table's data file
};
