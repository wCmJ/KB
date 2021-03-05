


void preprocess(const string &p, vector<int> &v){
    if(p.size() == 0){
        return;
    }
    if(p.size() == 1){
        v[0] == -1;
        return;
    }
    v[0] = -1;
    v[1] = 0;
    int i = 2, cn = 0;
    while(i < p.size()){
        if(p[i-1] == p[cn]){
            v[i++] = ++cn;
        }
        else{
            if(cn == 0){
                ++i;
            }
            else{
                cn = v[cn];
            }
        }
    }
}

int kmp(const string& s, const string &p){
    vector<int> next(p.size(), 0);
    getNext(p, next);
    int i = 0, j = 0;
    while(i < s.size() && j < p.size()){
        if(s[i] == p[j]){
            ++i;
            ++j;
        }
        else{
            if(j == 0){
                ++i;
            }
            else{
                j = next[j];
            }
        }
    }
    return j == p.size() ? i - j : -1;
}




