#ifndef UNTITLED2_TRIT_H
#define UNTITLED2_TRIT_H

class TritSet {
private:
    int length;
    bool *data;
    int getIndex();
public:
    int index_to_save = -1;
    TritSet();
    explicit TritSet(int len);
    int getData(int index);
    TritSet &operator=(int trit);
    TritSet &operator[](int index);
    int capacity() const;
    void shrink();
    void reallocate(int len);
    friend bool operator == (TritSet c1, int c2);
    friend TritSet &operator & (TritSet c1, TritSet c2);
    friend TritSet& operator|(TritSet c1, TritSet c2);
    friend TritSet& operator~(TritSet c1);
};

bool operator == (TritSet c1, int c2);
TritSet& operator&(TritSet c1, TritSet c2);
TritSet& operator|(TritSet c1, TritSet c2);
TritSet& operator~(TritSet c1);

#endif
