#pragma once

// cocos2d
#include "cocos2d.h"

using namespace cocos2d;

namespace AttackOfSlime
{

	/// <summary>
	/// The directory service allows objects in a scene to register themselves as
	/// lookups, which other objects can then call and retrieve access to.
	/// </summary>
	class DirectoryService
	{
	public:

		/// <summary>
		/// Return a reference to the directory service instance.
		/// </summary>
		/// <returns>reference to the directory</returns>
		static DirectoryService* getInstance()
		{
			if ( __instance == nullptr )
			{
				__instance = new DirectoryService();
			}

			return __instance;
		}

		// add a new node to the directory service
		void registerNode( const char* name, Node* node );

		// look up a node in the directory
		Node* lookUp( const char* name );

	private:

		// instance of the static member
		static DirectoryService* __instance;

		// a map of resource names and their references
		std::map<const char*, Node*> directoryEntries;

	};
}