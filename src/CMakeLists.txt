file(GLOB SOURCES "**/*.cpp")
target_sources(app PRIVATE src/aquasense.cpp ${SOURCES})
target_sources(asopen PRIVATE src/objects.cpp ${SOURCES})