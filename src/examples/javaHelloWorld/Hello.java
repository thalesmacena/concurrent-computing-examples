class Hello implements Runnable{
  private String msg;

  public Hello (String m) {
    this.msg = m;
  }

  public void run() {
    System.out.println(msg);
  }
}

class HelloThread {
  static final int N = 10;

  public static void main (String[] args) {
    Thread[] threads = new Thread[N];

    // Cria as threads
    for (int i=0; i<threads.length; i++) {
      final String m = "Hello World da thread: " + i;
      System.out.println("--Cria a thread " + i);
      threads[i] = new Thread(new Hello(m));
    }

    // Inicia as threads
    for (int i=0; i<threads.length; i++) {
      threads[i].start();
    }

    // Espera as threads
    for(int i=0; i<threads.length; i++) {
      try {
        threads[i].join();
      } catch (InterruptedException e) {
        return;
      }
    }

    System.out.println("Terminou");

  }

}