target_sources(taller_server
    PRIVATE
    # .cpp files
    server_main.cpp
        items/bullets/bullet.cpp

        items/weapons/weapon.cpp
        items/ducks/duck.cpp
        items/objeto.cpp
        items/bullets/granada_bullet.cpp
        items/weapons/granada.cpp
        items/weapons/banana.cpp
        items/bullets/banana_bullet.cpp
        configuration/load_game.cpp
    PUBLIC
    # .h files
        items/bullets/bullet.h

        items/weapons/weapon.h
        items/ducks/duck.h
        items/objeto.h
        items/bullets/granada_bullet.h
        items/weapons/granada.h
        items/weapons/banana.h
        items/bullets/banana_bullet.h
        configuration/load_game.h
)
