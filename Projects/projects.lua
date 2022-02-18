Projects = { 
	"PolyEngine",
    "Polygon"
}

function includeProject(projName) 
	includedirs ("%{wks.location}/Projects/" .. projName .. "/src")
end

group ""
    for k,v in pairs(Projects) do
        print("Including " .. v)
        include ("Projects/" .. tostring(v))
    end