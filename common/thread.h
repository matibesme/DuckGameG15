#ifndef __THREAD_H__
#define __THREAD_H__

#include <exception>
#include <iostream>
#include <thread>
#include <vector>

#define N 10

class Thread {
private:
    std::thread thread;

public:
    Thread() {}

    void start() {
        /* [2] Lanzamos el thread que correrá
           siempre la misma función (Thread::main)

           Como Thread::main es un **método**
           sin parámetros y std::thread espera
           a una **función** podemos ver a
           Thread::main como una función que
           recibe como primer argumento al
           objeto this (tal como en los TDA de C!)

           std::thread soporta correr una
           función con argumentos con la llamada:

              std::thread( funcion, arg1, arg2, ...)

           Por lo tanto
                std::thread( metodo, this )

           es equivalente a correr el método
           sin argumentos en un thread.

           Como Thread::main llama a Thread::run
           y Thread::run es un método **polimórfico**,
           cada objeto ejecutara
           un código particular en el thread.

           Objetos distintos podrán correr en
           sus propios threads con esta única
           implementación de Thread mientras
           hereden de Thread y creen sus propias
           versiones del método run.
        */
        thread = std::thread(&Thread::main, this);
    }

    // [3]
    //
    // Este método es el que correrá en su propio thread.
    //
    // Obviamente el que hacer esta dentro de Thread::run
    // que es polimórfico
    //
    // La idea de Thread::main es que me permite poner
    // un try-catch y atrapar cualquier excepción que
    // se lance en Thread::run.
    //
    // Si una excepción se escapa de la función que esta
    // corriendo en un thread, el program termina con un abort
    //
    // Not nice.
    //
    // Quienes implementen Thread::run deberían atrapar
    // las excepciones ellos. El try-catch de Thread::main
    // es solo como último recurso.
    void main() {
        try {
            this->run();
        } catch (const std::exception& err) {
            // Nota: por simplicidad estoy haciendo unos prints.
            // Código productivo debería *loggear* el error, no solo
            // prints.
            std::cerr << "Unexpected exception: " << err.what() << "\n";
        } catch (...) {
            std::cerr << "Unexpected exception: <unknown>\n";
        }
    }

    void join() { thread.join(); }

    /* [4] Virtual puro para forzar una
       definición en las clases hijas.

       Sera responsabilidad de ellas implementar lo que quieran
       que corran en un thread aquí.
    */
    virtual void run() = 0;


    /* [5] Destructor virtual: siempre hacerlo
       virtual si pensamos en usar herencia.
    */
    virtual ~Thread() {}


    /* [6] No tiene sentido copiar hilos, así
       que forzamos a que no se puedan copiar.
    */
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    /* [7] Y aunque tiene sentido, vamos a ver
       que es un peligro permitir mover un thread
       así que también vamos a prohibir el move.

       Lo vas a entender cuando veas [10]
    */
    Thread(Thread&& other) = delete;
    Thread& operator=(Thread&& other) = delete;
};

#endif
