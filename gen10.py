import os
import numpy as np
import matplotlib.pyplot as plt
#os.chdir("C:/Users/Nikita/Documents/GitHub/Self-learning-Monte-carlo-algorithms")
#os.chdir("C:/aut/Self-learning-Monte-carlo-algorithms")
import Ising

#Train data generation
train = Ising.Ising(10, 10)
x = np.arange(1, 3.5, 0.0625)
label = []
curr_label = 0
X_train = []
var = []
y = []
N = 10**4
count = 0
for T in x:
    mag = []
    if T >= 2.266:
        curr_label = 0
    else :
        curr_label = 1
    for i in (range(N)):
        train.cluster_ising(1-np.exp(-(1/T)*2))
    for _ in (range(1000)):
        for _ in range(100):
            train.cluster_ising(1-np.exp(-(1/T)*2))
        X_train.append(np.array(train.lattice.reshape((1, train.y*train.x))[0]))
        label.append(curr_label)
    

# Save 30x30
np.save("data_size10_min1_max3.5_steap0.0625_batch1000_re100_N10000", X_train)
np.save("labels_size10_min1_max3.5_steap0.0625_batch1000_re100_N10000", label)
