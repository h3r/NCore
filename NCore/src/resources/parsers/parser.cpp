#include "ncpch.h"
#include "parser.h"

void CParserRegistry::Add(std::string resourcetype_name, std::string extension, CParserFactory creator) {
	m_parsers[resourcetype_name][extension] = creator;
}

CParserRegistry& CParserRegistry::_INSTANCE_() {
	static CParserRegistry instance;
	return instance;
}

CParserFactory CParserRegistry::GetParser(std::string rt_name, std::string ext) {
	nc_assert(m_parsers.count(rt_name), "There is no parser registered for that IResource.");
	nc_assert(m_parsers[rt_name].count(ext), "The IResource class '{}' has no parser registered for the '{}' extension.", rt_name, ext);
	return m_parsers[rt_name][ext];
}

CParserRegistration::CParserRegistration(std::string resourcetype_name, std::string extension, CParserFactory factory) {
	CParserRegistry::_INSTANCE_().Add(resourcetype_name, extension, factory);
}

bool CParserRegistry::HasExtension(std::string rt_name, std::string ext) {
	nc_assert(m_parsers.count(rt_name),"There is no parser registered for that IResource.");
	return m_parsers[rt_name].count(ext) != 0;
}

std::vector<std::string> CParserRegistry::GetExtensionsFor(std::string rt_name) {
	std::vector<std::string> keys;
	if (!m_parsers.count(rt_name))
		return keys;

	auto map = m_parsers[rt_name];
	for (auto it = map.begin(); it != map.end(); ++it)
		keys.push_back(it->first);
	return keys;
}
