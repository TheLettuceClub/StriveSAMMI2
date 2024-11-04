local projectname = "SAMMI-Integration"

target(projectname)
	add_rules("ue4ss.mod")
	add_includedirs(".")
	add_files("dllmain.cpp")
