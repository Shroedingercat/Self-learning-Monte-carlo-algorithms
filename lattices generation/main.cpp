#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "Ising.h"

int main() {
    std::vector<std::vector<int>> lattice;
    std::ofstream X_train, labels;
    int curr;
    double count = 0;
    int start_size, end_size, step;
    std::cout << "start size: ";
    std::cin >> start_size;
    std::cout << std::endl << "end size: ";
    std::cin >> end_size;
    std::cout << std::endl << "step: ";
    std::cin >> step;

    for (int size=start_size; size <= end_size; size+=5) {
        Ising ising(size);
        std::string file = "size"+std::to_string(size);
        file += "_min1_max3.5_step0.0625_batch1000_re100_N10000_triangular";
        X_train.open(file);
        labels.open("labels_" + file);
        for (double T = 1; T < 3.5; T += 0.0625) {
            count++;
            std::cout << count / 40 << std::endl;
            if (T >= 3.65) {
                curr = 0;
            } else {
                curr = 1;
            }
            double p = 1 - exp(-(1 / T) * 2);
            for (int i = 0; i < 10000; i++) {
                ising.cluster_ising(p);
            }
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 100; j++) {
                    ising.cluster_ising(p);
                }
                lattice = ising.get_lattice();
                for (const auto &row: lattice) {
                    for (auto number: row) {
                        X_train << number << " ";
                    }
                    X_train << std::endl;
                }
                X_train << ";" << std::endl;
                labels << curr << std::endl;
            }
        }
        X_train.close();
        labels.close();
    }
    return 0;
}
