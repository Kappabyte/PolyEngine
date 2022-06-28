Libraries = { 
	GLFW = "GLFW/include",
	Glad = "Glad/include",
	glm = "glm/glm"
}

function includeLibrary(libName) 
	print("project including library: " .. libName)
	includedirs ("%{wks.location}/Libraries/" .. Libraries[libName])
end

group "Libraries"
	for k,v in pairs(Libraries) do
		include ("Libraries/" .. tostring(k) .. ".lua")
	end