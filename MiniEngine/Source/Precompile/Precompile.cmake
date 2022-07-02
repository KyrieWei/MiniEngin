set(PRECOMPILE_TOOLS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Bin")
set(MiniEngine_PRECOMPILE_PARAMS_IN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source/Precompile/Precompile.json.in")
set(MiniEngine_PRECOMPILE_PARAMS_PATH "${PRECOMPILE_TOOLS_PATH}/Precompile.json")
configure_file(${MiniEngine_PRECOMPILE_PARAMS_IN_PATH} ${MiniEngine_PRECOMPILE_PARAMS_PATH})

if(CMAKE_HOST_WIN32)
    set(PRECOMPILE_PRE_EXE)
    set(PRECOMPILE_PARSER ${PRECOMPILE_TOOLS_PATH}/MiniEngineParser.exe)
    set(sys_include "*")
endif()

set(PARSER_INPUT ${CMAKE_BINARY_DIR}/parser_header.h)

### BUILDING ===========================================================
set(PRECOMPILE_TARGET "MiniEnginePreCompile")

# Called first time when building target
add_custom_target(${PRECOMPILE_TARGET} ALL

COMMAND
    ${CMAKE_COMMAND} -E echo "*****************************************************"
COMMAND
    ${CMAKE_COMMAND} -E echo "***************** [Precompile] BEGIN "
COMMAND
    ${CMAKE_COMMAND} -E echo "*****************************************************"

COMMAND
    ${PRECOMPILE_PARSER} "${MiniEngine_PRECOMPILE_PARAMS_PATH}" "${PARSER_INPUT}" "${ENGINE_ROOT_DIR}/Source" ${sys_include} "MiniEngine" 0

COMMAND
    ${CMAKE_COMMAND} -E echo "+++ Precompile finished +++"

)