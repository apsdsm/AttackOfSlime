#include "DirectoryService.h"

using namespace AttackOfSlime;

DirectoryService* DirectoryService::__instance = nullptr;

/// <summary>
/// Register a node with the directory.
/// </summary>
/// <param name="name">name of node</param>
/// <param name="node">reference to node</param>
void DirectoryService::registerNode( const char* name, Node* node )
{
	directoryEntries[ name ] = node;
}

/// <summary>
/// Look up a node in the directory.
/// </summary>
/// <param name="name">name of node to look up</param>
/// <returns>reference to node or null</returns>
Node* DirectoryService::lookUp( const char* name )
{
	if ( directoryEntries.find( name ) == directoryEntries.end() )
	{
		return nullptr;
	}

	return directoryEntries[ name ];
}