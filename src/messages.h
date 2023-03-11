#pragma once
//%u for decimal
//%x for hex
//%X for HEX
#define DebugMessage(x, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, x, __VA_ARGS__)