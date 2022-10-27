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
    curr_time_unit_lbl->setText("Current Time Unit: 0");
    curr_time_unit_lbl->setFont(QFont("Times", 9));
    curr_time_unit_lbl->setStyleSheet("color:black");
    curr_time_unit_lbl->setGeometry(225,265,200,20);

    curr_job_lbl = new QLabel(this);
    curr_job_lbl->setText("Current Job: 0");
    curr_job_lbl->setFont(QFont("Times", 9));
    curr_job_lbl->setStyleSheet("color:black");
    curr_job_lbl->setGeometry(225,285,200,20);

    curr_jobs_fin_lbl = new QLabel(this);
    curr_jobs_fin_lbl->setText("Jobs Finished: 0");
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
        //inputBlockArray.push_back(blockSize);
        //block_ctr = block_ctr + 1;
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

    int currentYval = 0;
    painter.setPen(pen);
    painter.drawRect(QRect(5,28,410,190));
    painter.drawRect(QRect(5,230,410,160));

    pen.setColor(Qt::black);

    pen.setWidth(3);
    painter.setPen(pen);

    int blockXval = 450;
    int blockYval = 5;
    int blockHeight;

    //display memory block rectangles
    int memoryBlockSize = memoryBlockArray.size();
    for (int i = 0; i < memoryBlockSize; i++) {
      //rectangle output
      blockHeight = (memoryBlockArray[i][1]);
      blockHeight = blockHeight*2;
      QString blockHeightStr = QString::number(blockHeight);
      blockHeight = blockHeight/2;
      painter.drawRect(QRect(blockXval,blockYval,100,blockHeight));

      //text output
      blockYval = blockYval + blockHeight + 1;
      QString blockSizeValTxt = blockHeightStr + "Kb";
      painter.drawText(blockXval+103,blockYval, blockSizeValTxt);

      //moves block to next line
      currentYval = (memoryBlockArray[i+1][3]);
      if (currentYval > 750){
        blockXval = blockXval + 143;
        blockYval = 5;
      }
    }


    //display allocation rectangles
    QPen pen1;
    pen1.setColor(Qt::black);
    QBrush brush(Qt::cyan, Qt::SolidPattern);
    pen1.setWidth(2);


    QPen pen2;
    pen2.setColor(Qt::black);
    pen2.setWidth(2);

    int blockXval2 = 450;
    int blockYval2 = 5;
    int blockHeight2;

    int alloSize = allocationArray.size();
    for (int i = 0; i < alloSize; i++)
    {
        //rectangle output
        blockHeight2 = (allocationArray[i][1]);
        QString blockHeightStr = QString::number(blockHeight2*2);
        blockHeight2 = blockHeight2/2;

        painter.setPen(pen1);
        painter.drawRect(QRect(blockXval2,blockYval2,100,blockHeight2));
        painter.fillRect(QRect(blockXval2,blockYval2,100,blockHeight2), brush);

        //text output
        painter.setPen(pen2);
        int midAlloBlockHeight = allocationArray[i][3]+(blockHeight2/2);
        QString alloBlockHeightStr = QString::number(allocationArray[i][4]);
        QString blockSizeValTxt = "Job " + alloBlockHeightStr;
        painter.drawText(blockXval2+20,midAlloBlockHeight, blockSizeValTxt);

        //catches maximum range
        blockHeight2 = allocationArray[i+1][1];

        //moves block to next line
        int currentYval2 = blockHeight2 + blockYval2;
        if (currentYval2 > 750)
        {
            blockXval2 = blockXval2 + 143;
            blockYval2 = 5;
        }
    }

}

void Widget::FirstFit(){
    int processArraySize = processArray.size();
    int blockArraySize = memoryBlockArray.size();
    int allocationArraySize = allocationArray.size();
    int completedJobs = 0;
    int currentTime = 0;


    for (int jobCounter = 0; completedJobs < processArraySize; jobCounter++){

        //check if a process cannot fit into any block
        int overSizeBlock = 0;
        for (int blockCounter = 0; blockCounter < blockArraySize;blockCounter++)
        {
            if ((processArray[blockCounter][0]/2) > memoryBlockArray[blockCounter][1])
            {
                overSizeBlock++;
            }
            if(overSizeBlock >= blockArraySize)
            {
                goto error;
            }
        }


        //check if job is not in allocations and finished
        completedJobs = 0;//reset counter
        for (int processCounter = 0; processCounter < processArraySize;processCounter++){
            //qInfo() << processArray[processCounter][3] << processArray[processCounter][1];
            if(processArray[processCounter][3] == false && processArray[processCounter][1] == 0){
               completedJobs++;
               //since this iteration covers all jobs, if all jobs are complete we abort the the simulation loop
            }
            if (completedJobs >= processArraySize){
                goto complete;
            }
        }

        //resets loop indefinitely
        if(jobCounter>=processArraySize){
            jobCounter = 0;
        }

        //manages the time variable
        currentTime++;
        QString timeStr = QString::number(currentTime);
        QString timValTxt = "Current Time Unit: " + timeStr;
        curr_time_unit_lbl->setText(timValTxt);


        //increment turnaround time despite not in memory
        for (int jobCounter = 0; jobCounter<processArraySize; jobCounter++){
            if(processArray[jobCounter][3] == false && processArray[jobCounter][1] != 0){
                processArray[jobCounter][2] = processArray[jobCounter][2] + 1;

                input_table->setItem(jobCounter,2,new QTableWidgetItem(QString::number(processArray[jobCounter][1])));
                input_table->setItem(jobCounter,3,new QTableWidgetItem(QString::number(processArray[jobCounter][2])));
            }
        }

        //check if job is in the allocations and not finished
        for (int jobCounter = 0; jobCounter<processArraySize; jobCounter++){
            if(processArray[jobCounter][3] == true && processArray[jobCounter][1] != 0){
                processArray[jobCounter][1] = processArray[jobCounter][1] - 1;
                processArray[jobCounter][2] = processArray[jobCounter][2] + 1;

                input_table->setItem(jobCounter,2,new QTableWidgetItem(QString::number(processArray[jobCounter][1])));
                input_table->setItem(jobCounter,3,new QTableWidgetItem(QString::number(processArray[jobCounter][2])));
            }
        }

        for (int blockCounter = 0; blockCounter < blockArraySize; blockCounter++){
            //qInfo() << jobCounter << blockCounter << (processArray[jobCounter][0]/2) << memoryBlockArray[blockCounter][1];

            if ((processArray[jobCounter][0]/2) <= memoryBlockArray[blockCounter][1] && processArray[jobCounter][3] == false)
            {
                if(allocationArraySize==0 && processArray[jobCounter][3] == false)
                {
                    int possibleAllocationStart = memoryBlockArray[blockCounter][2];
                    int possibleAllocationEnd = possibleAllocationStart + (processArray[jobCounter][0]/2);

                    std::vector<int> vectorSimArray = {blockCounter+1, (processArray[jobCounter][0]/2), possibleAllocationStart, possibleAllocationEnd, jobCounter+1};
                    allocationArray.push_back(vectorSimArray);
                    qInfo() << "New allocationArray: " << allocationArray;
                    processArray[jobCounter][3] = true;
                    update();
                    allocationArraySize = allocationArray.size();

                    //break out of for loop
                    goto resetLoop;
                }

                std::vector<int> tempAlloArray;

                for(int alloCounter = 0; alloCounter < allocationArraySize; alloCounter++)
                {
                    int alloEnd = allocationArray[alloCounter][3];
                    for (int alloStart = allocationArray[alloCounter][2]; alloStart<=alloEnd;alloStart++){
                         tempAlloArray.push_back(alloStart);
                    }
                }
                int tempAlloSize = tempAlloArray.size();

                for(int memoryCounter = memoryBlockArray[blockCounter][2]; memoryCounter <= memoryBlockArray[blockCounter][3]; memoryCounter++)
                {
                    int possibleAllocationStart = memoryCounter;
                    int possibleAllocationEnd = possibleAllocationStart + (processArray[jobCounter][0]/2);

                    for (int tempAlloCounter =0;tempAlloCounter<tempAlloSize;tempAlloCounter++){
                        if (std::count(tempAlloArray.begin(), tempAlloArray.end(), possibleAllocationStart)) {
                        }
                        else
                        {
                            if (possibleAllocationEnd-1 <= memoryBlockArray[blockCounter][3] && processArray[jobCounter][3] == false){
                                std::vector<int> vectorSimArray = {blockCounter+1, (processArray[jobCounter][0]/2), possibleAllocationStart, possibleAllocationEnd, jobCounter+1};
                                allocationArray.push_back(vectorSimArray);
                                qInfo() << "Updated more allocationArray: " << allocationArray;
                                processArray[jobCounter][3] = true;
                                update();
                                allocationArraySize = allocationArray.size();

                                tempAlloArray.clear();

                                for(int alloCounter = 0; alloCounter < allocationArraySize; alloCounter++)
                                {
                                    int alloEnd = allocationArray[alloCounter][3];
                                    for (int alloStart = allocationArray[alloCounter][2]; alloStart<=alloEnd;alloStart++){
                                         tempAlloArray.push_back(alloStart);
                                    }
                                }
                                tempAlloSize = tempAlloArray.size();

                            }
                        }
                    }
                }
            }
        }

        //remove allocation if finished
        for (int processCounter = 0; processCounter < processArraySize;processCounter++){
            //qInfo() << processArray[processCounter][1]<<processArray[processCounter][3];
            if(processArray[processCounter][1] == 0){
               processArray[processCounter][3]=false;
               for (int i = 0; i < allocationArraySize; i++)
               {
                   if ((processCounter+1) == allocationArray[i][4])
                   {
                        allocationArray.erase( std::next( std::begin( allocationArray ), i ) );
                        qInfo() << "after removal" << allocationArray;
                        update();
                        allocationArraySize = allocationArray.size();
                   }
               }
            }
        }
        resetLoop:
        delay();
    }

    goto complete;

    error:
    QMessageBox::critical(this, "Error", "One of the job sizes is too large for any of the inputted memory blocks");

    //enaable buttons
    add_job_btn->setEnabled(true);
    del_job_btn->setEnabled(true);
    add_block_btn->setEnabled(true);
    del_block_btn->setEnabled(true);
    simul_job_btn->setEnabled(true);
    goto exit;

    complete:
    QMessageBox::information(this, "Complete", "Simulation Complete");

    //reset all process
    for (int processCounter = 0; processCounter < processArraySize;processCounter++){
           processArray[processCounter][3]=false;
           processArray[processCounter][1] = processArray[processCounter][2];
           processArray[processCounter][2] = 0;
    }

    //enaable buttons
    add_job_btn->setEnabled(true);
    del_job_btn->setEnabled(true);
    add_block_btn->setEnabled(true);
    del_block_btn->setEnabled(true);
    simul_job_btn->setEnabled(true);

    exit:
    return;

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

void Widget::tableUpdate(int x,int y, int z){
    input_table->setItem(x,2,new QTableWidgetItem(QString::number(y)));
    input_table->setItem(x,3,new QTableWidgetItem(QString::number(z)));
}

