#pragma once

#include <vcruntime_internal.h>

#define __pSETranslator (RENAME_BASE_PTD(__vcrt_getptd)()->_translator)
