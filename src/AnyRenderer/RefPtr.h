#pragma once
#include <type_traits>
namespace AnyRenderer
{
    class Object;
    template <typename T>
    // requires std::is_base_of<Object, T>::value
    class RefPtr
    {
    public:
        RefPtr() : ptr_(nullptr)
        {
        }
        RefPtr(T *ptr) : ptr_(ptr)
        {
            if (ptr_)
            {
                ptr_->ref();
            }
        }
        RefPtr(const RefPtr &other) : ptr_(other.ptr_)
        {
            if (ptr_)
            {
                ptr_->ref();
            }
        }

        template <typename TOther>
        // requires std::is_base_of<Object, TOther>::value
        RefPtr(const RefPtr<TOther> &other) : ptr_(other.ptr_)
        {
            if (ptr_)
            {
                ptr_->ref();
            }
        }

        ~RefPtr()
        {
            if (ptr_)
            {
                ptr_->unref();
            }
        }

    public:
        T *get() const
        {
            return ptr_;
        }

        void set(T *ptr)
        {
            if (ptr == ptr_)
                return;
            if (ptr_)
                ptr_->unref();
            ptr_ = ptr;
            if (ptr_)
                ptr_->ref();
        }

        T *release()
        {
            auto temp = ptr_;
            if (ptr_)
                ptr_->unref(false);
            ptr_ = nullptr;
            return temp;
        }

        void swap(RefPtr &other)
        {
            std::swap(ptr_, other.ptr_);
        }

    public:
        bool operator!()
        {
            return !!ptr_;
        }

        T *operator->()
        {
            return ptr_;
        }

        T &operator*()
        {
            return *ptr_;
        }

        RefPtr &operator=(const RefPtr &right)
        {
            set(right.ptr_);
            return *this;
        }

        template <typename TOther>
        // requires std::is_base_of<T, TOther>::value
        RefPtr &operator=(const RefPtr<TOther> &right)
        {
            set(right.ptr_);
            return *this;
        }

        template <typename TOther>
        // requires std::is_base_of<T, TOther>::value
        RefPtr &operator=(TOther *ptr)
        {
            set(ptr);
            return *this;
        }

        bool operator==(const RefPtr &right) const
        {
            return ptr_ == right.ptr_;
        }

        bool operator==(const T *right) const
        {
            return ptr_ == right;
        }

        bool operator!=(const RefPtr &right) const
        {
            return !(*this == right);
        }

        bool operator!=(const T *right) const
        {
            return ptr_ != right;
        }

        bool valid() const
        {
            return ptr_ != nullptr;
        }

        bool operator<(const RefPtr<T> &right) const
        {
            return ptr_ < right.ptr_;
        }

        bool operator<(const T *right) const
        {
            return ptr_ < right;
        }

        bool operator>(const RefPtr<T> &right) const
        {
            return ptr_ > right.ptr_;
        }

        bool operator>(const T *right) const
        {
            return ptr_ > right;
        }

    private:
        template <typename TOther>
        // requires std::is_base_of<Object, TOther>::value
        friend class RefPtr;

    private:
        T *ptr_;
    };

    template <class T>
    inline void swap(RefPtr<T> &rp1, RefPtr<T> &rp2) { rp1.swap(rp2); }

    template <class T>
    inline T *get_pointer(const RefPtr<T> &rp) { return rp.get(); }

    template <class T, class Y>
    inline RefPtr<T> static_pointer_cast(const RefPtr<Y> &rp) { return static_cast<T *>(rp.get()); }

    template <class T, class Y>
    inline RefPtr<T> dynamic_pointer_cast(const RefPtr<Y> &rp) { return dynamic_cast<T *>(rp.get()); }

    template <class T, class Y>
    inline RefPtr<T> const_pointer_cast(const RefPtr<Y> &rp) { return const_cast<T *>(rp.get()); }
}