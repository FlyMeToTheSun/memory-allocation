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


std::vector<int> inputBlockArray;
std::vector<std::vector<int>> processArray;
std::vector<std::vector<int>> allocationArray;
std::vector<std::vector<int>> memoryBlockArray;

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

    curr_time_unit_lbl = new QLabel(this);
    curr_time_unit_lbl->setText("Current Time Unit: ");
    curr_time_unit_lbl->setFont(QFont("Times", 9));
    curr_time_unit_lbl->setStyleSheet("color:black");
    curr_time_unit_lbl->setGeometry(225,265,200,20);

    curr_fragmentation_lbl = new QLabel(this);
    curr_fragmentation_lbl->setText("Current Fragmentation: ");
    curr_fragmentation_lbl->setFont(QFont("Times", 9));
    curr_fragmentation_lbl->setStyleSheet("color:black");
    curr_fragmentation_lbl->setGeometry(225,285,200,20);

    curr_jobs_fin_lbl = new QLabel(this);
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

        //for the actuall process array
        std::vector<int> vectorProArray = {processSize,TUSize,0, false};
        processArray.push_back(vectorProArray);

        //for display only
        inputProcessSize->setText("");
        inputTUSize->setText("");

        input_table->setRowCount(in_tbl_ctr);
        input_table->setItem(in_tbl_ctr-1,0,new QTableWidgetItem(QString::number(in_tbl_ctr)));
        input_table->setItem(in_tbl_ctr-1,1,new QTableWidgetItem(QString::number(processArray[in_tbl_ctr-1][0])));
        input_table->setItem(in_tbl_ctr-1,2,new QTableWidgetItem(QString::number(processArray[in_tbl_ctr-1][1])));
        input_table->setItem(in_tbl_ctr-1,3,new QTableWidgetItem(QString::number(processArray[in_tbl_ctr-1][2])));
        in_tbl_ctr++;
    }
    else {
      QMessageBox::warning(this, "Error", "Illegal Entry");
    }

    qInfo() << processArray;

}

void Widget::delJob(){
    if (in_tbl_ctr > 1){
        in_tbl_ctr = in_tbl_ctr - 2;
        input_table->setRowCount(in_tbl_ctr);
        processArray.pop_back();

        in_tbl_ctr++;
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
        inputBlockArray.push_back(blockSize);
        block_ctr = block_ctr + 1;
        int blockYval = 5;
        int blockHeight = 200;

        //initializes a seperate  array for block allocation calculation
        memoryBlockArray.clear();
        for (int i = 1; i <= block_ctr; i++) {

          //rectangle output
          blockHeight = inputBlockArray[i-1];
          blockHeight = blockHeight/2;

          //block array replication
          int blockMaxRange = blockYval + blockHeight;
          std::vector<int> vectorArray = {i, blockHeight, blockYval, blockMaxRange};
          memoryBlockArray.push_back(vectorArray);
          qInfo() << "memoryBlockArray" << memoryBlockArray;

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
        block_ctr--;
        inputBlockArray.pop_back();
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

    //display memory block rectangles
    for (int i = 0; i < block_ctr; i++) {

      //rectangle output
      blockHeight = inputBlockArray[i];
      QString blockHeightStr = QString::number(blockHeight);
      blockHeight = blockHeight/2;
      painter.drawRect(QRect(blockXval,blockYval,100,blockHeight));

      //job simulation output

      //text output
      blockYval = blockYval + blockHeight + 1;
      QString blockSizeValTxt = blockHeightStr + "Kb";
      painter.drawText(blockXval+103,blockYval, blockSizeValTxt);

      //catches maximum range
      blockHeight = inputBlockArray[i+1];
      blockHeight = blockHeight/2;

      //moves block to next line
      currentYval = blockHeight + blockYval;
      if (currentYval > 750){
        blockXval = blockXval + 143;
        blockYval = 5;
      }
    }


    //display allocation rectangles
    int alloBlockXval = 450;
    QPen pen1;
    pen1.setColor(Qt::cyan);
    QBrush brush(Qt::cyan, Qt::SolidPattern);
    pen1.setWidth(1);


    QPen pen2;
    pen2.setColor(Qt::black);
    pen2.setWidth(2);


    int alloSize = allocationArray.size();
    for (int i = 0; i < alloSize; i++) {

      //rectangle output
      int alloBlockHeight = allocationArray[i][1];
      int alloBlockYVal = allocationArray[i][2];
      int alloBlockMaxRange = allocationArray[i][3];

      int paintYval = alloBlockYVal;
      if (alloBlockYVal > 750){
        paintYval = alloBlockYVal - 750;
      }
      else if (alloBlockYVal > 1500){
        paintYval = alloBlockYVal - 1500;
      }
      else if (alloBlockYVal > 2250){
          paintYval = alloBlockYVal - 2250;
      } else {
          paintYval = alloBlockYVal;
      }

      painter.setPen(pen1);
      painter.drawRect(QRect(alloBlockXval,paintYval,100,alloBlockHeight));
      painter.fillRect(QRect(alloBlockXval,paintYval,100,alloBlockHeight), brush);


      //text output
      painter.setPen(pen2);
      int midAlloBlockHeight = alloBlockYVal+(alloBlockHeight/2);
      QString alloBlockHeightStr = QString::number(allocationArray[i][4]);
      QString blockSizeValTxt = "Job " + alloBlockHeightStr;
      painter.drawText(alloBlockXval+20,midAlloBlockHeight, blockSizeValTxt);
    }
}

void Widget::FirstFit(){
    //qInfo() << "First Fit Started";

    int processArraySize = processArray.size();

    int blockArraySize = memoryBlockArray.size();

    int completedJobs = 0;
    int currentTime = 0;
    int currentJob = 1;
    int allocationArraySize = allocationArray.size();

    while (completedJobs <= processArraySize){
        qInfo() << "completed jobs: " <<currentJob;
        qInfo() << "proceessing: " <<currentJob;

        //check if job is not in the table
        if(processArray[currentJob-1][3] == false && processArray[currentJob-1][2] == 0){

            //iterates current job through all memory blocks
            for (int currentBlock = 1; currentBlock <= blockArraySize; currentBlock++)
            {

                //setup current block variables
                allocationArraySize = allocationArray.size();

                int currentJobSize = processArray[currentJob - 1][0];

                int currentBlockHeight=memoryBlockArray[currentBlock-1][1];
                int currentblockYval=memoryBlockArray[currentBlock-1][2];
                int currentblockMaxRange=memoryBlockArray[currentBlock-1][3];
                int currentblockNumber=memoryBlockArray[currentBlock-1][0];

                int currentAllocationBlockNumber;
                if (allocationArraySize>0)
                currentAllocationBlockNumber=allocationArray[currentBlock-1][0];

                //Check if process fits in memory block without considering allocations
                if (currentJobSize < currentBlockHeight){

                    //setup allocation variables
                    int allocationHeight = currentJobSize;

                    //check if process fits in memory block considering allocations
                    //considers if the array has members and if allocations exist within the memory block
                    if(allocationArraySize > 0)
                    {
                        int currentAllocationMaxRange;
                        for(int currentAllocationNumber = 0; currentAllocationNumber < allocationArraySize; currentAllocationNumber++){
                            for (int currentAllocationYValStart = 0; currentAllocationYValStart < currentBlockHeight; currentAllocationYValStart++){
                                int currentAllocationYVal = currentAllocationYValStart + currentblockYval;

                                int allocationArrayYVal = allocationArray[currentAllocationNumber][2];
                                int allocationArrayMaxRange = allocationArray[currentAllocationNumber][3];
                                //qInfo() << allocationArrayYVal << allocationArrayMaxRange;
                                if (currentBlock = allocationArray[currentAllocationNumber][0]){
                                    currentAllocationMaxRange = currentAllocationYVal + allocationArray[currentAllocationNumber][1];
                                    if(currentAllocationYVal > allocationArrayMaxRange){
                                        int allocationEnd = currentAllocationYVal + currentJobSize;
                                        std::vector<int> vectorSimArray = {currentBlock, currentJobSize, currentAllocationYVal, allocationEnd, currentJob};
                                        allocationArray.push_back(vectorSimArray);
                                        qInfo() << "Updated allocationArray: " << allocationArray;
                                        qInfo() << "Requirements: " << allocationArrayYVal << allocationArrayMaxRange;
                                        processArray[currentJob-1][3] = true;

                                        //break out of loop
                                        currentAllocationNumber = allocationArraySize;
                                        currentAllocationYValStart = currentBlockHeight;

                                    }
                                    else if(currentAllocationYVal < allocationArrayYVal && currentAllocationMaxRange < allocationArrayMaxRange){
                                        int allocationEnd = currentAllocationYVal + currentJobSize;
                                        std::vector<int> vectorSimArray = {currentBlock, currentJobSize, currentAllocationYVal, allocationEnd, currentJob};
                                        allocationArray.push_back(vectorSimArray);
                                        qInfo() << "Updated allocationArray: " << allocationArray;
                                        qInfo() << "Requirements: " << allocationArrayYVal << allocationArrayMaxRange;
                                        processArray[currentJob-1][3] = true;

                                        //break out of loop
                                        currentAllocationNumber = allocationArraySize;
                                        currentAllocationYValStart = currentBlockHeight;
                                    }
                                }
                                else{
                                    qInfo() << "no availiable block for allocation";
                                }
                            }
                        }
                    }
                    //catches if there is no allocations yet
                    else if(allocationArraySize <= 0){
                        int allocationStart = currentblockYval;
                        int allocationEnd = currentblockYval + currentJobSize;

                        //assigns allocation
                        std::vector<int> vectorSimArray = {currentBlock, allocationHeight, allocationStart, allocationEnd, currentJob};
                        allocationArray.push_back(vectorSimArray);
                        qInfo() << "New AllocationArray: " << allocationArray;
                        processArray[currentJob-1][3] = true;
                        currentBlock=1;//reset crrentBlock
                    }
                }
            }
        }


        //remove allocation if finished
        for (int processCounter = 0; processCounter < processArraySize;processCounter++){
            if(processArray[processCounter][1] == 0){
               processArray[processCounter][3]=false;
               for (int i = 0; i < allocationArraySize; i++)
               {
                   if (processCounter == allocationArray[i][0])
                   {
                        allocationArray.erase(allocationArray.begin() + i);
                   }
               }
            }
        }


        //check if job is in the allocations and not finished
        if(processArray[currentJob-1][3] == true && processArray[currentJob-1][1] != 0){
            processArray[currentJob-1][1] = processArray[currentJob-1][1] - 1;
            processArray[currentJob-1][2] = processArray[currentJob-1][1] + 1;
        }

        //check if job is not in allocations and finished
        completedJobs = 0;//reset counter
        for (int processCounter = 0; processCounter < processArraySize;processCounter++){
            if(processArray[processCounter][3] == false && processArray[processCounter][1] == 0){
               completedJobs++;
               //since this iteration covers all jobs, if all jobs are complete we abort the the simulation loop

            }
        }

        //movement of variables
        delay();
        if (currentJob < processArraySize){
            currentJob = currentJob + 1;
        }
        else {
            currentJob = 1;
        }

        update();
        currentTime = currentTime + 1;
        QString timeStr = QString::number(currentTime);
        QString timValTxt = "Current Time Unit: " + timeStr;
        curr_time_unit_lbl->setText(timValTxt);
    }

    QMessageBox::information(this, "Complete", "Simulation Complete");

    //enaable buttons
    add_job_btn->setEnabled(true);
    del_job_btn->setEnabled(true);
    add_block_btn->setEnabled(true);
    del_block_btn->setEnabled(true);
    simul_job_btn->setEnabled(true);


}
void Widget::BestFit(){

}
void Widget::WorstFit(){

}

void Widget::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


