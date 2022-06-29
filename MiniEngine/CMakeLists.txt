set(ENGINE_ROOT_DIR "${MiniEgine_ROOT_DIR}/MiniEngine")
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/3rdParty")
set(ENGINE_ASSET_DIR "${ENGINE_ROOT_DIR}/Assets")

set(CODEGEN_TARGET "MiniEnginePreCompile")
include(Source/Precompile/Precompile.cmake)
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "Engine")

add_dependencies(MiniEngineRuntime "${CODEGEN_TARGET}")