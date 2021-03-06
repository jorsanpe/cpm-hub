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
#include <vector>
#include <string>

#include <management/program_options_parser.h>
#include <management/cpm_hub_starter.h>

using namespace std;


static vector<string> asVector(int argc, char **argv)
{
    vector<string> command_line;

    for (int i=0; i<argc; i++) {
        command_line.emplace_back(string(argv[i]));
    }

    return command_line;
}


int main(int argc, char *argv[])
{
    ProgramOptions program_options;
    vector<string> command_line = asVector(argc, argv);

    program_options = parseProgramOptions(argc, argv);

    startCpmHub(program_options, command_line);

    return 0;
}
