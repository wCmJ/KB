#include <iostream>
#include <string>
using namespace std;

/*
    "adc"
    "dcda"
*/


bool checkInclusion(string s1, string s2) {
    if(s1.empty() || s2.empty() || s1.size() > s2.size())return false;
    unordered_map<char, int> record;
    for(auto c:s1){
        record[c]++;
    }
    int len1 = s1.size(), len2 = s2.size();
    int cnt = 0;
    for(int i = 0;i<len1;++i){
        if(record.count(s2[i]) > 0){
            if(--record[s2[i]] == 0){
                ++cnt;
            }
        }
    }
    if(cnt == record.size())return true;
    int start = 0, end = len1;
    while(end < len2){
        if(record.count(s2[start]) > 0){
            if(++record[s2[start]] == 1){
                --cnt;
            }
        }
        if(record.count(s2[end]) > 0){
            if(--record[s2[end]] == 0){
                ++cnt;
            }
        }

        if(cnt == record.size())return true;
        ++end;
        ++start;
    }
    return false;
}