#include <iostream>
#include <cassert>
#include <vector>
#include "trit.h"

using namespace std;
using uint = unsigned int;
// 1,0 - True;   0,1 - False

TritSet::TritSet() {
    data = nullptr;
    length = 0;
}

TritSet::TritSet(int len) : length(len) {
    assert(len >= 0);
    data = new bool[len * 2];
    for (int i = 0; i < len*2; ++i)
        data[i] = false;
}

int TritSet::getData(int index) {
    assert(index >= 0);
    if(index >= length)
        reallocate(index+1);
    int t = data[index*2] * 10 + data[index*2+1];
    if(t == 10)
        return 1;
    else if(t == 1)
        return -1;
    else
        return 0;
}

int TritSet::getIndex() {
    int i = index_to_save;
    index_to_save = -1;
    return i;
}

TritSet& TritSet::operator=(int trit) {
    if (trit == 1) {
        if(length < index_to_save) {
            return *this;
        }
        data[index_to_save * 2] = false;
        data[index_to_save * 2 + 1] = false;
        return *this;
    }

    if (length <= index_to_save)
        reallocate(index_to_save + 1);

    if (trit == 2) {
        data[index_to_save * 2] = true;
        data[index_to_save * 2 + 1] = false;
    } else if (trit == 0) {
        data[index_to_save * 2] = false;
        data[index_to_save * 2 + 1] = true;
    }

    index_to_save = -1;
    return *this;
}

TritSet& TritSet::operator[](int index) {
    index_to_save = index;
    return *this;
}

int TritSet::capacity() const {
    return length;
}

void TritSet::shrink() {
    int c = 0;
    for(int i = 0; i < length * 2; i += 2)
        if(data[i] == 1 or data[i+1] == 1)
            c = i ;
    reallocate(c/2 + 1);
}

void TritSet::reallocate(int len) {
    if (len == length)
        return;
    bool *data_new;
    data_new = new bool[len * 2];

    if (length > 0) {
        int elementsToCopy = (len > length) ? length : len;
        int index;
        for (index = 0; index < elementsToCopy * 2; index += 2) {
            data_new[index] = data[index];
            data_new[index + 1] = data[index + 1];
        }
        for (; index < len * 2; index += 2) {
            data_new[index] = false;
            data_new[index + 1] = false;
        }
    }

    delete[] data;

    data = data_new;
    length = len;
}

bool operator == (TritSet c1, int c2) {
    int index = c1.getIndex();
    int len = c1.capacity();

    if (index >= len)
        return false;
    else {
        int g = c1.getData(index);
        return g == c2;
    }
}

TritSet& operator&(TritSet c1, TritSet c2) {
    int s1 = c1.capacity();
    int s2 = c2.capacity();
    int len = s1 > s2? s1 : s2;
    auto b = new TritSet(len);
    for(int i = 0; i < len; ++i) {
        int x = c1.getData(i);
        int y = c2.getData(i);
        if(x == 0) {
            if(y == 0 or y == 1) {
                (*b)[i] = 1;
            } else {
                (*b)[i] = 0;
            }
        } else if(x == 1) {
            if(y == 0) {
                (*b)[i] = 1;
            } else if(y == 1) {
                (*b)[i] = 2;
            } else {
                (*b)[i] = 0;
            }
        } else {
            (*b)[i] = 0;
        }
    }
    return *b;
}

TritSet& operator|(TritSet c1, TritSet c2) {
    int len = c1.capacity() > c2.capacity()? c1.capacity() : c2.capacity();
    auto b = new TritSet(len);
    for(int i = 0; i < len; ++i) {
        int x = c1.getData(i);
        int y = c2.getData(i);
        if(x == 0) {
            if(y == 1) {
                (*b)[i] = 2;
            } else {
                (*b)[i] = 1;
            }
        } else if(x == 1) {
            (*b)[i] = 2;
        } else {
            (*b)[i] = y+1;
        }
    }
    return *b;
}

TritSet& operator~(TritSet c1) {
    int len = c1.capacity();
    auto b = new TritSet(len);
    for(int i = 0; i < len; ++i) {
        int x = c1.getData(i);
        if(x == -1)
            (*b)[i] = 2;
        else if(x == 0)
            (*b)[i] = 1;
        else
            (*b)[i] = 0;
    }
    return *b;
}