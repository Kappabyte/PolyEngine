Projects = { 
	"PolyEngine"
}

function includeProject(projName) 
	includedirs (Projects[libName])
end

group ""
    for k,v in pairs(Projects) do
        print("Including " .. v)
        include ("Projects/" .. tostring(v))
    end