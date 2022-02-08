#pragma once
#include "ncpch.h"
#include "resources/parsers/parser.h"

class CResourceType;

class IResource 
{
public:
	virtual ~IResource() {}
	virtual void Reflect() {}
	virtual void OnFileChanged(const std::string& filename) {}

	const std::string& GetName() const {
		return m_name;
	}

	const CResourceType* GetResourceType() const { 
		return m_resource_type; 
	}

	template< typename T>
	T* As() const 
	{
		nc_assert(m_resource_type);
		nc_assert(GetResourceTypeFor<T>());
		nc_assert(GetResourceTypeFor<T>() == m_resource_type,"You are trying to convert the resource '%s' of type '%s' to resource type '%s'", , GetName().c_str(), m_resource_type->GetName(), GetResourceTypeFor<T>()->GetName());
		return static_cast<T*>(const_cast<IResource*>(this));
	}

	void SetNameAndType(const std::string& _new_name, const CResourceType* _new_resource_type) {
		assert(!_new_name.empty());
		assert(_new_resource_type != nullptr);
		m_name = _new_name;
		m_resource_type = _new_resource_type;
	}

protected:
	std::string          m_name;
	const CResourceType* m_resource_type = nullptr;
};

class CResourceType {
public:
	virtual const char* GetName() const = 0;
	virtual IResource* Create(const std::string& name) const = 0;
protected:
	int m_num_extensions = 0;
};

// Forward declaration for a function that given a type will return a CResourceType
template< typename T >
const CResourceType* GetResourceTypeFor();

class CResourcesManager {
public:

	static CResourcesManager& _INSTANCE_() {
		static CResourcesManager Resources;
		return Resources;
	}

	void RegisterResource(IResource* new_resource) 
	{
		nc_assert(new_resource && !new_resource->GetName().empty(),"Attempting to register a malformed resource");
		std::string name = new_resource->GetName();
		CResourceType* rt = const_cast<CResourceType*>(new_resource->GetResourceType());
		m_all_resources[name] = new_resource;
	}

	void RegisterResourceType(const CResourceType* res_type) 
	{
		// assert is new!! and the handled extension is not handled by any other res type
		auto extensions = ParserRegistry.GetExtensionsFor(res_type->GetName());
		for (auto ext : extensions)
			nc_assert(FindResourceTypeByExtension(ext) == nullptr, "Resource type already registered!");
		m_resource_types.push_back(res_type);
	}

	void RemoveResource(IResource* _existing_resource) 
	{
		nc_assert(_existing_resource && !_existing_resource->GetName().empty(), "Attempting to remove nullish resource pointer");
		std::string name = _existing_resource->GetName();
		m_all_resources.erase(name);
		//This does not free the resource memory
	}

	void RemoveResourceByName(const std::string& _res_name) 
	{
		nc_assert(Exists(_res_name), "Resource does not exist on memory: {}", _res_name);
		m_all_resources.erase(_res_name);
	}

	void FreeAllResources() {
		// Delete all resources
		for (auto it : m_all_resources)
			delete it.second;

		m_all_resources.clear();
		m_resource_types.clear();
	}

	bool Exists(const std::string& _name) {
		return m_all_resources.find(_name) != m_all_resources.end();
	}

	void OnFileChanged(const std::string& filename) {
		for (auto it : m_all_resources) {
			if (!it.second)
				continue;
			it.second->OnFileChanged(filename);
		}
	}

	const IResource* Get(const std::string& name) {

		auto it = m_all_resources.find(name);
		if (it != m_all_resources.end())
			return it->second;

		// Identify the type
		auto resource_type = FindResourceType(name);
		nc_assert(resource_type, "Can't identify resource type {}", name);

		// Someone to load
		IResource* new_resource = resource_type->Create(name);
		nc_assert(new_resource, "Failed to create resource {} of type {}", name, resource_type->GetName());

		RegisterResource(new_resource);


		return new_resource;
	}

private:
	std::vector< const CResourceType* > m_resource_types;
	std::unordered_map< std::string, IResource* > m_all_resources;

	// name = data/meshes/car.mesh
	const CResourceType* FindResourceType(const std::string& _name) {
		nc_assert(!_name.empty(), "Resourcetype name cannot be empty");

		// Find extension
		auto idx = _name.find_last_of(".");
		nc_assert(idx != std::string::npos, "Can't find extension to identify resource in {}", _name);

		// ext = mesh
		std::string ext = _name.substr(idx);
		return FindResourceTypeByExtension(ext);
	}

	const CResourceType* FindResourceTypeByExtension(const std::string& ext) 
	{
		for (auto it : m_resource_types) 
		{
			auto name = it->GetName();
			size_t n = ParserRegistry.GetNumExtensions(name);
			if (ParserRegistry.HasExtension(name, ext))
				return it;
		}
		return nullptr;
	}

};
#define Resources CResourcesManager::_INSTANCE_()


/*
	Factory instance to be registered.
*/
template<class T>
class CResourceRegistration {
public:
	CResourceRegistration() {
		Resources.RegisterResourceType(GetResourceTypeFor<T>());
	}
};

#define REGISTER_RESOURCE(resource_type) \
    CResourceRegistration<resource_type> _resource_registration_ ## resource_type;
