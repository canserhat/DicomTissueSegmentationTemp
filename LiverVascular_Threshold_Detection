void AKTissueSegmentation::automaticThresholdDetectionForLiver()
{


    int medianValue=0;
    int medianValueCount=0;

    int startHistogramValue=meanEnhancementImage;

    for(int i=startHistogramValue;i<400;i++)
    {

        if(histogramBinVector[i]>medianValueCount)
        {
            medianValueCount=histogramBinVector[i];
            medianValue=i;
        }

    }

    int minEstThreshold=(medianValue-stdEnhancementImage*0.3);
    int maxEstThreshold=(medianValue+stdEnhancementImage*0.4);


    std::cout<<"minEstThreshold---------------------******>"<<minEstThreshold<<std::endl;
    std::cout<<"maxEstThreshold---------------------******>"<<maxEstThreshold<<std::endl;


    this->minThresholdValue=minEstThreshold;
    this->maxThresholdValue=maxEstThreshold;


}


void AKTissueSegmentation::automaticThresholdDetectionForVein()
{

   
    int clickedIndexValue=(orignalImageITK->GetPixel(pointClickedIndex));

    int medianValue=0;
    int medianValueCount=0;

    int startHistogramValue=meanEnhancementImage+5;

    for(int i=startHistogramValue;i<400;i++)
    {

        if(histogramBinVector[i]>medianValueCount)
        {
            medianValueCount=histogramBinVector[i];
            medianValue=i;
        }

    }

 
    int p_max=meanEnhancementImage+(0.7*stdEnhancementImage);

    int minEstThreshold=(0.7*medianValue+0.3*p_max);
    int maxEstThreshold=400;


    if(minEstThreshold<clickedIndexValue)
    {
        std::cout<<"Min Protection is activated..."<<std::endl;
         int  minEstThresholdFirst=(p_max+clickedIndexValue)/2;
         minEstThreshold=0.7*p_max+0.3*clickedIndexValue;

        
    }

    this->minThresholdValue=minEstThreshold;
    this->maxThresholdValue=maxEstThreshold;


    std::cout<<"minThresholdValue---------------------******>"<<minThresholdValue<<std::endl;
    std::cout<<"maxThresholdValue---------------------******>"<<maxThresholdValue<<std::endl; 

}


