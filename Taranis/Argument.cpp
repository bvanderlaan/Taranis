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
#include "Argument.hpp"

using namespace Taranis;

////////////////////////////////////////////////////////////////////////////////////////////////
Argument::Argument(const QString name, const QString description, const ArgumentType type, std::function<void ()> callback) :
    m_name( name ),
    m_description( description ),
    m_type( type ),
    m_actionCallback( callback )
{
    switch (m_type)
    {
    case ArgumentType::Boolean:
        m_value = false;
        break;
    default:
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString Argument::name() const
{
    return m_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString Argument::shortName() const
{
    return m_name.at(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool Argument::hasShortName() const
{
    return m_name.length() > 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString Argument::description() const
{
    return m_description;
}

////////////////////////////////////////////////////////////////////////////////////////////////
ArgumentType Argument::type() const
{
    return m_type;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QVariant Argument::value() const
{
    return m_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Argument::setValue(QVariant value)
{
    m_value = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
std::function<void ()> Argument::callback()
{
    return m_actionCallback;
}
