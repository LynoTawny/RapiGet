#include <core/TorrentParser.h>

bool IntegerType::parser( QString &content )
{
    if( content.isEmpty() )
    {
        MY_DEBUG << "error : content is empty";
        return false;
    }

    if( content.at(0) != 'i' )
    {
        MY_DEBUG << "error : content is not interger type";
        return false;
    }

    size_t pos = content.indexOf('e' , 0);

    if( -1 == pos )
    {
        MY_DEBUG << "error : cannot find a end flag";
        return false;
    }

    QString s_value = content.mid(1, pos-1);

    bool ok = false;
    _value = s_value.toInt(&ok, 10);

    content.remove(0, pos+1);

    return ok;
}


bool StringType::parser( QString & content )
{
    if( content.isEmpty() )
    {
        MY_DEBUG << "error : content is empty";
        return false;
    }

    if( content.size() < 3 )
    {
        MY_DEBUG << "error : content is not string type";
        return false;
    }

    size_t pos = content.indexOf(':' , 0 );

    if( -1 == pos )
    {
        MY_DEBUG << "error : cannot find a colon ";
        return false;
    }

    bool ok = false;
    int count = content.mid(0, pos).toInt(&ok, 10);

    if( false == ok )
    {
        MY_DEBUG << "error : fail to convert string to int";
        return false;
    }

    _value = content.mid( pos+1 , count );

    content.remove(0, pos+1+count);

    return true;
}

bool ListType::parser( QString &content )
{
    if( content.isEmpty() )
    {
        MY_DEBUG << "error : content is empty";
        return false;
    }

    if( content.at(0) != 'l' )
    {
        MY_DEBUG << "error : content is not list type";
        return false;
    }

    content = content.remove(0,1); // delete 'l'

    while( !content.isEmpty() )
    {
        AnyType * anyType = NULL;

        if( content.at(0) == 'l' )
            anyType = new ListType();
        else if( content.at(0) == 'i' )
            anyType = new IntegerType();
        else if( content.at(0) == 'd' )
            anyType = new DictType();
        else
            anyType = new StringType();

        // call this method will parse the content into
        // the right value and store it into the _value of
        // anyType
        anyType->parser( content );

        _list_values.push_back(anyType);

        if( content.at(0) == 'e' )
        {
            // arrived the end of the list

            content = content.remove(0,1);
            break;
        }
    } // while

    return true;
}

bool DictType::parser( QString &content )
{
    if( content.isEmpty() )
    {
        MY_DEBUG << "error : content is empty";
        return false;
    }

    if( content.at(0) != 'd' )
    {
        MY_DEBUG << "error : content is not dictionary type";
        return false;
    }

    if( content.size() < 3 )
    {
        MY_DEBUG << "error : content is not dictionary type";
        return false;
    }

    content = content.remove( 0 , 1 ); // delete 'd'

    while( !content.isEmpty() )
    {
        StringType *key = new StringType();
        key->parser(content);
        // extract the key : string from dict <key>:<value>

        if( content.isEmpty() )
            break;

        AnyType *anyType = NULL; // value is type of list
        // we not sure what and how many type list will store

        if( content.at(0) =='i' ) // type of integer
            anyType = new IntegerType();
        else if( content.at(0) == 'l' ) // type of list
            anyType = new ListType();
        else if( content.at(0) == 'd' ) // type of dict
            anyType = new DictType();

        else // type of string , begin with an integer
            anyType = new StringType();

        if( anyType == NULL ) // contents is empty now
            return false;

        anyType->parser(content);

        _map_values[key] = anyType;

        if( content.at(0) == 'e' )
        {
            // end of the dict : <d>....<e>
            content = content.remove(0 , 1);
            break;
        }
    }
    return true;
}
