
#include "ThreadPool.h"



std::unique_ptr<ThreadPool>				g_threadPool;


ThreadPool&				ThreadPool::getPool()
{
	if (!g_threadPool)
	{
		g_threadPool.reset( new ThreadPool() );
	}

	return(*g_threadPool);
}
