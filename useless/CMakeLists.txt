add_library(useless useless.cpp)

install(TARGETS useless DESTINATION lib)
install(FILES useless DESTINATION include)