//package kwai.lyou.test;

import java.io.*;
import java.util.Scanner;


public class Test{
    public void punAge(){
        int age = 0;
        age = age + 7;
        System.out.println("age is: " + age);
    }
    static void deleteFolder(File folder){
        File[] files = folder.listFiles();
        if(files != null){
            for(File f: files){
                if(f.isDirectory()){
                    deleteFolder(f);
                    f.delete();
                }
                else{
                    f.delete();
                }
            }
        }
    }

    static void intTest(int i){
        i = 10;
    }

    static void arrayTest(int[] arr){
        arr[0] = 99;
    }

    public static void main(String[] args) throws IOException{
        
        int it = 1;
        int[] at = new int[10];
        intTest(it);
        arrayTest(at);
        System.out.println("it is: " + it);
        System.out.println("at[0] is: " + at[0]);
        


        Penguin pen = new Penguin("123", 123);
        pen.child();

        
        File folder = new File("files/");
        deleteFolder(folder);



        Test test = new Test();
        test.punAge();
        char c;
        String str;
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("input character, q exit:");
        do{
            c = (char)br.read();
            str = br.readLine();
            System.out.println(c);
        }while(c != 'q');
    }
}

abstract class Animal{
    abstract void eat();
}

class Cat extends Animal{
    public void eat(){
        System.out.println("chiyu");
    }
}


