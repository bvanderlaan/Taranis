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
#ifndef INPUTARGUMENT_HPP
#define INPUTARGUMENT_HPP

#include <QObject>
#include <QStringList>
#include <QVariant>

namespace Taranis
{
    /**
     * @brief The InputArgument class parses the users input string and identifies the prefix, argument name and value.
     */
    class InputArgument : public QObject
    {
        Q_OBJECT
    public:
        explicit InputArgument(const QString arg, QList<QString> acceptedArgumentPrefixs, QObject *parent = 0);
        ~InputArgument() {}

        QString name() const;
        QString prefix() const;
        bool isValid() const;
        QVariant value() const;

    private:
        const QString m_originalInput;
        QString m_argument;
        QString m_prefix;
        QVariant m_value;
        QStringList m_acceptedArgumentPrefixs;
        void clipPrefix();
        bool updatePrefix();
        void updateValue();
    };
}

#endif // INPUTARGUMENT_HPP
