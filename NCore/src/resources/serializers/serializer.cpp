#include "ncpch.h"
#include "serializer.h"

void CSerializerRegistry::Add(std::string resourcetype_name, std::string extension, CSerializerFactory creator) {
	m_serializers[resourcetype_name][extension] = creator;
}

CSerializerRegistry& CSerializerRegistry::_INSTANCE_() {
	static CSerializerRegistry instance;
	return instance;
}

CSerializerFactory CSerializerRegistry::GetSerializer(std::string rt_name, std::string ext) {
	nc_assert(m_serializers.count(rt_name),"There is no parser registered for that IResource.");
	nc_assert(m_serializers[rt_name].count(ext), "The IResource class '{}' has no serializer registered for the '{}' extension.", rt_name, ext);
	return m_serializers[rt_name][ext];
}

CSerializerRegistration::CSerializerRegistration(std::string resourcetype_name, std::string extension, CSerializerFactory factory) {
	CSerializerRegistry::_INSTANCE_().Add(resourcetype_name, extension, factory);
}

bool CSerializerRegistry::HasExtension(std::string rt_name, std::string ext) {
	nc_assert(m_serializers.count(rt_name),"There is no serializer registered for that IResource.");
	return m_serializers[rt_name].count(ext) != 0;
}

std::vector<std::string> CSerializerRegistry::GetExtensionsFor(std::string rt_name) {
	std::vector<std::string> keys;
	if (!m_serializers.count(rt_name))
		return keys;

	auto map = m_serializers[rt_name];
	for (auto it = map.begin(); it != map.end(); ++it)
		keys.push_back(it->first);
	return keys;
}
