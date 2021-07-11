void AK2DFreeHandDrawing::initializeArgument()
{


    std::cout<<"initializeArgument..."<<std::endl;

    this->nodeManagement=AKGlobalOperationManagement::getGlobalOperationManagement()->nodeManagement;
    this->MultiViewObj=AKGlobalOperationManagement::getGlobalOperationManagement()->multiWidget;
    this->currentDicomSerieGeometryBase=AKGlobalOperationManagement::getGlobalOperationManagement()->nodeManagement->currentGeometryBase;

    this->c_renderer=mitk::BaseRenderer::GetInstance( MultiViewObj->GetRenderWindow1()->GetRenderWindow());

    sizeImage  = {{ currentDicomSerieGeometryBase->GetBounds()[1]-currentDicomSerieGeometryBase->GetBounds()[0],
                    currentDicomSerieGeometryBase->GetBounds()[3]-currentDicomSerieGeometryBase->GetBounds()[2],
                    currentDicomSerieGeometryBase->GetBounds()[5]-currentDicomSerieGeometryBase->GetBounds()[4]}}; //Size along {X,Y,Z}



    ImageTempNode=AKGlobalOperationManagement::getGlobalOperationManagement()->nodeManagement->tempMaskDataNode;

    if (ImageTempNode)
    {

         m_Segmentation = dynamic_cast<mitk::Image*>(ImageTempNode->GetData());
         m_Interpolator->SetSegmentationVolume( m_Segmentation );

    }


    dataStorage=this->nodeManagement->dataStorage;
    ImageMaskNode=((AKMaskImageNode *)nodeManagement->maskImageNodeVector[AKGlobalOperationManagement::getGlobalOperationManagement()->currentNodeIndex])->maskDataNode;
    currentMaskImageAllSteps=&(((AKMaskImageNode *)nodeManagement->maskImageNodeVector[AKGlobalOperationManagement::getGlobalOperationManagement()->currentNodeIndex])->maskImageSteps);


    std::cout << "LVSetDataStorage..." << std::endl;

    dataStorage->Add(segSurface);

    contourImage = mitk::ContourModel::New();
    contourImage->SetClosed(true);

    contourImage->SetProperty("contour.color", mitk::ColorProperty::New(1, 0, 0));
    contourImage->SetProperty("showVolume", mitk::BoolProperty::New( false ) );
    contourImage->SetProperty("visible", mitk::BoolProperty::New(true));

    contourImageNode = mitk::DataNode::New();
    contourImageNode->SetData( contourImage );
    contourImageNode->SetProperty("name", mitk::StringProperty::New("contourNodes"));
    contourImageNode->SetProperty("visible", mitk::BoolProperty::New(true));
    contourImageNode->SetProperty("helper object", mitk::BoolProperty::New(true));
    contourImageNode->SetProperty("layer", mitk::IntProperty::New(1000));
    contourImageNode->SetProperty("contour.project-onto-plane", mitk::BoolProperty::New(false));
    contourImageNode->SetProperty("contour.width", mitk::FloatProperty::New(3.0));
    contourImageNode->SetProperty("contour.color", mitk::ColorProperty::New(1, 0, 0));
    contourImageNode->SetProperty("showVolume", mitk::BoolProperty::New( true ) );

    dataStorage->Add(contourImageNode);
    dataStorage->Add( m_3DContourNode );

    segSurface->SetVisibility(true,MultiViewObj->GetRenderWindow4()->GetRenderer());
    segSurface->SetVisibility(true,MultiViewObj->GetRenderWindow1()->GetRenderer());
    segSurface->SetVisibility(true,MultiViewObj->GetRenderWindow2()->GetRenderer());
    segSurface->SetVisibility(true,MultiViewObj->GetRenderWindow3()->GetRenderer());

    m_3DContourNode->SetVisibility(false, MultiViewObj->GetRenderWindow1()->GetRenderer());
    m_3DContourNode->SetVisibility(false, MultiViewObj->GetRenderWindow2()->GetRenderer());
    m_3DContourNode->SetVisibility(false, MultiViewObj->GetRenderWindow3()->GetRenderer());
    m_3DContourNode->SetVisibility(true, MultiViewObj->GetRenderWindow4()->GetRenderer());

    if ( ImageTempNode->GetData()!=NULL )
     {


           mitk::Vector3D spacing = ImageTempNode->GetData()->GetGeometry(0)->GetSpacing();
           double minSpacing (100);
           double maxSpacing (0);

           for (int i =0; i < 3; i++)
           {
             if (spacing[i] < minSpacing)
             {
               minSpacing = spacing[i];
             }
             if (spacing[i] > maxSpacing)
             {
               maxSpacing = spacing[i];
             }
           }


           std::cout<<"maxSpacing-->"<<maxSpacing<<std::endl;
           std::cout<<"minSpacing-->"<<minSpacing<<std::endl;

           m_SurfaceInterpolator->SetMaxSpacing(maxSpacing);
           m_SurfaceInterpolator->SetMinSpacing(minSpacing);
           m_SurfaceInterpolator->SetDistanceImageVolume(ui->maxSampleSpinBox->value()); //50000

           m_SurfaceInterpolator->SetCurrentInterpolationSession(m_Segmentation);
           m_SurfaceInterpolator->SetCurrentTimeStep(0);
     }


    dicomSerieMaskImage=AKGlobalOperationManagement::getGlobalOperationManagement()->dicomImagesMask.at(AKGlobalOperationManagement::getGlobalOperationManagement()->selectedImageIndex);


    QObject::connect(MultiViewObj->GetRenderWindow1(),SIGNAL(mousePressSignal(QMouseEvent *,int)),this,SLOT(window1PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow1(),SIGNAL(mouseMoveSignal(QMouseEvent *,int)),this,SLOT(window1PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow1(),SIGNAL(mouseReleaseSignal(QMouseEvent *,int)),this,SLOT(window1PencilClick(QMouseEvent *,int)));


    QObject::connect(MultiViewObj->GetRenderWindow2(),SIGNAL(mousePressSignal(QMouseEvent *,int)),this,SLOT(window2PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow2(),SIGNAL(mouseMoveSignal(QMouseEvent *,int)),this,SLOT(window2PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow2(),SIGNAL(mouseReleaseSignal(QMouseEvent *,int)),this,SLOT(window2PencilClick(QMouseEvent *,int)));


    QObject::connect(MultiViewObj->GetRenderWindow3(),SIGNAL(mousePressSignal(QMouseEvent *,int)),this,SLOT(window3PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow3(),SIGNAL(mouseMoveSignal(QMouseEvent *,int)),this,SLOT(window3PencilClick(QMouseEvent *,int)));
    QObject::connect(MultiViewObj->GetRenderWindow3(),SIGNAL(mouseReleaseSignal(QMouseEvent *,int)),this,SLOT(window3PencilClick(QMouseEvent *,int)));


 
}
