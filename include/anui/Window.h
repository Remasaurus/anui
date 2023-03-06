#pragma once
#include <anui/core.h>
#include <string>
#include <anui/Point.h>
#include <anui/Size.h>
#include <anui/events.h>
#include <typeindex>
#include <functional>
#include <string_view>
#include <anui/constraints.h>

ANUI_BEGIN

struct WindowProps {
	int x = USE_DEFAULTX;
	int y = USE_DEFAULTY;
	unsigned int width = USE_DEFAULT_WIDTH;
	unsigned int height = USE_DEFAULT_HEIGHT;
	std::wstring_view label;
};


template<typename Func, typename Event>
concept CallbackConcept = requires(Func f, Event e) {
	{ std::invoke(f, e) } -> std::same_as<typename Event::return_type>;
};


class WindowBase {
public:

	
	template<EventConcept T>
	using Function = std::function<typename T::return_type(T&)>;

	// You will only receive events from this mask
	// Other events will immediately be propogated
	void setEventMask(EventCategory mask) {
		m_EventMask = mask;
	}

	// These events won't be propogated or received
	void setIgnoreMask(EventCategory mask) {
		m_IgnoreMask = mask;
	}

	
	// 
	// Force native windows implement these functions
	// This class is a guarantee 
	// Native windows can add extra OS specific functions
	//

	void setLabel(std::wstring_view label) {
		m_Label = label;
		// sendEvent(LabelChanged);
	}

	std::wstring_view getLabel() const {
		return m_Label;
	}

	int getX() const { return m_Pos.x; }
	void setX(int x) { m_Pos.x = x; }
	int getY() const { return m_Pos.y; }
	void getY(int y) { m_Pos.y = y; }

	AnuiPoint getPos() const { return m_Pos; }
	void setPos(const AnuiPoint& point) { m_Pos = point; }
	void setPos(int x, int y) { m_Pos.x = x; m_Pos.y = y; }
	
	void move(const AnuiPoint& point) {
		m_Pos += point;
	}

	unsigned int getWidth() const { return m_Size.width; }
	void setWidth(unsigned int width) { m_Size.width = width; }
	unsigned int getHeight() const { return m_Size.height; }
	void getHeight(unsigned int height) { m_Size.height = height; }
	AnuiSize getSize() const { return m_Size; }
	void setSize(const AnuiSize& size) { m_Size = size; }
	void setSize(unsigned int width, unsigned int height) { m_Size.width = width; m_Size.height = height; }



	void show();
	void hide();
	bool isHidden();
	void close();



	template<EventConcept T>
	void bind(const CallbackConcept<T> auto& callback) {
		
		auto& callbacks = getAllCallbacksOfType<T>();
		m_CallbackIndex[typeid(T)] = callbacks.size();
		callbacks.emplace_back(callback);
		
	}
	

	template<EventConcept T>
	T::return_type sendEvent(T& event) {
		if (T::category & m_IgnoreMask)
			return typename T::return_type {};

		if (T::category & m_EventMask) {
			auto it = m_CallbackIndex.find(typeid(T));

			if (it != m_CallbackIndex.end()) {

				auto& func = getAllCallbacksOfType<T>()[it->second];
				return func(event);
			}
		}
		
		if (m_Parent) {
			return m_Parent->sendEvent<T>(event);
		}

		return typename T::return_type{};
	}

protected:
	WindowBase() = default;

private:
	std::wstring m_Label;

	EventCategory m_EventMask = EventCategory::Any;
	EventCategory m_IgnoreMask = EventCategory::None;


	template<EventConcept T>
	static std::vector<Function<T>>& getAllCallbacksOfType() {
		static std::vector<Function<T>> s_Callbacks;
		return s_Callbacks;
	}


	void onSizeChange() {
		//sendEvent();

		for (auto& child : m_Children) {
			child->onParentSizeChange();
		}
	}

	void onParentSizeChange() {

	}





	AnuiSize m_Size;
	constraints::IConstraint* m_X;
	constraints::IConstraint* m_Y;
	AnuiPoint m_Pos;
	constraints::IConstraint* m_Width;
	constraints::IConstraint* m_Height;

	std::unordered_map<std::type_index, int> m_CallbackIndex;
	std::vector<WindowBase*> m_Children;
	WindowBase* m_Parent;


	template<EventConcept T>
	friend void sendAll(T& event);
};

template<EventConcept T>
void sendAll(T& event) {

	for (auto&& callback : WindowBase::getAllCallbacksOfType<T>()) {
		callback(event);
	}
}


#include ANUI_PATH(Window)
ANUI_RENAME(NativeWindow, Window);


ANUI_END
