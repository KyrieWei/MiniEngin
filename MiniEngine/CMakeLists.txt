set(ENGINE_ROOT_DIR "${MiniEgine_ROOT_DIR}/MiniEngine")
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/3rdParty")
set(ENGINE_ASSET_DIR "${ENGINE_ROOT_DIR}/Assets")

set(vulkan_include $(THIRD_PARTY_DIR)/vulkan)

if(WIN32)
    set(vulkan_lib $(THIRD_PARTY_DIR)/libs/vulkan-1.lib)
else()
endif()

add_subdirectory(Source/Runtime)
add_subdirectory(Source/Editor)

add_subdirectory(Source/MetaParser)

set(CODEGEN_TARGET "MiniEnginePreCompile")
include(Source/Precompile/Precompile.cmake)
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "Engine")

# add_dependencies(MiniEngineRuntime "${CODEGEN_TARGET}")
add_dependencies("${CODEGEN_TARGET}" "MiniEngineParser")