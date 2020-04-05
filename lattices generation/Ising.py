import numpy as np
import matplotlib.pyplot as plt


class Ising:
    def __init__(self, x=16, y=16, z=1):
        self.x = x
        self.y = y
        self.z = z
        self.lattice = None
        self.all_lattice = []
        self.gen = True

    ##
    def get_neighbors(self, index, lattice_type="square"):
        """
        :param lattice_type: lattice type
        :param index: spin index
        :return: neighbors index
        """
        neig = []
        if (index[0] + 1) < self.y:
            neig.append((index[0]+1, index[1]))
        if (index[0] - 1) >= 0:
            neig.append((index[0]-1, index[1]))
        if (index[1] + 1) < self.x:
            neig.append((index[0], index[1]+1))
        if (index[1] - 1) >= 0:
            neig.append((index[0], index[1]-1))
        if lattice_type != "square":
            if (index[0] + 1) < self.y and (index[1] + 1) < self.x:
                neig.append((index[0]+1, index[1]+1))
            if (index[0] - 1) >= 0 and (index[1] - 1) >= 0:
                neig.append((index[0] - 1, index[1] - 1))
        return neig

    def cluster_ising(self, p, lattice_type="square", save=False):
        if self.lattice is None:
            self.lattice = np.random.randint(2, size=(self.y, self.x))
            self.lattice[self.lattice == 0] = -1
        j = (np.random.randint(self.y), np.random.randint(self.x))
        queue = [j]
        used = [j]
        while len(queue) != 0:
            curr = queue.pop(0)
            if lattice_type == "square":
                neighbors = self.get_neighbors(curr, "square")
            else:
                neighbors = self.get_neighbors(curr, "triangular")
            for neighbor in neighbors:
                rd = np.random.rand(1)[0]
                if self.lattice[curr] == self.lattice[neighbor] and neighbor not in used and rd < p:
                    queue.append(neighbor)
                    used.append(neighbor)

        for index in used:
            self.lattice[index] *= -1
        if save:
            self.all_lattice.append(np.array(self.lattice.reshape((1, self.y * self.x))[0]))

    def show(self):
        x_plus = []
        y_plus = []
        x_minus = []
        y_minus = []
        for i in range(self.y):
            for j in range(self.x):
                if self.lattice[i][j] == 1:
                    x_plus.append(j)
                    y_plus.append(i)
                else:
                    x_minus.append(j)
                    y_minus.append(i)

        plt.scatter(x_minus, y_minus)
        plt.legend("minus")
        plt.scatter(x_plus, y_plus)
        plt.legend("plus")
        plt.show()

    def magnetism(self):
        return np.abs(self.lattice.mean())


if __name__ == '__main__':
    y = []
    x_ = np.arange(1, 5, 0.1)
    test_ising = Ising(32, 32)
    test_ising.gen = False
    for T in (x_):
        mag = []
        p = 1 - np.exp(-(1 / T) * 2)
        for i in (range(100)):
            while not test_ising.gen:
                print(i)
                test_ising.cluster_ising(p, "triangular")
                mag.append(test_ising.magnetism())
        test_ising.gen = False
        mn = np.mean(mag)
        y.append(mn)
    plt.plot(x_, y)
    plt.xlabel("T")
    plt.ylabel("magnetism")
    x_line = np.arange(0, 1.1, 0.1)
    plt.plot([2.266] * x_line.shape[0], x_line, '-')
    plt.show()
