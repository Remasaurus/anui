#include <anui/event_handler.h>


std::size_t std::hash<anui::group>::operator()(const anui::group& group) const noexcept {
	return std::hash<std::size_t>()(group.id);
}

std::size_t anui::event_handler::key_hash::operator()(const key& key) const noexcept {
	return std::hash<std::type_index>()(key.first) ^
	       std::hash<group>()(key.second);
}


