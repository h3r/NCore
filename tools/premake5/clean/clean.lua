-- Clean Function --
newaction {
    trigger     = "clean",
    description = "clean the software",
    execute     = function ()
       print("clean the build...")
       os.rmdir("./build")
       os.rmdir("./bin")
       os.remove{"**.ninja", "**.ninja_deps", "**.ninja_log"}
       os.remove{"**.sln", "**.vcxproj", "**.vcxproj.*"}
       os.remove{"CMakeLists.txt", "**.cmake" }
       print("done.")
    end
 }