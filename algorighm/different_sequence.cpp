#include <iostream>
#include <string>

using std::string;

/*
    i.e. s="rabbbit" t="rabbit" return 3
    dp[i][j]表示在s[i:]的子序列中t[j:]出现的个数
    s[i:]表示s从下标i到末尾的子字符串
    t[j:]表示t从下标j到末尾的子字符串

    1. 当j=n时，t[j:]为空，由于空字符串是任何字符串的子序列，因此对任意i，有dp[i][n] = 1;
    2. 当i=m时且j<n时，s[i:]为空字符串，因此dp[m][j] = 0
    3. 当i<m且j<n时，
        3.1. 当s[i] = t[j]时，dp[i][j]由两部分组成：
            3.1.1. 如果s[i]和t[j]匹配，则考虑t[j+1:]作为s[i+1:]的子序列，dp[i+1][j+1]
            3.1.2. 如果s[i]和t[j]不匹配，则考虑t[j:]作为s[i+1:]的子序列，dp[i+1][j]
            因此，dp[i][j] = dp[i+1][j+1] + dp[i+1][j]
        3.2. 当s[i] ≠ t[j]时，s[i]不能和t[j]匹配，因此只考虑t[j:]作为s[i+1:]的子序列，dp[i+1][j]
            因此，dp[i][j] = dp[i+1][j]
*/

int cnts(const string& s, const string& t){
    int ls = s.size(), lt = t.size();
    vector<vector<int>> dp(ls + 1, vector<int>(lt + 1, 0));
    for(int i = 0;i<ls+1;++i){
        dp[i][lt] = 1;
    }

    for(int i = ls - 1;i>=0;--i){
        for(int j = lt - 1;j>=0;--j){
            if(s[i] == t[j]){
                dp[i][j] = dp[i+1][j+1] + dp[i+1][j];
            }
            else{
                dp[i][j] = dp[i+1][j];
            }
        }
    }
    return dp[0][0];
}


