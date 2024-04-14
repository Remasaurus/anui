#pragma once

#include <concepts>
#include <cstdint>
#include <functional>
#include <optional>
#include <typeindex>
#include <utility>
#include <unordered_map>
#include <vector>


namespace anui {


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



template<>
struct std::hash<anui::group> {
	std::size_t operator()(const anui::group&) const noexcept;
};




namespace anui {



	class event_handler {
	public:
		static constexpr std::size_t default_group = -1;
		
		event_handler() = default;


		template<typename T>
		void send(T event) {
			auto func = get_bind<std::remove_cvref_t<T>>();
			if (func) {
				(*func)(event);
			}
		}

		void change_group(group group) {
			active_group = group;
		}


		//
		// Bind overloads
		//
		
		// bind methods
		template<typename T, typename U>
		void bind(void(U::*func)(T), U* this_pointer, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(std::bind(func, this_pointer, std::placeholders::_1), group);
		}

		template<typename T, typename U>
		void bind(void(U::*func)(T) const, U* this_pointer, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(std::bind(func, this_pointer, std::placeholders::_1), group);
		}

		// bind function pointers
		template<typename T>
		void bind(void(*func)(T), group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(func, group);
		}

		// bind anonymouse function
		template<typename Fn>
		void bind(Fn&& func, group group = default_group) {
			bind(&Fn::operator(), &func, group);
		}
		
		// bind any invocable
		template<typename T>
		void bind(std::invocable<void, T> auto&& func, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(func, group);
		}

		// bind a function variable
		template<typename T>
		void bind(std::function<void(T)>&& func, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(std::move(func, group));
		}

		// bind a function variable
		template<typename T>
		void bind(const std::function<void(T)>& func, group group = default_group) {
			set_bind<std::remove_cvref_t<T>>(func, group);
		}
		

	private:

		template<typename T>
		static auto& stored_bindings() {
			static std::vector<std::function<void(T)>> funcs;
			return funcs;
		}
		

		template<typename T>
		std::optional<std::reference_wrapper<std::function<void(T)>>>
			get_bind() {

			auto result = functions.find(std::make_pair(std::type_index(typeid(T)), active_group));

			if (result == functions.end()) 
				return std::nullopt;
			
			
			auto& funcs = stored_bindings<std::remove_cvref_t<T>>();
			return funcs[result->second];
		}

		template<typename T>
		void set_bind(const std::function<void(T)>& func, group group) {
			set_bind(std::function<void(T)>(func), group);
		}

		template<typename T>
		void set_bind(std::function<void(T)>&& func, group group) {
			auto& funcs = stored_bindings<T>();

			key key = std::make_pair(std::type_index(typeid(T)), active_group);
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
	};
	

	
	template<typename T>
	void send_all(T event) {
		auto& funcs = event_handler::stored_bindings<std::remove_cvref_t<T>>();
		for (auto& f :funcs) {
			f(event);
		}
	}

}



