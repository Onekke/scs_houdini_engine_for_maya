#ifndef __util_h__
#define __util_h__

#include <maya/MObject.h>
#include <maya/MString.h>
#include <maya/MIntArray.h>
#include <maya/MFloatArray.h>

#include <vector>

#include <HAPI/HAPI.h>

class MDGModifier;
class MFnDagNode;

class HAPIError: public std::exception
{
    public:
        HAPIError() throw();
        HAPIError( const HAPIError & error ) throw();
        HAPIError( MString msg ) throw();

        virtual	   ~HAPIError() throw() {}

        virtual const char* what() const throw();

    protected:
        mutable MString myBuffer;
        MString myMessage;
};

#define CHECK_HAPI(r) \
{ \
    HAPI_Result hapi_result = (r); \
    if(hapi_result != HAPI_RESULT_SUCCESS) \
    { \
	std::cerr << "HAPI error in " __FILE__ " at line " << __LINE__ << std::endl; \
	\
        int bufferLength; \
        HAPI_GetStatusStringBufLength(HAPI_STATUS_RESULT, &bufferLength); \
        char * buffer = new char[bufferLength]; \
        HAPI_GetStatusString(HAPI_STATUS_RESULT, buffer); \
	std::cerr << buffer << std::endl; \
	delete [] buffer; \
    } \
}

class Util {
    public:
        static MString getString(int handle);
	static MString getAttrNameFromParm(const HAPI_ParmInfo &parm);
	static MStringArray getAttributeStringData(int assetId, int objectId,
						    int geoId, int partId,
						    HAPI_AttributeOwner owner,
						    const MString & name);
	static MString getParmAttrPrefix();
        static void reverseWindingOrderInt(MIntArray& data, MIntArray& faceCounts);
        static void reverseWindingOrderFloat(MFloatArray& data, MIntArray& faceCounts);
        static bool hasHAPICallFailed(HAPI_Result stat);

        // Throws an exception if an error occurred
        static void checkHAPIStatus(HAPI_Result stat);
	static void statusCheckLoop();
	static void showProgressWindow(const MString & title, const MString & status, int progress);
	static void updateProgressWindow(const MString & status, int progress);
	static void hideProgressWindow();

        static MObject findNodeByName(const MString &name);
	static MObject findDagChild(const MFnDagNode &dag, const MString &name);
	static MStatus createNodeByModifierCommand(
		MDGModifier &dgModifier,
		const MString &command,
		MObject &object,
		unsigned int index = 0
		);
        static MString replaceString(const MString &str, const MString &searchStr, const MString &newChar);

        // Returns true if the parm was found.
        static int findParm(std::vector<HAPI_ParmInfo>& parms, MString name);
};

#endif
