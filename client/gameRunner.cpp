#include "gameRunner.h"

GameRunner::GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<GameState>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
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
        while (true) {
            handler.correrHandlers();
            //command = queue_receiver.pop();
            while(queue_receiver.try_pop(command)) //y nos quedamos con la ultima
            { actualizar = true; }

            if(actualizar){
                gameRenderer.actualizarElementos(command, ducks, bullets, weapons, armors, helmets);
                actualizar = false;
            }
            gameRenderer.dibujar(sdl_renderer, ducks, bullets, weapons, armors, helmets);

            SDL_Delay(1); //reemplazar frame rate
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

//correr valgrind con
//valgrind --tool=callgrind --compress-strings=no --dump-line=yes ./build-relwithdebinfo/tarlike x.xoz a ~/Documents/*pdf
//en mi caso
//valgrind --tool=callgrind --compress-strings=no --dump-line=yes ./taller_client localhost 8080
//y luego para ver el callgrind
//kcachegrind callgrind.out.xxxx donde xxxx es el numero de la corrida

//otra app es Linux perf Examples