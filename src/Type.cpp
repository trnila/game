#include "Type.h"

#include <assimp/Importer.hpp>

template<> GLenum Type<float>::value = GL_FLOAT;
template<> GLenum Type<aiVector3t<float>>::value = GL_FLOAT;