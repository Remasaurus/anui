#pragma once
/**
 * @file 	event_handler.h
 * @brief	Code related to the event_handler class
 * @author	Anui dev
 * @date 	2024-04-15
 */



#include <cstdint>
#include <functional>
#include <optional>
#include <typeindex>
#include <utility>
#include <unordered_map>
#include <vector>


namespace anui {

	
	/**
	 * @class group.
	 * @brief Group event_handler bindings together.
	 */
	class group {
	public:
		
		group(std::size_t id)
			: id(id) {}


		bool operator== (const group& rhs) const = default;

	private:
		std::int64_t id;

		friend class std::hash<anui::group>;
	};


} // namespace anui


// specialize the hash function
template<>
struct std::hash<anui::group> {
	std::size_t operator()(const anui::group&) const noexcept;
};




namespace anui {


	/**
	 * @class event_handler
	 *
	 * @brief class that can receive events and handle them
	 *
	 * Primarely used as a base class for function that want to
	 * receive events
	 *
	 */
	class event_handler {
	public:
		// Group that is used if no group is specified
		// in in the call to event_handler::bind
		static constexpr std::size_t default_group = -1;
		
		event_handler() = default;


		/**
		 * @brief Send an event to the event_handler.
		 * @warning There is no way to check if the event actually gets handled.
		 *
		 *
		 * @tparam T	The type of an event.
		 * @param event Event that has to be handled.
		 */
		template<typename T>
		void send(T event) {
			auto func = get_bind<T>();
			if (func) {
				(*func)(event);
			}
		}

		/**
		 * @brief Change what the active group.
		 * @param Group The new active group.
		 *
		 * @warning Make sure to call event_handler::bind with the right group.
		 *
		 * Can be used to easily change which functions handle
		 * events.
		 */
		void change_group(group group) {
			active_group = group;
		}


		//
		// Bind overloads
		//
	
		/**
		 * @brief Bind a event to a given member function.
		 *
		 * @tparam T Type of the event.
		 * @tparam U Type of class that the member function relates to.
		 *
		 * @param func 			The function that should be called.
		 * @param this_pointer	Pointer to the object that func should be called on.
		 * @param group 		Which group this binding should belong to.
		 */
		template<typename T, typename U>
		void bind(void(U::*func)(T), U* this_pointer, group group = default_group) {
			set_bind<T>(std::bind(func, this_pointer, std::placeholders::_1), group);
		}

		/**
		 * @brief Bind a event to a given const member function.
		 *
		 * @tparam T Type of the event.
		 * @tparam U Type of class that the member function relates to.
		 *
		 * @param func 			The function that should be called.
		 * @param this_pointer	Pointer to the object that func should be called on.
		 * @param group 		Which group this binding should belong to.
		 */
		template<typename T, typename U>
		void bind(void(U::*func)(T) const, U* this_pointer, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(std::bind(func, this_pointer, std::placeholders::_1), group);
		}

		/**
		 * @brief Bind a event to a given anonymouse function
		 *
		 * @tparam Fn Type of the anonymouse function.
		 *
		 * @param func 			The function that should be called.
		 * @param group 		Which group this binding should belong to.
		 */
		template<typename Fn>
		void bind(Fn&& func, group group = default_group) {
			set_bind(std::function(std::forward<Fn>(func)), group);
		}

	private:

		// A way to store all the function for a type
		template<typename T>
		static auto& stored_bindings() {
			static std::vector<std::function<void(T)>> funcs;
			return funcs;
		}
		

		// Get the bind if it exists
		template<typename T>
		std::optional<std::reference_wrapper<std::function<void(T)>>> get_bind() {
			using CleanT = std::remove_cvref_t<T>;
			auto result = functions.find(
				std::make_pair(
					std::type_index(typeid(CleanT)),
					active_group
				)
			);


			if (result == functions.end()) 
				return std::nullopt;
			
			
			auto& funcs = stored_bindings<CleanT>();
			return funcs[result->second];
		}

		// Implementation for bind
		template<typename T>
		void set_bind(std::function<void(T)>&& func, group group) {
			using CleanT = std::remove_cvref_t<T>;
			auto& funcs = stored_bindings<CleanT>();

			key key = std::make_pair(std::type_index(typeid(CleanT)), active_group);
			auto result = functions.find(key);
	

			// checks if result did not find the key
			if (result == functions.end()) {
				// Binding does not yet exist!

				// Size will be the index of the next
				// element we push back
				functions[key] = funcs.size();
				funcs.push_back(std::move(func));
			} else {
				// Binding exists we just have to override it

				// result->second is the index of the previous function
				// and now we override it
				funcs[result->second] = std::move(func);
			}
		}

	

		// hashmap
		using key = std::pair<std::type_index, group>;
		struct key_hash {
			std::size_t operator()(const key&) const noexcept;
		};

		using map = std::unordered_map<key, std::size_t, key_hash>;
		
		// Data members
		group active_group = default_group;
		map functions;



		// Friend classes
		template<typename T>
		friend void send_all(T);

		friend std::hash<anui::group>;
	}; // class event_handler
	

	/**
	 * @brief send an event to all event_handlers
	 *
	 * @tparam T	Type of the given event
	 * @param event Event that will be sent
	 */
	template<typename T>
	void send_all(T event) {
		auto& funcs = event_handler::stored_bindings<std::remove_cvref_t<T>>();
		for (auto& f :funcs) {
			f(event);
		}
	}


} // namespace anui



