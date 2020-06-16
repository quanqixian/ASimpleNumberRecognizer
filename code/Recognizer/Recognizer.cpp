#include "Recognizer.h"

/* /第一阶段，内部可实现一些与资源无关的操作 */
Recognizer::Recognizer()
{
}

/* 第二阶段，所有可能发生异常的操作都可放在这里执行 */
bool Recognizer::construct()
{
    m_ui = RecognizerUI::NewInstance();

    if( m_ui != NULL )
    {
        m_ui->setRecognizer(&m_algorithm);
    }

    return (m_ui != NULL);
}
/* 使用二阶构造模式 */
Recognizer* Recognizer::NewInstance()
{
    Recognizer* ret = new Recognizer();

    if( (ret == NULL) || !ret->construct() )
    {
        /* 构造失败或者第二阶段失败，就销毁半成品对象 */
        delete ret;
        ret = NULL;
    }

    /* 否则返回已经生成完成的对象指针 */
    return ret;
}


void Recognizer::show()
{
    m_ui->show();
}

Recognizer::~Recognizer()
{
    delete m_ui;
}
