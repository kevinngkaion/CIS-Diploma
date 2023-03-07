/*
Author: Kevin Ngkaion
OC#: 300325759
COSC-315 Lab 5
This program solves the equation below with threads using the inherent parallelism of the problem:
    (((a + b) / 4) ^ c) + (d / 2) - ((3 * a) + (4 * e / b))
*/
public class lab5{
    public static Thread1 t1;
    public static Thread2 t2;
    public static Thread3 t3;

    public static void main(String args[]){
        double a, b, c, d, e, answer;
        a = Double.parseDouble(args[0]);
        b = Double.parseDouble(args[1]);
        c = Double.parseDouble(args[2]);
        d = Double.parseDouble(args[3]);
        e = Double.parseDouble(args[4]);

        t1 = new Thread1(a);
        t1.start();
        t2 = new Thread2(d);
        t2.start();
        t3 = new Thread3(a, b, c);
        t3.start();
        
        answer = e * 4;
        answer /= b;
        // merge t1 back to main thread
        try {
            t1.join();
        } catch(InterruptedException ie){}
        answer += t1.getResult(); // do the calculation with t1 result
        // merge t3 back to main thread
        try {
            t3.join();
        } catch(InterruptedException ie){}
        answer = t3.getResult() - answer; //do the final calc
        System.out.printf("(((%3.1f + %3.1f) / 4) ^ %3.1f + %3.1f / 2) - (3 * %3.1f + (4 * %3.1f / %3.1f)) = %3.3f\n", a, b, c, d, a, e, b, answer);
    }

    private static class Thread1 extends Thread{
        double a;
        double result;
        public Thread1(double arg){
            this.a = arg;
        }

        // What the thread will do
        public void run(){
            this.result = this.a * 3;
        }

        public double getResult(){return this.result;}
    }

    private static class Thread2 extends Thread{
        double d;
        double result;
        public Thread2(double arg){
            this.d = arg;
        }

        // What the thread will do
        public void run(){
            this.result = this.d / 2;
        }

        public double getResult(){return this.result;}
    }

    private static class Thread3 extends Thread{
        double a, b, c;
        double result;
        public Thread3(double a, double b, double c){
            this.a = a;
            this.b = b;
            this.c = c;
        }

        // What the thread will do
        public void run(){
            this.result = this.a + this.b;
            this.result /= 4;
            this.result = Math.pow(this.result, this.c);

            
            try{
                t2.join();
            }catch(InterruptedException ie){}
            this.result += t2.getResult();
        }

        public double getResult(){return this.result;}
    }

}