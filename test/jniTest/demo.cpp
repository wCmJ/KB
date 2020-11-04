//#include "demo.h"
#include<iostream>
#include "jni.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_demo_sayHello(JNIEnv *, jobject){
    cout<<"hello"<<endl;
}
#ifdef __cplusplus
}
#endif


