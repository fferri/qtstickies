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

#include <QApplication>
#include <QAction>
#include <QFile>
#include <QMenuBar>
#include <QMenu>
#include <QDateTime>
#include <QIcon>
#include <QSystemTrayIcon>

#include "StickiesManager.h"

void addColor(QMenu *menu, QActionGroup *group, QString const &colorString)
{
  QAction *colorAction = new QAction(colorString, group);
  colorAction->setData(colorString.toLower());
  colorAction->setCheckable(true);
  group->addAction(colorAction);
  menu->addAction(colorAction);
}

int main(int argc, char **argv)
{
  QApplication app (argc, argv);
  app.setApplicationName("CuteStickies");

  QDateTime now = QDateTime::currentDateTime();
  qsrand(now.toTime_t());

  // Load an application style
  QFile styleFile(":/stylesheet.qss");
  styleFile.open(QFile::ReadOnly);
  QString style(styleFile.readAll());
  app.setStyleSheet(style);

  StickiesManager *stickiesManager = new StickiesManager();
  stickiesManager->restoreStickies();

  // File Menu
  QMenu *fileMenu = new QMenu("File");
  // File -> New Note
  QAction *newStickyAction = new QAction("New Note", fileMenu);
  newStickyAction->setShortcuts(QKeySequence::New);
  stickiesManager->connect(newStickyAction, SIGNAL(triggered()), stickiesManager, SLOT (handleNewSticky()));
  fileMenu->addAction(newStickyAction);

  // Color Menu
  QMenu *colorMenu = new QMenu("Color");
  colorMenu->connect(colorMenu, SIGNAL(aboutToShow()), stickiesManager, SLOT (handleMenuWillShow()));
  QActionGroup *colorGroup = new QActionGroup(colorMenu);
  colorGroup->setExclusive(true);
  colorGroup->connect(colorGroup, SIGNAL(triggered(QAction *)), stickiesManager, SLOT (handleColorChanged(QAction *)));
  // Add all the colors
  addColor(colorMenu, colorGroup, QString("Yellow"));
  addColor(colorMenu, colorGroup, QString("Red"));
  addColor(colorMenu, colorGroup, QString("Green"));
  addColor(colorMenu, colorGroup, QString("Blue"));
  addColor(colorMenu, colorGroup, QString("Purple"));
  addColor(colorMenu, colorGroup, QString("Grey"));

  // Top-level menu
  QMenu *appMenu = new QMenu("QtStickies");
  appMenu->addMenu(fileMenu);
  appMenu->addMenu(colorMenu);

  // System Tray
  QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
  trayIcon->setIcon(QIcon(":/sticky-note.png"));
  trayIcon->setContextMenu(appMenu);
  trayIcon->show();

#ifdef __APPLE__
  QMenuBar *menuBar = new QMenuBar(0);
  menuBar->addMenu(fileMenu);
  menuBar->addMenu(colorMenu);
#endif

  return app.exec();
}
