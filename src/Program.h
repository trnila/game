#pragma once
#include "Shader.h"
#include "Observer.h"
#include "Camera.h"
#include "Color.h"

class Light;
class Texture;

class Program : public Observer<Camera>, public Observer<Light> {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	void setMatrix(const char* var, const glm::mat4 &mat);

	void setColor(float r, float g, float b);
	void setLight(glm::vec3 position);
	void setBool(const char *var, bool val);
	void setAmbientColor(const Color &color);

	void useTexture(const char *name, Texture &texture, int pos);

	virtual void updated(Camera &camera) override;
	virtual void updated(Light &obj) override;

	void sendVector(const char *name, const glm::vec3& vec);
	void sendFloat(const char *name, float v);
private:
	GLuint id;
};
