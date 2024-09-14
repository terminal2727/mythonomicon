#include "type_registry.hpp"

std::unordered_map<std::type_index, int> type_registry;
std::mutex type_registry_mutex;
int next_tag = 1; // 0 is reserved for invalid types