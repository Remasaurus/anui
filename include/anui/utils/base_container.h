#include <anui/core.h>
#include <concepts>
#include <utility>

ANUI_BEGIN
namespace utils
{

    template <typename Base>
    class base_container
    {
    public:
        // constructors
        template <std::convertible_to<Base> T>
        base_container(T &&arg)
            : mPtr(new T(std::forward<T>(arg))),
              mClone([](Base *other)
                     { return new T(other); }) {}

        base_container(base_container &&arg)
            : mPtr(arg.mPtr), mClone(arg.mClone) {}

        base_container(const base_container &arg)
            : mPtr(arg.mClone(arg.mPtr)), mClone(arg.mClone) {}

        ~base_container()
        {
            delete mPtr;
        }

        // operators
        Base *operator->() { return mPtr; }

        template <std::convertible_to<Base> T>
        base_container &operator=(T &&arg)
        {
            mPtr = new T(std::forward<T>(arg));
            mClone = [](Base *other)
            { return new T(other); };
            return *this;
        }
        base_container &operator=(base_container &&arg)
        {
            mPtr = arg.mPtr;
            mClone = arg.mClone;
            return *this;
        }

        base_container &operator=(const base_container &arg)
        {
            mPtr = arg.mClone(arg.mPtr);
            mClone = arg.mClone;
            return *this;
        }

        Base *data() { return mPtr; }

    private:
        Base *mPtr;
        Base *(*mClone)();
    };

} // utils
ANUI_END
