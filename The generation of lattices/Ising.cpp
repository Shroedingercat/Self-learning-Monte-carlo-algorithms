#include "Ising.h"

Ising::Ising() {
    size = 30;
    for (int i = 0; i <size; i++) {
        lattice.emplace_back(size, 1);
    }

}

Ising::Ising(int sz) {
    size = sz;
    for (int i = 0; i <size; i++) {
        lattice.emplace_back(size, 1);
    }
}

std::vector<std::pair<int, int>> Ising::get_neighbors(const std::pair<int, int>& index, std::string lattice_type) const{
    std::vector<std::pair<int, int>> neig;
    if ((index.first + 1) < size)
        neig.emplace_back(index.first+1, index.second);
    if ((index.first - 1) >= 0)
        neig.emplace_back(index.first-1, index.second);
    if ((index.second + 1) < size)
        neig.emplace_back(index.first, index.second+1);
    if ((index.second - 1) >= 0)
        neig.emplace_back(index.first, index.second-1);
    if (lattice_type != "square") {
        if ((index.first + 1) < size && (index.second + 1) < size)
            neig.emplace_back(index.first + 1, index.second + 1);
        if ((index.first - 1) >= 0 && (index.second - 1) >= 0)
            neig.emplace_back(index.first - 1, index.second - 1);
    }
    return std::move(neig);
}

void Ising::cluster_ising(double p, std::string lattice_type) {
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size-1);
    std::pair<int, int> curr, j;

    j.first = dis(gen);
    j.second = dis(gen);

    std::vector<std::vector<bool>> used;
    for (int i = 0; i <size; i++) {
        used.emplace_back(size, false);
    }
    std::vector<std::pair<int, int>> neighbors;
    std::queue<std::pair<int, int>> q;

    q.push(j);
    used[j.first][j.second] = true;

    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (lattice_type == "square") {
            neighbors = get_neighbors(curr, "square");
        } else {
            neighbors = get_neighbors(curr, "triangular");
        }
        for (auto neighbor: neighbors) {
            auto rand = std::generate_canonical<double, 30>(gen);
            //???
            if (lattice[j.first][j.second] == lattice[neighbor.first][neighbor.second] && rand < p &&
            !used[neighbor.first][neighbor.second]) {
                q.push(neighbor);
                used[neighbor.first][neighbor.second] = true;
                lattice[neighbor.first][neighbor.second] *= -1;
            }
        }
    }
    lattice[j.first][j.second] *= -1;

}
