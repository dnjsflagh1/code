//**************************************************************************************************
#ifndef _H_IANY_
#define _H_IANY_
//**************************************************************************************************

#include "MGEngineInterfacePreqs.h"
#include <typeinfo>
#include <algorithm>

//**************************************************************************************************
namespace MG
{
    class IAny
    {
    private:
        struct IAnyEmpty 
        { 
            IAnyEmpty(){};
        };

    public:
        static IAnyEmpty AnyNull;

    public:
        IAny() :
          mContent(NULL)
          {
          }

          template<typename ValueType> IAny(const ValueType& value) :
          mContent(new IHolder<ValueType>(value))
          {
          }

          IAny(const IAny::IAnyEmpty& value) :
          mContent(NULL)
          {
          }

          IAny(const IAny& other) :
          mContent(other.mContent ? other.mContent->clone() : NULL)
          {
          }

          ~IAny()
          {
              delete mContent;
          }

          IAny& swap(IAny& rhs)
          {
              std::swap(mContent, rhs.mContent);
              return *this;
          }

          template<typename ValueType> IAny& operator = (const ValueType& rhs)
          {
              IAny(rhs).swap(*this);
              return *this;
          }

          IAny& operator = (const IAny::IAnyEmpty& rhs)
          {
              delete mContent;
              mContent = NULL;
              return *this;
          }

          IAny& operator = (const IAny& rhs)
          {
              IAny(rhs).swap(*this);
              return *this;
          }

          bool empty() const
          {
              return !mContent;
          }

          const std::type_info& getType() const
          {
              return mContent ? mContent->getType() : typeid(void);
          }

          template<typename ValueType>
          ValueType * castType(bool _throw = true) const
          {
               return &static_cast<IAny::IHolder<ValueType> *>(this->mContent)->held;
          }

          void * castUnsafe() const
          {
              return mContent ? static_cast<IAny::IHolder<void *> *>(this->mContent)->held : NULL;
          }

    private:
        class IPlaceholder
        {
        public:
            virtual ~IPlaceholder() { }

        public:
            virtual const std::type_info& getType() const = 0;
            virtual IPlaceholder * clone() const = 0;

        };

        template<typename ValueType> class IHolder : public IPlaceholder
        {
        public:
            IHolder(const ValueType& value) :
              held(value)
              {
              }

        public:
            virtual const std::type_info& getType() const
            {
                return typeid(ValueType);
            }

            virtual IPlaceholder * clone() const
            {
                return new IHolder(held);
            }

        public:
            ValueType held;

        private:
            IHolder& operator=(const IHolder &);

        };


    private: // representation
        IPlaceholder * mContent;

    };
}
//**************************************************************************************************
#endif
//**************************************************************************************************