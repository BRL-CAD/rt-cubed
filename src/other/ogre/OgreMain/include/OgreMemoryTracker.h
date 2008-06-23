/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2008 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source under the terms of a specific version of
the OGRE Unrestricted License provided you have obtained such a license from
Torus Knot Software Ltd
---------------------------------------------------------------------------
*/

#ifndef _MemoryTracker_H__
#define _MemoryTracker_H__

#include "OgrePrerequisites.h"

// If we're using the GCC 3.1 C++ Std lib
#if OGRE_COMPILER == OGRE_COMPILER_GNUC && OGRE_COMP_VER >= 310 && !defined(STLPORT)
// We need to define a hash function for void*
#include <ext/hash_map>
namespace __gnu_cxx
{
	template <> struct hash< void* >
	{
		size_t operator()( void* const & ptr ) const
		{
			return (size_t)ptr;
		}
	};
}

#endif

namespace Ogre
{

#if OGRE_MEMORY_TRACKER

	/** This class tracks the allocations and deallocations made, and
		is able to report memory statistics and leaks.
	@note
		This class is only available in debug builds.
	*/
	class _OgreExport MemoryTracker
	{
	protected:
		OGRE_AUTO_MUTEX

		// Allocation record
		struct Alloc
		{
			size_t bytes;
			unsigned int pool;
			const char* filename;
			size_t line;
			const char* function;

			Alloc() :line(0), bytes(0) {}
			Alloc(size_t sz, unsigned int p, const char* file, size_t ln, const char* func)
				:bytes(sz), pool(p), filename(file), line(ln), function(func) {}
		};
		
		String mLeakFileName;
		bool mDumpToStdOut;
		typedef HashMap<void*, Alloc> AllocationMap;
		AllocationMap mAllocations;
		
		size_t mTotalAllocations;
		typedef std::vector<size_t> AllocationsByPool;
		AllocationsByPool mAllocationsByPool;

		void reportLeaks();

		// protected ctor
		MemoryTracker()
			: mLeakFileName("OgreLeaks.log"), mDumpToStdOut(true),
			mTotalAllocations(0)
		{
		}
	public:

		/** Set the name of the report file that will be produced on exit. */
		void setReportFileName(const String& name)
		{
			mLeakFileName = name;
		}
		/// Return the name of the file which will contain the report at exit
		const String& getReportFileName() const
		{
			return mLeakFileName;
		}
		/// Sets whether the memory report should be sent to stdout
		void setReportToStdOut(bool rep)
		{
			mDumpToStdOut = rep;
		}
		/// Gets whether the memory report should be sent to stdout
		bool getReportToStdOut() const
		{
			return mDumpToStdOut;
		}
		
		/// Get the total amount of memory allocated currently.
		size_t getTotalMemoryAllocated() const;
		/// Get the amount of memory allocated in a given pool 
		size_t getMemoryAllocatedForPool(unsigned int pool) const;
		

		/** Record an allocation that has been made. Only to be called by
			the memory management subsystem.
			@param ptr The pointer to the memory
			@param sz The size of the memory in bytes
			@param pool The memory pool this allocation is occurring from
			@param file The file in which the allocation is being made
			@param ln The line on which the allocation is being made
			@param func The function in which the allocation is being made
		*/
		void _recordAlloc(void* ptr, size_t sz, unsigned int pool = 0, 
						  const char* file = 0, size_t ln = 0, const char* func = 0);
		/** Record the deallocation of memory. */
		void _recordDealloc(void* ptr);

		~MemoryTracker()
		{
			reportLeaks();
		}
		
		/// Static utility method to get the memory tracker instance
		static MemoryTracker& get();

		
	};
	

	
#endif
}

#endif
