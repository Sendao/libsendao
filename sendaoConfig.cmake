add_library(sendao SHARED IMPORTED)
find_library(SENDAO_LIBRARY_PATH sendao HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(sendao PROPERTIES IMPORTED_LOCATION "${SENDAO_LIBRARY_PATH}")

