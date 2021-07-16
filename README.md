<div align="center">
  <br />
  <img src=".github/banner.png" width="546" alt="Conc. Comp. Examples" />
  <br />
  <p>
    <img src="https://img.shields.io/badge/made%20by-Thales%20Macena-2D325E?labelColor=F0DB4F&style=for-the-badge&logo=visual-studio-code&logoColor=2D325E" alt="Made by Thales Macena">
    <img alt="Top Language" src="https://img.shields.io/github/languages/top/thalesmacena/concurrent-computing-examples?color=2D325E&labelColor=F0DB4F&style=for-the-badge&logo=c&logoColor=2D325E">
    <a href="https://github.com/thalesmacena/concurrent-computing-examples/commits/master">
      <img alt="Last Commits" src="https://img.shields.io/github/last-commit/thalesmacena/concurrent-computing-examples?color=2D325E&labelColor=F0DB4F&style=for-the-badge&logo=github&logoColor=2D325E">
    </a>
    <a href="https://github.com/thalesmacena/concurrent-computing-examples/issues"><img alt="Top Language" src="https://img.shields.io/github/issues-raw/thalesmacena/concurrent-computing-examples?color=2D325E&labelColor=F0DB4F&style=for-the-badge&logo=github&logoColor=2D325E"></a>
  </p>
</div>

## 🗂 Table of Contents
- [🗂 Table of Contents](#-table-of-contents)
- [📑 About](#-about)
- [🧩 Examples](#-examples)
    - [Hello World](#hello-world)
    - [Increment Array](#increment-array)
    - [Matrix multiplication by vector](#matrix-multiplication-by-vector)
    - [Matrix multiplication by Matrix](#matrix-multiplication-by-matrix)
    - [Array reduce sum](#array-reduce-sum)
    - [Pi Aprox](#pi-aprox)
    - [Prefix Sum](#prefix-sum)
    - [Java Hello World](#java-hello-world)
    - [Java Increment Variable](#java-increment-variable)
    - [Java Array Sum](#java-array-sum)
- [✨ Installation](#-installation)
- [🔥 Running](#-running)
  
  
## 📑 About

This repository is a list of examples of the implementation of concurrent computing done in C using the POSIX Threads library, built during the discipline of Concurrent Computing at the Federal University of Rio de Janeiro and taught by Prof. [Silvana Rossetto](https://dcc.ufrj.br/~silvana/) (DCC-- UFRJ)

**It is recommended that you use a Linux, macOS or WSL system if you use windows to run and run programs**

## 🧩 Examples

#### [Hello World](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/helloWorld)
First notion of creating threads to create a hello world in multiple threads and present the concept of concurrent computing

#### [Increment Array](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/incrementArray)
Shows the use of threads to manipulate arrays, increasing the value of each position by 1

#### [Matrix multiplication by vector](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/matrixVector)
Program that performs the multiplication of a matrix by a vector, has a sequential version and versions with different concurrent solutions.

#### [Matrix multiplication by Matrix](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/matrixMultiplication)
Program that performs the multiplication of a square matrix by a square matrix, has a sequential version and a concurrent version. In the folder you will also find a [benchmark](https://github.com/thalesmacena/concurrent-computing-examples/blob/main/src/examples/matrixMultiplication/benchmark.md) analysis on the advantages of a concurrent approach.

#### [Array reduce sum](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/arrayReduce)
Program that traverses an array of double and adds their values

#### [Pi Aprox](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/piAprox)
Program that use threads to calculate a aproximation to pi value

#### [Prefix Sum](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/prefixSum)
Program that use threads to calculate array prefix sum

#### [Java Hello World](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/javaHelloWorld)
First notion of creating threads in Java to create a hello world in multiple threads and present the concept of concurrent computing

#### [Java Increment Variable](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/javaIncrementVariable)
Program that use threads to calculate increment a variable

#### [Java Array Sum](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/javaArraySum)
Shows the use of threads in Java to manipulate arrays, increasing the value of each position by 1

#### [Semaphore](https://github.com/thalesmacena/concurrent-computing-examples/tree/main/src/examples/semaphore)
Shows the semaphore example in threads

## ✨ Installation
Open a terminal and run the following commands:

```PowerShell
# To copy this repository
git clone https://github.com/thalesmacena/concurrent-computing-examples.git

# To move to project directory
cd concurrent-computing-examples
```

## 🔥 Running
You can open powershell as wsl with the command:
```Powershell
wsl code .
```

You can run each example by running its respective .exe file or build with the command:

```Powershell
gcc fileName -o exitName -Wall -lpthread
./exitName args
```

You can compile and run with java with the following commands:
```Powershell
javac Main.java
java Main
```
