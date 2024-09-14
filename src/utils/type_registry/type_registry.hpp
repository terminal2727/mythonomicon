#ifndef TYPE_REGISTRY_HPP
#define TYPE_REGISTRY_HPP

#include <unordered_map>
#include <typeindex>
#include <mutex>

extern std::unordered_map<std::type_index, int> type_registry;
extern std::mutex type_registry_mutex;
extern int next_tag;

/**
 * @brief Retrieves or assigns a unique type tag for the specified type.
 *
 * This function ensures that each type is associated with a unique integer tag.
 * If the type has already been registered, it returns the existing tag.
 * Otherwise, it assigns a new tag to the type and returns it.
 *
 * @tparam T The type for which to retrieve or assign a tag.
 * @return An integer representing the unique tag for the specified type.
 */
template <typename T>
int type_registry_get_type_tag() {
    std::lock_guard<std::mutex> lock(type_registry_mutex);
    
    auto iterator = type_registry.find(std::type_index(typeid(T)));
    
    if (iterator != type_registry.end()) { 
        return iterator->second; 
    }

    int tag = next_tag++;
    type_registry[std::type_index(typeid(T))] = tag;
    return tag;
}

/**
 * @brief Checks if the given object is of the specified type T.
 *
 * This function verifies if the provided object matches the type T by comparing
 * its type tag with the expected type tag for T. If the object is of the expected
 * type and a non-null return_value pointer is provided, the function will set
 * return_value to point to the casted object.
 *
 * @tparam T The type to check against.
 * @param object A pointer to the object to be checked.
 * @param return_value An optional pointer to a pointer of type T. If the object
 *                     is of type T, this will be set to point to the casted object.
 * @return true if the object is of type T, false otherwise.
 */
template <typename T>
bool is_type_of(void* object, T** return_value = nullptr) {
    if (object == nullptr) { return false; }
    
    // We use type_registry_get_type_tag<T>() instead of type_registry[T] because we want to create the tag if it doesn't exist
    // This is because we can't guarantee that the type has been registered before calling this function
    int expected_tag = type_registry_get_type_tag<T>();
    
    T* casted_object = static_cast<T*>(object);

    bool is_expected_type = casted_object->type_tag == expected_tag;

    if (is_expected_type && return_value != nullptr) {
        *return_value = casted_object;
    }

    return is_expected_type;
}

#endif // TYPE_REGISTRY_HPP