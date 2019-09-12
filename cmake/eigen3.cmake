macro(import_eigen)
## Eigen
if (NOT Eigen3_FOUND)
	if (UNIX)
		find_package (Eigen3 REQUIRED)
		include_directories(${EIGEN3_INCLUDE_DIR})
		message(${EIGEN3_INCLUDE_DIR})
	endif()
	if(WIN32)
		include_directories("$ENV{EIGEN_DIR}")
		message("Eigen3 directory : " "$ENV{EIGEN_DIR}")
	endif()
endif()
endmacro(import_eigen)