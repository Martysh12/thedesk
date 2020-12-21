/****************************************
 *
 *   INSERT-PROJECT-NAME-HERE - INSERT-GENERIC-NAME-HERE
 *   Copyright (C) 2020 Victor Tran
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * *************************************/
#include "plugin.h"

#include <QDebug>
#include <QApplication>
#include <statemanager.h>
#include <localemanager.h>
#include <statuscentermanager.h>
#include <QDir>
#include <tsettings.h>
#include "settings/bluetoothsettingspane.h"

struct PluginPrivate {
    int translationSet;

    BluetoothSettingsPane* bluetoothSettings;
};

Plugin::Plugin() {
    d = new PluginPrivate();
}

Plugin::~Plugin() {
    delete d;
}

void Plugin::activate() {
    d->translationSet = StateManager::localeManager()->addTranslationSet({
        QDir::cleanPath(qApp->applicationDirPath() + "/../plugins/BluetoothPlugin/translations"),
        "/usr/share/thedesk/BluetoothPlugin/translations"
    });

    tSettings::registerDefaults(QDir::cleanPath(qApp->applicationDirPath() + "/../plugins/BluetoothPlugin/defaults.conf"));
    tSettings::registerDefaults("/etc/theSuite/theDesk/BluetoothPlugin/defaults.conf");

    d->bluetoothSettings = new BluetoothSettingsPane();
    StateManager::statusCenterManager()->addPane(d->bluetoothSettings, StatusCenterManager::SystemSettings);
}

void Plugin::deactivate() {
    StateManager::statusCenterManager()->removePane(d->bluetoothSettings);
    d->bluetoothSettings->deleteLater();
    StateManager::localeManager()->removeTranslationSet(d->translationSet);
}
