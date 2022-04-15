import numpy as np
import pandas as pd


def main2_pandas(path1, path2):
    """
    Reads csv file from path1, filters it, adds new columns and changes few available
    Then writes into path2
    :param path2:
    :param path1:
    :return:
    """

    global mx
    global md

    df = pd.read_csv(path1, sep=' ', index_col=0)
    df = df[(df['sex'] == 'М') | (df['sex'] == 'м') | (df['sex'] == 'Ж')
            | (df['sex'] == 'ж') | (df['sex'] == 'm') | (df['sex'] == 'M') | (df['sex'] == 'Мужчина')]
    mx = df['row_number'].idxmax()
    df_m = df[(df['liters_drunk'] >= 0) & (df['liters_drunk'] < 7)]
    md = df_m['liters_drunk'].mean()
    df['age_0'] = 0
    df['age_18'] = 0
    df['age_50'] = 0
    df['morning'] = 0
    df['day'] = 0
    df['evening'] = 0
    df = df.apply(main1_pandas, axis=1)
    del df['age']
    df = df.astype(int)
    df.to_csv(path2)


def main1_pandas(row):
    """
    Function takes row and do this:
    1) Converts column 'sex' into digit version
    2) Converts column null values of 'row_number' into max in 'row_number'
    3) Converts column bad values of 'liters_drunk' into mean value
    4) Changes columns 'age_0', 'age_18', 'age_50' to 1 or 0 depending on 'age'
    5) Changes column 'drink' into 1 or 0 depending on whether it was beer
    6) Changes columns 'morning', 'day', 'evening' depending on check_number:
            if      (0 <= x < 3333) then (day == 1)
            elif    (3333 <= x < 6666) then (day == 1)
            else    (evening == 1)
    Then returns modified row
    :param row
    :return row
    """
    n = row.at['sex']
    if n == 'M' or n == 'm' or n == 'М' or n == 'м':
        row.at["sex"] = 1
    else:
        row.at["sex"] = 0

    n = row.at["row_number"]
    if np.isnan(n):
        row.at["row_number"] = mx

    n = row.at["liters_drunk"]
    if n > 7 or n < 0:
        row.at["liters_drunk"] = round(md)

    n = row.at['age']
    if 0 < n < 18:
        n = 'age_0'
    elif 18 <= n < 50:
        n = 'age_18'
    elif n >= 50:
        n = 'age_50'
    row.at[n] = 1

    n = row.at['drink']
    if 'beer' in n:
        row.at['drink'] = 1
    else:
        row.at['drink'] = 0

    t = row.at['check_number']
    g = 0
    f = ''
    if not g:
        g = t // 6666
        f = "evening"
    if not g:
        g = t // 3333
        f = "day"
    if not g:
        f = "morning"
    row.at[f] = 1

    return row


main2_pandas("cinema_sessions.csv", "cinema_sessions_refactored.csv")
