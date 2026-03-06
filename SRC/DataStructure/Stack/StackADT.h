template <class type>
class StackADT
{
	public:
		virtual void initializeStack() = 0;
		
		virtual bool isStackEmpty() const = 0;
		
		virtual bool isStackFull() const = 0;
		
		virtual void push( const type &newItem ) = 0;
		
		virtual type top() const = 0;
		
		virtual void pop() = 0;
};