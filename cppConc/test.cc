
#include <unistd.h>

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <deque>
#include <list>
#include <random>
#include <time.h>


template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input){
    if(input.empty()){
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    T const& pivot = *result.begin();

    auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t){
        return t < pivot;
    });

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    auto new_lower(
        sequential_quick_sort(std::move(lower_part))
    );

    auto new_higher(
        sequential_quick_sort(std::move(input))
    );

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);
    return result;
}


class Itest{
public:
    virtual void printItest() = 0;
};

class Test: public Itest{
public:
    void printItest() override{
        std::cout<<"class Test"<<std::endl;
    }
};

template<typename T>
std::list<T> quick_sort(std::list<T> input){
    if(input.empty())return input;

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());
    const T val = *result.begin();

    auto len = std::partition(input.begin(), input.end(), [=](const T& t){return t < val;});

    std::list<T> lower;
    lower.splice(lower.begin(), input, input.begin(), len);

    auto res_lower = quick_sort(std::move(lower));

    //std::future<std::list<T>> res_higher = std::async(std::launch::async, quick_sort<T>,std::move(input));

    auto res_higher = quick_sort(std::move(input));

    result.splice(result.begin(), res_lower);
    //result.splice(result.end(), res_higher.get());
    result.splice(result.end(), res_higher);
    return result;
}





namespace fut{
    std::mutex m;
    std::deque<std::packaged_task<void()> > tasks;
    bool gui_shutdown_message_received(){
        return false;
    }
    void get_and_process_gui_message(){}

    void gui_thread(){
        while(!gui_shutdown_message_received()){
            get_and_process_gui_message();
            std::packaged_task<void()> task;
            {
                std::lock_guard<std::mutex> lk(m);
                if(tasks.empty()){
                    continue;
                }
                task = std::move(tasks.front());
                tasks.pop_front();
            }            
            task();
        }
    }
    std::thread gui_bg_thread(gui_thread);
    template<typename Func>
    std::future<void> post_task_for_gui_thread(Func f){
        std::packaged_task<void()> task(f);
        std::future<void> res = task.get_future();
        std::lock_guard<std::mutex> lk(m);
        tasks.push_back(std::move(task));
        return res;
    }
}





std::condition_variable cv;

int find_the_answer(int n){
    //sleep(10);
    std::cout<<"find_the_answer: "<<std::this_thread::get_id()<<std::endl;;
    return n + 100;
}
void do_other_stuff(){
    //sleep(5);
}







int g_int = 20;

class thread_guard{
public:
    explicit thread_guard(std::thread& th):th_(th){}
    ~thread_guard(){
        if(th_.joinable()){
            th_.join();
        }
    }

    thread_guard(const thread_guard& ) = delete;
    thread_guard& operator=(const thread_guard&) = delete;

private:    
    std::thread& th_;    
};

class scoped_thread{
public:
    scoped_thread(std::thread th):th_(std::move(th)){
        if(!th_.joinable()){
            throw std::logic_error("No thread");
        }
    }
    ~scoped_thread(){        
        std::cout<<"deconstruct"<<std::endl;
        th_.join();

    }
    std::thread& transfer(){
        return th_;
    }
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
private:
    std::thread th_;
};

int coinChange(std::vector<int>& coins, int amount) {

    {
        using std::vector;
        if(coins.empty())return 0;
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for(int i = 0;i<coins.size();++i){
            for(int j = 0;j<amount+1;++j){
                if(j >= coins[i])dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return dp[amount] >= amount + 1 ? -1 : dp[amount];


        for(int i = 1;i<amount + 1;++i){
            for(int j = 0;j<coins.size();++j){
                if(i >= coins[j]){
                    dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] >= amount + 1 ? -1 : dp[amount];


    }


    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for(int i = 0;i<coins.size();++i){
        for(int j = amount; j >= 1;--j){
            for(int k = 0;k*coins[i] <= j;++k){
                dp[j] = std::min(dp[j], k + dp[j - k*coins[i]]);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}


struct suc{
    int &ri_;
    suc(int &ri):ri_(ri){}
    void operator()(){
        for(int i = 0;i<10000000;++i){
            ri_ += i;
        }
        std::cout<<ri_<<std::endl;
    }
};

void refe(int &input){

}

void ops(){
    int tmp = 20;
    suc so(tmp);
    std::thread th(so);
    thread_guard tg(th);

}

class background{
public:
    void operator()(){
        std::cout<<"class background"<<std::endl;
    }
};



void oops(){
    std::cout<<std::thread::hardware_concurrency()<<std::endl;
}

std::thread g_th1, g_th2;



void thread1(){
    std::cout<<"thread1 start"<<std::endl;
    //sleep(5);
    if(g_th2.joinable()){
        g_th2.join();
    }
    std::cout<<"thread1 exit"<<std::endl;
}

void thread2(){
    std::cout<<"thread2 start"<<std::endl;
    //sleep(10);
    if(g_th1.joinable()){
        g_th1.join();
    }
    std::cout<<"thread2 exit"<<std::endl;
}

#if 0
std::unique_lock<std::mutex> get_lock(){
    extern std::mutex some_mutex;
    std::unique_lock<std::mutex> lk(some_mutex);
    return lk;
}

void process_data(){
    std::unique_lock<std::mutex> lk(get_lock());
    std::cout<<"process_data"<<std::endl;
}
#endif

class cls{
public:
    static void class_func(){
        //sleep(1);
        std::cout<<"class_func: "<<std::this_thread::get_id()<<std::endl;
    }
    void class_func_non_static(){
        std::cout<<"class_func_non_static"<<std::this_thread::get_id()<<std::endl;
    }
};

void new_func(){
    std::cout<<"new_func: "<<std::this_thread::get_id()<<std::endl;
}

double square_root(double x){
    if(x < 0){
        throw std::out_of_range("x < 0");
    }
    return sqrt(x);
}
using std::list;

class TH_test{
public:
    int th_func(){
        sleep(3);
        std::cout<<"class::th_func: "<<std::this_thread::get_id()<<std::endl;        
        return 1;
    }
};



int main(){
    {
        {
            TH_test tt;
            std::thread th = std::thread(static_cast<int (TH_test::*)()>(&TH_test::th_func), &tt);
            std::cout<<"main::"<<std::this_thread::get_id()<<std::endl;
            sleep(5);
            return 0;
        }




        {

            std::shared_ptr<int> sp = std::make_shared<int>(1);
            std::cout<<*sp<<std::endl;

            std::shared_ptr<Itest> spi = std::make_shared<Test>();
            //auto tmp = std::make_shared<Test>();
            //tmp->printItest();
            //spi = tmp;
            spi->printItest();
            std::cout<<std::endl;
        }






        {
            std::vector<int> coins{259,78,94,130,493,4,168,149};
            int amount = 4769;
            std::cout<<coinChange(coins, amount)<<std::endl;
            std::cout<<"end coinchange"<<std::endl;

        }

        #if 0
        {
            std::list<int> li{4,5,6,1,2,3,19};
            srand(time(NULL));
            for(int i = 0;i<10000;++i){
                li.push_back(rand() % 10000);
            }
            auto t1 = std::chrono::steady_clock::now();
            auto res = quick_sort(li);
            auto t2 = std::chrono::steady_clock::now();
            std::cout<<std::chrono::duration<double, std::milli>(t2 - t1).count()<<" ms"<<std::endl;
            for(auto it = res.begin();it != res.end();++it){
                std::cout<<*it<<" ";
            }
            std::cout<<"end quick_sort"<<std::endl;

        }
        

        {
            std::list<int> li{4,5,6,1,2,3,19};
            auto res = sequential_quick_sort(li);
            for(auto it = res.begin();it != res.end();++it){
                std::cout<<*it<<std::endl;
            }

            auto start = std::chrono::high_resolution_clock::now();
            for(int i = 0;i<100000;++i){

            }
            auto stop = std::chrono::high_resolution_clock::now();
            //std::cout<<"do something: "<<std::chrono::duration<long long, std::chrono::seconds>(stop - start).count()<<std::endl;

        }
        #endif

    }



    #if 0
    {
        std::future<double> f = std::async(std::launch::async,square_root, -1);
        double y = f.get();
        std::cout<<"y: "<<y<<std::endl;
    }
    #endif

    {
        std::future<void> sfv = std::async(std::launch::async, new_func);
        std::future<void> sfv2 = std::async(std::launch::deferred, new_func);
        //sleep(1);
        std::cout<<"main func(sleep 1s): "<<std::this_thread::get_id()<<std::endl;        
        
        sfv2.wait();




        cls cls_obj;
        std::future<void> cls_answer = std::async(&cls::class_func);
        std::future<void> cls_answer_non_static = std::async(&cls::class_func_non_static, &cls_obj);



        std::future<int> the_answer = std::async(find_the_answer, 100);
        std::cout<<"do_other_stuff start: "<<std::this_thread::get_id()<<std::endl;
        do_other_stuff();
        std::cout<<"do_other_stuff finished: "<<std::this_thread::get_id()<<std::endl;
        std::cout<<"The answer is: "<<the_answer.get()<<std::endl;
        std::cout<<"The answer is------: "<<the_answer.get()<<std::endl;
        
    }


    std::cout<<std::this_thread::get_id()<<std::endl;
    
    //scoped_thread st1((std::thread(oops)));
    //scoped_thread st2((std::thread(oops)));
    



#if 0
    int mi = 10;
    std::thread thr(refe, std::ref(mi));
    thr.join();


    std::thread ths(oops);
    ths.join();

    std::vector<int> some_list{1,2,3,4,5};
    int total = 0;
    std::for_each(begin(some_list)
                 ,end(some_list)
                 ,[=](int x){std::cout<<total<<std::endl;
                                //total += x;
                                g_int += 20;});
    



    std::thread bt((background()));
    bt.join();
    std::thread mt([=]{
        std::cout<<"g_int is: "<<g_int<<std::endl;
        g_int += 30;
        std::cout<<"g_int is: "<<g_int<<std::endl;

    });
    mt.join();
    std::cout<<"main g_int is: "<<g_int<<std::endl;
    #endif
    return 0;
}


/*
线程共享数据：
    只读没有冲突
    读写-写写

*/

