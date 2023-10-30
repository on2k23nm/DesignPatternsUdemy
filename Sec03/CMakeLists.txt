# Add your source files to the project
add_executable(test_s03 test.cpp)
add_executable(LifeWithoutBuilders LifeWithoutBuilders.cpp)
add_executable(ForceBuilders ForceBuilders.cpp)
add_executable(GroovyStyleBuilder GroovyStyleBuilder.cpp)

# List all your source files
set(SOURCE_FILES
    Person.cpp
    PersonBuilder.cpp
    #BuilderFacets.cpp
    # ... other source files ...
)

# Create an object library for the common code
add_library(Common OBJECT ${SOURCE_FILES})

# Create an executable for BuilderFacets and link it with the Common library
add_executable(BuilderFacets BuilderFacets.cpp)
target_link_libraries(BuilderFacets Common)