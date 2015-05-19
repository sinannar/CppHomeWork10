/*
 *	...There are some tricks...
 * 
 *  TEMPORARY SECONDARY POINTER FOR INCREMENT PREFIX
 * 	
 * 	BUT ITS NOT USEFUL FOR INCREMENT POSTFIX;IN THIS CASE WE CATCH THE OBJECT that WE CREATE TEMPORARLY AND RELEASE IT
 * 	
 *  Also i copy this all auto_ptr class from the include directory
 * And also i think in this homework,we broke the rules of auto_ptr
 *  
 * !!!Should use new getter after both increment operator also after binaryplus operator for pointer arithmetic
 * get2 should be in use...
 *	
 * 	I have some trick on this program to have nonwarning or nonerror in this case i release object after postfix
 * incrementation and i normally should have one pointer but i am using two cause after prefix increment operator
 * i do not want to delete somewhere this is not mine
 * 
 * 	I didnt touch so much thing,cause its library header and i tought it works well as this way
 * I changed just what i need to change cause of the reason that i give before this sentence.
 * 
 */
#include <iostream>
#include <bits/c++config.h>
#include <debug/debug.h>
#include "091044005HW10P02.cpp"

using namespace std;

  /**
   *  A wrapper class to provide auto_ptr with reference semantics.
   *  For example, an auto_ptr can be assigned (or constructed from)
   *  the result of a function which returns an auto_ptr by value.
   *
   *  All the auto_ptr_ref stuff should happen behind the scenes.
   */
	template<typename _Tp1>
    struct auto_ptr_ref
    {
      _Tp1* _M_ptr;

      explicit
      auto_ptr_ref(_Tp1* __p): _M_ptr(__p) { }
    } _GLIBCXX_DEPRECATED_ATTR;


  /**
   *  @brief  A simple smart pointer providing strict ownership semantics.
   *
   *  The Standard says:
   *  <pre>
   *  An @c auto_ptr owns the object it holds a pointer to.  Copying
   *  an @c auto_ptr copies the pointer and transfers ownership to the
   *  destination.  If more than one @c auto_ptr owns the same object
   *  at the same time the behavior of the program is undefined.
   *
   *  The uses of @c auto_ptr include providing temporary
   *  exception-safety for dynamically allocated memory, passing
   *  ownership of dynamically allocated memory to a function, and
   *  returning dynamically allocated memory from a function.  @c
   *  auto_ptr does not meet the CopyConstructible and Assignable
   *  requirements for Standard Library <a
   *  href="tables.html#65">container</a> elements and thus
   *  instantiating a Standard Library container with an @c auto_ptr
   *  results in undefined behavior.
   *  </pre>
   *  Quoted from [20.4.5]/3.
   *
   *  Good examples of what can and cannot be done with auto_ptr can
   *  be found in the libstdc++ testsuite.
   *
   *  _GLIBCXX_RESOLVE_LIB_DEFECTS
   *  127.  auto_ptr<> conversion issues
   *  These resolutions have all been incorporated.
   */
	template<typename _Tp>
    class auto_ptr
    {
    private:
      _Tp* _M_ptr;
      _Tp* _M_ptr2;

    public:
      /// The pointed-to type.
      typedef _Tp element_type;

      /**
       *  @brief  An %auto_ptr is usually constructed from a raw pointer.
       *  @param  p  A pointer (defaults to NULL).
       *
       *  This object now @e owns the object pointed to by @a p.
       */
      explicit
      auto_ptr(element_type* __p = 0) throw() : _M_ptr(__p),_M_ptr2(__p) { }

      /**
       *  @brief  An %auto_ptr can be constructed from another %auto_ptr.
       *  @param  a  Another %auto_ptr of the same type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownership.
       */
      auto_ptr(auto_ptr& __a) throw() : _M_ptr(__a.release()),_M_ptr2(__a.release()) { }

      /**
       *  @brief  An %auto_ptr can be constructed from another %auto_ptr.
       *  @param  a  Another %auto_ptr of a different but related type.
       *
       *  A pointer-to-Tp1 must be convertible to a
       *  pointer-to-Tp/element_type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownership.
       */
      template<typename _Tp1>
        auto_ptr(auto_ptr<_Tp1>& __a) throw() : _M_ptr(__a.release()),_M_ptr2(__a.release()) { }

      /**
       *  @brief  %auto_ptr assignment operator.
       *  @param  a  Another %auto_ptr of the same type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownership.  The object that this one @e
       *  used to own and track has been deleted.
       */
      auto_ptr&
      operator=(auto_ptr& __a) throw()
      {
			reset(__a.release());
			return *this;
      }

      /**
       *  @brief  %auto_ptr assignment operator.
       *  @param  a  Another %auto_ptr of a different but related type.
       *
       *  A pointer-to-Tp1 must be convertible to a pointer-to-Tp/element_type.
       *
       *  This object now @e owns the object previously owned by @a a,
       *  which has given up ownership.  The object that this one @e
       *  used to own and track has been deleted.
       */
		template<typename _Tp1>
        auto_ptr&
        operator=(auto_ptr<_Tp1>& __a) throw()
        {
		  reset(__a.release());
		  return *this;
		}

      /**
       *  When the %auto_ptr goes out of scope, the object it owns is
       *  deleted.  If it no longer owns anything (i.e., @c get() is
       *  @c NULL), then this has no effect.
       *
       *  The C++ standard says there is supposed to be an empty throw
       *  specification here, but omitting it is standard conforming.  Its
       *  presence can be detected only if _Tp::~_Tp() throws, but this is
       *  prohibited.  [17.4.3.6]/2
       */
      ~auto_ptr() { delete _M_ptr; }

      /**
       *  @brief  Smart pointer dereferencing.
       *
       *  If this %auto_ptr no longer owns anything, then this
       *  operation will crash.  (For a smart pointer, "no longer owns
       *  anything" is the same as being a null pointer, and you know
       *  what happens when you dereference one of those...)
       */
      element_type&
      operator*() const throw(string)
      {
		  if(_M_ptr==NULL)
			throw "Null is here";		//if _M_Ptr is null,throw an exception as a string
		_GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
		return *_M_ptr;
      }

      /**
       *  @brief  Smart pointer dereferencing.
       *
       *  This returns the pointer itself, which the language then will
       *  automatically cause to be dereferenced.
       */
      element_type*
      operator->() const throw()
      {
		_GLIBCXX_DEBUG_ASSERT(_M_ptr != 0);
		return _M_ptr;
      }

	  /******************************************************************/
		//operator overloading
		//prefix increment
		auto_ptr&
		operator++()
		{
			_M_ptr2++;

			return *this;
		}
		
		auto_ptr&
		operator+(int increase)
		{
			_M_ptr2=_M_ptr2+increase;

			return *this;
		}

		//postfix increment
		auto_ptr
		operator++(int)
		{
			element_type* tmp=_M_ptr;
			auto_ptr<element_type> temp(tmp);
			_M_ptr2=1+_M_ptr2;
			return temp;
		}

		//Operator== and Operator!= overloading
		friend bool operator==(auto_ptr _Var_1,auto_ptr _Var_2)
		{
			if(_Var_1._M_ptr==_Var_2._M_ptr)
				return true;
			return false;
		}

		friend bool operator!=(auto_ptr _Var_1,auto_ptr _Var_2)
		{
			return !( operator==(_Var_1, _Var_2) );
		}

	  /******************************************************************/

      /**
       *  @brief  Bypassing the smart pointer.
       *  @return  The raw pointer being managed.
       *
       *  You can get a copy of the pointer that this object owns, for
       *  situations such as passing to a function which only accepts
       *  a raw pointer.
       *
       *  @note  This %auto_ptr still owns the memory.
       */
      element_type*
      get() const throw() { return _M_ptr; }

      element_type*
      get2() const throw() { return _M_ptr2; }

      /**
       *  @brief  Bypassing the smart pointer.
       *  @return  The raw pointer being managed.
       *
       *  You can get a copy of the pointer that this object owns, for
       *  situations such as passing to a function which only accepts
       *  a raw pointer.
       *
       *  @note  This %auto_ptr no longer owns the memory.  When this object
       *  goes out of scope, nothing will happen.
       */
      element_type*
      release() throw()
      {
		element_type* __tmp = _M_ptr;
		_M_ptr = 0;
		_M_ptr2 = 0;
		return __tmp;
      }

      /**
       *  @brief  Forcibly deletes the managed object.
       *  @param  p  A pointer (defaults to NULL).
       *
       *  This object now @e owns the object pointed to by @a p.  The
       *  previous object has been deleted.
       */
      void
      reset(element_type* __p = 0) throw()
      {
		if (__p != _M_ptr)
		  {
				delete _M_ptr;
				_M_ptr = __p;
				_M_ptr2 = __p;
		  }
      }

      /**
       *  @brief  Automatic conversions
       *
       *  These operations convert an %auto_ptr into and from an auto_ptr_ref
       *  automatically as needed.  This allows constructs such as
       *  @code
       *    auto_ptr<Derived>  func_returning_auto_ptr(.....);
       *    ...
       *    auto_ptr<Base> ptr = func_returning_auto_ptr(.....);
       *  @endcode
       */
      auto_ptr(auto_ptr_ref<element_type> __ref) throw()
      : _M_ptr(__ref._M_ptr),_M_ptr2(__ref._M_ptr) { }

      auto_ptr&
      operator=(auto_ptr_ref<element_type> __ref) throw()
      {
		if (__ref._M_ptr != this->get())
			{
			delete _M_ptr;
			_M_ptr = __ref._M_ptr;
			}
		return *this;
      }

      template<typename _Tp1>
      operator auto_ptr_ref<_Tp1>() throw()
        { return auto_ptr_ref<_Tp1>(this->release()); }

      template<typename _Tp1>
      operator auto_ptr<_Tp1>() throw()
        { return auto_ptr<_Tp1>(this->release()); }
    } _GLIBCXX_DEPRECATED_ATTR;

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 541. shared_ptr template assignment and void
  template<>
    class auto_ptr<void>
    {
    public:
      typedef void element_type;
    } _GLIBCXX_DEPRECATED_ATTR;

int main()
{

	Money *eee=new Money(1);	//money pointer and initializing
	int *a=new int[10];				//int   pointer and initializing
	for(int i=0;i<10;++i)			
	*(a+i)=i;						
	auto_ptr<Money> aaaddd(eee),tmmp;	//using auto_ptr with money

	auto_ptr<int> tp(a);			//using auto_ptr with int
	auto_ptr<int> tmp;				//using auto_ptr with int
	for(int i=0;i<10;++i)
	{
		++tp;						//using auto_ptr with int
	}
	aaaddd+2;						//increment	with number
	++aaaddd;						//increment prefix
	tmmp=aaaddd++;					//increment postfix
	tmmp.release();					//release the object cause if we didnt release,we are going to deletesomehere 
									//are not really  ours
									
	tp+14;							//increment with number
	tmp=tp++;						//increment postfix 
	tmp.release();					//release the object cause if we didnt release,we are going to deletesomehere 
									//are not really  ours

	
	cout<<"If you see just this five line after the compiling and execution program"<<endl;
	cout<<"There are no errors occur so program works like well but it is not exactly true"<<endl;
	cout<<"In this program,we try to implement some code to add auto_ptr"<<endl;
	cout<<"But this broke the behaviour of auto_ptr"<<endl;
	cout<<"Its the fifth line of program..."<<endl;


	return 0;
}
