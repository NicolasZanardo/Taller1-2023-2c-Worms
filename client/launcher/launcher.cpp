#include "launcher.h"
#include "./ui_launcher.h"

#include <iostream>

Launcher::Launcher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Launcher)
{
    ui->setupUi(this);

    this->line_edit_create_game = findChild<QLineEdit*>("lineEditGameName");  // lineEditGameName
    this->spin_box_num_players = findChild<QSpinBox*>("spinBoxNumPlayers");  // spinBoxNumPlayers
    this->combo_box_scenario = findChild<QComboBox*>("comboBoxScenario");  // comboBoxScenario

    // Hardcoded.
    this->combo_box_scenario->addItem("Escenario 1");
    this->combo_box_scenario->addItem("Escenario 2");
    this->combo_box_scenario->addItem("Escenario 3");

    this->push_button_create = findChild<QPushButton*>("pushButtonCreate"); // pushButtonCreate

    QObject::connect(this->push_button_create, &QPushButton::clicked, this, &Launcher::handleCreateGame_);

    this->push_button_list = findChild<QPushButton*>("pushButtonList");   // pushButtonList
    this->tree_widget_list = findChild<QTreeWidget*>("treeWidgetList");  // treeWidgetList

    QObject::connect(this->push_button_list, &QPushButton::clicked, this, &Launcher::handleRefreshGameList_);

    this->check_box_music = findChild<QCheckBox*>("checkBoxMusic");  // checkBoxMusic
    this->check_box_sound_effects = findChild<QCheckBox*>("checkBoxSoundEffects");   // checkBoxSoundEffects
    this->push_button_join = findChild<QPushButton*>("pushButtonJoin");  // pushButtonJoin

    QObject::connect(this->push_button_join, &QPushButton::clicked, this, &Launcher::handleJoinGame_);
    
    this->push_button_start = findChild<QPushButton*>("pushButtonStart");  // pushButtonStart

    QObject::connect(this->push_button_start, &QPushButton::clicked, this, &Launcher::handleStartGame_);

    this->line_edit_messages = findChild<QLineEdit*>("lineEditMessages");  // lineEditMessages
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::handleCreateGame_() {
    // Obtener nombre del juego
    std::string room_name = this->line_edit_create_game->text().toStdString();;
    // Obtener cantidad de jugadores.
    uint16_t num_players = static_cast<uint16_t>(this->spin_box_num_players->value());
    // Obtener escenario.
    std::string scenario = this->combo_box_scenario->currentText().toStdString();

    std::cout << "[Create game] - room: [" << room_name
                << "] - scenario: [" << scenario
                << "] - players: [" << num_players << "]\n";
}

void Launcher::handleRefreshGameList_() {
    std::cout << "[Refresh rooms list]\n";

    // Limpiar elementos viejos.
    this->tree_widget_list->model()->removeRows(0, this->tree_widget_list->model()->rowCount());

    QTreeWidgetItem* item = new QTreeWidgetItem(this->tree_widget_list);
    item->setText(0, "qqq");
    item->setText(1, "Escenario 1");
    item->setText(2, "(1/2)");

    QTreeWidgetItem* item2 = new QTreeWidgetItem(this->tree_widget_list);
    item2->setText(0, "www");
    item2->setText(1, "Escenario 2");
    item2->setText(2, "(1/2)");
}

void Launcher::handleJoinGame_() {
    // int current_room = this->tree_widget_list->currentColumn();
    // std::cout << "[Join game]: [" << current_room << "]\n";

    QTreeWidgetItem* item = this->tree_widget_list->currentItem();
    std::string game_room = item->text(0).toStdString();

    std::cout << "[Join game]: [" << game_room << "]\n";
}

void Launcher::handleStartGame_() {
    std::cout << "[Start game]\n";

    // Cerrar launcher para pasar a SDL.
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmar", "Desea iniciar el juego?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

void Launcher::handleLeaveGame_() {
    std::cout << "[Leave game]\n";
}
