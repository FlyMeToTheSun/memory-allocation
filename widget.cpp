#include "widget.h"

#include<QLabel>
#include<QPushButton>
#include<QMenu>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QMessageBox>
#include<QPainter>

#include<QGraphicsScene>
#include<QGraphicsView>

#include<vector>

#include "ui_widget.h"

#include <QTime>


std::vector<int> processSizeArray;
std::vector<int> processTUArray;
std::vector<int> blockSizeArray;
std::vector<std::vector<int>> allocationArray;
std::vector<std::vector<int>> blockGeneralArray;

int in_tbl_ctr = 1;
int block_ctr = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    m_clicked = false;
    setWindowTitle("Memory Allocation");
    resize(1000,750);

    QLabel *label = new QLabel(this);
    label->setText("Control Panel");
    label->setFont(QFont("Times", 11));
    label->setStyleSheet("color:black");
    label->setGeometry(170,10,200,20);

    /*QLabel *label1 = new QLabel(this);
    label1->setText("Visualization");
    label1->setFont(QFont("Times", 11));
    label1->setStyleSheet("color:black");
    label1->setGeometry(600,10,200,20);*/

    //MODIFY JOBS ---------------------------------------------------------------------------
    QLabel *add_job_lbl = new QLabel(this);
    add_job_lbl->setText("Modify Jobs");
    add_job_lbl->setFont(QFont("Times",9));
    add_job_lbl->setStyleSheet("color:black");
    add_job_lbl->setGeometry(80,30,100,30);

    QLabel *process_size_lbl = new QLabel(this);
    process_size_lbl->setText("Job Size (Kb)");
    process_size_lbl->setFont(QFont("Times",9));
    process_size_lbl->setStyleSheet("color:black");
    process_size_lbl->setGeometry(10,65,100,30);

    inputProcessSize = new QLineEdit(this);
    inputProcessSize->setFont(QFont("Times", 9));
    inputProcessSize->setGeometry(100,65,100,30);

    QLabel *time_unit_lbl = new QLabel(this);
    time_unit_lbl->setText("Time Unit");
    time_unit_lbl->setFont(QFont("Times",9));
    time_unit_lbl->setStyleSheet("color:black");
    time_unit_lbl->setGeometry(10,105,100,30);

    inputTUSize = new QLineEdit(this);
    inputTUSize->setFont(QFont("Times", 9));
    inputTUSize->setGeometry(100,105,100,30);

    add_job_btn = new QPushButton(this);
    add_job_btn->setText("Add Job");
    add_job_btn->setFont(QFont("Times", 9));
    add_job_btn->setGeometry(10,140,200,30);
    connect(add_job_btn, SIGNAL(clicked()), this, SLOT(addJob()));

    del_job_btn = new QPushButton(this);
    del_job_btn->setText("Delete Latest Job");
    del_job_btn->setFont(QFont("Times", 9));
    del_job_btn->setGeometry(10,175,200,30);
    connect(del_job_btn, SIGNAL(clicked()), this, SLOT(delJob()));

    //MODIFY MEMORY BLOCK SIZE ---------------------------------------------------------------------------
    QLabel *mod_block_lbl = new QLabel(this);
    mod_block_lbl->setText("Modify Memory Blocks");
    mod_block_lbl->setFont(QFont("Times",9));
    mod_block_lbl->setStyleSheet("color:black");
    mod_block_lbl->setGeometry(250,30,130,30);

    QLabel *block_size_lbl = new QLabel(this);
    block_size_lbl->setText("Block Size (Kb)");
    block_size_lbl->setFont(QFont("Times", 9));
    block_size_lbl->setStyleSheet("color:black");
    block_size_lbl->setGeometry(210,85,100,30);

    inputBlockSize = new QLineEdit(this);
    inputBlockSize->setFont(QFont("Times", 9));
    inputBlockSize->setGeometry(300,85,100,30);

    add_block_btn = new QPushButton(this);
    add_block_btn->setText("Add Memory Block");
    add_block_btn->setFont(QFont("Times", 9));
    add_block_btn->setGeometry(210,140,200,30);
    connect(add_block_btn, SIGNAL(clicked()), this, SLOT(addBlock()));

    del_block_btn = new QPushButton(this);
    del_block_btn->setText("Delete Latest Memory Block");
    del_block_btn->setFont(QFont("Times", 9));
    del_block_btn->setGeometry(210,175,200,30);
    connect(del_block_btn, SIGNAL(clicked()), this, SLOT(delBlock()));

    //SELECT ALGO ---------------------------------------------------------------------------
    QLabel *sel_algo_lbl = new QLabel(this);
    sel_algo_lbl->setText("Modify Algorithm");
    sel_algo_lbl->setFont(QFont("Times", 9));
    sel_algo_lbl->setStyleSheet("color:black");
    sel_algo_lbl->setGeometry(50,230,200,30);

    alloc_select_cmb = new QComboBox(this);
    alloc_select_cmb->setFont(QFont("Times", 9));
    alloc_select_cmb->addItem("First Fit");
    alloc_select_cmb->addItem("Best Fit");
    alloc_select_cmb->addItem("Worst Fit");
    alloc_select_cmb->setGeometry(10,265,200,30);

    simul_job_btn = new QPushButton(this);
    simul_job_btn->setText("Begin Simulation");
    simul_job_btn->setFont(QFont("Times", 9));
    simul_job_btn->setGeometry(210,350,200,30);
    connect(simul_job_btn, SIGNAL(clicked()), this, SLOT(startSim()));


    //SELECT ALGO VALUES --------------------------------------------------------------------------
    QLabel *comp_time_lbl = new QLabel(this);
    comp_time_lbl->setText("Compaction\nTime:");
    comp_time_lbl->setFont(QFont("Times",9));
    comp_time_lbl->setStyleSheet("color:black");
    comp_time_lbl->setGeometry(10,305,85,30);
    comp_time_lbl->setWordWrap(true);
    comp_time_lbl->setAlignment(Qt::AlignRight);

    inputCompTime = new QLineEdit(this);
    inputCompTime->setFont(QFont("Times", 9));
    inputCompTime->setGeometry(100,305,100,30);

    QLabel *coal_time_lbl = new QLabel(this);
    coal_time_lbl->setText("Coalescing\nHole Time:");
    coal_time_lbl->setFont(QFont("Times",9));
    coal_time_lbl->setStyleSheet("color:black");
    coal_time_lbl->setGeometry(10,350,85,30);
    coal_time_lbl->setWordWrap(true);
    coal_time_lbl->setAlignment(Qt::AlignRight);

    inputCoalTime = new QLineEdit(this);
    inputCoalTime->setFont(QFont("Times", 9));
    inputCoalTime->setGeometry(100,350,100,30);

    //SIMULATION RESULTS ---------------------------------------------------------------------------
    QLabel *job_off_lbl = new QLabel(this);
    job_off_lbl->setText("Job Information");
    job_off_lbl->setFont(QFont("Times", 9));
    job_off_lbl->setStyleSheet("color:black");
    job_off_lbl->setGeometry(260,230,200,30);

    QLabel *curr_time_unit_lbl = new QLabel(this);
    curr_time_unit_lbl->setText("Current Time Unit: ");
    curr_time_unit_lbl->setFont(QFont("Times", 9));
    curr_time_unit_lbl->setStyleSheet("color:black");
    curr_time_unit_lbl->setGeometry(225,265,200,20);

    QLabel *curr_fragmentation_lbl = new QLabel(this);
    curr_fragmentation_lbl->setText("Current Fragmentation: ");
    curr_fragmentation_lbl->setFont(QFont("Times", 9));
    curr_fragmentation_lbl->setStyleSheet("color:black");
    curr_fragmentation_lbl->setGeometry(225,285,200,20);

    QLabel *curr_jobs_fin_lbl = new QLabel(this);
    curr_jobs_fin_lbl->setText("Jobs Finished: ");
    curr_jobs_fin_lbl->setFont(QFont("Times", 9));
    curr_jobs_fin_lbl->setStyleSheet("color:black");
    curr_jobs_fin_lbl->setGeometry(225,305,200,20);

    //TABLES ---------------------------------------------------------------------------
    input_table = new QTableWidget(this);
    input_table->setFont(QFont("Times", 9));
    input_table->setGeometry(10,400,400,300);

    QStringList input_table_horzHeaders;
    input_table_horzHeaders << "Job Number" << "Job Size" << "Remaining Time" << "Turn Around Time";

    input_table->setRowCount(0);
    input_table->setColumnCount(4);
    input_table->setHorizontalHeaderLabels(input_table_horzHeaders);

    //VISUALIZATION OF MEMORY BLOCKS ---------------------------------------------------------------------------

}

Widget::~Widget()
{
}

void Widget::startSim(){
    QString algorithm_selected = alloc_select_cmb->currentText();
    QString compTimeStr = inputCompTime->text();
    QString coalTimeStr = inputCoalTime->text();

    bool ok;

    int compTime = compTimeStr.toInt(&ok);
    int coalTime = coalTimeStr.toInt(&ok);

    if (compTime > 0 && coalTime > 0 && compTime <= 50 && coalTime <= 50 && in_tbl_ctr > 0 && block_ctr > 0) {
        qInfo() << "Simulation Start";
        qDebug() << algorithm_selected;
        qInfo() <<  "Comp: " << compTime << "\nCoal: " << coalTime;

        //disable buttons
        add_job_btn->setEnabled(false);
        del_job_btn->setEnabled(false);
        add_block_btn->setEnabled(false);
        del_block_btn->setEnabled(false);
        simul_job_btn->setEnabled(false);

        if (algorithm_selected == "First Fit"){
            FirstFit();
        }
        else if (algorithm_selected == "Best Fit"){
            BestFit();
        }
        else {
            WorstFit();
        }

    }
    else {
             QMessageBox::warning(this, "Error", "Incomplete Values\nCompaction/Coalescing Time Size Out of Bounds, Max 50");
        }

}

void Widget::addJob(){

    QString processSizeStr = inputProcessSize->text();
    QString blockTUStr = inputTUSize->text();

    bool ok;

    int processSize = processSizeStr.toInt(&ok);
    int TUSize = blockTUStr.toInt(&ok);


    if (processSize > 0 && TUSize > 0 && processSize < 1000 && TUSize < 1000 ) {
        processSizeArray.push_back(processSize);
        processTUArray.push_back(TUSize);
        inputProcessSize->setText("");
        inputTUSize->setText("");

        qInfo() << processSizeArray[in_tbl_ctr-1];
        qInfo() << processTUArray[in_tbl_ctr-1];
        input_table->setRowCount(in_tbl_ctr);
        input_table->setItem(in_tbl_ctr-1,0,new QTableWidgetItem(QString::number(in_tbl_ctr)));
        input_table->setItem(in_tbl_ctr-1,1,new QTableWidgetItem(QString::number(processSizeArray[in_tbl_ctr-1])));
        input_table->setItem(in_tbl_ctr-1,2,new QTableWidgetItem(QString::number(processTUArray[in_tbl_ctr-1])));
        in_tbl_ctr = in_tbl_ctr + 1;
    }
    else {
      QMessageBox::warning(this, "Error", "Illegal Entry");
    }


    qInfo() << processSizeArray;
    qInfo() << processTUArray;

}

void Widget::delJob(){
    if (in_tbl_ctr > 1){
        in_tbl_ctr = in_tbl_ctr - 2;
        input_table->setRowCount(in_tbl_ctr);
        processSizeArray.pop_back();
        processTUArray.pop_back();

        in_tbl_ctr = in_tbl_ctr + 1;
    }
    else {
             QMessageBox::warning(this, "Error", "Nothing to Delete");
        }
}

void Widget::addBlock(){
    QString blockSizeStr = inputBlockSize->text();
    bool ok;
    int blockSize = blockSizeStr.toInt(&ok);
    if (blockSize > 0 && blockSize <= 1450 ) {
        //below array used for block gui presentaiton
        blockSizeArray.push_back(blockSize);
        block_ctr = block_ctr + 1;
        int blockYval = 5;
        int blockHeight = 200;

        //initializes a seperate  array for block allocation calculation
        blockGeneralArray.clear();
        for (int i = 0; i < block_ctr; i++) {

          //rectangle output
          blockHeight = blockSizeArray[i];
          blockHeight = blockHeight/2;

          //block array replication
          int blockMaxRange = blockYval + blockHeight;
          std::vector<int> vectorArray = {i, blockHeight, blockYval, blockMaxRange};
          blockGeneralArray.push_back(vectorArray);
          qInfo() << blockGeneralArray;

          blockYval = blockMaxRange + 1;

        }

        inputBlockSize->setText("");
        update();
    }
    else {
             QMessageBox::warning(this, "Error", "Illegal Entry or Size Out of Bounds\nMax 1.45Mb or 1450Kb per block due to GUI limitations\nMinimum recommended sizes above 50k");
        }
}

void Widget::delBlock(){
    if (block_ctr >= 1){
        block_ctr = block_ctr - 1;
        blockSizeArray.pop_back();
        update();
    }
    else {
             QMessageBox::warning(this, "Error", "Nothing to Delete");
        }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen;

    pen.setColor(Qt::gray);
    pen.setWidth(1);

    int blockXval = 450;
    int blockYval = 5;
    int blockHeight = 200;
    int currentYval = 0;
    painter.setPen(pen);
    painter.drawRect(QRect(5,28,410,190));
    painter.drawRect(QRect(5,230,410,160));

    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    //display rectangles
    for (int i = 0; i < block_ctr; i++) {

      //rectangle output
      blockHeight = blockSizeArray[i];
      QString blockHeightStr = QString::number(blockHeight);
      blockHeight = blockHeight/2;
      painter.drawRect(QRect(blockXval,blockYval,100,blockHeight));

      //job simulation output

      //text output
      blockYval = blockYval + blockHeight + 1;
      QString blockSizeValTxt = blockHeightStr + "Kb";
      painter.drawText(blockXval+103,blockYval, blockSizeValTxt);

      //catches maximum range
      blockHeight = blockSizeArray[i+1];
      blockHeight = blockHeight/2;

      //moves block to next line
      currentYval = blockHeight + blockYval;
      if (currentYval > 750){
        blockXval = blockXval + 143;
        blockYval = 5;
      }
    }
}

void Widget::FirstFit(){
    qInfo() << "First Fit Started";

    int jobArraySize = processSizeArray.size();

    int blockArraySize = blockGeneralArray.size();

    int completedJobs = 0;
    int currentTime = 0;

    int currentJob = 1;

    while (completedJobs < jobArraySize){

        for (int currentBlock = 0; currentBlock < blockArraySize; currentBlock++)
        {
            qInfo() << "Current Block: "<< currentBlock;
            //setup current block variables
            int allocationArraySize = allocationArray.size();
            qInfo() << "Current AllocationSize: "<< allocationArraySize;
            int currentBlockHeight=blockGeneralArray[currentBlock][1];
            int currentblockYval=blockGeneralArray[currentBlock][2];
            int currentblockMaxRange=blockGeneralArray[currentBlock][3];
            int currentblockNumber=blockGeneralArray[currentBlock][0];

            int currentJobSize = processSizeArray[currentJob - 1];

            //Check if process fits in memory block without considering previous allocations
            if (currentJobSize < currentBlockHeight){

                //setup allocation variables
                int allocationHeight = currentJobSize;

                //check if process fits in memory block considering previous allocations
                //considers if the array has members and if said allocations exist with the memory block
                if(allocationArraySize > 0 && currentBlock == currentblockNumber)
                {
                    //iterates through all avaliable spaces(Kb) of the memory block
                    for (int currentAllocation = 0; currentAllocation < currentBlockHeight; currentAllocation++){

                        int checkCurrentAllocation = currentAllocation + currentBlockHeight;
                        int checkPossibleMaxAllocation = checkCurrentAllocation + allocationHeight;

                        //checks if currentAllocation is within range of any other allocations.
                        if (checkCurrentAllocation != allocationArray[currentAllocation][2]){

                            //checks if possible max allocation is within block range
                            if(checkPossibleMaxAllocation < allocationArray[currentAllocation][3] && checkPossibleMaxAllocation < currentblockMaxRange){
                                int allocationStart = checkCurrentAllocation;
                                int allocationEnd = allocationArray[currentAllocation][3];

                                //assigns allocation
                                std::vector<int> vectorSimArray = {currentBlock, allocationHeight, allocationStart, allocationEnd};
                                allocationArray.push_back(vectorSimArray);
                                qInfo() << "Inserted Value";
                            }
                        }
                    }
                }
                else{
                    int allocationStart = currentBlockHeight;
                    int allocationEnd = currentBlockHeight + currentJobSize;

                    //assigns allocation
                    std::vector<int> vectorSimArray = {currentBlock, allocationHeight, allocationStart, allocationEnd};
                    allocationArray.push_back(vectorSimArray);
                    qInfo() << "Inserted Value via no array";
                }

            }
        }

        //checks if job is complete

        //movement of variables
        delay();
        currentJob = currentJob + 1;
        currentTime = currentTime + 1;
    }
}
void Widget::BestFit(){

}
void Widget::WorstFit(){

}

void Widget::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


