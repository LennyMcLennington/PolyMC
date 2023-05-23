// SPDX-License-Identifier: GPL-3.0-only
/*
 *  PolyMC - Minecraft Launcher
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

#include "JavaSettings.h"
#include <Json.h>

JavaSettings::JavaSettings(QString filePath) : m_path{ filePath } {}

QJsonObject JavaSettings::saveState()
{
    QJsonObject o;

    o["formatVersion"] = 1;

    QJsonArray runtimes;
    for (const auto& [majorVersion, list] : m_runtimes) {
        for (const auto& runtime : list) {
            runtimes.append(runtime->saveState());
        }
    }
    o["runtimes"] = runtimes;

    return o;
}

void JavaSettings::resumeState(QJsonObject o)
{
    int formatVersion = Json::requireInteger(o, "formatVersion");

    if (formatVersion != 1)
        /* TODO: Figure out how to handle this. */;
    clear();

    QJsonArray runtimes = Json::requireArray(o, "runtimes");
    for (const auto& runtimeJsonVal : qAsConst(runtimes)) {
        QJsonObject runtimeJsonObject = Json::requireObject(runtimeJsonVal);
        JavaRuntime runtime;
        runtime.resumeState(runtimeJsonObject);

        appendRuntime(runtime);
    }
}

void JavaSettings::insertRuntime(int index, JavaRuntime runtime, bool emitSignal)
{
    auto& runtimeVec = m_runtimes[runtime.version.major()];
    auto runtime_ptr = std::make_shared<JavaRuntime>(runtime);
    runtimeVec.insert(runtimeVec.begin() + index, runtime_ptr);
    if (emitSignal) {
        emit runtimeInserted(runtime.version.major(), index, runtime_ptr);
    }
}

void JavaSettings::removeRuntime(int majorVersion, int index, bool emitSignal)
{
    auto runtime = m_runtimes[majorVersion].at(index);
    m_runtimes[majorVersion].erase(std::next(m_runtimes[majorVersion].begin(), index));
    if (emitSignal) {
        emit runtimeRemoved(majorVersion, index, runtime);
    }
}
