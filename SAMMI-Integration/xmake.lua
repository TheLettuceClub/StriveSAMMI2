local projectname = "SAMMI-Integration"

target(projectname)
	add_rules("ue4ss.mod")
	add_includedirs(".")
	add_files("dllmain.cpp")
	add_files("arcsys.cpp")
	add_files("bbscript.cpp")
	add_files("bind_watcher.cpp")
	add_files("draw_utils.cpp")
	add_files("framebar.cpp")
	add_files("hitboxes.cpp")
	add_files("menu.cpp")
	add_files("sigscan.cpp")
	add_files("sammi.cpp")
