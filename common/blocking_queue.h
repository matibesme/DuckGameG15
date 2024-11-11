#pragma once
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

struct ClosedQueue : public std::runtime_error {
  ClosedQueue() : std::runtime_error("The queue is closed") {}
};

template <typename T> class BlockingQueue {
private:
  std::queue<T> q;
  const unsigned int max_size;

  bool closed;

  std::mutex mtx;
  std::condition_variable is_not_full;
  std::condition_variable is_not_empty;

public:
  explicit BlockingQueue(const unsigned int max_size)
      : max_size(max_size), closed(false) {}

  bool try_push(const T &val) {
    std::unique_lock<std::mutex> lck(mtx);

    /*
     * Si la queue esta cerrada no se aceptan más elementos
     * y try_push() y push() deben fallar.
     *
     * En esta implementación se lanza una excepción si la queue
     * esta cerrada;
     * en otras implementaciones se retorna via algún mecanismo
     * un bool o tienen un método is_closed()
     *
     * Python por ejemplo implementa ambos cosa pero realmente
     * is_closed() te puede llevar a una race condition.
     *
     * Por ejemplo, podrías pensar que esto es correcto:
     *
     *      while (not blocking_queue.is_closed()) {
     *          blocking_queue.try_push(...);
     *      }
     *
     * Pero ese código **no** evitara q hagas un push() (o un pop())
     * sobre una queue que esta cerrada.
     *
     * Pudiste ver la RC?
     * */
    if (closed) {
      throw ClosedQueue();
    }

    if (q.size() == this->max_size) {
      return false;
    }

    if (q.empty()) {
      is_not_empty.notify_all();
    }

    q.push(val);
    return true;
  }

  bool try_pop(T &val) {
    std::unique_lock<std::mutex> lck(mtx);

    /*
     * Tentador pero **no**!!
     *
     * Tanto try_pop() como pop() deben fallar si la queue
     * esta cerrada **y** esta vacía.
     *
     * Si la queue esta cerrada eso **no** implica que no
     * queden elementos **aun** en la queue y para
     * la perspectiva de cualquier thread consumidor
     * **aun** hay trabajo por hacer.
     * */
    // if (closed) {
    //     throw ClosedQueue();
    // }

    if (q.empty()) {
      if (closed) {
        throw ClosedQueue();
      }
      return false;
    }

    if (q.size() == this->max_size) {
      is_not_full.notify_all();
    }

    val = q.front();
    q.pop();
    return true;
  }

  void push(const T &val) {
    std::unique_lock<std::mutex> lck(mtx);

    if (closed) {
      throw ClosedQueue();
    }

    while (q.size() == this->max_size) {
      is_not_full.wait(lck);
    }

    if (q.empty()) {
      is_not_empty.notify_all();
    }

    q.push(val);
  }

  T pop() {
    std::unique_lock<std::mutex> lck(mtx);

    while (q.empty()) {
      if (closed) {
        throw ClosedQueue();
      }
      is_not_empty.wait(lck);
    }

    if (q.size() == this->max_size) {
      is_not_full.notify_all();
    }

    const T val = q.front();
    q.pop();

    return val;
  }

  void close() {
    std::unique_lock<std::mutex> lck(mtx);

    /*
     * Cerrar dos veces una queue no es ningún problema
     * realmente (al final es cambiar un booleano).
     *
     * Pero **lógicamente esta mal**: o hay algo mal programado
     * o hay algún bug que hizo q se llame a close() más de
     * una vez.
     *
     * Es como querer cerrar un file o hacer un free dos veces.
     *
     * Consejo: si sabes que hay un estado invalido, checkearlo
     * y fallar rápido. Hara que descubras bugs mucho más rápido.
     * */
    if (closed) {
      throw std::runtime_error("The queue is already closed.");
    }
    closed = true;

    /* Probablemente estoy mintiendo aquí ya q no se si la queue
     * esta vacio o no realmente **pero** en el caso de que lo
     * este puede que algún thread este bloqueado en el pop().
     *
     * Si es así este notify_all() lo va a despertar y ese thread
     * tendrá la oportunidad de ver q la queue esta cerrada y
     * q no debe continuar con el pop()
     *
     * */
    is_not_empty.notify_all();
  }

private:
  BlockingQueue(const BlockingQueue &) = delete;
  BlockingQueue &operator=(const BlockingQueue &) = delete;
};
