class S {
  // recurso compartilhado
  private int r;

  // constructor
  public S() {
    this.r = 0;
  }

  public synchronized void inc() {
    this.r++;
  }

  public synchronized int get() {
    return this.r;
  }
}

class T extends Thread {
  private int id;

  S s;

  public T(int tid, S s) {
    this.id = tid;
    this.s = s;
  }

  public void run() {
    System.out.println("Thread " + this.id + " iniciou!");
    for (int i = 0; i<100000; i++) {
      this.s.inc();
    }
    System.out.println("Thread " + this.id + " terminou!");
  }
}

public class TIncrementoBase {
 static final int N = 2;
 public static void main (String[] args) {
   Thread[] threads = new Thread[N];

   // cria uma instancia do recurso compartilhado entre as threads

   S s = new S();

   // crira as threads da aplicação
   for (int i=0; i< threads.length; i++) {
     threads[i] = new T(i, s);
   }
   
   // inicia as threads
   for (int i=0; i<threads.length; i++) {
     threads[i].start();
   }

   // espera pelo termino de todads as threads
   for (int i=0; i<threads.length; i++) {
     try {
       threads[i].join();
     } catch (InterruptedException e) {
       return;
     }
   }

   System.out.println("Valor de s = " + s.get());
 } 
}
