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
#ifndef INPUTARGUMENTKEYVALUEPAIR_HPP
#define INPUTARGUMENTKEYVALUEPAIR_HPP

#include <QObject>
#include <QStringList>
#include <QVariant>

namespace Taranis
{
    class InputArgumentKeyValuePair : QObject
    {
    public:
        explicit InputArgumentKeyValuePair(const QString arg, QObject *parent = 0);
        explicit InputArgumentKeyValuePair(const QString arg, QStringList acceptedArgumentPrefixs, QObject *parent = 0);
        ~InputArgumentKeyValuePair() {}

        QString key() const;
        QVariant value() const;
        bool isValid() const;

    private:
        QString m_key;
        QVariant m_value;
        QStringList m_valueSeperators;
        QString m_originalArgumentString;
        QPair<QString,int> getSeperatorInfo(const QString argument) const;
        void updateKeyValuePair(const QPair<QString,int> seperatorInfo);
    };
}

#endif // INPUTARGUMENTKEYVALUEPAIR_HPP
