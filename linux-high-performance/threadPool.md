NonCopyable: 
    - protected:
        - NonCopyable()
        - ~NonCopyable()
    - private:
        - NonCopyable(const NonCopyable&)
        - const NonCopyable& operator=(const NonCopyable&)

IThread: NonCopyable
    - public:
        - virtual ~IThread()
        - virtual void Run() = 0
        - void Start()
        - void Join()
    - private:
        