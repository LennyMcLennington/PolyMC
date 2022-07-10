// SPDX-License-Identifier: GPL-3.0-only
/*
 *  PolyMC - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
 *  Copyright (C) 2022 Lenny McLennington <lenny@sneed.church>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <QDateTime>
#include <QObject>
#include <QUuid>
#include <QJsonObject>

#include <memory>

#include "JavaVersion.h"

struct JavaRuntime
{
public:
    /**
     * @brief Converts the data in the JavaRuntime object into a QJsonObject
     * @return A QJsonObject representing the JavaRuntime object
     */
    QJsonObject saveState() const;
    /**
     * @brief Loads the data from a QJsonObject into the JavaRuntime object
     * @param data The QJsonObject containing the data to be loaded
     * @throw Json::JsonException
     */
    void resumeState(QJsonObject data);

    void updateMetadata();

    QUuid uuid;
    QString name;
    bool enabled;

    QString path;
    JavaVersion version;
    QString architecture;
    QString vendor;

    QDateTime added;
    QDateTime modified;
    QDateTime lastSeen;
    QDateTime lastUsed;
};
