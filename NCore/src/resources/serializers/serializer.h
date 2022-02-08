#pragma once

#define SerializerRegistry CSerializerRegistry::_INSTANCE_()
class IResource;
class ISerializer {
public:
	virtual bool Serialize(void* out, std::string path) { return false; };
};

template<class T>
ISerializer* factory() {
	return new T;
}

typedef ISerializer* (*CSerializerFactory)();

class CSerializerRegistry {
public:
	std::unordered_map<std::string, std::unordered_map<std::string, CSerializerFactory >> m_serializers;

	typedef std::unordered_map<std::string, std::unordered_map<std::string, CSerializerFactory >>::iterator iterator;
	iterator begin() { return m_serializers.begin(); }
	iterator end() { return m_serializers.end(); }

	static CSerializerRegistry& _INSTANCE_();
	CSerializerFactory GetSerializer(std::string rt_name, std::string ext);
	void Add(std::string resourcetype_name, std::string extension, CSerializerFactory creator);

	bool HasExtension(std::string rt_name, std::string ext);
	size_t GetNumExtensions(std::string rt_name) { return m_serializers.count(rt_name); }
	std::vector<std::string> GetExtensionsFor(std::string rt_name);
};

class CSerializerRegistration {
public:
	CSerializerRegistration(std::string resourcetype_name, std::string extension, CSerializerFactory factory);
};

#define REGISTER_SERIALIZER(resourcetype_name,serializer_extension, serializer) \
    CSerializerRegistration _serializer_registration_ ## serializer(resourcetype_name, serializer_extension, &factory<serializer>);
