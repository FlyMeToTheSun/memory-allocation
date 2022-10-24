#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QMenu>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QTableWidget>
#include<QTableWidgetItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTime>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;

    QLineEdit *algo_line;
    QLabel *sel_algo_lbl;
    QPushButton *alloc_select_btn;
    QComboBox *alloc_select_cmb;
    QLineEdit *inputProcessSize;
    QLineEdit *inputBlockSize;
    QLineEdit *inputTUSize;
    QLineEdit *inputCompTime;
    QLineEdit *inputCoalTime;
    QTableWidget *input_table;

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    QGraphicsView* view;

    QPushButton *add_job_btn;
    QPushButton *del_job_btn;
    QPushButton *add_block_btn;
    QPushButton *del_block_btn;
    QPushButton *simul_job_btn;

    bool m_clicked;


public slots:
    void addJob();
    void delJob();
    void addBlock();
    void delBlock();
    void paintEvent(QPaintEvent *event);
    void startSim();

    void FirstFit();
    void BestFit();
    void WorstFit();

    void delay();
};
#endif // WIDGET_H
