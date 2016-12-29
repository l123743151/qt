#include "autotest.h"
#include "ui_autotest.h"
#include <QtCore>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QScrollBar>



QString fileName14 ="/mnt/jffs2/autotest.log";
void my_msleep(qint64 msec);

AUTOTEST::AUTOTEST(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AUTOTEST)
{
    ui->setupUi(this);
    setStyleSheet("background-color:gray;");

}

AUTOTEST::~AUTOTEST()
{
    delete ui;
}


void AUTOTEST::hhbar()

{
    QScrollBar *hbar = ui->textEdit->verticalScrollBar();
    hbar->setValue(99999999);
}

bool AUTOTEST::loadFile(const QString& fileName14)
{
    //uint i,j;
    QString t;
    QFile file(fileName14);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
       QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);


        ui->textEdit->setText(in.readAll());

    return true;
}


// report
void AUTOTEST::on_pushButton_autotest_start_3_clicked()
{
    report.show();
}





 //Buzzer test




void AUTOTEST::BuzzerTest()

{
        char str[1024];

       memset(str,0,1024);

        sprintf(str,"atop_buzzer > /mnt/jffs2/autotest.log");
        qDebug(str);

        system(str);


          my_msleep(2000);


        if (!fileName14.isEmpty())
        {
            if(loadFile(fileName14)){

            }
        }
}



void AUTOTEST::on_pushButton_autotest_disable_clicked()
{
    manual.show();
}

void AUTOTEST::on_pushButton_autotest_start_clicked()
{

   //QPixmap::grabWindow(QApplication::desktop()->winId()).save("/mnt/jffs2/test.png","png");


    ui->pushButton_autotest_start->setEnabled(false);




    char str[1024];

   memset(str,0,1024);

    sprintf(str,"atop_buzzer > /mnt/jffs2/autotest.log");
    qDebug(str);

    system(str);


      my_msleep(2000);


    if (!fileName14.isEmpty())
    {
        if(loadFile(fileName14)){

        }
    }

     my_msleep(3000);


     QFile file2("/mnt/jffs2/autotest.log");
     if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
     {
          QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file2.errorString()));

      }


     QTextStream in2(&file2);


      QString line2 = in2.readAll();

       if(line2.contains("Buzzer on"))
       {
           ui->label_autotest_buzzer->setText("PASS");
           ui->label_autotest_buzzer->setStyleSheet("color:green");
       }

       else
       {
               ui->label_autotest_buzzer->setText("FAIL");
               ui->label_autotest_buzzer->setStyleSheet("color:red");

       }
      file2.close();

    //COM Test

        char str3[1024];
         char str5[1024];
          char str4[1024];


       memset(str3,0,1024);

        sprintf(str3,"rs485_loopback 2 3  >> /mnt/jffs2/autotest.log");
        qDebug(str3);

        system(str3);

        sprintf(str4,"rs232_loopback 4 5  >> /mnt/jffs2/autotest.log");
        qDebug(str4);

        system(str4);

          my_msleep(2000);
        sprintf(str5,"rs485_loopback 1 6 >> /mnt/jffs2/autotest.log");
        qDebug(str5);

        system(str5);


          my_msleep(5000);


        if (!fileName14.isEmpty())
        {
            if(loadFile(fileName14)){

            }
        }


        my_msleep(3000);

        QFile file("/mnt/jffs2/autotest.log");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
             QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file.errorString()));

         }

         QTextStream in(&file);
         QString line;
          line=in.readAll();
          if(line.contains("rs485 loopback test ok"))
          {
              ui->label_autotest_com->setText("PASS");
              ui->label_autotest_com->setStyleSheet("color:green");
          }

          else
          {
                  ui->label_autotest_com->setText("FAIL");
                  ui->label_autotest_com->setStyleSheet("color:red");

          }



     //CAN TEST


                char str6[1024];
                char str7[1024];




               memset(str6,0,1024);

                sprintf(str6,"dcan_loopback 0 1 >> /mnt/jffs2/autotest.log");
                qDebug(str6);

                system(str6);
                sprintf(str7,"dcan_loopback 1 0");
                qDebug(str7);

                system(str7);



                  my_msleep(5000);


                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }

                 hhbar();

                my_msleep(3000);

                QFile file3("/mnt/jffs2/autotest.log");
                if (!file3.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file3.errorString()));

                 }

                QTextStream in3(&file);


                 QString line3;


                  line3=in3.readAll();
                  if(line3.contains("can 0 to can 1 loopback test passed!"))
                  {
                      ui->label_autotest_can->setText("PASS");
                      ui->label_autotest_can->setStyleSheet("color:green");
                  }

                  else
                  {
                          ui->label_autotest_can->setText("FAIL");
                          ui->label_autotest_can->setStyleSheet("color:red");

                  }


                    /*CAN SEND TEST

                    system("killall dcan_recv");
                    system("dcan_recv -b 125000 can1 &");

                    sprintf(str8,"dcan_send -e -D can0 -b 125000 0x0123457 1 2 3 4 5 0x66 0x77 0x88 > /mnt/jffs2/autotest.log");
                    qDebug(str8);

                    system(str8);


                      my_msleep(5000);


                    if (!fileName14.isEmpty())
                    {
                        if(loadFile(fileName14)){

                        }
                    }



                        if (!str7 == "<0x00123457> [8] 01 02 03 04 05 66 77 88")
                        {
                            ui->label_autotest_can->setText("FAIL");
                            ui->label_autotest_can->setStyleSheet("color:red");

                        }
                        else
                        {
                            ui->label_autotest_can->setText("PASS");
                            ui->label_autotest_can->setStyleSheet("color:green");
                        }

                    */

            //EEPROM


                char str9[1024];

                QString eeprom ="00f0: ff ff ff ff 03 03 03 01 c0 a8 02 01 ff ff 00 00    ................";

               memset(str9,0,1024);

                sprintf(str9,"atop_eeprom_util EEPROM 0 256 >> /mnt/jffs2/autotest.log");
                qDebug(str9);

                system(str9);


                  my_msleep(5000);


                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }

                 hhbar();

                my_msleep(3000);

                QFile file4("/mnt/jffs2/autotest.log");
                if (!file4.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file4.errorString()));

                 }

                    QTextStream in4(&file4);


                     QString line4;
                     while (!in4.atEnd()) {
                      line4 = in4.readLine();

                                         }

                    if (line4 == eeprom)
                    {
                        ui->label_autotest_eeprom->setText("PASS");
                        ui->label_autotest_eeprom->setStyleSheet("color:green");

                    }
                    else
                    {
                        ui->label_autotest_eeprom->setText("FAIL");
                        ui->label_autotest_eeprom->setStyleSheet("color:red");

                    }





            //DIDO

                char str11[1024];


                QString dido ="DI1 = 1";

               memset(str11,0,1024);

                sprintf(str11,"atop_di 1 1>> /mnt/jffs2/autotest.log");
                qDebug(str11);

                system(str11);

                system("atop_do 1 1");
                 my_msleep(1000);
                system("atop_do 1 0");
                 my_msleep(1000);
                system("atop_do 2 1");
                 my_msleep(1000);
                system("atop_do 2 0");
                 my_msleep(1000);
                system("atop_do 3 1");
                 my_msleep(1000);
                system("atop_do 3 0");
                 my_msleep(1000);
                system("atop_do 4 1");
                 my_msleep(1000);
                system("atop_do 4 0");
                 my_msleep(1000);
                system("atop_do 5 1");
                 my_msleep(1000);
                system("atop_do 5 0");
                 my_msleep(1000);
                system("atop_do 6 1");
                 my_msleep(1000);
                system("atop_do 6 0");



                  my_msleep(5000);


                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }

                hhbar();

                my_msleep(3000);

                QFile file5("/mnt/jffs2/autotest.log");
                if (!file5.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file5.errorString()));

                 }

                    QTextStream in5(&file5);


                     QString line5;
                     while (!in5.atEnd()) {
                      line5 = in5.readLine();

                                         }


                    if (line5 == dido)
                    {

                        ui->label_autotest_dido->setText("PASS");
                        ui->label_autotest_dido->setStyleSheet("color:green");


                    }
                    else
                    {
                        ui->label_autotest_dido->setText("FAIL");
                        ui->label_autotest_dido->setStyleSheet("color:red");
                    }






            //ESAM


                char str13[1024];
               QString esam= "ESAM_Responce : 90  0";

               memset(str13,0,1024);

                sprintf(str13,"esam_test >> /mnt/jffs2/autotest.log");
                qDebug(str13);

                system(str13);

                  my_msleep(5000);


                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }

                 hhbar();

                my_msleep(3000);

                QFile file6("/mnt/jffs2/autotest.log");
                if (!file6.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file6.errorString()));

                 }

                    QTextStream in6(&file6);


                     QString line6;
                     while (!in6.atEnd()) {
                      line6 = in6.readLine();

                                         }


                    if (line6 == esam)
                    {

                        ui->label_autotest_esam->setText("PASS");
                        ui->label_autotest_esam->setStyleSheet("color:green");

                    }
                    else
                    {
                        ui->label_autotest_esam->setText("FAIL");
                        ui->label_autotest_esam->setStyleSheet("color:red");

                    }






            //LAN


                char str15[1024];

               memset(str15,0,1024);

                sprintf(str15,"ifconfig  >> /mnt/jffs2/autotest.log");
                qDebug(str15);

                system(str15);




                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }
                 hhbar();

                my_msleep(3000);

                QFile file7("/mnt/jffs2/autotest.log");
                if (!file7.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file7.errorString()));

                 }

                    QTextStream in7(&file7);


                     QString line7;


                      line7=in7.readAll();
                      if(line7.contains("127.0.0.1"))
                      {
                          ui->label_autotest_lan->setText("PASS");
                          ui->label_autotest_lan->setStyleSheet("color:green");
                      }

                      else
                      {
                              ui->label_autotest_lan->setText("FAIL");
                              ui->label_autotest_lan->setStyleSheet("color:red");

                      }





                     /*
                     //while (!in7.atEnd()) {

                      //                   }

                    if (line7 == lan)
                    {
                        ui->label_autotest_lan->setText("PASS");
                        ui->label_autotest_lan->setStyleSheet("color:green");

                    }
                    else
                    {
                        ui->label_autotest_lan->setText("FAIL");
                        ui->label_autotest_lan->setStyleSheet("color:red");

                    }

                    */




            //rtc


                char str17[1024];

                char str19[1024];



               memset(str17,0,1024);

               system("killall date_adjust");
               system("ifconfig eth1 down");


                sprintf(str17,"set_rtc 2010/01/01-1:2:3 >> /mnt/jffs2/autotest.log");
                qDebug(str17);

                system(str17);


                sprintf(str19,"get_rtc  >> /mnt/jffs2/autotest.log");
                qDebug(str19);

                system(str19);




                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }
                 hhbar();


                my_msleep(3000);

                QFile file8("/mnt/jffs2/autotest.log");
                if (!file8.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file8.errorString()));

                 }

                    QTextStream in8(&file8);


                     QString line8;

                      line8 = in8.readAll();

                      if(line8.contains("2010/01/01 01:02:03"))
                      {
                          ui->label_autotest_time->setText("PASS");
                          ui->label_autotest_time->setStyleSheet("color:green");
                      }

                      else
                      {
                              ui->label_autotest_time->setText("FAIL");
                              ui->label_autotest_time->setStyleSheet("color:red");

                      }





            system("ifconfig eth1 up");

            //gprs


                char str20[1024];

               memset(str20,0,1024);

                system("killall gprs_run_daemon");
                sprintf(str20,"gprs_run_daemon 10 3 >> /mnt/jffs2/autotest.log&");
                qDebug(str20);

                system(str20);

                int j;
                for(j=0;j<6;j++)
                {

                my_msleep(5000);

                if (!fileName14.isEmpty())
                {
                    if(loadFile(fileName14)){

                    }
                }
                 hhbar();
                }

                 system("killall gprs_run");

                 my_msleep(3000);

                 QFile file9("/mnt/jffs2/autotest.log");
                 if (!file9.open(QIODevice::ReadOnly | QIODevice::Text))
                 {
                      QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file9.errorString()));

                  }

                 QTextStream in9(&file);


                  QString line9;


                   line9=in9.readAll();
                   if(line9.contains("GPRS is connected"))
                   {
                       ui->label_autotest_gprs->setText("PASS");
                       ui->label_autotest_gprs->setStyleSheet("color:green");
                   }

                   else
                   {
                           ui->label_autotest_gprs->setText("FAIL");
                           ui->label_autotest_gprs->setStyleSheet("color:red");

                   }



        //memory test



                   ui->label_autotest_memory->setText("Testing");
                   ui->label_autotest_memory->setStyleSheet("color:yellow");

                char str22[1024];
                QString memory="Done.";

               memset(str22,0,1024);

                sprintf(str22,"/mnt/usbdiska1/memtester 44M 1 >> /mnt/jffs2/autotest.log&");
                qDebug(str22);

                system(str22);

                int i;
                for(i=0;i<110;i++)
                {

                my_msleep(5000);

                    if (!fileName14.isEmpty())
                    {
                        if(loadFile(fileName14)){

                                }
                    }

                    hhbar();
                }




                QFile file10("/mnt/jffs2/autotest.log");
                if (!file10.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                     QMessageBox::warning(this, tr("Read File"),tr("can't read file %1:\n%2.").arg(fileName14).arg(file10.errorString()));

                 }

                    QTextStream in10(&file10);


                     QString line10;
                     while (!in10.atEnd()) {
                      line10 = in10.readLine();

                                         }

                    if (line10 == memory)
                    {
                        ui->label_autotest_memory->setText("PASS");
                        ui->label_autotest_memory->setStyleSheet("color:green");


                    }
                    else
                    {
                        ui->label_autotest_memory->setText("FAIL");
                        ui->label_autotest_memory->setStyleSheet("color:red");
                    }






              ui->pushButton_autotest_start->setEnabled(true);




}









