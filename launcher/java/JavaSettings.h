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

#pragma once

#include "JavaRuntime.h"
#include "JavaCheckerJob.h"

#include <QHash>
#include <QUuid>
#include <QList>

class JavaSettings : public QObject
{
    Q_OBJECT
public:
    JavaSettings(QString filePath);

    QJsonObject saveState();
    void resumeState(QJsonObject);

    void insertRuntime(int index, JavaRuntime runtime);
    void appendRuntime(JavaRuntime runtime) { insertRuntime(m_runtimes[runtime.version.major()].size(), runtime); };
    void clear()
    {
        m_runtimes.clear();
        emit cleared();
    }
    void removeRuntime(int major, int index);
    std::weak_ptr<const JavaRuntime> getRuntime(QUuid uuid)
    {
        for (const auto &[majorVersion, list] : std::as_const(m_runtimes))
        {
            for (const auto &runtime : list)
            {
                if (runtime->uuid == uuid)
                    return runtime;
            }
        }
        return std::weak_ptr<const JavaRuntime>{};
    }
signals:
    void runtimeInserted(int major, int index, JavaRuntime& runtime);
    void runtimeRemoved(int major, int index, JavaRuntime& runtime);
    void cleared();
private:
    JavaCheckerJobPtr m_javaCheckerJob;
    QString m_path;
    std::map<int, std::vector<std::shared_ptr<JavaRuntime>>> m_runtimes;

    friend class JavaSettingsModel;
};
