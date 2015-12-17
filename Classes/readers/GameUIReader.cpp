// classes
#include "GameUIReader.h"
#include "GameUI.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

// static global variable //
static GameUIReader* _instanceDungeonReader = nullptr;


/// <summary>
/// Provides a reference to the singleton.
/// </summary>
/// <returns></returns>
GameUIReader* GameUIReader::getInstance()
{
	if ( !_instanceDungeonReader )
	{
		_instanceDungeonReader = new GameUIReader();
	}

	return _instanceDungeonReader;
}


/// <summary>
/// called on delete
/// </summary>
void GameUIReader::purge()
{
	CC_SAFE_DELETE( _instanceDungeonReader );
}


/// <summary>
/// Create a new node object.
/// </summary>
/// <param name="nodeOptions">undocumented in cocos2d</param>
/// <returns>reference to new node</returns>
Node* GameUIReader::createNodeWithFlatBuffers( const flatbuffers::Table* nodeOptions )
{
	GameUI* node = GameUI::create();
	setPropsWithFlatBuffers( node, nodeOptions );
	return node;
}