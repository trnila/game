#include "StreamLog.h"

void StreamLog::write(const char *message) {
	out << message;
}
