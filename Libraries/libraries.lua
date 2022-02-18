Libraries = { 
	GLFW = "GLFW/include"
}

function includeLibrary(libName) 
	print("project including library: " .. libName)
	includedirs ("%{wks.location}/Libraries/" .. Libraries[libName])
end

group "Libraries"
	for k,v in pairs(Libraries) do
		include ("Libraries/" .. tostring(k))
	end