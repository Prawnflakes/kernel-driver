#pragma once

#define DebugMessage(x, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, x, __VA_ARGS__)