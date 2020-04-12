/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Connect X is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file OS.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <unistd.h>
#include <linux/limits.h>

#include <cxinv/include/assertion.h>

#include <OS.h>

std::string cxmodel::GetCurrentExecutablePath(const bool p_pathOnly)
{
    // Get the symlink path to the current exexutable:
    char symlinkToCurrentExec[32];
    sprintf(symlinkToCurrentExec, "/proc/%d/exe", getpid());

    // Read the symlink:
    char readPath[PATH_MAX];

    const ssize_t nbBytesRead{readlink(symlinkToCurrentExec,
                                       readPath,
                                       PATH_MAX)};

    // Make sure there is no overflow in path length from readlink:
    const ssize_t nbBytesInPath{std::min(nbBytesRead, static_cast<ssize_t>(PATH_MAX - 1))};

    // If something has been read, the 'end of string' character must be added
    // before the read path can be manipulated:
    if(nbBytesInPath >= 0)
    {
        readPath[nbBytesInPath] = '\0';
    }

    // Make sure file exists:
    ASSERT_MSG(access(readPath, F_OK) != -1, "The executable path does not exist.");

    std::string pathToCurrentExecutable(readPath);

    if(p_pathOnly)
    {
        // Only the path to directory is wanted, so the executable name is
        // removed from the path:
        const size_t indexOfDirectoryDelim{pathToCurrentExecutable.find_last_of("/")};

        ASSERT_MSG(indexOfDirectoryDelim != std::string::npos, "Error while trying to get the directory containing the current running executable.");

        pathToCurrentExecutable = pathToCurrentExecutable.substr(0, indexOfDirectoryDelim);
    }

    return pathToCurrentExecutable;
}
