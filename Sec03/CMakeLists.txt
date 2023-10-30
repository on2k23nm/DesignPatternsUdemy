# Add your source files to the project
add_executable(test_s03 test.cpp)
add_executable(LifeWithoutBuilders LifeWithoutBuilders.cpp)
add_executable(ForceBuilders ForceBuilders.cpp)
add_executable(GroovyStyleBuilder GroovyStyleBuilder.cpp)



add_library(PersonBuilder.o OBJECT PersonBuilder.cpp)
add_library(Person.o OBJECT Person.cpp)
add_library(BuilderFacets.o OBJECT BuilderFacets.cpp)

# add_executable(BuilderFacets BuilderFacets.o)
# target_link_libraries(MyExecutable test_object)
