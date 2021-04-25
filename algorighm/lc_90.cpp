#include <string>
#include <vector>

using std::string;
using std::vector;

bool equal(const string s1, const string s2, const string s3){
    if(s3.size() != s1.size() + s2.size())return false;
    if(s3 == s1 + s2 || s3 == s2 + s1)return true;
    int l1 = s1.size(), l2 = s2.size();

    if(s3[0] != s1[0] && s3[0] != s2[0])return false;
    vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
    
    dp[0][0] = true;
    
    for(int i = 0;i<=l1;++i){
        for(int j = 0;j<=l2;++j){
            int p = i + j - 1;
            if(i > 0){
                dp[i][j] = dp[i][j] || (dp[i-1][j] && (s3[p] == s1[i - 1]));
            }
            if(j > 0){
                dp[i][j] = dp[i][j] || (dp[i][j-1] && (s3[p] == s2[j - 1]));
            }
        }
    }
    return dp[l1][l2];
}


bool equal(const string s1, const string s2, const string s3){
    if(s3.size() != s1.size() + s2.size())return false;
    if(s3 == s1 + s2 || s3 == s2 + s1)return true;
    int l1 = s1.size(), l2 = s2.size();

    if(s3[0] != s1[0] && s3[0] != s2[0])return false;

    vector<int> dp(l2 + 1, false);
    for(int i = 0;i<=l1;++i){
        for(int j = 0;j<=l2;++j){
            int p = i + j - 1;
            if(i > 0){
                dp[j] = dp[j] && (s3[p] == s1[i-1]);
            }
            if(j > 0){
                dp[j] = dp[j] || (dp[j-1] && (s3[p] == s2[j-1]));
            }
        }
    }
    return dp[l2];
}




