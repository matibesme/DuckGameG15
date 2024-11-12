#define IMAGEN_END_ROUND DATA_PATH "/pantallaVictoria.png"
#include "endRoundscene.h"
#include <QGraphicsView>
#include <QtWidgets>
#include <iostream>
#include <string>
#include <map>
#include <QScreen>

EndRoundScene::EndRoundScene(std::map<std::string, uint8_t>& players, QWidget* parent)
    : QMainWindow(parent) {
  // Establecer tamaño más pequeño para la ventana
  this->setFixedSize(600, 400);  // Ventana de tamaño fijo
  this->setWindowTitle("");     // Eliminar el título de la ventana

  // Centrar la ventana en la pantalla usando QGuiApplication
  QScreen* screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - this->width()) / 2;
  int y = (screenGeometry.height() - this->height()) / 2;
  this->move(x, y);

  // Crear un layout principal
  QWidget* centralWidget = new QWidget(this);
  QVBoxLayout* layout = new QVBoxLayout(centralWidget);

  // Crear un título para la escena
  QLabel* title = new QLabel("End of Round Results", this);
  title->setStyleSheet(
      "font-size: 20px;"  // Tamaño más grande para el texto
      "font-weight: bold;"
      "color: white;"
      "background-color: rgba(0, 0, 0, 200);"  // Fondo más opaco
      "padding: 8px;"
      "border-radius: 5px;"
  );
  title->setAlignment(Qt::AlignCenter);
  layout->addWidget(title, 0, Qt::AlignCenter);

  // Crear la tabla para mostrar los resultados
  QTableWidget* table = new QTableWidget(this);
  table->setColumnCount(2);  // Dos columnas: Nombre y Partidas Ganadas
  table->setHorizontalHeaderLabels({"Player Name", "Wins"});
  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  table->verticalHeader()->setVisible(false);  // Ocultar encabezados de las filas
  table->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Hacer la tabla no editable
  table->setSelectionMode(QAbstractItemView::NoSelection);    // Desactivar selección
  table->setStyleSheet(
      "background-color: rgba(255, 255, 255, 200);"
      "border: 2px solid black;"
      "border-radius: 5px;"
      "font-size: 16px;"  // Tamaño de texto más grande para la tabla
  );

  // Rellenar la tabla con los datos del mapa
  table->setRowCount(players.size());
  int row = 0;
  for (const auto& [name, wins] : players) {
    // Columna 1: Nombre del jugador
    QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(name));
    nameItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 0, nameItem);

    // Columna 2: Partidas ganadas
    QTableWidgetItem* winsItem = new QTableWidgetItem(QString::number(wins));
    winsItem->setTextAlignment(Qt::AlignCenter);
    table->setItem(row, 1, winsItem);

    ++row;
  }

  // Ajustar tamaño más pequeño para la tabla
  table->setFixedSize(450, 200);
  // Centrar la tabla tanto horizontal como verticalmente y subirla un poco en y
  layout->addWidget(table, 0, Qt::AlignCenter);
  layout->setAlignment(table, Qt::AlignCenter);

  // Configurar el widget central
  this->setCentralWidget(centralWidget);

  // Establecer el fondo
  QPixmap background(IMAGEN_END_ROUND);
  if (!background.isNull()) {
    QPalette palette;
    palette.setBrush(QPalette::Window, background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    this->setPalette(palette);
  }
}

EndRoundScene::~EndRoundScene() {}
