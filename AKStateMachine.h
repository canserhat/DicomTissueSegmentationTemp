#ifndef AKSTATEMACHINE_H
#define AKSTATEMACHINE_H



#include "iostream"
#include "QObject"
#include "QString"
#include "bitset"
#include "iostream"
#include "vector"


#include "mitkBaseGeometry.h"
#include "mitkRenderingManager.h"
#include "mitkImageCast.h"

#include "AKRenderWindows/AKImageCheckMap.h"
#include "AKStartWindow/AKGlobalOperationManagement.h"
#include "AKImageToPolygon/AKCreatePolygonManagement.h"



#include "mitkPoint.h"
#include "mitkImage.h"
#include "itkImage.h"
#include "itkTimeProbe.h"


class AKStateMachine
{

private:



    AKStateMachine();

    static AKStateMachine* stateMachineUndo;


    mitk::Image::Pointer maskImage;
    GlobalMaskImageType::Pointer maskITKImage;
    mitk::BaseGeometry::Pointer geometrybase;
    std::vector<std::pair<std::vector<mitk::Point3D>,int>> *currentMaskImageAllSteps;

    bool stateMachineRunStatus;
    bool isReadyToRun;
    bool isImageEmpty;

   
public:


    /** @brief
     * Aktif kullanılan mitk image'in bir önceki duruma getirilmesi işlemini yürütür.
     */

    static AKStateMachine* getStateMachineUndo();

    /** @brief
     * Aktif kullanılan mitk image'in parametrelerinin atandığı fonksiyon
     */

    void setImageandParamaters(mitk::Image::Pointer _maskImage,                           
                               mitk::BaseGeometry::Pointer _geometrybase,
                               std::vector<std::pair<std::vector<mitk::Point3D>,int>> *currentMaskImageAllSteps );



    mitk::Image::Pointer getMaskImage();

    GlobalMaskImageType::Pointer getItkMaskImage();

    bool getReadyToRun();
    void setReadToRun(bool _isReadyToRun);

    void setStateMachineRunStatus(bool stateMachineRunStatus);
    bool getStateMachineRunStatus();

    void setIsImageEmpty(bool _isImageEmpty);
    bool getIsImageEmpty();


    bool runUndo();

    int hitLocalSerie;

  
    /** @brief
     * mitk mask verilerinin pixel bazlı değerlerinin toplamının bir mask imagede ifade edilmesi
     */
    GlobalMaskImageType::Pointer dicomSerieMaskImage;


};

#endif // AKSTATEMACHINE_H
