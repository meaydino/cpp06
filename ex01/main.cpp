#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data data;
    data.s1 = "Hello";
    data.n = 42;
    data.s2 = "World";

    Data* originalPtr = &data;

    uintptr_t raw = Serializer::serialize(originalPtr);
    Data* deserializedPtr = Serializer::deserialize(raw);

    std::cout << "--- Address Information ---" << std::endl;
    std::cout << "Original Pointer Address   : " << originalPtr << std::endl;
    std::cout << "Casting value              : " << raw << std::endl;
    std::cout << "Deserialized Pointer Address: " << deserializedPtr << std::endl;
    std::cout << std::endl;

    std::cout << "--- Data Contents ---" << std::endl;
    std::cout << "Original Data   : " << originalPtr->s1 << ", " << originalPtr->n << ", " << originalPtr->s2 << std::endl;
    std::cout << "Deserialized Data: " << deserializedPtr->s1 << ", " << deserializedPtr->n << ", " << deserializedPtr->s2 << std::endl;
    std::cout << std::endl;

    std::cout << "--- Test Result ---" << std::endl;
    if (originalPtr == deserializedPtr) {
        std::cout << "SUCCESS: Pointers match!" << std::endl;
    } else {
        std::cout << "FAILURE: Pointers do not match!" << std::endl;
    }

    return 0;
}
