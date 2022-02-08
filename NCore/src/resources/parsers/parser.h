#pragma once

#define ParserRegistry CParserRegistry::_INSTANCE_()
class IResource;
class IParser {
public:
	virtual bool Parse(void* out, std::string path) { return false; };
};

template<class T>
IParser* factory() {
	return new T;
}

typedef IParser* (*CParserFactory)();

class CParserRegistry {
public:
	std::unordered_map<std::string, std::unordered_map<std::string, CParserFactory >> m_parsers;

	typedef std::unordered_map<std::string, std::unordered_map<std::string, CParserFactory >>::iterator iterator;
	iterator begin() { return m_parsers.begin(); }
	iterator end() { return m_parsers.end(); }

	static CParserRegistry& _INSTANCE_();
	CParserFactory GetParser(std::string rt_name, std::string ext);
	void Add(std::string resourcetype_name, std::string extension, CParserFactory creator);

	bool HasExtension(std::string rt_name, std::string ext);
	size_t GetNumExtensions(std::string rt_name) { return m_parsers.count(rt_name); }
	std::vector<std::string> GetExtensionsFor(std::string rt_name);
};

class CParserRegistration {
public:
	CParserRegistration(std::string resourcetype_name, std::string extension, CParserFactory factory);
};

#define REGISTER_PARSER(resourcetype_name,parser_extension, parser) \
    CParserRegistration _parser_registration_ ## parser(resourcetype_name, parser_extension, &factory<parser>);
