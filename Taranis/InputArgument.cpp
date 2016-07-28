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
#include "InputArgument.hpp"
#include "InputArgumentKeyValuePair.hpp"

using namespace Taranis;

////////////////////////////////////////////////////////////////////////////////////////////////
InputArgument::InputArgument(const QString arg, QStringList acceptedArgumentPrefixs, QObject *parent) :
    QObject(parent),
    m_originalInput( arg ),
    m_acceptedArgumentPrefixs(acceptedArgumentPrefixs)
{
    // Sorting the list in reverse ensures that -- is checked before - preventing false hits.
    std::reverse( m_acceptedArgumentPrefixs.begin(), m_acceptedArgumentPrefixs.end() );
    clipPrefix();
    updateValue();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void InputArgument::clipPrefix()
{
    if ( !updatePrefix() ) return;
    m_argument = m_originalInput.trimmed().remove(0, m_prefix.length());
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool InputArgument::updatePrefix()
{
    foreach( QString prefix, m_acceptedArgumentPrefixs )
    {
        if ( m_originalInput.startsWith( prefix, Qt::CaseInsensitive) )
        {
            m_prefix = prefix;
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void InputArgument::updateValue()
{
    InputArgumentKeyValuePair argumentPair(m_argument);
    m_nameValueSeperator = argumentPair.seperator();

    if ( argumentPair.isValid() )
    {
        m_value = argumentPair.value();
        m_argument = argumentPair.key();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgument::name() const
{
    return m_argument;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgument::prefix() const
{
    return m_prefix;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QVariant InputArgument::value() const
{
    return ( !m_value.isValid() && isValid() ) ? true : m_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool InputArgument::isValid() const
{
    return !m_argument.isEmpty() && !m_prefix.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString InputArgument::nameValueSeperator() const
{
    return m_nameValueSeperator;
}
