import pandas as pd
import numpy as np


def function_task1(row):
    r = row[row > 0.3]
    print(r.mean())


def function_task2(row):
    t = pd.to_datetime(row['CompletionDate']) - pd.to_datetime(row['SpudDate'])
    print(round((t.days/30) + 0.5))


def task1():
    data1 = np.random.random((10, 5))
    df1 = pd.DataFrame(data1, columns=['a', 'b', 'c', 'd', 'e'])
    print(df1)
    df1.apply(function_task1, axis=1)


def task2():
    df = pd.read_csv("wells_info.csv")
    df.apply(function_task2, axis=1)
