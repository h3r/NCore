
import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupVulkan import VulkanConfiguration as VulkanRequirements
os.chdir('./../../') # Change from devtools/scripts directory to root

VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

if platform.system() == "Windows":
		print("\nRunning premake...")
		subprocess.call([os.path.abspath("./tools/scripts/Win-GenProjects.bat"), "nopause"])

print("\nSetup completed!")

