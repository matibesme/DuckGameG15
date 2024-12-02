#include "Graficos.h"

#include <SDL_image.h>

Graficos::Graficos(const char *title, int width, int height)
    : window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
             height, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE),
      renderer(window, -1, SDL_RENDERER_ACCELERATED) {
  loadAllTextures();
}

Renderer &Graficos::GetRenderer() { return renderer; }

Texture &Graficos::getTexture(std::string path) { return *textures[path]; }

void Graficos::Clear() {
  renderer.SetDrawColor(0, 0, 0, 255);
  renderer.Clear();
}

void Graficos::show_window() { SDL_ShowWindow(window.Get()); }

void Graficos::loadAllTextures() {
  // Cargo por unica vez todas las texturas
  Surface surface(IMG_Load(IMAGE_ARMOR));
  textures.emplace(IMAGE_ARMOR,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AK47_GUN));
  textures.emplace(IMAGE_AK47_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AK47_GUN_EQUIPPED));
  textures.emplace(IMAGE_AK47_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_ARMOR));
  textures.emplace(IMAGE_ARMOR,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_BANANA_GUN));
  textures.emplace(IMAGE_BANANA_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_BANANA_GUN_EQUIPPED));
  textures.emplace(IMAGE_BANANA_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_BOX_WEAPON));
  textures.emplace(IMAGE_BOX_WEAPON,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_COWBOY_GUN));
  textures.emplace(IMAGE_COWBOY_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_COWBOY_GUN_EQUIPPED));
  textures.emplace(IMAGE_COWBOY_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_ESCOPETA_GUN));
  textures.emplace(IMAGE_ESCOPETA_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_ESCOPETA_GUN_EQUIPPED));
  textures.emplace(IMAGE_ESCOPETA_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_BULLET));
  textures.emplace(IMAGE_GRANADA_BULLET,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_EXPLOTION));
  textures.emplace(IMAGE_GRANADA_EXPLOTION,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_AMMO));
  textures.emplace(IMAGE_LASER_AMMO,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_AMMO2));
  textures.emplace(IMAGE_LASER_AMMO2,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_MAGNUM_GUN));
  textures.emplace(IMAGE_MAGNUM_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_MAGNUM_GUN_EQUIPPED));
  textures.emplace(IMAGE_MAGNUM_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PEW_PEW_LASER_GUN));
  textures.emplace(IMAGE_PEW_PEW_LASER_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PEW_PEW_LASER_GUN_EQUIPPED));
  textures.emplace(IMAGE_PEW_PEW_LASER_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PISTOLA_DUELOS_GUN));
  textures.emplace(IMAGE_PISTOLA_DUELOS_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED));
  textures.emplace(IMAGE_PISTOLA_DUELOS_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_SNIPER_GUN));
  textures.emplace(IMAGE_SNIPER_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_SNIPER_GUN_EQUIPPED));
  textures.emplace(IMAGE_SNIPER_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_WALL_DONUT));
  textures.emplace(IMAGE_WALL_DONUT,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_WALL_NATURE));
  textures.emplace(IMAGE_WALL_NATURE,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_WALL_UNDERGROUND));
  textures.emplace(IMAGE_WALL_UNDERGROUND,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_DONUT));
  textures.emplace(IMAGE_PLATAFORMA_DONUT,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_DONUT_LONG));
  textures.emplace(IMAGE_PLATAFORMA_DONUT_LONG,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_INDUSTRIAL));
  textures.emplace(IMAGE_PLATAFORMA_INDUSTRIAL,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_NATURE));
  textures.emplace(IMAGE_PLATAFORMA_NATURE,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_NATURE_LONG));
  textures.emplace(IMAGE_PLATAFORMA_NATURE_LONG,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_SPACE));
  textures.emplace(IMAGE_PLATAFORMA_SPACE,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_PLATAFORMA_UNDERGROUND));
  textures.emplace(IMAGE_PLATAFORMA_UNDERGROUND,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_HELMET));
  textures.emplace(IMAGE_HELMET,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_DUCK));
  textures.emplace(IMAGE_DUCK,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AMMO_1));
  textures.emplace(IMAGE_AMMO_1,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AMMO_2));
  textures.emplace(IMAGE_AMMO_2,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AMMO_3));
  textures.emplace(IMAGE_AMMO_3,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AMMO_4));
  textures.emplace(IMAGE_AMMO_4,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_AMMO_5));
  textures.emplace(IMAGE_AMMO_5,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_AMMO));
  textures.emplace(IMAGE_LASER_AMMO,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_AMMO2));
  textures.emplace(IMAGE_LASER_AMMO2,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_BULLET));
  textures.emplace(IMAGE_GRANADA_BULLET,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_EXPLOTION));
  textures.emplace(IMAGE_GRANADA_EXPLOTION,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_BANANA_BULLET));
  textures.emplace(IMAGE_BANANA_BULLET,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_BANANA_THROWN));
  textures.emplace(IMAGE_BANANA_THROWN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_GUN));
  textures.emplace(IMAGE_GRANADA_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_GRANADA_GUN_EQUIPPED));
  textures.emplace(IMAGE_GRANADA_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_RIFLE_GUN));
  textures.emplace(IMAGE_LASER_RIFLE_GUN,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_LASER_RIFLE_GUN_EQUIPPED));
  textures.emplace(IMAGE_LASER_RIFLE_GUN_EQUIPPED,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_CLOUDY_NIGHT));
  textures.emplace(IMAGE_CLOUDY_NIGHT,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_River));
  textures.emplace(IMAGE_River,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
  surface = Surface(IMG_Load(IMAGE_FOREST));
  textures.emplace(IMAGE_FOREST,
                   std::make_unique<SDL2pp::Texture>(renderer, surface));
}

Graficos::~Graficos() {
  for (auto &texture : textures) {
    texture.second.reset();
  }
  textures.clear();
}
