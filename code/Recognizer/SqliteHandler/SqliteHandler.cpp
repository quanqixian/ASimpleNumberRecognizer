#include "SqliteHandler.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMutexLocker>
 
QSqlDatabase SqliteHandler::m_db;
SqliteHandler *SqliteHandler::m_instance = nullptr;

SqliteHandler::SqliteHandler()
{
    init();
}

SqliteHandler::~SqliteHandler()
{
    m_db.close();
    qDebug()<<"m_db.close()";
}

SqliteHandler* SqliteHandler::getInstance(void)
{
    static QMutex mutex;
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        if (!m_instance)
        {
            m_instance = new SqliteHandler;
        }
    }
    return m_instance;
}

bool SqliteHandler::init(void)
{
    /* 打开数据库，不存在的话，创建数据库并打开 */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./learnResult.db");
    
    if (!m_db.open())
    {
        qDebug() << __func__<<":"<<__LINE__<< "fail to open database";
        qDebug() << m_db.lastError();
        return false;
    }
    else
    {
       qDebug()<<"open database success"<<endl;
    }

    QSqlQuery sqlQuery(m_db);

    /* 检查是否存在表,不存在创建表table0~table9 */
    for(int i=0; i<10; i++)
    {
        QString sqlStr = QString("CREATE TABLE IF NOT EXISTS table%1(").arg(QString::number(i));
        QString itemStr = "";
        for(int j=0; j<9; j++)
        {
            if(j<8)
            {
                itemStr += QString("dimension%1 INTEGER NOT NULL,").arg(QString::number(j));
            }
            else
            {
                itemStr += QString("dimension%1 INTEGER NOT NULL").arg(QString::number(j));/* 最后一句没有逗号 */
            }
        }
        sqlStr = sqlStr + itemStr + ");";
        qDebug()<<sqlStr<<endl;
        if(false == sqlQuery.exec(sqlStr))
        {
            qDebug() << __func__<<":"<<__LINE__<<  sqlQuery.lastError().text();
        }
    }
    return true;
}
/**
 * 向指定的表中添加一个九维特征值
 */
bool SqliteHandler::additem(int tableIndex, int (&array)[9])
{
    bool ret = false;
    if((tableIndex>9)||(tableIndex<0))
    {
        return false;
    }

    QSqlQuery sqlQuery(m_db);

    QString sqlStr = QString("insert into table%1 values(").arg(QString::number(tableIndex));

    for(int j=0; j<9; j++)
    {
        if(j<8)
        {
            sqlStr += "'"+QString::number(array[j])+"',";
        }
        else
        {
            sqlStr += "'"+QString::number(array[j])+"')";/* 最后一句没有逗号 */
        }
    }
    qDebug()<<sqlStr<<endl;
    ret = sqlQuery.exec(sqlStr);

    if(false == ret)
    {
        qDebug() << __func__<<":"<<__LINE__<< sqlQuery.lastError().text();
    }
    return ret;
}
bool SqliteHandler::clearTable(int tableIndex)
{
    bool ret = false;
    if((tableIndex>9)||(tableIndex<0))
    {
        return false;
    }
    QSqlQuery sqlQuery(m_db);

    QString sqlStr = QString("delete from table%1").arg(QString::number(tableIndex));
    qDebug()<<sqlStr<<endl;
    ret = sqlQuery.exec(sqlStr);
    if(false == ret)
    {
        qDebug() << __func__<<":"<<__LINE__<< sqlQuery.lastError().text();
    }
    return ret;
}
bool SqliteHandler::getitems(int tableIndex, int startIndex, int number, QList<Characteristic > &retList)
{
    bool ret = false;
    if((tableIndex>9)||(tableIndex<0))
    {
        return false;
    }

    QSqlQuery sqlQuery(m_db);

   // select * From table0  Limit 9 Offset 1;
    QString sqlStr = QString("select * From table%1  Limit %2 Offset %3;")
        .arg(QString::number(tableIndex))
        .arg(QString::number(number))
        .arg(QString::number(startIndex));

    ret = sqlQuery.exec(sqlStr);
    if(false == ret)
    {
        qDebug() << __func__<<":"<<__LINE__<< sqlQuery.lastError().text();
    }
	retList.clear();
	Characteristic chara = {};
	while(sqlQuery.next())
	{
		for(int i=0; i<9; i++)
		{
            chara.array[i] = sqlQuery.value(i).toInt();
		}
        retList.push_back(chara);
	}

    return ret;
}
