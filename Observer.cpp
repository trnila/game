#include "Camera.h"
#include "Observer.h"


void Subject::notify() {
	for(Observer *observer: listeners) {
		observer->notify(reinterpret_cast<Camera&>(*this));
	}
}
