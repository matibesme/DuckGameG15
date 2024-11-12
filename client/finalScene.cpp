#include "finalScene.h"
#include <QGraphicsView>
#include <QtWidgets>
#include <iostream>
#include <string>

#define IMAGEN_VICTORIA DATA_PATH "/pantallaVictoria.png"
#define FUENTE DATA_PATH "/fonts/8-bit-hud.ttf"

FinalScene::FinalScene(std::string winner, QWidget* parent)
    : QMainWindow(parent) {
  // Establecer tamaño de la ventana
  this->setGeometry(0, 0, 800, 600);

  QGraphicsScene* main_scene = new QGraphicsScene(this);
  QGraphicsView* view = new QGraphicsView(main_scene, this);
  main_scene->setSceneRect(0, 0, 800, 600);
  view->setGeometry(0, 0, 800, 600);

  // Cargar y ajustar la imagen de fondo
  QPixmap initial_background(IMAGEN_VICTORIA);
  if (initial_background.isNull()) {
    qWarning("No se pudo cargar la imagen de fondo");
  } else {
    initial_background = initial_background.scaled(800, 600, Qt::KeepAspectRatioByExpanding);
  }

  // Crear el mensaje del ganador en dos líneas
  std::string message = "Winner is:\n" + winner;
  QLabel* message_label = new QLabel(message.c_str());

  // Estilo del mensaje
  message_label->setStyleSheet(
      "background-color: rgba(0, 0, 0, 128);" // Fondo semitransparente
      "color: white;"                         // Texto blanco
      "border: 2px solid white;"              // Borde blanco
      "border-radius: 10px;"                  // Bordes redondeados
      "padding: 10px;"                        // Espaciado interno
  );
  message_label->setAlignment(Qt::AlignCenter);

  // Ajustar tamaño y posición del texto
  message_label->setGeometry(50, 400, 300, 80); // Posicionado más arriba a la izquierda

  // Cargar la fuente personalizada
  int id = QFontDatabase::addApplicationFont(FUENTE);
  if (id != -1) {
    QString fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont customFont(fontFamily, 16); // Tamaño de fuente reducido
    message_label->setFont(customFont);
  } else {
    qWarning("No se pudo cargar la fuente personalizada");
  }

  // Añadir el mensaje a la escena
  main_scene->addWidget(message_label);

  // Establecer el fondo en la escena
  main_scene->setBackgroundBrush(initial_background);

  view->setScene(main_scene);
  view->show();
}

FinalScene::~FinalScene() {}
