import numpy as np
import random_select as rs
import get_data as gd


file1, file2, p = gd.get_data()
# file1, file2, p = "input1.txt", "input2.txt", 0.2

with open(file1) as f1:
    real = np.fromfile(f1, sep=" ")
with open(file2) as f2:
    syn = np.fromfile(f2, sep=" ")

if real.size != syn.size:
    raise ValueError

rs.random_select1(real, syn, p)
