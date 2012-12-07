#include "cellapp.hpp"
#include "forward_message_over_handler.hpp"
#include "entitydef/entities.hpp"
#include "cstdkbe/memorystream.hpp"
#include "entity.hpp"
#include "space.hpp"
#include "spaces.hpp"

namespace KBEngine{	

//-------------------------------------------------------------------------------------
FMH_Baseapp_onEntityGetCellFrom_onCreateInNewSpaceFromBaseapp::
FMH_Baseapp_onEntityGetCellFrom_onCreateInNewSpaceFromBaseapp(Entity* e, SPACE_ID spaceID, PyObject* params):
_e(e),
_spaceID(spaceID),
params_(params)
{
}

//-------------------------------------------------------------------------------------
void FMH_Baseapp_onEntityGetCellFrom_onCreateInNewSpaceFromBaseapp::process()
{
	KBE_ASSERT(_e != NULL);
	
	Space* space = Spaces::findSpace(_spaceID);
	
	if(space == NULL)
	{
		ERROR_MSG(boost::format("FMH_Baseapp_onEntityGetCell::process: not found space(%1%), %2% %3%.\n") %
			_spaceID % _e->getScriptName() % _e->getID());

		return;
	}

	// ���ӵ�space
	space->addEntity(_e);
	_e->initializeEntity(params_);
	Py_XDECREF(params_);
}

//-------------------------------------------------------------------------------------
FMH_Baseapp_onEntityGetCellFrom_onCreateCellEntityFromBaseapp::
	FMH_Baseapp_onEntityGetCellFrom_onCreateCellEntityFromBaseapp(
			std::string& entityType, ENTITY_ID createToEntityID, ENTITY_ID entityID, MemoryStream* pCellData, 
			 bool hasClient, COMPONENT_ID componentID, SPACE_ID spaceID):
_entityType(entityType),
_createToEntityID(createToEntityID),
_entityID(entityID),
_pCellData(pCellData),
_hasClient(hasClient),
_componentID(componentID),
_spaceID(spaceID)
{
}

//-------------------------------------------------------------------------------------
void FMH_Baseapp_onEntityGetCellFrom_onCreateCellEntityFromBaseapp::process()
{
	Cellapp::getSingleton()._onCreateCellEntityFromBaseapp(_entityType, _createToEntityID, _entityID, 
		_pCellData, _hasClient, _componentID, _spaceID);

	MemoryStream::ObjPool().reclaimObject(_pCellData);
}

//-------------------------------------------------------------------------------------
}
