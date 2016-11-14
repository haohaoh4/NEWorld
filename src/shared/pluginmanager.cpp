/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "common.h"
#include "utils.h"
#include "pluginmanager.h"
#include "logger.h"
#include <filesys.h>

PluginManager::PluginManager(bool isClient)
    : mIsClient(isClient)
{
}

void PluginManager::loadPlugin(const std::string& filename)
{
    mPlugins.emplace_back(filename);
    Plugin& plugin = mPlugins[mPlugins.size() - 1];
    if (!plugin.isCompatible(mIsClient))
    {
        mPlugins.pop_back();
        return;
    }

    plugin.init();

    if (!plugin.isLoaded())
    {
        mPlugins.pop_back();
        warningstream << "Failed to load plugin from \"" << filename << "\", skipping";
        return;
    }

    infostream << "Loaded plugin \"" << plugin.getData().pluginName << "\"["
               << plugin.getData().internalName
               << "], authored by \"" << plugin.getData().authorName << "\"";
}

void PluginManager::loadPlugins()
{
    std::string path = "./plugins/";
    if (FileSystem::exists(path))
    {
        FileSystem::forInDirectory(path, [this](std::string filename)
        {
            std::string suffix = filename.substr(filename.size() - std::string(LibSuffix).size() - 1);
            strtolower(suffix);
            if (suffix != std::string(".") + LibSuffix) return;
            loadPlugin(filename);
        });
    }
}

void PluginManager::unloadPlugins()
{
    mPlugins.clear();
}
