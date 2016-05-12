/// \file [FileName]
/// \brief [enter brief description for file]
///
/// [Enter detailed description of the file here]
///

// +----------------------------------------------------------+
// |                                                          |
// |        Copyright (C) 2006 - 2012 IMS - ZHW               |
// |          Institute For Mechatronic Systems               |
// |        Applied science University of Zuerich             |
// |                                                          |
// | SEDE: Seatovic Dejan     (7090)                          |
// |                 ALL RIGHTS RESERVED!                     |
// |                                                          |
// +----------------------------------------------------------+
//

#ifndef IMAGEPROCESSING_GLOBAL_H
#define IMAGEPROCESSING_GLOBAL_H

#include <QtCore/qglobal.h>
#include <circle.h>
#include <math.h>
#include "opencv2/opencv.hpp"


#if defined(IMAGEPROCESSING_LIBRARY)
#  define IMAGEPROCESSINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEPROCESSINGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEPROCESSING_GLOBAL_H
