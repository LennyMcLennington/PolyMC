// SPDX-License-Identifier: GPL-3.0-only
/*
 *  PolyMC - Minecraft Launcher
 *  Copyright (C) 2022 Sefa Eyeoglu <contact@scrumplex.net>
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

#include "JavaRuntime.h"

#include <Json.h>

QJsonObject JavaRuntime::saveState() const
{
    QJsonObject o;

    o["uuid"] = uuid.toString();
    o["name"] = name;
    o["enabled"] = enabled;

    o["path"] = path;
    o["version"] = version.toJsonObject();
    o["architecture"] = architecture;
    o["vendor"] = vendor;

    o["added"] = added.toString(Qt::ISODate);
    if (!lastSeen.isNull())
        o["lastSeen"] = lastSeen.toString(Qt::ISODate);
    if (!lastUsed.isNull())
        o["lastUsed"] = lastUsed.toString(Qt::ISODate);
    return o;
}

bool JavaRuntime::resumeState(QJsonObject data)
{
    uuid = QUuid::fromString(Json::requireString(data, "uuid"));
    name = Json::requireString(data, "name");
    enabled = Json::requireBoolean(data, "enabled");

    path = Json::requireString(data, "path");
    version = JavaVersion(Json::requireString(data, "version"));
    architecture = Json::requireString(data, "architecture");
    vendor = Json::requireString(data, "vendor");

    // Are these null if they fail to parse?
    added = QDateTime::fromString(Json::requireString(data, "added"), Qt::ISODate);
    lastSeen = QDateTime::fromString(Json::requireString(data, "lastSeen"), Qt::ISODate);
    lastUsed = QDateTime::fromString(Json::requireString(data, "lastUsed"), Qt::ISODate);

    return true;
}
