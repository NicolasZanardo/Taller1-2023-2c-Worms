#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTreeWidget>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    Launcher(QWidget *parent = nullptr);
    ~Launcher();

private:
    void handleCreateGame_();
    void handleRefreshGameList_();
    void handleJoinGame_();
    void handleStartGame_();
    void handleLeaveGame_();

    Ui::Launcher *ui;

    QLineEdit* line_edit_create_game;  // lineEditGameName
    QSpinBox* spin_box_num_players;  // spinBoxNumPlayers
    QComboBox* combo_box_scenario;  // comboBoxScenario
    QPushButton* push_button_create; // pushButtonCreate

    QPushButton* push_button_list;   // pushButtonList
    QTreeWidget* tree_widget_list;  // treeWidgetList

    QCheckBox* check_box_music;  // checkBoxMusic
    QCheckBox* check_box_sound_effects;   // checkBoxSoundEffects
    QPushButton* push_button_join;  // pushButtonJoin
    QPushButton* push_button_start;  // pushButtonStart

    QLineEdit* line_edit_messages;  // lineEditMessages
};
#endif // LAUNCHER_H
