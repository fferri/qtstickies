// Copyright (C) 2015 Francois Baldassari
// Copyright (C) 2018 Federico Ferri
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class CloseButton : public QPushButton {
Q_OBJECT
public:
  explicit CloseButton(QWidget *parent=0);
  void paintEvent(QPaintEvent *e);
};

class HeaderLabel : public QWidget {
Q_OBJECT
public:
  explicit HeaderLabel(const QString &text="", QWidget *parent=0);
  ~HeaderLabel();

public slots:
  void setFixedHeight(int height);
  void setText(const QString &text);

private slots:
  void onCloseClicked();

signals:
  void closeClicked();
  void doubleClicked();
  void pressed(QMouseEvent *e);
  void moved(QMouseEvent *e);

protected:
  void mouseDoubleClickEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:
  QHBoxLayout *m_layout;
  QLabel *m_label;
  CloseButton *m_closeButton;
};
