target_sources(taller_server
    PRIVATE
    # .cpp files
    server_main.cpp
        items/bullets/bullet.cpp
        items/bullets/bullet_pistola_cowboy.cpp
        items/weapons/weapon.cpp
        items/ducks/personaje.cpp
        items/objeto.cpp
    PUBLIC
    # .h files
        items/bullets/bullet.h
        items/bullets/bullet_pistola_cowboy.h
        items/weapons/weapon.h
        items/ducks/personaje.h
        items/objeto.h
)
