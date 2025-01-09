
#include <iostream>

using namespace std;

int numberOfSteps(int num) {
    if (num <= 0) return 0;

    int steps = 0;
    while (num > 0) {
        steps += (num & 1) + 1;
        num >>= 1;
    }

    return steps - 1;
}

int main() {
    int num = 8;
    cout << "Number of steps to reduce " << num << " to zero: " << numberOfSteps(num) << endl;

    return 0;
}
