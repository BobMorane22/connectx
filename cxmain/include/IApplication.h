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
 * @file IApplication.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B
#define IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B

namespace cx
{

/*********************************************************************************************//**
 * @brief Interface for building an application.
 *
 * Use this interface to hide the complexity of an application setup process (such as command
 * line parsing).
 *
 ************************************************************************************************/
class IApplication
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IApplication() = default;


    /******************************************************************************************//**
     * @brief Runs the application.
     *
     * @return A return code indicating if the application ran successfully (@c EXIT_SUCCESS) or
     *         not (@c EXIT_FAILURE).
     *
     * Runs the application. The content of this method should be equivalent of what would go in
     * the @c function.
     *
     * Example usage:
     *
     * @code
     *
     * int main(int argc, char *argv[])
     * {
     *     std::unique_ptr<cx::IApplication> app = std::make_unique<cx::MyApplication>(argc, argv);
     *
     *     return app->Run();
     * }
     *
     * @endcode
     *
     * where @c cx::MyApplication is a user defined type inheriting from this interface.
     *
     ********************************************************************************************/
    virtual int Run() = 0;

};

} // namespace cx

#endif // IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B
