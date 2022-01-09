#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->displayPanel->clear();//Set up empty display panel

    operatorClicked = false;
    hasStoredNumber = false;//Set operator and store number flags to false

    ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(numberGroup_clicked(QAbstractButton*)));//Set number button group listener
    
    ui->actionGroup->connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(actionGroup_clicked(QAbstractButton*)));//Set operator button group listener

    
    this->setFixedSize(QSize(306, 319));//Set window fix width and height
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberGroup_clicked(QAbstractButton* button)
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display

    /* Check if the previous button that was clicked was an operator button.
     * If so, clear the display and set the flag to false. Then proceed to
     * add the digit requested. */
    if (operatorClicked) {
        displayLabel.clear();
        operatorClicked = false;
    }

    
    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }//Append the digit only if we are not exceeding the digit limit

    
    displayLabel.append(button->text());//Append requested digit

    
    ui->displayPanel->setText(displayLabel);//Set number back to display
}


void MainWindow::actionGroup_clicked(QAbstractButton* button)
{
    /* If the previous button that was clicked was not an operator, then we just need to save the operator
     * that was requested and exit.
     * If it was though, we need to see whether we just need to save the number that is
     * displayed or if there is already a number stored in memory, perform the calculation and
     * store the result.
     * Example for this case: 5 + 7 + -> We need to save 12 in memory and then save operator. */

    if (operatorClicked) {
        storedOperator = button->text().at(0);
    }
    else {
        if (hasStoredNumber) {
            calculate_result();
        }
        else {
            hasStoredNumber = true;//Set the flag to indicate that we now have a number stored in memory
            QString displayLabel = ui->displayPanel->text();//Get string from display
            storedNumber = displayLabel.toDouble();//Convert string to double and save
        }
        
        operatorClicked = true;//Set the flag that the last button that was clicked was an operator
        storedOperator = button->text().at(0);//Store operator in memory
    }
}

void MainWindow::on_actionDel_clicked()
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display

    
    if (displayLabel.length() == 0) {
        return;
    }//Check if label is empty

    
    displayLabel.QString::chop(1);//Delete last digit from string
    ui->displayPanel->setText(displayLabel);//Set number back to display
}

void MainWindow::on_actionCalc_clicked()
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display
    /* A number must be saved in memory to be able calculate a result.
     * In addition, a number with at least one digit should be present in the display and
     * The last button that was clicked should not be an operator */

    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        return;
    }

    
    calculate_result();//Calculate result and set in on display
    hasStoredNumber = false;//Set stored number flag to false (we have it on screen now)

}

void MainWindow::on_comma_clicked()
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display

    /* Append the digit only if we are not exceeding the digit limit.
     * More specifically in this case, we need 2 digits to be available.
     * One for the comma and at least another one for a remaining digit.
     * Also check if whether there is another comma already present. */
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }//If label is empty, add zero and then append comma

    
    displayLabel.append('.');//Append comma
    ui->displayPanel->setText(displayLabel);//Set number back to display
}

void MainWindow::on_actionClear_clicked()
{
    
    ui->displayPanel->clear();//Clear display label (for now)
    
    operatorClicked = false;
    hasStoredNumber = false;//Set operator and store number flags to false
}

void MainWindow::on_actionPercent_clicked()
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display
    double percentage = displayLabel.toDouble();//Convert to double
    percentage *= 0.01;//Just multiply with 0.01 to make it a percentage
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);//Since there might be an overflow, its best to convert the number carefully
    ui->displayPanel->setText(displayLabel);//Set number back to display
}

void MainWindow::on_actionSign_clicked()
{
    
    QString displayLabel = ui->displayPanel->text();//Get string from display
    double percentage = displayLabel.toDouble();//Convert to double
    percentage *= -1;//Just multiply with -1 to change its sign
    displayLabel = QString::number(percentage,'g', DIGIT_LIMIT);//Convert the number carefully
    ui->displayPanel->setText(displayLabel);//Set number back to display
}

void MainWindow::calculate_result() {
    
    QString displayLabel = ui->displayPanel->text();//Get string from display

    
     if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
         displayLabel.QString::chop(1);
     }//If the displayed number ends with a comma, drop the comma.

     
     if (storedOperator == '+') {
         storedNumber += displayLabel.toDouble();
     }
     else if (storedOperator == '-') {
         storedNumber -= displayLabel.toDouble();
     }
     else if (storedOperator == 'x') {
         storedNumber *= displayLabel.toDouble();
     }
     else if (storedOperator == '/') {
         storedNumber /= displayLabel.toDouble();
     }//Decide what to do according to operation

     
     displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);//Since there might be an overflow, its best to convert the number carefully
     ui->displayPanel->setText(displayLabel);//Set number back to display
}

//Keyboard buttons should call the corresponding functions
void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
        //Numbers
        case Qt::Key_1:
            numberGroup_clicked(ui->num1);
            break;
        case Qt::Key_2:
            numberGroup_clicked(ui->num2);
            break;
        case Qt::Key_3:
            numberGroup_clicked(ui->num3);
            break;
        case Qt::Key_4:
            numberGroup_clicked(ui->num4);
            break;
        case Qt::Key_5:
            numberGroup_clicked(ui->num5);
            break;
        case Qt::Key_6:
            numberGroup_clicked(ui->num6);
            break;
        case Qt::Key_7:
            numberGroup_clicked(ui->num7);
            break;
        case Qt::Key_8:
            numberGroup_clicked(ui->num8);
            break;
        case Qt::Key_9:
            numberGroup_clicked(ui->num9);
            break;
        case Qt::Key_0:
            numberGroup_clicked(ui->num0);
            break;
        //Operators
        case Qt::Key_Plus:
            actionGroup_clicked(ui->actionPlus);
            break;
        case Qt::Key_Minus:
            actionGroup_clicked(ui->actionMinus);
            break;
        case Qt::Key_Asterisk:
            actionGroup_clicked(ui->actionMul);
            break;
        case Qt::Key_Slash:
            actionGroup_clicked(ui->actionDiv);
            break;
        //Comma
        case Qt::Key_Period:
            on_comma_clicked();
            break;
        //Return (enter)
        case Qt::Key_Enter:
        case Qt::Key_Return:
            on_actionCalc_clicked();
            break;
        //Backspace and delete
        case Qt::Key_Backspace:
            on_actionDel_clicked();
            break;
        case Qt::Key_Delete:
            on_actionClear_clicked();
            break;
        //Percentage
        case Qt::Key_Percent:
            on_actionPercent_clicked();
            break;
    }
}
