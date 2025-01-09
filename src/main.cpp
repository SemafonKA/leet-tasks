
#include <iostream>
#include <vector>

using namespace std;

int maximumWealth(vector<vector<int>>& accounts) {
    int max = 0;

    size_t customersCount = accounts.size();
    size_t banksCount = accounts.at(0).size();

    for (size_t i = 0; i < customersCount; i++) {
        int sum = 0;
        auto& account = accounts[i];
        for (size_t j = 0; j < banksCount; j++) {
            sum += account[j];
        }

        max = std::max(max, sum);
    }

    return max;
}

int main() {
    vector<vector<int>> accounts = {
        {1, 5},
        {7, 3},
        {3, 5},
    };

    auto maxWealth = maximumWealth(accounts);
    cout << "Maximum wealth: " << maxWealth << "\n";
    return 0;
}
