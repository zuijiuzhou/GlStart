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

        bool operator==(const RefPtr &right)
        {
            return ptr_ == right.ptr_;
        }

        bool operator==(const T *right)
        {
            return ptr_ == right;
        }

        bool operator!=(const RefPtr &right)
        {
            return !(*this == right);
        }

        bool operator!=(const T *right)
        {
            return ptr_ != right;
        }

    private:
        template <typename TOther>
            // requires std::is_base_of<Object, TOther>::value
        friend class RefPtr;

    private:
        T *ptr_;
    };
}