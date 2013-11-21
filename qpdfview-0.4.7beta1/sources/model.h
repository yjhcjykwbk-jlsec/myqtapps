/*

Copyright 2013 Adam Reichold

This file is part of qpdfview.

qpdfview is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

qpdfview is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with qpdfview.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <QList>
#include <QtPlugin>
#include <QRect>
#include <QStandardItemModel>
#include <QString>
#include <QWidget>

class QColor;
class QImage;
class QPrinter;
class QSizeF;

#include "global.h"

namespace Model
{
    struct Link
    {
        QPainterPath boundary;

        int page;
        qreal left;
        qreal top;

        QString urlOrFileName;

        Link() : boundary(), page(-1), left(0.0), top(0.0), urlOrFileName() {}

        Link(const QPainterPath& boundary, int page, qreal left = 0.0, qreal top = 0.0) : boundary(boundary), page(page), left(left), top(top), urlOrFileName() {}
        Link(const QRectF& boundingRect, int page, qreal left = 0.0, qreal top = 0.0) : boundary(), page(page), left(left), top(top), urlOrFileName() { boundary.addRect(boundingRect); }

        Link(const QPainterPath& boundary, const QString& url) : boundary(boundary), page(-1), left(0.0), top(0.0), urlOrFileName(url) {}
        Link(const QRectF& boundingRect, const QString& url) : boundary(), page(-1), left(0.0), top(0.0), urlOrFileName(url) { boundary.addRect(boundingRect); }

        Link(const QPainterPath& boundary, const QString& fileName, int page) : boundary(boundary), page(page), left(0.0), top(0.0), urlOrFileName(fileName) {}
        Link(const QRectF& boundingRect, const QString& fileName, int page) : boundary(), page(page), left(0.0), top(0.0), urlOrFileName(fileName) { boundary.addRect(boundingRect); }

    };

    class Annotation : public QObject
    {
        Q_OBJECT

    public:
        Annotation() : QObject() {}
        virtual ~Annotation() {}

        virtual QRectF boundary() const = 0;
        virtual QString contents() const = 0;

        virtual QWidget* createWidget() = 0;

    signals:
        void wasModified();

    };

    class FormField : public QObject
    {
        Q_OBJECT

    public:
        FormField() : QObject() {}
        virtual ~FormField() {}

        virtual QRectF boundary() const = 0;
        virtual QString name() const = 0;

        virtual QWidget* createWidget() = 0;

    signals:
        void wasModified();

    };

    class Page
    {
    public:
        virtual ~Page() {}

        virtual QSizeF size() const = 0;

        virtual QImage render(qreal horizontalResolution = 72.0, qreal verticalResolution = 72.0, Rotation rotation = RotateBy0, const QRect& boundingRect = QRect()) const = 0;

        virtual QList< Link* > links() const { return QList< Link* >(); }

        virtual QString text(const QRectF& rect) const { Q_UNUSED(rect); return QString(); }
        virtual QList< QRectF > search(const QString& text, bool matchCase) const { Q_UNUSED(text); Q_UNUSED(matchCase); return QList< QRectF >(); }

        virtual QList< Annotation* > annotations() const { return QList< Annotation* >(); }

        virtual bool canAddAndRemoveAnnotations() const { return false; }
        virtual Annotation* addTextAnnotation(const QRectF& boundary, const QColor& color) { Q_UNUSED(boundary); Q_UNUSED(color); return 0; }
        virtual Annotation* addHighlightAnnotation(const QRectF& boundary, const QColor& color) { Q_UNUSED(boundary); Q_UNUSED(color); return 0; }
        virtual void removeAnnotation(Annotation* annotation) { Q_UNUSED(annotation); }

        virtual QList< FormField* > formFields() const { return QList< FormField* >(); }

    };

    class Document
    {
    public:
        virtual ~Document() {}

        virtual int numberOfPages() const = 0;

        virtual Page* page(int index) const = 0;

        virtual bool isLocked() const { return false; }
        virtual bool unlock(const QString& password) { Q_UNUSED(password); return false; }

        virtual QStringList saveFilter() const { return QStringList(); }

        virtual bool canSave() const { return false; }
        virtual bool save(const QString& filePath, bool withChanges) const { Q_UNUSED(filePath); Q_UNUSED(withChanges); return false; }

        virtual bool canBePrintedUsingCUPS() const { return false; }

        virtual void setPaperColor(const QColor& paperColor) { Q_UNUSED(paperColor); }

        virtual void loadOutline(QStandardItemModel* outlineModel) const { outlineModel->clear(); }
        virtual void loadProperties(QStandardItemModel* propertiesModel) const { propertiesModel->clear(); }

        virtual void loadFonts(QStandardItemModel* fontsModel) const { fontsModel->clear(); }

    };
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget* parent = 0) : QWidget(parent) {}

    virtual void accept() = 0;
    virtual void reset() = 0;

};

class Plugin
{
public:
    virtual ~Plugin() {}

    virtual Model::Document* loadDocument(const QString& filePath) const = 0;

    virtual SettingsWidget* createSettingsWidget(QWidget* parent = 0) const { Q_UNUSED(parent); return 0; }

};

Q_DECLARE_INTERFACE(Plugin, "local.qpdfview.Plugin")

#endif // DOCUMENTMODEL_H
