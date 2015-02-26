#pragma once

#include "HandlerBase.h"

bool HandlerBase::isTypeValid(int eType) {
	return (eType > BEGIN) && (eType < END);
}

HandlerBase* HandlerBase::find(int eType) {
	if (isTypeValid(eType) == false)
		return nullptr;
	return pHandlerMap[eType];
}

HandlerBase* HandlerBase::pHandlerMap[END];