#include <list>
#include "constant_definitons.h"
#include "../../common/dto_definitions.h"
#include "../items/ducks/duck.h"
#include "../items/weapons/weapon.h"
#include <yaml-cpp/yaml.h>



class LoadGameFile {

public:
    LoadGameFile();
    void loadGame(std::list<DTOPlatform> &platforms);
};