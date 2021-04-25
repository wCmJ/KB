#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


void process_0421(string& curWord
                    , const string& endWord
                    , int &min_len
                    , vector<string>& tmp
                    , unordered_map<string, bool> &maps
                    , unordered_map<int, vector<vector<string>>> &res){
        if(curWord == endWord){
            for(auto &str:tmp){
                std::cout<<str<<" ";
            }
            std::cout<<"---------------------------"<<std::endl;
            res[tmp.size()].push_back(tmp);
            if(min_len == -1 || tmp.size() < min_len){
                min_len = tmp.size();
            }
            return;
        }          

        if(min_len != -1 && tmp.size() >= min_len){
            return;
        }       
        if(min_len != -1)
            std::cout<<"--------------  process_0421: "<<min_len<<"  -------------"<<std::endl;
        for(int i = 0;i<curWord.size();++i){
            char t = curWord[i];
            for(char j = 'a';j<='z';++j){
                if(j == t){
                    continue;
                }
                curWord[i] = j;
                if(maps.count(curWord) && !maps[curWord]){
                    maps[curWord] = true;
                    tmp.push_back(curWord);
                    process_0421(curWord, endWord, min_len, tmp, maps, res);
                    tmp.pop_back();
                    maps[curWord] = false;
                }
            }
            curWord[i] = t;
        }
    }

void dfs(vector<vector<string>> &res, const string &Node, unordered_map<string, set<string>> &from, vector<string>& path){
    if(from[Node].empty()){
        res.push_back({path.rbegin(), path.rend()});
        return;
    }

    for(const string& Parent: from[Node]){
        path.push_back(Parent);
        dfs(res, Parent, from, path);
        path.pop_back();
    }
}



vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //official
        {
            vector<vector<string>> res;
            unordered_set<string> dict = {wordList.begin(), wordList.end()};
            if(dict.find(endWord) == dict.end()){
                return res;
            }

            dict.erase(beginWord);

            unordered_map<string, int> steps = {{beginWord, 0}};
            unordered_map<string, set<string>> from = {{beginWord, {}}};

            int step = 0;
            bool found = false;

            queue<string> q = queue<string> {{beginWord}};

            int wordLen = beginWord.length();

            while(!q.empty()){
                step++;
                int size = q.size();
                
                for(int i = 0;i<size;++i){
                    const string currWord = move(q.front());
                    string nextWord = currWord;
                    q.pop();

                    for(int j = 0;j<wordLen;++j){
                        const char origin = nextWord[j];
                        for(char c = 'a';c<='z';++c){
                            nextWord[j] = c;
                            if(steps[nextWord] == step){
                                from[nextWord].insert(currWord);
                            }
                            if(dict.find(nextWord) == dict.end()){
                                continue;
                            }
                            dict.erase(nextWord);
                            q.push(nextWord);
                            from[nextWord].insert(currWord);
                            steps[nextWord] = step;
                            if(nextWord == endWord){
                                found = true;
                            }
                        }
                        nextWord[j] = origin;
                    }
                }
                if(found){
                    break;
                }
            }
            if(found){
                vector<string> Path = {endWord};
                dfs(res, endWord, from, Path);
            }
            return res;
        }




        //0423
        //bfs
        {
            unordered_map<string, int> words;
            words[beginWord] = false;
            for(auto& word: wordList){
                words[word] = false;
            } 
            if(words.count(endWord) == 0)return vector<vector<string>> ();

            deque<string> dq;
            dq.push_back(beginWord);

            vector<vector<string>> res;
            unordered_map<string, vector<string>> record;
            record[beginWord] = vector<string>{beginWord};
            words[beginWord] = true;

            while(!dq.empty()){
                int len = dq.size();
                bool flag = false;
                for(int i = 0;i<len;++i){
                    string tmp = dq.front();
                    dq.pop_front();
                    
                    auto vecs = record[tmp];

                    for(int j = 0;j<tmp.size();++j){
                        char t = tmp[j];
                        for(int c = 'a';c<='z';++c){
                            if(c == t)continue;
                            tmp[j] = c;
                            if(words.count(tmp) && !words[tmp]){

                                if(tmp == endWord){
                                    flag = true;
                                    vecs.push_back(tmp);
                                    res.push_back(vecs);
                                    vecs.pop_back();
                                    continue;
                                }
                                words[tmp] = true;                                
                                vecs.push_back(tmp);
                                record[tmp] = vecs;
                                vecs.pop_back();
                                dq.push_back(tmp);
                            }
                        }
                        tmp[j] = t;
                    }
                }
                if(flag){
                    break;
                }
            }
            return res;
        }

int main(){
    {
        vector<string> strs{"hot","dot","dog","lot","log","cog"};
        string bw = "hit", ew = "cog";
        auto res = findLadders(bw, ew, strs);

        return 0;


    }





    vector<string> strs{"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal"
                        ,"bar","die","war","hay","eco"
                        ,"pub","lob","rue","fry","lit"
                        ,"rex","jan","cot","bid","ali"
                        ,"pay","col","gum","ger","row"
                        ,"won","dan","rum","fad","tut"
                        ,"sag","yip","sui","ark","has"
                        ,"zip","fez","own","ump","dis"
                        ,"ads","max","jaw","out","btu"
                        ,"ana","gap","cry","led","abe"
                        ,"box","ore","pig","fie","toy"
                        ,"fat","cal","lie","noh","sew"
                        ,"ono","tam","flu","mgm","ply"
                        ,"awe","pry","tit","tie","yet"
                        ,"too","tax","jim","san","pan"
                        ,"map","ski","ova","wed","non"
                        ,"wac","nut","why","bye","lye"
                        ,"oct","old","fin","feb","chi"
                        ,"sap","owl","log","tod","dot"
                        ,"bow","fob","for","joe","ivy"
                        ,"fan","age","fax","hip","jib"
                        ,"mel","hus","sob","ifs","tab"
                        ,"ara","dab","jag","jar","arm"
                        ,"lot","tom","sax","tex","yum"
                        ,"pei","wen","wry","ire","irk"
                        ,"far","mew","wit","doe","gas"
                        ,"rte","ian","pot","ask","wag"
                        ,"hag","amy","nag","ron","soy"
                        ,"gin","don","tug","fay","vic"
                        ,"boo","nam","ave","buy","sop"
                        ,"but","orb","fen","paw","his"
                        ,"sub","bob","yea","oft","inn"
                        ,"rod","yam","pew","web","hod"
                        ,"hun","gyp","wei","wis","rob"
                        ,"gad","pie","mon","dog","bib"
                        ,"rub","ere","dig","era","cat"
                        ,"fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog"
                        ,"hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev"
                        ,"axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat"
                        ,"sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd"
                        ,"you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam"
                        ,"zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew"
                        ,"zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada"
                        ,"bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut"
                        ,"ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun"
                        ,"try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod"
                        ,"fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red"
                        ,"doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup"
                        ,"jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo"
                        ,"nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot"
                        ,"sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah"
                        ,"hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola"
                        ,"ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil"
                        ,"rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her"
                        ,"nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow"
                        ,"jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin"
                        ,"dun","pat","ten","mob"};

    string bw = "cem", ew = "ism";

    auto res = findLadders(bw, ew, strs);



    return 0;
}
