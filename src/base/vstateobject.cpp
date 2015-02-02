#include <VStateObject>

VStateObject::VStateObject(void* owner) : VObject(owner)
{
  m_state = VState::Closed;

}

VStateObject::~VStateObject()
{

}
