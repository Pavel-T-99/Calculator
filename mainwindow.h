#ifndef MAINWINDOW_H
#define MaINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QKeyEvent>

namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:

        void numberGroup_clicked(QAbstractButton*);
        void actionGroup_clicked(QAbstractButton*);

        void on_actionDel_clicked();
        void on_actionCalc_clicked();
        void on_comma_clicked();
        void on_actionClear_clicked();
        void on_actionPercent_clicked();
        void on_actionSign_clicked();


private:

        Ui::MainWindow *ui;
        const int DIGIT_LIMIT = 16; //digit limit
        bool operatorClicked; //check if an operator was clicked beforehand
        QChar storedOperator; //last operator requested
        bool hasStoredNumber; //check if a number is stored in memory
        double storedNumber; //stored number
        void calculate_result(); //calculate the result of the given number and the stored number in the memory

    protected:
        void keyPressEvent(QKeyEvent *e);
};

#endif //MAINWIDOW_H
