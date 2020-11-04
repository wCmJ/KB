#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

class joining_thread
{
  std::thread t;
public:
  joining_thread() noexcept=default;
  template<typename Callable,typename ... Args>
  explicit joining_thread(Callable&& func,Args&& ... args):
    t(std::forward<Callable>(func),std::forward<Args>(args)...)
  {}
  explicit joining_thread(std::thread t_) noexcept:
    t(std::move(t_))
  {}
  joining_thread(joining_thread&& other) noexcept:
    t(std::move(other.t))
  {}
  joining_thread& operator=(joining_thread&& other) noexcept
  {
    if(joinable()){
      join();
    }
    t = std::move(other.t);
    return *this;
  }
  joining_thread& operator=(std::thread other) noexcept
  {
    if(joinable())
      join();
    t=std::move(other);
    return *this;
  }
  ~joining_thread() noexcept
  {
    if(joinable())
    join();
  }
  void swap(joining_thread& other) noexcept
  {
    t.swap(other.t);
  }
  std::thread::id get_id() const noexcept{
    return t.get_id();
  }
  bool joinable() const noexcept
  {
    return t.joinable();
  }
  void join()
  {
    t.join();
  }
  void detach()
  {
    t.detach();
  }
  std::thread& as_thread() noexcept
  {
    return t;
  }
  const std::thread& as_thread() const noexcept
  {
    return t;
  }
};



class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_): 
    t(std::move(t_))
  {
    if(!t.joinable()){
      //throw std::logic_error(“No thread”);
    }
  }
  ~scoped_thread()
  {
    t.join();
  }
  scoped_thread(scoped_thread const&)=delete;
  scoped_thread& operator=(scoped_thread const&)=delete;
};
void do_work(int i){}

void f()
{
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < 20; ++i)
  {
    threads.emplace_back(std::thread(do_work,i)); // 产生线程
  } 
  for (auto& entry : threads) // 对每个线程调用 join()
    entry.join();       
}

void non(){}

//std::thread::id
//std::this_thread::get_id()


void transfer(){
    std::thread t1(non);
    std::cout<<std::this_thread::get_id()<<std::endl;
    std::thread t2 = std::move(t1);
    t1 = std::thread(non);//临时对象会隐式调用移动操作
    std::thread t3;// valid: t1, t2; invalid: t3
    t3 = std::move(t2);// valid: t1, t3; invalid: t2
    t1 = std::move(t3);//abort
}




void refe(int &i){
    i = 2;
    std::cout<<"child-thread refe: "<<i<<std::endl;
    sleep(2);
    i = 10;
    std::cout<<"refe after sleep: "<<i<<std::endl;

}

void val(int i){
    i = 3;
    std::cout<<"child-thread val: "<<i<<std::endl;
}

void point(int* p){
    *p = 2;
    std::cout<<"child-thread point: "<<*p<<std::endl;
}


void tmp_func(){
    int tf = 10;
    std::thread st(refe, std::ref(tf));
    st.detach();
}

int main(){

    {
        transfer();
        tmp_func();


    }
    return 0;


    int i = 1;
    std::thread th(refe, std::ref(i));
    std::thread th1(val, i);
    int p = 1;
    std::thread thp(point, &p);
    thp.join();
    std::cout<<"main p: "<<p<<std::endl;
    th.join();
    th1.join();
    std::cout<<"main i: "<<i<<std::endl;

}

