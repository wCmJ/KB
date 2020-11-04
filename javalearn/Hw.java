


public class Hw{
    public static void main(String[] args){
        System.out.println("Hello World");
        FreshJuice juice = new FreshJuice();
        juice.size = FreshJuice.FreshJuiceSize.SMALL;
        System.out.println("size is: " + juice.size);
    }
}

class FreshJuice{
    enum FreshJuiceSize {SMALL, MEDIUM, LARGE}
    FreshJuiceSize size;
}

