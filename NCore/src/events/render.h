#pragma once

#include "event.h"

namespace NC {
	namespace Renderer {
		struct NC_API Begin : public Event { DECLARE_EVENT(Begin,  EventCategoryApplication); };
		struct NC_API Submit: public Event { DECLARE_EVENT(Submit, EventCategoryApplication); 
			Submit( const Ref<VertexArray>&  _vertex_array) : m_vertex_array(_vertex_array){}
			Ref<VertexArray>  m_vertex_array;
		};
		struct NC_API End   : public Event { DECLARE_EVENT(End,    EventCategoryApplication); };
		struct NC_API Flush : public Event { DECLARE_EVENT(Flush,  EventCategoryApplication); };
	}
}