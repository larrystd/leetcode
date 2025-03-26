#include <iostream>
#include <type_traits>

// 处理整数类型的函数
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
printType(T value) {
    std::cout << "Integer: " << value << std::endl;
}

// 处理浮点数类型的函数
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
printType(T value) {
    std::cout << "Floating point: " << value << std::endl;
}

int main() {
    printType(42);          // 调用整数类型的函数
    printType(3.14);        // 调用浮点数类型的函数
    // printType("hello");   // 这行代码会导致编译错误，因为没有匹配的模板函数
    return 0;
}