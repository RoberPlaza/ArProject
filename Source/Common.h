/**
 * @file Common.h
 * @author Roberto Plaza (Roberto.Plaza@alu.uclm.es)
 * @brief Stores the headers common to every module of the application
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v.3.0
 * 
 */
#ifndef COMMON_HEADER__
#define COMMON_HEADER__


#include <array>
#include <chrono>
#ifdef DEBUG
    #include <iostream>
#endif // DEBUG


using   namespace               std;
using   Clock           =       chrono::system_clock;


typedef std::array<double, 16>  Transform;
typedef std::array<double, 16>  Center;
typedef std::array<double, 3>   Vector;


#endif // !COMMON_HEADER__