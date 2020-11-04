
#include "test.h"
#include "impl.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     test
 * Method:    testPrint
 * Signature: ()V
 */
void JNICALL Java_test_testPrint
  (JNIEnv *, jobject){
      Singleton::Instance().Print();
}

jint JNICALL Java_test_transfer(JNIEnv *env, jobject obj){
    return 0;
  }

void JNICALL Java_test_set
  (JNIEnv *env, jobject obj, jint input){
    Singleton::Instance().Set(input);
  }

jint JNICALL Java_test_get
  (JNIEnv *, jobject){
    jint res = (jint)Singleton::Instance().Get();
    return res;
  }


#ifdef __cplusplus
}
#endif

