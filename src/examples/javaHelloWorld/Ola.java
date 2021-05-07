class Ola extends Thread {
  private String msg;

  public Ola(String m) {
    this.msg = m;
  }

  public void run() {
    System.out.println(msg);
  }
}

class OlaThread {
  static final int N = 10;

  public static void main (String[] args) {
    Thread[] threads = new Thread[N];

    for (int i=0; i<threads.length; i++) {
      final String m = "Ola da thread " + i;
      System.out.println("--Cria a thread " + i);
      threads[i] = new Ola(m);  
    }

    for (int i=0; i< threads.length; i++) {
      threads[i].start();
    }

    for (int i=0; i<threads.length; i++) {
      try {
        threads[i].join();
      } catch (InterruptedException e) {
        return;
      }
    }

    System.out.println("Terminou");
  }

}
