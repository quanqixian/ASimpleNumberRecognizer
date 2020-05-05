#include "Recognizer.h"

Recognizer::Recognizer()
{
}

bool Recognizer::construct()
{
    m_ui = RecognizerUI::NewInstance();

    if( m_ui != NULL )
    {
        m_ui->setRecognizer(&m_algorithm);
    }

    return (m_ui != NULL);
}

Recognizer* Recognizer::NewInstance()
{
    Recognizer* ret = new Recognizer();

    if( (ret == NULL) || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }

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
