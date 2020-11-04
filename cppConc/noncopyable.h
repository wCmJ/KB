#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class noncopyable{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif //#ifndef NON_COPYABLE_H
