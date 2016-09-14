#include "core.hpp"

/* includes for preparation */

// #include "../???/???.hpp"
#include "../test/test.hpp"

// ===== Core =====

// --- CONSTRUCTORS ---

Core::Core
()
{
	Config::construct() ;
	
	// construct everything
	ld_ = LogDevice::get_instance() ;
	im_ = InstanceManager::get_instance() ;
	cp_ = CommandParser::get_instance() ;
	ps_ = ProjectStorage::get_instance() ;
	
	// preparation for type
	void * useless = nullptr ;
	
	// it is important to prepare the core for each OOF_OBJECT
	// prepare( static_cast< ??? * >( useless ) ) ;
	prepare( static_cast< Test * >( useless ) ) ;
}

// --- DESTRUCTORS ---

Core::~Core
()
{
	delete ps_ ;
	delete cp_ ;
	delete im_ ;
	
	/*
	 * because it is the last destructor called, maybe we need to save
	 * every logs before ending the process.
	 */
	ld_->save() ;
	delete ld_ ;
	
	Config::destroy() ;
}

// --- METHODS ---

void
Core::display_logs
()
const
{
	std::cout << *ld_ ;
}

void
Core::load
()
const
{
	ps_->load( "/users/dpf1/Desktop/Chut/Work/git/newOOF/oofobject_v4/projects/1469195975/1469195975.oof_proj" ) ;
}

/*
 * At the start, without preparation, there is no ObjectStorage nor SubCommandParser.
 * But, if your first choice is to use a command or to load an object, the
 * core will be unable to do it because it will not know what is the object.
 * 
 * It is important to make the preparation : it means create an ObjectStorage
 * and a SubCommandParser for each object implemented. It's the aim of this
 * method. Just by using the type of an useless pointer, it creates what is needed.
 */
template < class T >
void
Core::prepare
(
	T * useless
)
const
{
	ObjectStorage< T >::construct() ;
	SubCommandParser< T >::construct() ;
}

void
Core::save
()
const
{
	ps_->save() ;
}
