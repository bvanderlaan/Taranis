/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Brad van der Laan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "InputArgumentKeyValuePair.hpp"

using namespace Taranis::Internal;

////////////////////////////////////////////////////////////////////////////////////////////////
InputArgumentKeyValuePair::InputArgumentKeyValuePair(const QString arg, QObject* parent) :
    InputArgumentKeyValuePair( arg, {"=", ":"}, parent )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
InputArgumentKeyValuePair::InputArgumentKeyValuePair(const QString arg, QStringList valueSeperators, QObject* parent) :
    QObject(parent),
    m_valueSeperators( valueSeperators ),
    m_originalArgumentString(arg)
{
    updateKeyValuePair( getSeperatorInfo(arg) );
}

////////////////////////////////////////////////////////////////////////////////////////////////
QPair<QString, int> InputArgumentKeyValuePair::getSeperatorInfo(const QString argument) const
{
    int index(-1);
    QString sep;

    for( auto seperator : m_valueSeperators )
    {
        int seperator_index = argument.indexOf(seperator);
        if ( ( seperator_index >= 0 ) && ( (seperator_index < index ) || ( index == -1 ) ) )
        {
            index = seperator_index;
            sep = seperator;
        }
    }
    return qMakePair(sep, index);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void InputArgumentKeyValuePair::updateKeyValuePair(const QPair<QString, int> seperatorInfo)
{
    QString seperator = seperatorInfo.first;
    int index = seperatorInfo.second;
    if ( index >= 0 )
    {
        m_seperator = seperator;
        m_value = m_originalArgumentString.right( m_originalArgumentString.length() - index - seperator.length() );
        m_key = m_originalArgumentString.left(index);
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgumentKeyValuePair::key() const
{
    return m_key;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgumentKeyValuePair::value() const
{
    return m_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgumentKeyValuePair::seperator() const
{
    return m_seperator;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool InputArgumentKeyValuePair::isValid() const
{
    return ( !m_value.isEmpty() && !m_key.isEmpty() );
}
