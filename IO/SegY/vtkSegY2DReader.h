/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkSegY2DReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef vtkSegY2DReader_h
#define vtkSegY2DReader_h

#include "vtkStructuredGridAlgorithm.h"

#include <vtkIOSegYModule.h> // For export macro

// Forward declarations
class vtkSegYReader;

class VTKIOSEGY_EXPORT vtkSegY2DReader : public vtkStructuredGridAlgorithm
{
public:
  static vtkSegY2DReader* New();
  vtkTypeMacro(vtkSegY2DReader, vtkStructuredGridAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  vtkSegY2DReader();
  ~vtkSegY2DReader();

  vtkSetStringMacro(FileName);

  enum VTKSegYCoordinateModes
  {
    VTK_SEGY_SOURCE = 0, // default
    VTK_SEGY_CDP = 1,
    VTK_SEGY_CUSTOM = 2
  };

  //@{
  /**
   * Specify whether to use source x/y coordinates or CDP coordinates or custom
   * byte positions for data position in the SEG-Y trace header. Defaults to
   * source x/y coordinates.
   *
   * As per SEG-Y rev 2.0 specification,
   * Source XY coordinate bytes = (73, 77)
   * CDP XY coordinate bytes = (181, 185)
   */
  vtkSetClampMacro(XYCoordMode, int, VTK_SEGY_SOURCE, VTK_SEGY_CUSTOM);
  vtkGetMacro(XYCoordMode, int);
  vtkBooleanMacro(XYCoordMode, int);
  void SetXYCoordModeToSource();
  void SetXYCoordModeToCDP();
  void SetXYCoordModeToCustom();
  //@}

  //@{
  /**
   * Specify X and Y byte positions for custom XYCoordinateMode.
   * By default, XCoordByte = 73, YCoordByte = 77 i.e. source xy.
   *
   * \sa SetXYCoordinatesModeToCustom()
   */
  vtkSetMacro(XCoordByte, int);
  vtkGetMacro(XCoordByte, int);
  vtkSetMacro(YCoordByte, int);
  vtkGetMacro(YCoordByte, int);
  //@}

protected:
  int RequestData(vtkInformation* request,
    vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

  int XYCoordMode;

  // Custom XY coordinate byte positions
  int XCoordByte;
  int YCoordByte;

private:
  char* FileName;
  vtkSegYReader* Reader;

private:
  vtkSegY2DReader(const vtkSegY2DReader&) VTK_DELETE_FUNCTION;
  void operator=(const vtkSegY2DReader&) VTK_DELETE_FUNCTION;
};

#endif // vtkSegY2DReader_h
