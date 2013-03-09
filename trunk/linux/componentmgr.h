#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "component.h"
#ifdef _WIN32
#include <bcm/win32/dll.h>
#else
#include <bcm/linux/dll.h>
#endif


namespace pcm {

	class ComponentManager
	{
		typedef const ComponentSet *(GET_COMPONENT_SET)();
	public:
		ComponentManager()
		{
		}
		bool loadComponentSet()
		{
		}
		bool releaseComponentSet()
		{
		}
		ComponentSet *getComponentSet(const char *dllName)
		{
			ComponentDatabase &compdb = ComponentDatabase::instance();
			if (open(compdb.getFileName(Component::name())) == false)
				throw std::runtime_error(compdb.getLoaderName(Component::name()));
			CREATE_FUNCTION lpGetInterface = (CREATE_FUNCTION)getProc(compdb.getLoaderName(Component::name()));
			if (lpGetInterface == (CREATE_FUNCTION)NULL)
				throw std::runtime_error(compdb.getLoaderName(Component::name()));
			return (*lpGetInterface)();
		}
   	};

} // namespace pcm

#endif

