// classes
#include "DungeonReader.h"
#include "Dungeon.h"

// using namespaces
using namespace cocos2d;
using namespace AttackOfSlime;

// static global variable //
static DungeonReader* _instanceDungeonReader = nullptr;


/// <summary>
/// Provides a reference to the singleton.
/// </summary>
/// <returns></returns>
DungeonReader* DungeonReader::getInstance()
{
	if ( !_instanceDungeonReader )
	{
		_instanceDungeonReader = new DungeonReader();
	}

	return _instanceDungeonReader;
}


/// <summary>
/// called on delete
/// </summary>
void DungeonReader::purge()
{
	CC_SAFE_DELETE( _instanceDungeonReader );
}


/// <summary>
/// Create a new node object.
/// </summary>
/// <param name="nodeOptions">undocumented in cocos2d</param>
/// <returns>reference to new node</returns>
Node* DungeonReader::createNodeWithFlatBuffers( const flatbuffers::Table* nodeOptions )
{
	Dungeon* node = Dungeon::create();
	setPropsWithFlatBuffers( node, nodeOptions );
	return node;
}