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

#include "HeaderLabel.h"

#include <QString>
#include <QMouseEvent>
#include <QPainter>

CloseButton::CloseButton(QWidget *parent) : QPushButton(parent) {
  setStyleSheet("border: none;");
  setFlat(true);
}

void CloseButton::paintEvent(QPaintEvent *e) {
  QSize sz = size();
  QPainter p(this);
  const int b = 2;
  p.drawLine(b, b, sz.width() - 2 * b + 1, sz.height() - 2 * b + 1);
  p.drawLine(b, sz.height() - 2 * b + 1, sz.width() - 2 * b + 1, b);
}

HeaderLabel::HeaderLabel(const QString& text, QWidget* parent) : QWidget(parent)
{
  m_layout = new QHBoxLayout(this);
  m_layout->setContentsMargins(QMargins());
  m_layout->setSpacing(0);

  m_label = new QLabel(text, this);
  m_layout->addWidget(m_label);

  m_closeButton = new CloseButton(this);
  connect(m_closeButton, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
  m_layout->addWidget(m_closeButton);
}

HeaderLabel::~HeaderLabel() {
}

void HeaderLabel::setFixedHeight(int height) {
  m_label->setFixedHeight(height);
  m_closeButton->setIconSize(QSize(height, height));
  m_closeButton->setFixedSize(QSize(height, height));
}

void HeaderLabel::setText(const QString &text) {
  m_label->setText(text);
}

void HeaderLabel::onCloseClicked() {
  emit closeClicked();
}

void HeaderLabel::mouseDoubleClickEvent(QMouseEvent* event) {
  emit doubleClicked();
  event->accept();
}

void HeaderLabel::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    emit moved(event);
    event->accept();
  }
}

void HeaderLabel::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    event->accept();
    emit pressed(event);
  }
}



