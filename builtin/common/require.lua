local function wrapped_loadfile(filepath)
	local loader, err = loadfile(filepath)
	if not loader then
		return err
	end
	return loader
end

local function file_is_readable(filepath)
	local file = io.open(filepath, "r")
	if file then
		file:close()
		return true
	end
	return false
end

-- If mod security is disabled, our loader should be first in line.
table.insert(package.loaders, 1, function(path_str)
	local path = path_str:split(".")
	local modname = path[1]
	if package.loaded[modname] == nil then
		return "Mod " .. modname .. " not loaded. Depend on it in `mod.conf`."
	end

	local modpath = core.get_modpath(modname)
	if not modpath then
		return "Mod not found: " .. modname
	end

	local stem = modpath .. "/" .. table.concat(path, "/", 2)
	if file_is_readable(stem .. ".lua") then
		return wrapped_loadfile(stem .. ".lua")
	end
	return wrapped_loadfile(stem .. "/init.lua")
end)
