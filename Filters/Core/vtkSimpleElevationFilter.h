/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkSimpleElevationFilter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkSimpleElevationFilter
 * @brief   generate scalars along a specified direction
 *
 * vtkSimpleElevationFilter is a filter to generate scalar values from a
 * dataset.  The scalar values are generated by dotting a user-specified
 * vector against a vector defined from the input dataset points to the
 * origin.
 *
 * @warning
 * This class has been threaded with vtkSMPTools. Using TBB or other
 * non-sequential type (set in the CMake variable
 * VTK_SMP_IMPLEMENTATION_TYPE) may improve performance significantly.  Note
 * however that the associated threading/templating implements a fast path,
 * which will only kick in when the input has explicit point representation
 * (e.g. a vtkPointSet).
 *
 * @warning
 * See also vtkElevationFilter provides more control over the operation,
 * including clamping the output scalars within a range.
 *
 * @sa
 * vtkElevationFilter
*/

#ifndef vtkSimpleElevationFilter_h
#define vtkSimpleElevationFilter_h

#include "vtkFiltersCoreModule.h" // For export macro
#include "vtkDataSetAlgorithm.h"

class VTKFILTERSCORE_EXPORT vtkSimpleElevationFilter : public vtkDataSetAlgorithm
{
public:
  vtkTypeMacro(vtkSimpleElevationFilter,vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Construct object with Vector=(0,0,1).
   */
  static vtkSimpleElevationFilter *New();

  //@{
  /**
   * Define the vector with which to dot against.
   */
  vtkSetVector3Macro(Vector,double);
  vtkGetVectorMacro(Vector,double,3);
  //@}

protected:
  vtkSimpleElevationFilter();
  ~vtkSimpleElevationFilter() override {}

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
  double Vector[3];
private:
  vtkSimpleElevationFilter(const vtkSimpleElevationFilter&) VTK_DELETE_FUNCTION;
  void operator=(const vtkSimpleElevationFilter&) VTK_DELETE_FUNCTION;
};

#endif
