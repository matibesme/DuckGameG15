#include "gameRunner.h"

GameRunner::GameRunner(BlockingQueue<uint8_t>& queue_sender, BlockingQueue<CommandGame>& queue_receiver)
        : graficos("DUCK GAME", 640, 480),
          handler(queue_sender),
          queue_sender(queue_sender),
          queue_receiver(queue_receiver) {}

void GameRunner::run() {
    try {
        Renderer& sdl_renderer = graficos.GetRenderer();
        CommandGame command;
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

        while (true) {
            handler.correrHandlers();
            if (queue_receiver.try_pop(command)) {
                gameRenderer.actualizarElementos(command, ducks, bullets, weapons, armors, helmets);
                gameRenderer.dibujar(sdl_renderer, ducks, bullets, weapons, armors, helmets);
            }
            SDL_Delay(1);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        queue_sender.close();
    }
    graficos.GetRenderer().Clear();
}

