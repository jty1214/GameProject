#include "MemoryPool.h"

#define PRELOAD(Type, name)	Type* Type::name;
#define BEGIN_INIT_FUNC void Initialize() { 
#define ENUM_INIT_FUNC(func) func();
#define END_INIT_FUNC }

PRELOAD(MemoryPool, mPool);

BEGIN_INIT_FUNC
ENUM_INIT_FUNC(MemoryPool::makeMemoryPool);
END_INIT_FUNC