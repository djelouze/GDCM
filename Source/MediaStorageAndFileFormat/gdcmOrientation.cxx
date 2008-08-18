/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmOrientation.h"

#include <math.h>

namespace gdcm
{

Orientation::Orientation() {}
Orientation::~Orientation() {}

void Orientation::Print(std::ostream &) const {}

static const char *OrientationStrings[] = {
  "UNKNOWN",
  "AXIAL",
  "CORONAL",
  "SAGITTAL",
  "OBLIQUE",
  NULL
};

// http://public.kitware.com/pipermail/insight-users/2005-March/012246.html
// 0.5477 would be the square root of 1 (unit vector sum of squares) divided by 3 (oblique axes - a "double" oblique)
// 0.7071 would be the square root of 1 (unit vector sum of squares) divided by 2 (oblique axes)
const double Orientation::obliquityThresholdCosineValue = 0.8;
//const double Orientation::obliquityThresholdCosineValue = 0.7071;
char Orientation::GetMajorAxisFromPatientRelativeDirectionCosine(double x, double y, double z)
{
  char axis = 0;

  char orientationX = x < 0 ? 'R' : 'L';
  char orientationY = y < 0 ? 'A' : 'P';
  char orientationZ = z < 0 ? 'F' : 'H';

  double absX = fabs(x);
  double absY = fabs(y);
  double absZ = fabs(z);

  // The tests here really don't need to check the other dimensions,
  // just the threshold, since the sum of the squares should be == 1.0
  // but just in case ...

  if (absX>obliquityThresholdCosineValue && absX>absY && absX>absZ)
    {
    axis = orientationX;
    }
  else if (absY>obliquityThresholdCosineValue && absY>absX && absY>absZ)
    {
    axis = orientationY;
    }
  else if (absZ>obliquityThresholdCosineValue && absZ>absX && absZ>absY)
    {
    axis = orientationZ;
    }
  else
    {
    // nothing
    }
  return axis;
}

Orientation::OrientationType Orientation::GetType(const double *dircos)
{
  if( !dircos )
    {
    return Orientation::UNKNOWN;
    }
  OrientationType type;
  char rowAxis = GetMajorAxisFromPatientRelativeDirectionCosine(dircos[0],dircos[1],dircos[2]);
  char colAxis = GetMajorAxisFromPatientRelativeDirectionCosine(dircos[3],dircos[4],dircos[5]);
  if (rowAxis != 0 && colAxis != 0 )
    {
    if      ((rowAxis == 'R' || rowAxis == 'L') && (colAxis == 'A' || colAxis == 'P')) type = Orientation::AXIAL;
    else if ((colAxis == 'R' || colAxis == 'L') && (rowAxis == 'A' || rowAxis == 'P')) type = Orientation::AXIAL;

    else if ((rowAxis == 'R' || rowAxis == 'L') && (colAxis == 'H' || colAxis == 'F')) type = Orientation::CORONAL;
    else if ((colAxis == 'R' || colAxis == 'L') && (rowAxis == 'H' || rowAxis == 'F')) type = Orientation::CORONAL;

    else if ((rowAxis == 'A' || rowAxis == 'P') && (colAxis == 'H' || colAxis == 'F')) type = Orientation::SAGITTAL;
    else if ((colAxis == 'A' || colAxis == 'P') && (rowAxis == 'H' || rowAxis == 'F')) type = Orientation::SAGITTAL;
    }
  else
    {
    type = Orientation::OBLIQUE;
    }
  return type;
}

const char *Orientation::GetLabel(OrientationType type)
{
  return OrientationStrings[type];
}


}

