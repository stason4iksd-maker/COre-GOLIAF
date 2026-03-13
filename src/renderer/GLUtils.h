#pragma once
#include <string>

namespace goliaf::renderer {

bool CheckShader(unsigned int shader, const std::string& type);
bool CheckProgram(unsigned int program);

}
