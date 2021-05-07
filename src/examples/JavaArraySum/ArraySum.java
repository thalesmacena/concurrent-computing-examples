import java.util.Scanner;

class ArrayCompartilhado {
  // recurso compartilhado
  private int[] array;

  // constructor
  public ArrayCompartilhado(int length) {
    this.array = new int[length];
    for (int i = 0; i < length; i++ ) {
      this.array[i] = 0;
    }
  }

  public synchronized void setValue(int index) {
    this.array[index] = this.array[index]++;
  }

  public synchronized int[] get() {
    return this.array;
  }
}

class T extends Thread {
  private int id;

  int[] array;

  int NThreads;

  public T(int tid, ArrayCompartilhado a, int n) {
    this.id = tid;
    this.array = a.get();
    this.NThreads = n;
  }

  public void run() {
    for (int i = id; i < array.length; i += NThreads) {
      array[i]++;
    }
  }
}

public class ArraySum {
  public static void main (String[] args) {
    Scanner sc = new Scanner(System.in);

    System.out.println("Entre com o tamanho do vetor:");
    int DIM = sc.nextInt();
    System.out.println("Entre com o número de Threads:");
    int NThreads = sc.nextInt();

    sc.close();

    if (NThreads > DIM) {
      NThreads = DIM;
    }

    // Cria o array de threads
    Thread[] threads = new Thread[NThreads];
 
    // cria uma instancia do recurso compartilhado entre as threads
    ArrayCompartilhado array = new ArrayCompartilhado(DIM);
 
    // cria as threads da aplicação
    for (int i=0; i < threads.length; i++) {
      threads[i] = new T(i, array, NThreads);
    }
    
    // inicia as threads
    for (int i=0; i<threads.length; i++) {
      threads[i].start();
    }
 
    // espera pelo termino de todads as threads
    for (int i=0; i < threads.length; i++) {
      try {
        threads[i].join();
      } catch (InterruptedException e) {
        return;
      }
    }


    // Validação
    for (int element: array.get()) {
      if (element != 1) {
        System.out.println("--Erro de validação");
        return;
      };
    }

    System.out.println("Passou na validação");
    // System.out.println("Array: " + Arrays.toString(array.get()));    
  } 

}
