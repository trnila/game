#pragma once
#include "Shader.h"
#include "../Utils/Observer.h"
#include "../Scene/Camera.h"
#include "../Utils/Color.h"

class BaseLight;
class Texture;

class Program : public Observer<Camera>, public Observer<BaseLight> {
public:
	Program();
	void attach(Shader &shader);
	void link();
	void use();
	void send(const char* var, const glm::mat4 &mat);

	void setColor(float r, float g, float b);

	void send(const char *var, bool val);
	void setAmbientColor(const Color &color);

	void useTexture(const char *name, Texture &texture, int pos);

	virtual void updated(Camera &camera) override;
	virtual void updated(BaseLight &obj) override;

	void send(const char *name, const glm::vec3& vec);
	void send(const char *name, const glm::vec4& vec);
	void send(const char *name, float v);
	void send(const char *name, int value);
private:
	GLuint id;
	int activeLights = 0;

	int getUniformLocation(const char* name);
};
