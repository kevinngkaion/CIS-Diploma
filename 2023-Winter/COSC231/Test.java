public class Test{
    public static void main(String[] args){
        Account joe, mary;
        joe = new Account(20);
        mary = new Account(30);
        joe.deposit(100);
        mary.deposit(200);
        System.out.println("Joe: " + joe);
        System.out.println("Mary: " + mary);

    }
}