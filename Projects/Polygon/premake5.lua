-- Our first project, the static library
project "Polygon"
	-- kind is used to indicate the type of this project.
	kind "ConsoleApp"

	-- We specify where the source files are.
	-- It would be better to separate header files in a folder and sources
	-- in another, but for our simple project we will put everything in the same place.
	-- Note: ** means recurse in subdirectories, so it will get all the files in ExampleLib/
	files {
        "src/**.cpp",
        "src/**.h",
    }

	-- We need GLFW, so we include it
	includeProject("PolyEngine")
    includeLibrary("GLFW")
    links {"GLFW", "PolyEngine"}