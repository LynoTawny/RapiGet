#ifndef _TORRENT_PARSER_H_
#define _TORRENT_PARSER_H_

#include <head.h>
#include <QVector>
#include <QMap>

class AnyType
{
public :
    virtual ~AnyType() {}
    virtual void showValue() {}
    virtual bool parser( QString &content) = 0;
};

class IntegerType : public AnyType
{
public :
    virtual ~IntegerType() {}
    virtual bool parser( QString &content );
    virtual void showValue()
    {
        MY_DEBUG << "integer type value : "<< _value;
    }
    int _value;
};

class StringType : public AnyType
{
public :
    virtual ~StringType() {}
    virtual bool parser( QString & content );

    QString _value;

    virtual void showValue()
    {
        MY_DEBUG <<"string type value : "<< _value;
    }
};


class ListType : public AnyType
{
public :
    virtual ~ListType()
    {
        for( QVector<AnyType*>::iterator it = _list_values.begin();
            it != _list_values.end(); it++ )
        {
            delete *it;
        }

        _list_values.clear();
    }

    virtual bool parser( QString &content );

    virtual void showValue()
    {
        MY_DEBUG <<" listType show values ";

        for( QVector<AnyType*>::iterator it = _list_values.begin(); it != _list_values.end(); it++ )
        {
            (*it)->showValue();
        }
    }

    QVector<AnyType*> _list_values;
};


class DictType : public AnyType
{
public :
    virtual ~DictType()
    {
        for( QMap<StringType*, AnyType *>::iterator it = _map_values.begin();
            it != _map_values.end(); it++ )
        {
            delete it.key();
            delete it.value();
        }

        _map_values.clear();
    }


    virtual bool parser( QString &content );

    virtual void showValue()
    {
        MY_DEBUG << " dict type show values " << endl;

        for( QMap<StringType *, AnyType *>::iterator it = _map_values.begin();
            it != _map_values.end(); it++ )
        {
            StringType *it1 = it.key();
            AnyType *it2 = it.value();

            MY_DEBUG << "key : ";
            it1->showValue();

            MY_DEBUG <<"value :";
            it2->showValue();
        }

    }

    QMap<StringType * , AnyType *> _map_values;
};

#endif
