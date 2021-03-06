#pragma once

// cocos2d
#include "cocos2d.h"
#include "cocostudio\WidgetReader\NodeReader\NodeReader.h"

using namespace cocos2d;
using namespace cocostudio;

namespace AttackOfSlime {

	/// <summary>
	/// Provides a reader interface to load dungeon objects from the studio.
	/// </summary>
	class DungeonReader : public NodeReader
	{
	public:

		// get instance to node reader
		static DungeonReader* getInstance();

		// called on delete
		static void purge();

		// create a new reader node
		Node* createNodeWithFlatBuffers( const flatbuffers::Table *nodeOptions );
	};
}
