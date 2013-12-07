#ifndef __Geo_h__
#define __Geo_h__

#include <maya/MStatus.h>
#include <maya/MDataBlock.h>

#include <vector>

#include <HAPI/HAPI.h>

class Object;
class GeometryPart;

class Geo {

    public:
        
        
        Geo( int assetId, int objectId, int geoId, Object * parentObject );
        ~Geo();

        MStatus setClean( MPlug& geoPlug, MDataBlock& data );

        MStatus compute(MDataHandle &geoHandle, bool &needToSyncOutputs);
    
        void update();
    
    protected:
        
        Object* myParentObject;        
        HAPI_GeoInfo myGeoInfo;
        int myAssetId;
        int myObjectId;
        int myGeoId;

        std::vector<GeometryPart> myParts;
        
};

#endif