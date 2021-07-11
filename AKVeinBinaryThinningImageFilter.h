#ifndef AKVEINBINARYTHINNINGIMAGEFILTER_H
#define AKVEINBINARYTHINNINGIMAGEFILTER_H


#include "QThread"
#include "QObject"
#include "QEventLoop"

#include <itkNeighborhoodIterator.h>
#include <itkImageToImageFilter.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkConstantBoundaryCondition.h>
#include "itkImageRegionConstIterator.h"
#include "itkImageRegionIterator.h"

#include "AKImageToPolygon/AKGlobalPolygonOperationManagement.h"

class AKVeinBinaryThinningImageFilter:public QThread
{    

public:

    /** @brief
     Implementation of extraction of vein skeleton structure
     */
    
    AKVeinBinaryThinningImageFilter(GlobalMaskImageType::Pointer _inputBinaryImage,
                                    GlobalMaskImageType::RegionType _boundingBoxImage);


    void run();

    GlobalMaskImageType::Pointer outputBinaryThinningImage;


private:

    using ConstIteratorType = itk::ImageRegionConstIterator<GlobalMaskImageType>;
    using ConstBoundaryConditionType = itk::ConstantBoundaryCondition<GlobalMaskImageType>;
    using NeighborhoodIteratorType = itk::NeighborhoodIterator<GlobalMaskImageType, ConstBoundaryConditionType>;

    GlobalMaskImageType::RegionType boundingBoxImage;
    GlobalMaskImageType::Pointer inputBinaryImage;
    

    void runThinning();
    void PrepareData();
    void ComputeThinImage();
    
     /** Check for Euler invariance (see [Lee94]). */
    bool IsEulerInvariant(NeighborhoodIteratorType::NeighborhoodType neighbors, const int * LUT);
    
    /** Fill the Euler look-up table (LUT) for later check of the Euler
     * invariance (see [Lee94]). */
    void FillEulerLUT(int * LUT);
    
    /** Check if the current point is a simple point.
      * This method is named 'N(v)_labeling' in [Lee94].
      * Outputs the number of connected objects in a neighborhood of a point
      * after this point would have been removed. */
    bool IsSimplePoint(NeighborhoodIteratorType::NeighborhoodType neighbors);
    
    /** Recursive method that calculates the number of connected components in
      * the 3D neighbourhood after the center pixel would have been removed (see)
      * [Lee94]). */
    void OctreeLabeling(int octant, int label, int * cube);


    


};

#endif // AKVEINBINARYTHINNINGIMAGEFILTER_H
