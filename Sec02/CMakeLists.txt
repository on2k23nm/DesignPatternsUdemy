# Add your source files to the project
add_executable(test test.cpp)
add_executable(SingleRespPrinciple SingleRespPrinciple.cpp)
add_executable(OpenClosedPrinciple OpenClosedPrinciple.cpp)
add_executable(LiskovSubstitutionPrinciple LiskovSubstitutionPrinciple.cpp)
add_executable(InterfaceSegregationPrinciple InterfaceSegregationPrinciple.cpp)
add_executable(DependencyInversionPrinciple DependencyInversionPrinciple.cpp)

# Link the pthread library to your executable
target_link_libraries(SingleRespPrinciple boost_system)


# get_target_property(PTHREAD_LIBRARIES LINK_LIBRARIES)
# message(STATUS "Pthread library in use: ${PTHREAD_LIBRARIES}")