#ifndef RECOGNIZERUI_H
#define RECOGNIZERUI_H
#include "IRecognizer.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "DrawingBoard.h"
class RecognizerUI : public QWidget
{
    Q_OBJECT
private:
    IRecognizer* m_algorithm = nullptr;
    QLabel  m_labelReminder; /* 顶部提示语 */
    QLabel   m_labelResult; /* 显示识别结果 */
    QPushButton m_buttonsLearn;  /* 学习按钮 */
    QComboBox m_comboBoxChoiceNumber; /* 数字选择下拉列表 */
    QPushButton m_buttonsRecognize; /* 识别按钮 */
    QPushButton m_buttonsClear; /* 清屏按钮 */
    DrawingBoard * m_drawingBoard;
private:
    RecognizerUI();
    bool construct();
public slots:
    void onComboBoxIndexChanged();
    void onButtonLearnClicked();
    void onButtonRecognizeClicked();
public:
    static RecognizerUI* NewInstance();
    void show();
    void setRecognizer(IRecognizer* rec);
    IRecognizer* getRecognizer();
    ~RecognizerUI();
};

#endif // RECOGNIZERUI_H
