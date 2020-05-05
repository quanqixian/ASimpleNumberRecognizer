#include "RecognizerUI.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

RecognizerUI::RecognizerUI(): QWidget(NULL, Qt::WindowCloseButtonHint)
{
    //QDesktopWidget *deskdop = QApplication::desktop ();
    this->resize(410, 300);
    this->move(300, 100);
    //this->move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);
}

bool RecognizerUI::construct()
{
    bool ret = true;

    /* 顶部提示语 */
    m_labelReminder.setParent(this);
    m_labelReminder.move(10,5);
    m_labelReminder.resize(400,30);
    m_labelReminder.setText("Please write a number between 0-9 use your mouse in drawing board");

    /* 显示识别结果 */
    QFont font ;
    m_labelResult.setParent(this);
    m_labelResult.move(30,60);
    m_labelResult.resize(150,180);
    m_labelResult.setStyleSheet("border:2px solid red;");
    font.setPointSize(110);
    m_labelResult.setFont(font);
    m_labelResult.setText("0");

    /* 画板 */
    m_drawingBoard = new DrawingBoard(this, 150,180);
    m_drawingBoard->move(240,60);
    /* 学习按钮 */
    m_buttonsLearn.setParent(this);
    m_buttonsLearn.move(30,260);
    m_buttonsLearn.resize(70,25);
    m_buttonsLearn.setText("Learn");

    /* 数字选择下拉列表 */
    QStringList textList;
    textList.clear();
    textList<<tr("0")<<tr("1")<<tr("2")<<tr("3")<<tr("4")<<tr("5")<<tr("6")<<tr("7")<<tr("8")<<tr("9");

    m_comboBoxChoiceNumber.setParent(this);
    m_comboBoxChoiceNumber.clear();
    m_comboBoxChoiceNumber.addItems(textList);
    m_comboBoxChoiceNumber.move(115,260);
    m_comboBoxChoiceNumber.resize(70,25);

    /* 识别按钮 */
    m_buttonsRecognize.setParent(this);
    m_buttonsRecognize.move(240,260);
    m_buttonsRecognize.resize(70,25);
    m_buttonsRecognize.setText("Recognize");

    /* 清屏按钮 */
    m_buttonsClear.setParent(this);
    m_buttonsClear.move(330,260);
    m_buttonsClear.resize(70,25);
    m_buttonsClear.setText("Clear");


    connect(&m_buttonsClear, SIGNAL(clicked()), m_drawingBoard, SLOT(clear()));
    connect(&m_comboBoxChoiceNumber,SIGNAL(currentIndexChanged(int)  ), this ,SLOT( onComboBoxIndexChanged()  ) );

    return ret;
}

RecognizerUI* RecognizerUI::NewInstance()
{
    RecognizerUI* ret = new RecognizerUI();

    if( (ret == NULL) || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void RecognizerUI::show()
{
    QWidget::show();

    setFixedSize(width(), height());
}

void RecognizerUI::setRecognizer(IRecognizer* rec)
{
    m_algorithm = rec;
}

IRecognizer* RecognizerUI::getRecognizer()
{
   return m_algorithm;
}
void RecognizerUI::onComboBoxIndexChanged()
{
    m_labelResult.setText(QString::number(m_comboBoxChoiceNumber.currentIndex()));
}

RecognizerUI::~RecognizerUI()
{

}
