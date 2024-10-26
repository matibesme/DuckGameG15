target_sources(taller_server
    PRIVATE
    # .cpp files
    server_main.cpp
        items/bullets/bullet.cpp

        items/weapons/weapon.cpp
        items/ducks/duck.cpp
        items/objeto.cpp
    PUBLIC
    # .h files
        items/bullets/bullet.h

        items/weapons/weapon.h
        items/ducks/duck.h
        items/objeto.h
)
