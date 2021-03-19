#include <vector>
#include <iostream>

class segment_tree{
public:
    segment_tree(const std::vector<int>& datas){
        _datas = datas;
        _size = datas.size();
        _sum_datas = new int[3 * _size];
        _init(0, 0, _size - 1);
    }
    ~segment_tree(){
        delete[] _sum_datas;
    }

    int search_sum(int l, int r){
        if(l < 0 || r >= _size){
            //error
            return 0;
        }
        return _search_sum(0, 0, _size - 1, l, r);
    }
    void update(int i, int val){
        if(i < 0 || i >= _size){
            return;
        }
        _update(0, 0, _size - 1, i, val);
    }
    void print_data(){
        std::cout<<"_datas:"<<std::endl;
        for(auto n:_datas){
            std::cout<<n<<" ";
        }
        std::cout<<std::endl<<"_sum_datas:"<<std::endl;
        for(int i = 0;i<3*_size;++i){
            std::cout<<_sum_datas[i]<<" ";
        }
        std::cout<<std::endl;
    }

private:

    void _update(int idx, int sl, int sr, int i, int val){
        if(sl > i || sr < i || idx >= 3 * _size){
            return;
        }
        if(sl == sr){
            if(sl == i){
                _datas[sl] = val;
                _sum_datas[idx] = val;
            }
            return;
        }
        int mid = sl + (sr - sl)/2;
        if(mid >= i){
            _update(2*idx+1, sl, mid, i, val);
        }
        else{
            _update(2*idx + 2, mid + 1, sr, i, val);
        }
        int lv = (2*idx+1 < 3 * _size ? _sum_datas[2*idx+1] : 0);
        int rv = (2*idx+2 < 3 * _size ? _sum_datas[2*idx+2] : 0);
        _sum_datas[idx] = lv + rv;
    }

    int _search_sum(int idx, int sl, int sr, int l, int r){
        if(sl >= l && sr <= r){
            return _sum_datas[idx];
        }
        int mid = sl + (sr - sl)/2;
        if(mid >= r){
            return _search_sum(2 * idx + 1, sl, mid, l, r);
        }
        else if(mid < l){
            return _search_sum(2 * idx + 2, mid + 1, sr, l, r);
        }
        else{
            return _search_sum(2 * idx + 1, sl, mid, l, r)
                +  _search_sum(2 * idx + 2, mid + 1, sr, l, r);
        }
    }

    int _init(int idx, int left, int right){
        if(idx >= 3 * _size || left > right){
            return 0;
        }
        if(left == right){
            _sum_datas[idx] = _datas[left];
            return _datas[left];
        }
        int mid = left + (right - left)/2;
        int lv = _init(2*idx + 1, left, mid);
        int rv = _init(2*idx + 2, mid + 1, right);
        _sum_datas[idx] = lv + rv;
        return lv + rv;
    }

    std::vector<int> _datas;
    int* _sum_datas;
    int _size;
};


int main(){
    std::vector<int> datas{1,5,3,9,7,10,25};
    segment_tree st(datas);
    st.print_data();
    std::cout<<st.search_sum(1,4)<<std::endl;
    std::cout<<st.search_sum(2,5)<<std::endl;
    st.update(3, 10);
    std::cout<<st.search_sum(1,4)<<std::endl;
    std::cout<<st.search_sum(2,5)<<std::endl;
    st.print_data();


    return 0;
}
