#include <vulkan/vulkan.hpp>
#include <glslang/SPIRV/GlslangToSpv.h>

class SpirvHelper
{
public:
	static void Init();
	static void Finalize();
	static void InitResources(TBuiltInResource &Resources);
	static EShLanguage FindLanguage(const vk::ShaderStageFlagBits shader_type);
	static bool GLSLtoSPV(const vk::ShaderStageFlagBits shader_type, const char *pshader, std::vector<unsigned int> &spirv);
};