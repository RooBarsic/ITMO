public class TestTaskJava {

    //public static Bum x;

    public static void testIt(){
        Bum x = new Bum();
        System.out.println(" bim_x = " + x.x);
        Tcheck1 t1 = new Tcheck1(x);
        Tcheck2 t2 = new Tcheck2(x);

        t1.start();
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        t2.start();

    }

}

class Tcheck1 extends Thread {
    private Bum x;

    Tcheck1(Bum x){
        this.x = x;
    }

    public void run(){
        System.out.println( "tred 1 - run M1 ");
        x.synxMetod();
    }
}

class Tcheck2 extends Thread {
    private Bum x;
    Tcheck2(Bum x){
        this.x = x;
    }

    public void run(){
        System.out.println(" tred 2 - run M2 ");
        x.anotherMetod();
    }
}

class Bum{
    int x = 0;

    Bum(){ }

    public synchronized void synxMetod(){
        x = 1;
        for(int i = 1; i <= 1000000000000l; i++){
            System.out.println(" M1 i = " + i + " x = " + x);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void anotherMetod(){
        x = 2;
        for(int i = 1; i <= 1000000000000l; i++){
            System.out.println(" M2 j = " + i + " x = " + x);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
