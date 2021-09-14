cmake_minimum_required(VERSION 2.6...3.0.2)

project(xbyak LANGUAGES CXX VERSION 6.00)

file(GLOB headers xbyak/*.h)

if (DEFINED CMAKE_VERSION AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.0.2)
	include(GNUInstallDirs)
	add_library(${PROJECT_NAME} INTERFACE)
	add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
	
	target_include_directories(
		${PROJECT_NAME} INTERFACE
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
	)

	install(
		TARGETS ${PROJECT_NAME}
		EXPORT ${PROJECT_NAME}-targets
		INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	)

	include(CMakePackageConfigHelpers)
	configure_package_config_file(
		cmake/config.cmake.in
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	)
	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
		COMPATIBILITY SameMajorVersion
	)

	install(
		FILES
			"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
			"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
		DESTINATION
			${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	)

	install(
		EXPORT ${PROJECT_NAME}-targets
		NAMESPACE ${PROJECT_NAME}::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	)
elseif(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
	set(CMAKE_INSTALL_INCLUDEDIR "include")
endif()

install(
	FILES ${headers}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xbyak
)
