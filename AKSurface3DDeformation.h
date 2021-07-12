#ifndef AKSURFACE3DDEFORMATION_H
#define AKSURFACE3DDEFORMATION_H


#include "MitkDataTypesExtExports.h"
#include "mitkDataInteractor.h"
#include "mitkMousePressEvent.h"
#include "mitkMouseReleaseEvent.h"
#include "mitkSurface.h"


#include "MitkDataTypesExtExports.h"
#include "mitkDataInteractor.h"
#include "mitkSurface.h"

namespace mitk
{

  class  AKSurface3DDeformation : public DataInteractor
  {
  public:
    mitkClassMacro(AKSurface3DDeformation, DataInteractor);
    itkFactorylessNewMacro(Self) itkCloneMacro(Self)

    /**
      * \brief AKSurface3DDeformation, vtkPolydata tipindeki Kesi-hattı'nın vertex noktalarını gaussian
      * eğrisine göre deforme işlemini gerçekleştirir.
      */

     protected : AKSurface3DDeformation();
    ~AKSurface3DDeformation() override;

    /** @brief
      * mitk tabanlı state machine pattern string degerlerini, etkileşim yapısına yükler, kesi hattı üzerinde
      * kullanıcı etkileşimlerini tetikler
      */
    void ConnectActionsAndFunctions() override;

    /** @brief
      * Data yapısı değişimde cağırılır.
      */
    void DataNodeChanged() override;

    /** @brief
      * Kesi hattı etkileşim araçları
      */
    virtual bool CheckOverObject(const InteractionEvent *);
    virtual bool SelectObject(StateMachineAction *, InteractionEvent *);
    virtual bool DeselectObject(StateMachineAction *, InteractionEvent *);
    virtual bool InitDeformation(StateMachineAction *, InteractionEvent *);
    virtual bool DeformObject(StateMachineAction *, InteractionEvent *);
    virtual bool ScaleRadius(StateMachineAction *, InteractionEvent *);


    enum
    {
      COLORIZATION_GAUSS,
      COLORIZATION_CONSTANT
    };



  private:

    void ColorizeSurface(
    vtkPolyData *polyData, int timeStep, const Point3D &pickedPoint, int mode, double scalar = 0.0);

    double m_InitialPickedWorldPoint[4];

    Point2D m_InitialPickedPointScreen;
    Point3D m_InitialPickedPoint;
    Point3D m_SurfaceColorizationCenter;

    Surface *m_Surface;
    vtkPolyData *m_OriginalPolyData;

    double m_GaussSigma;
    Vector3D m_ObjectNormal;

    bool deformedActive;
  };
}

#endif // AKSURFACE3DDEFORMATION_H
