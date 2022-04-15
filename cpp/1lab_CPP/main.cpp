#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool sortByVal(const pair<string, int> &a, const pair<string, int> &b) {
    return (a.second > b.second);
}

int main(int argc, char** argv) {
    string in_name = argv[1];
    string out_name = argv[2];
    string s;

    ifstream in(in_name);
    list <string> buff;
    while(getline(in, s))
        buff.push_back(s);
    in.close();
    map <string, int> mp;
    int all = 0;
    while(!buff.empty()){
        s = buff.front();
        buff.pop_front();
        string w;
        for(char i : s) {
            if(!isdigit(i) and !isalpha(i)) {
                if(!w.empty()) {
                    mp[w] += 1;
                    ++all;
                }
                w.clear();
                continue;
            }
            w += i;
        }
        if(!w.empty()) {
            ++all;
            mp[w] += 1;
        }
    }
    vector<pair<string, int>> vec;
    map<string, int> :: iterator it2;
    for (it2=mp.begin(); it2!=mp.end(); it2++)
        vec.emplace_back(it2->first, it2->second);
    sort(vec.begin(), vec.end(), sortByVal);
    std::map<string,int>::iterator it;
    ofstream out(out_name);
    for (auto & i : vec) {
        double d = (double) (i.second) / all * 100;
        out << i.first << ',' << i.second << ',' << d << " %\n";
    }
    out.close();
    return 0;
}
