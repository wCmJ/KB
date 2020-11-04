

public class test{

    {
        System.load("/Users/youliwei/Documents/klog/klogrecovery/boostasiodemo/src/libtest.dylib");
    }

    public native void testPrint();

    public native int transfer();

    public native void set(int val);

    public native int get();

    public static void main(String[] args){
        new test().testPrint();
        new test().set(50);
        System.out.println(new test().get());
    }


}

