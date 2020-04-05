#pragma once

#include <vector>
#include <string>
#include <random>
#include <queue>
#include <set>


class Ising {
public:
    Ising();
    Ising(int sz);
    void cluster_ising(double p, std::string lattice_type="square");
    std::vector<std::pair<int, int>> get_neighbors(const std::pair<int, int>& index, std::string lattice_type="square") const;
    std::vector<std::vector<int>> get_lattice() {return lattice;};

private:
    int size;
    std::random_device rd;
    std::vector<std::vector<int>> lattice;
};



