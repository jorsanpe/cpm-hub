/*
 * Copyright (C) 2020  Jordi Sánchez
 * This file is part of CPM Hub
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <infrastructure/plugin_index.h>


PluginIndex::PluginIndex(Filesystem *filesystem, std::string directory)
{
    this->filesystem = filesystem;
    this->directory = directory;
}


void PluginIndex::indexPlugin(PluginMetadata &metadata, std::string file_name)
{
    
}


std::list<PluginMetadata> PluginIndex::find(std::string pattern)
{
    std::list<PluginMetadata> plugins;
    return plugins;
}
