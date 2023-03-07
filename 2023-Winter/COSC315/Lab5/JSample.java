/* JSample.java -- Sample of threads
   Solaris compilation:  javac JSample.java
   Solaris run:          java JSample
*/

public class JSample {
    private static Thread t1, t2;       // two threads
    public static void main(String[] args) {
        t1 = new Thread1();
        t1.start();
        t2 = new Thread2();
        t2.start();
        System.out.println("Main thread running");
        try {
            t1.join();            // main thread waits for t1
        } catch(InterruptedException ie) { }
        System.out.println("Main thread running after t1 finished\n");
    }

    ///////////////////////////////////////////////////////

    private static class Thread1 extends Thread {
        public void run() {
            System.out.println("Thread 1 begins");
            try {
                t2.join();        // t1 thread waits for t2
                Thread.sleep(1000);
            } catch(InterruptedException ie) { }
            System.out.println("Thread 1 finished");
        } // run
    } // inner class Thread1

    ///////////////////////////////////////////////////////

    private static class Thread2 extends Thread {
        public void run() {
            System.out.println("Thread 2 begins");
            try {
                Thread.sleep(1000);
            } catch(InterruptedException ie) { }
            System.out.println("Thread 2 finished");
        } // run
    } // inner class Thread2

} // class Sample