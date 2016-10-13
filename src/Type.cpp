#include "Type.h"
#include <assimp/Importer.hpp>

struct Vertex;

template<> GLenum Type<float>::value = GL_FLOAT;
template<> GLenum Type<aiVector3t<float>>::value = GL_FLOAT;
template<> GLenum Type<Vertex>::value = GL_FLOAT;