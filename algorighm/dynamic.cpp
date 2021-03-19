#include <iostream>
#include <vector>


/*
    n个栅栏，k中颜色，不存在超过2个相邻柱子颜色相同，共有多少种染色方案？
    思路：
        栅栏从第一个到第n个，依次编号0~n-1
        每个栅栏维护一对数（x，y），x表示和前一个栅栏颜色相同的染色方案，y表示和前一个颜色不同的染色方案
        对于第n个栅栏的值(x,y)，已知第n-1个栅栏的值为(x1,y1)
        则  x = y1: 第n个和第n-1个相同，则第n-1和第n-2必须不同
            y = x1 * (k-1) + y1 * (k-1) = (x1 + y1) * (k-1): 只要保证第n个和第n-1个不同即可
        初始值为：x = 0, y = k
*/

int color_counts(int n, int k){
    if(n < 0 || k < 0)return 0;
    if(k == 1){
        return n <= 2 ? 1 : 0;
    }
    std::pair<int,int> cnts(0, k);
    for(int i = 1;i<n;++i){
        int same = cnts.second;
        int not_same = (cnts.first + cnts.second) * (k-1);
        cnts.first = same;
        cnts.second = not_same;
    }
    return cnts.first + cnts.second;
}

/*
    有两种高度的砖3和7，给出一个高度x，是否能由这两种砖砌成，砖的数量不限
    思路：
        构建一个数组F[0, x]，遍历砖的高度
        对于第n个高度的砖，F[i]的状态为F[i] || F[i-n] || F[i-2*n] || ...
*/

bool wall(int x, std::vector<int> heights){
    std::vector<bool> F(x+1);
    for(int i = 0;i<x+1;++i){
        if(i % heights[0] == 0){
            F[i] = true;
        }
        else{
            F[i] = false;
        }
    }

    for(int i = 1;i<heights.size();++i){
        if(F[x])return true;
        for(int j = x;j>=0;--j){
            for(int k = 1;k*heights[i] <= j;++k){
                F[j] = F[j] || F[j-k*heights[i]];
            }
        }
    }
    return F[x];
}


int main(){
    std::cout<<color_counts(3,2)<<std::endl;
    std::cout<<color_counts(4,2)<<std::endl;

    std::vector<int> heights = {3,7};
    std::cout<<wall(13, heights)<<std::endl;
    std::cout<<wall(9, heights)<<std::endl;
    std::cout<<wall(8, heights)<<std::endl;
    std::cout<<wall(23, heights)<<std::endl;
    return 0;
}


