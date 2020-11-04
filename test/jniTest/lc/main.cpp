#include<iostream>
#include<vector>
#include<set>

using namespace std;


void insertRange(vector<pair<int,int> > &input, pair<int,int> node){
    if(input.empty()){
        input.push_back(node);
        return;
    }

    int idx = input.size();
    for(int i = 0;i<input.size();++i){
        if(node.first < input[i].first){
            idx = i;
            input.insert(input.begin() + i, node);
            break;
        }
        else if(input[i].first <= node.first && node.first <= input[i].second){
            input[i].first = min(input[i].first, node.first);
            input[i].second = max(input[i].second, node.second);
            idx = i;
            break;
        }
        else{
            continue;
        }
    }
    if(idx == input.size()){
        input.push_back(node);
        return;
    }

    {
        //method2
        for(auto it = input.begin() + idx + 1;it != input.end();){
            if(it->first > input[idx].second)break;
            input[idx].second = max(input[idx].second, it->second);
            it = input.erase(it);
        }
        return;
    }

    {
        //method1
        set<int> dels;

        for(int i = idx + 1;i<input.size();++i){
            if(input[i].first > input[idx].second)break;
            else{
                dels.insert(i);
                input[idx].second = max(input[idx].second, input[i].second);
            }
        }

        vector<pair<int,int> > tmp;
        for(int i = 0;i<input.size();++i){
            if(dels.count(i) == 0){
                tmp.push_back(input[i]);
            }
        }

        input.swap(tmp);
    }


}

int main(){
    vector<pair<int,int> > input{{1,2}, {3,5}, {6,7}, {8,10}, {12,16}}, input1{{1,3}, {6,9}};
    insertRange(input, pair<int,int>(4,8));
    insertRange(input1, pair<int,int>(4,5));

    for(auto node:input){
        std::cout<<node.first<<","<<node.second<<"  ";
    }

    cout<<endl<<"-------------------------------------------------"<<endl;

    for(auto node:input1){
        std::cout<<node.first<<","<<node.second<<"  ";
    }


    cout<<endl;
    return 0;
}


