#include <format>
#include <iostream>


using namespace std;

int main() {
    constexpr auto greetingsTo = "World";

    cout << format("Hello, {}!\n", greetingsTo);

    return 0;
}
