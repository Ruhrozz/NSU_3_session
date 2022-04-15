from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score


def fst_tsk():
    df_main = pd.read_csv('titanic_prepared.csv', index_col=0)
    tst = df_main.iloc[:6000]
    tst = tst.drop(['row_number', 'check_number'], axis=1)
    real = df_main.iloc[6000:]
    real = real.drop(['row_number', 'check_number'], axis=1)

    model1 = DecisionTreeClassifier(splitter='random', criterion='entropy', random_state=0)
    model2 = XGBClassifier(max_depth=20,
                           eval_metric='mlogloss',
                           use_label_encoder=False,
                           n_estimators=40)
    model3 = LogisticRegression(random_state=0, max_iter=800,
                                solver='saga', multi_class='multinomial')

    model_all = [model1, model2, model3]
    model_names = ['DecisionTree', 'XGBoost', 'LogisticRegression']

    for i in range(0, len(model_all)):
        model = model_all[i]
        model.fit(tst.drop('label', axis=1), tst['label'])
        print(accuracy_score(model.predict(real.drop(['label'], axis=1)), real['label']) * 100, end='% ')
        print(model_names[i])

    importances = model1.feature_importances_
    features = tst.drop('label', axis=1).columns
    # Добавление сортировки по важности
    indices = np.argsort(importances)

    plt.title('Важность признаков')
    plt.barh(range(len(indices)), importances[indices], color='b', align='center')
    plt.yticks(range(len(indices)), features[indices])
    plt.xlabel('Относительная важность')
    plt.show()

    print()

    tst = tst.drop(['evening', 'age_old', 'day', 'age_adult', 'age_child',
                    'drink', 'sex'], axis=1)
    real = real.drop(['evening', 'age_old', 'day', 'age_adult', 'age_child',
                      'drink', 'sex'], axis=1)
    model_x = DecisionTreeClassifier(max_depth=3, criterion='entropy')

    model_x.fit(tst.drop(['label'], axis=1), tst['label'])

    print(accuracy_score(model_x.predict(real.drop(['label'], axis=1)), real['label']) * 100, end='% by two features\n')


class MyForest:
    def __init__(self, n_estimators=6):
        if n_estimators < 1:
            raise "error\n"
        self.n_estimators = n_estimators
        self.models = []
        for i in range(0, n_estimators):
            model = DecisionTreeClassifier(max_features='sqrt',
                                           criterion='entropy')
            self.models.append(model)

    def fit(self, data):
        for model in self.models:
            rnd = data.sample(frac=1, replace=True)
            rnd_prep_y = rnd['label']
            rnd_prep_x = rnd.drop(['label'], axis=1)
            model.fit(rnd_prep_x.values, rnd_prep_y.values)

    def predict(self, data):
        p = []
        data = data.values
        for i in self.models:
            p.append(i.predict(data))
        p = np.array(p)
        p = p.sum(axis=0)
        p = p / self.n_estimators
        p = p > 0.5
        return p * 1


def snd_tsk():
    s = MyForest(100)
    df_main = pd.read_csv('titanic_prepared.csv', index_col=0)
    tst = df_main.iloc[:6000]
    real = df_main.iloc[6000:]
    s.fit(tst)
    data = np.array(s.predict(real.drop(['label'], axis=1)))
    print(accuracy_score(data, real['label']) * 100, end='%\n')


snd_tsk()
