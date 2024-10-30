#include "gameRunner.h"
#include <chrono>
#include <functional>

GameRunner::GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<GameState>& queue_receiver)
        : graficos("DUCK GAME", SCENE_WIDTH, SCENE_HEIGHT),
          handler(queue_sender),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void GameRunner::run() {
    try {
        Renderer& sdl_renderer = graficos.GetRenderer();
        GameState command;
        std::list<ClientDuck> ducks;
        std::list<Bullet> bullets;
        std::list<Gun> weapons;
        std::list<Armor> armors;
        std::list<Helmet> helmets;

        //Para mas adelante cuando me pasen un comando background lo inicialiso aqui y lo paso por parametro
        //CommandBackGround commandBackground;
        //queue_receiver.pop(command);
        //Background background(graficos, commandBackground.lista_plataformas, commandBackground.background_id);

        Background background(graficos);
        GameRenderer gameRenderer(graficos, background);
        gameRenderer.dibujar(sdl_renderer, ducks, bullets, weapons, armors, helmets);
        bool actualizar = false;
        const int frameDelay = 1000 / 60;
        while (true) {
            auto t1 = std::chrono::high_resolution_clock::now();

            handler.correrHandlers();
            while(queue_receiver.try_pop(command)) //y nos quedamos con la ultima
            { actualizar = true; }

            if(actualizar){
                gameRenderer.actualizarElementos(command, ducks, bullets, weapons, armors, helmets);
                gameRenderer.dibujar(sdl_renderer, ducks, bullets, weapons, armors, helmets);
                actualizar = false;
            }
            //gameRenderer.dibujar(sdl_renderer, ducks, bullets, weapons, armors, helmets);

            //llamo al metodo delay para que no se ejecute mas de 60 veces por segundo
            delayIfNeeded(t1, frameDelay);
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

void GameRunner::delayIfNeeded(std::chrono::high_resolution_clock::time_point& t1, const int frameDelay) {
    // Calcular el tiempo de procesamiento de la iteración
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> elapsed = t2 - t1;
    int rest = frameDelay - static_cast<int>(elapsed.count());

    // Si estamos retrasados, ajustamos el tiempo de referencia
    if (rest < 0) {
        // Tiempo detrás del programado
        t1 = t2;  // Restablece t1 al tiempo actual
    } else {
        // Pausar solo si no estamos retrasados
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(frameDelay);  // Preparar t1 para la próxima iteración
    }
}


//correr valgrind con
//valgrind --tool=callgrind --compress-strings=no --dump-line=yes ./build-relwithdebinfo/tarlike x.xoz a ~/Documents/*pdf
//en mi caso
//valgrind --tool=callgrind --compress-strings=no --dump-line=yes ./taller_client localhost 8080
//y luego para ver el callgrind
//kcachegrind callgrind.out.xxxx donde xxxx es el numero de la corrida

//otra app es Linux perf Examples