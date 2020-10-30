

public class HelloWorld{
    public static native String sayHello(String name);

    public static void main(String[] args){
        String libraryDirs = System.getProperty("java.library.path");  
        System.out.println(libraryDirs);
        String text = sayHello("yx");
        System.out.println(text);
    }

    static{
        System.loadLibrary("HelloWorld");
    }


}



