public class Account{
    private int balance;
    public Account(int amount){ this.balance = amount;}
    public int getBalance(){return this.balance;}
    public void deposit(int amount){this.balance += amount;}
    public void withdraw(int amount){
        if(this.balance >= amount)
            this.balance -= amount;
        else
            System.out.println("Insufficient Funds!");
    }
    public String toString(){return "Balance: " + this.balance;}
}