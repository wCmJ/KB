

public class demo{
    {
        System.setProperty("java.library.path", "/Users/youliwei/Documents/test/jniTest");
        //System.load("/Users/youliwei/Documents/test/jniTest/libdemo.so");
        System.loadLibrary("libdemo.so");
    }

    public native void sayHello();

    public static void main(String[] args){
        new demo().sayHello();
    }


}